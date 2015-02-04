#include "espmissingincludes.h"
#include "c_types.h"
#include "user_interface.h"
#include "espconn.h"
#include "mem.h"
#include "osapi.h"
#include "ip_addr.h"
#include "io.h"
#include "tempd.h"
#include "ds18b20.h"



/*
 * ----------------------------------------------------------------------------
 * "THE MODIFIED BEER-WARE LICENSE" (Revision 42):
 * Mathew Hall wrote this file. As long as you
 * retain
 * this notice you can do whatever you want with this stuff. If we meet some
 * day,
 * and you think this stuff is worth it, you can buy sprite_tm a beer in return.
 * ----------------------------------------------------------------------------
 */

static struct espconn tempConn;
static struct _esp_udp socket;
static ip_addr_t master_addr;

#define DATA_PORT 19252
#define DATA_HOST "campi"
#define FALLBACK_IP 192,168,1,16

static ETSTimer broadcastTimer;
static ETSTimer lookupTimer;

static void transmitReading(struct sensor_reading* result){
    char buf[256];
    os_sprintf(buf,"%d.%d", (int)(result->temperature),(int)((result->temperature - (int)result->temperature)*100));
    espconn_sent(&tempConn, (uint8*)buf, os_strlen(buf));
}

static void broadcastReading(void* arg){

    os_printf("Sending heartbeat\n");
    struct sensor_reading* result = readDS18B20();

    transmitReading(result);
    
}

static void dnsLookupCb(const char *name, ip_addr_t *ipaddr, void *arg){
    struct espconn* conn = arg;
    ip_addr_t broadcast;
    if(ipaddr == NULL){
        os_printf("Logger: couldn't resolve IP address for %s; will broadcast instead\n", name);
//        return;

        
        broadcast.addr = (uint32)0xC0A8010A;
        IP4_ADDR(&broadcast, 192,168,1,16);
        os_printf("Falling back on %x for logging\n",broadcast.addr);
        ipaddr = &broadcast;
    }
    
    os_printf("Successfully resolved %s as %x\n", name, ipaddr->addr);
    
    if(master_addr.addr == 0 && ipaddr->addr != 0){
        master_addr.addr = ipaddr->addr;
        os_memcpy(conn->proto.udp->remote_ip, &ipaddr->addr, 4);
        os_printf("Will send to %d.%d.%d.%d\n", (int)conn->proto.udp->remote_ip[0], (int)conn->proto.udp->remote_ip[1], (int)conn->proto.udp->remote_ip[2], (int)conn->proto.udp->remote_ip[3]);
        conn->proto.udp->local_port = espconn_port();
    }
    
    espconn_create(conn);

    os_printf("Arming broadcast timer\n");
    os_timer_arm(&broadcastTimer, 300000, 1);
}
    
static void lookupTask(void* arg){
    os_sprintf("Attempting to resolve %s\n", DATA_HOST);
    espconn_gethostbyname(&tempConn, DATA_HOST, &master_addr, dnsLookupCb);
    os_timer_disarm(&lookupTimer);
}

void tempdInit(void){
    os_printf("Temperature logging initialising\n");
	tempConn.type=ESPCONN_UDP;
	tempConn.state=ESPCONN_NONE;
	tempConn.proto.udp=&socket;

    readDS18B20();
        
        master_addr.addr = 0;
        socket.remote_port=DATA_PORT;
        os_timer_setfn(&lookupTimer, lookupTask, NULL);
        os_timer_arm(&lookupTimer, 10000, 1);
    
        os_timer_setfn(&broadcastTimer, broadcastReading, NULL);
}

