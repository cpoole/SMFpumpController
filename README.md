SMFpumpController
=================

Sustainable Microfarms Pump controller

* Boards can be assembled using the BOM and the Eagle schematic files. 
* Eagle can be downloaded for free at http://www.cadsoftusa.com/download-eagle/
* main.c is very plain and simple, it simply turns on LEDs and the pump
* the buttons still need to be debounced in software, hopefully I'll get that done shortly, if not a simple tutorial can be followed here https://www.newbiehack.com/ButtonorSwitchDebounceinSoftware.aspx 

PROGRAMMING

* follow this tutorial to setup the software http://www.ladyada.net/learn/avr/index.html
* once AVR dude is working you can program the boards with the provided makefile
* if you are using the usbtiny ISP you will need to change line 3 of the make file to reflect that
* 1st: run sudo make flash
* 2nd: run make to verify the program compiles
* 3rd: run sudo make flash to program the boards

-best of luck, Connor 

