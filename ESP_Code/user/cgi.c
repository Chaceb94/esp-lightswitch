/*
Some random cgi routines.
*/

/*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * Jeroen Domburg <jeroen@spritesmods.com> wrote this file. As long as you retain 
 * this notice you can do whatever you want with this stuff. If we meet some day, 
 * and you think this stuff is worth it, you can buy me a beer in return. 
 * ----------------------------------------------------------------------------
 */


#include <string.h>
#include <osapi.h>
#include "user_interface.h"
#include "mem.h"
#include "httpd.h"
#include "cgi.h"
#include "io.h"
#include "ds18b20.h"
#include "espmissingincludes.h"

//cause I can't be bothered to write an ioGetLed()
static char currLedState=0;

//Cgi that turns the LED on or off according to the 'led' param in the GET data
int ICACHE_FLASH_ATTR cgiLed(HttpdConnData *connData) {
	//int len;
    char len;
	char buff[1024];
	
	if (connData->conn==NULL) {
		//Connection aborted. Clean up.
		return HTTPD_CGI_DONE;
	}

	len=httpdFindArg(connData->getArgs, "led", buff, sizeof(buff));
	if (len!=0) {
        if (len==2) {
            currLedState = 0;
        }
        if (len==3) {
            currLedState = 1;
        }
        
		//currLedState=atoi(buff);
		ioLed(currLedState);
	}

	httpdRedirect(connData, "index.html");
	return HTTPD_CGI_DONE;
}



//Template code for the led page.
void ICACHE_FLASH_ATTR tplLed(HttpdConnData *connData, char *token, void **arg) {
	char buff[128];
	if (token==NULL) return;

	os_strcpy(buff, "");
	if (os_strcmp(token, "ledstate")==0) {
		if (currLedState) {
			os_strcpy(buff, "on");
		} else {
			os_strcpy(buff, "off");
		}
	}

	struct sensor_reading* r = readDS18B20();
	float lastTemp=r->temperature;
	
    if(os_strcmp(token, "temperature") == 0){
        if(r->success){
            os_sprintf(buff,"%d.%d", (int)(lastTemp),(int)((lastTemp - (int)lastTemp)*100));
        }else{
            os_sprintf(buff, "NA");
        }
    }

	espconn_sent(connData->conn, (uint8 *)buff, os_strlen(buff));
}
