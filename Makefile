MCU = atmega328p
F_CPU = 16000000UL
CFLAGS = -Os -DF_CPU=$(F_CPU) -mmcu=$(MCU)
SRC = main.c src/peripherals/joystick.c src/peripherals/sound.c src/utils.c src/peripherals/shift_register.c
OBJ = $(SRC:.c=.o)

default: all

all: compile dump burn

compile: $(OBJ)
	avr-gcc -mmcu=$(MCU) $(OBJ) -o app

dump:
	avr-objcopy -O ihex -R .eeprom app app.hex

burn:
	avrdude -F -V -c arduino -p $(MCU) -P /dev/ttyACM0 -b 115200 -U flash:w:app.hex

%.o: %.c
	avr-gcc $(CFLAGS) -c -o $@ $<