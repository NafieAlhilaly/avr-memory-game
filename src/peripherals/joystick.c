#include "joystick.h"

void init_adc()
{
    // Set reference voltage to AVcc
    ADMUX = (1 << REFS0);

    // Enable ADC, set prescaler to 128 (16MHz/128 = 125kHz)
    ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
}

uint16_t read_adc(uint8_t *input_channel)
{
    // Select ADC channel with safety mask
    ADMUX = (ADMUX & 0xF8) | (*input_channel & 0x07);

    // Start single conversion
    ADCSRA |= (1 << ADSC);

    // Wait for conversion to complete
    while (ADCSRA & (1 << ADSC))
        ;

    return ADC;
}

void js_btn_init(struct JoyStickButton *button)
{
    DDRB &= ~(1 << button->ddr);  // set JOYSTICK_BTN_PORT as input
    PORTB |= (1 << button->port); // enable pull-up
};
uint8_t js_btn_state(struct JoyStickButton *button)
{
    return PINB & (1 << button->pin);
}