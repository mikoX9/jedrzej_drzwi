
progrm: a 
	sudo avrdude -F -V -c usbasp -p ATmega328P -P usb -U flash:w:main.hex


a: b
	avr-objcopy -O ihex -R .eeprom main main.hex
b: c
	avr-gcc -w -mmcu=atmega328p main.o -o main
c:
	avr-gcc -w -Os -DF_CPU=8000000UL -mmcu=atmega328p -c -o main.o main.c


clean:
	rm *.o *.hex