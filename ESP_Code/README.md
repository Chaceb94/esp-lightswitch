I'm not going to tell you how to compile it. I'm not trying to be mean I just
don't know which toolchain you used. I used esp-open-sdk version 0.9.5 and it
works except I had to use the c_types.h.orig file instead of the newer one.
If you have troubles take a look at README.Sprite_tm and that should help.

anyway you can configure the broadcast ip and port and the poll rate for the
sensor under 'tempd.c' and ds18b20.c'. Debugging info can be found by monitoring
minicom or another serial terminal.

To flash run:

$ make
$ make flash
$ make htmlflash

Then you can either navigate to your ESP's ip on your network or connect to it
directly wia wifi and navigate to 192.168.4.1/wifi.html to connect to your
network.
