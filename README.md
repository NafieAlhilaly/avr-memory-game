## Memory Game Using an AVR Microcontroller

This project involves creating a memory game utilizing an AVR microcontroller. The code is compiled using `avr-gcc`, `objdump`, and `avrdude` to flash the code onto the microcontroller.

### Peripherals
- 10 LEDs, divided into two groups
- 4 Shift Registers (model: 74HC595)
- 2 Joysticks
- 1 Buzzer
- 1 4-Digit 7-Segment Display

### Connecting Peripherals
- The LEDs are connected to the microcontroller via 2 Shift Registers (model: 74HC595) linked in series, allowing control over more than 8 LEDs using a single Shift Register.
- The 4-digit 7-Segment Display is also connected through 2 Shift Registers (model: 74HC595) in series to manage all 4 digits and 7 segments.
- The Joysticks connect to the microcontroller using 2 ADC channels to read the X and Y axes of the joysticks.
- The Buzzer is connected to the microcontroller via a PWM channel to produce sound.

### Interfacing with the Peripherals
Functions and header files located in `src/peripherals/` provide definitions and structures that facilitate interaction with the peripherals.

### Game Description
The game begins with a sequence of LEDs blinking in a random order, which the player must memorize. 

After the sequence finishes, players will take control of the LEDs, starting with one illuminated LED. Players can navigate the LEDs left and right using the joystick, and they confirm their choice by pressing the joystick. Each player has a limited number of chances, which decreases each time they confirm a position. When all players have used all thier tires, the player who correctly remembers the sequence will earn points.

The game ends when the timer reaches zero.