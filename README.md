# ESP8266-based DHT11 (and 22) logger

This application builds on [Martin's DHT22 webserver](http://harizanov.com/2014/11/esp8266-powered-web-server-led-control-dht22-temperaturehumidity-sensor-reading/) implementation, which uses [sprite_tm's ESP8266 httpd](http://www.esp8266.com/viewtopic.php?f=6&t=376).

This version adds a check to make sure a DHT sensor is connected, and prevents the sensor being polled past the manufacturer's maximum frequency. It also logs sensor readings to a remote machine over the network as JSON, sent over UDP.

In addition to a DHT sensor, a DS18B20 1wire temperature sensor can be attached to port 0. If there's one attached, readings will be sent to the logging server and shown in the dht22.tpl page on the webserver.

# Configuration

There are a few parameters that can be changed:
 * user/user_main.c: sensor type (DHT11 or DHT22) and poll rate
 * tempd.c: hostname and UDP port to send readings, poll rate for readings
 
# Building

Make sure the IoT SDK and toolchain are set up according to the instructions on the [ESP8266 wiki](https://github.com/esp8266/esp8266-wiki/wiki/Toolchain). The makefile in this project relies on some environment variables that need to be set. It should be enough to add these to your `.profile`:

	PATH="/opt/Espressif/crosstool-NG/builds/xtensa-lx106-elf/bin/:$PATH"
	export SDK_BASE="/opt/Espressif/ESP8266_SDK"
	export XTENSA_TOOLS_ROOT="/opt/Espressif/crosstool-NG/builds/xtensa-lx106-elf/bin/"
	export ESPTOOL="/opt/Espressif/esptool-py/esptool.py"

From the root of this repository, run `make`. This will build the two firmware images. To update the webserver's HTML files, run `make webpages.espfs`.

# Licenses

This code is entirely based on [Sprite_tm](http://www.esp8266.com/viewtopic.php?f=6&t=376)'s httpd implementation for the ESP8266, licensed under the Beer-ware license. See the license headers in the `user` directory for the full text of the license.

The webserver uses Scott Vokes's [heatshrink](https://github.com/atomicobject/heatshrink) library. See the LICENSE file in `lib/heatshrink` for the full text of the license.

The DHT code is based on [Martin's DHT22 cgi script](http://harizanov.com/2014/11/esp8266-powered-web-server-led-control-dht22-temperaturehumidity-sensor-reading/). The revised DHT driver itself is based on the implementation from Adafruit Industries. See the comment in dht.c for the full text of the license. 

The temperature logger is licensed under a modified Beer-wrare license. See the header for `tempd.c` for details.