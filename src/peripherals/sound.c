#include "sound.h"
#include <avr/io.h>
#include <util/delay.h>

void init_sound(uint8_t *ddr, uint8_t port)
{
    *ddr |= (1 << port);
}

void play(uint16_t tone)
{
    // Set Timer1, mode CTC, toggle on compare, prescale 8
    TCCR1A = (1 << COM1A0);
    TCCR1B = (1 << WGM12) | (1 << CS10);

    // play A4 for 0.5 sec
    OCR1A = tone;
    _delay_ms(250);

    // Reset
    TCCR1A = 0;
    TCCR1B = 0;
    OCR1A = 0;
}