
/*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * Jeroen Domburg <jeroen@spritesmods.com> wrote this file. As long as you retain 
 * this notice you can do whatever you want with this stuff. If we meet some day, 
 * and you think this stuff is worth it, you can buy me a beer in return. 
 * ----------------------------------------------------------------------------
 */

#include "ets_sys.h"
#include "osapi.h"
#include "espmissingincludes.h"
#include "c_types.h"
#include "user_interface.h"
#include "espconn.h"
#include "mem.h"
#include "gpio.h"

#define LEDGPIO 0

void ICACHE_FLASH_ATTR ioLed(int ena) {
	//gpio_output_set is overkill. ToDo: use better mactos
	if (ena) {
        gpio_output_set((1<<LEDGPIO), 0, (1<<LEDGPIO), 0); //on
	} else {
		gpio_output_set(0, (1<<LEDGPIO), (1<<LEDGPIO), 0); //off
	}
}

void ioInit() {
	//Set GPIO0 to output mode for LED
	PIN_FUNC_SELECT(PERIPHS_IO_MUX_GPIO0_U, FUNC_GPIO0);	
}
