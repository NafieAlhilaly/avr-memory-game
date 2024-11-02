#include "src/peripherals/joystick.h"
#include "src/peripherals/sound.h"
#include "src/utils.h"
#include "src/peripherals/display.h"
#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>

#define PATTERN_SIZE 5

int main()
{
    uint8_t state = 0;

    struct ShiftRegister leds_sr = {0x0000, PORTB0, PORTB2, PORTB3};
    struct ShiftRegister display_sr = {0xFF01, PORTD5, PORTD6, PORTD7};
    struct ShiftRegisterController leds_sr_controller1 = {&leds_sr, 0, 0, 5};

    struct JoyStick joy_stick1 = {0};
    struct JoyStickButton js_btn1 = {&joy_stick1, PINB4, PORTB4, DDB4};

    struct ShiftRegisterController leds_sr_controller2 = {&leds_sr, 1, 0, 5};
    struct JoyStick joy_stick2 = {1};
    struct JoyStickButton js_btn2 = {&joy_stick2, PINB5, PORTB5, DDB5};

    uint8_t player1_pattern[PATTERN_SIZE] = {0};
    uint8_t player2_pattern[PATTERN_SIZE] = {0};

    init_sr(&leds_sr, &DDRB);

    init_adc();
    js_btn_init(&js_btn1);
    js_btn_init(&js_btn2);
    init_sound(&DDRB, PORTB1);

    uint8_t patterns1[] = {16, 8, 4, 2, 1};
    uint8_t patterns2[] = {1, 2, 4, 8, 16};
    uint8_t retries1 = 6;
    uint8_t retries2 = 6;

    while (1)
    {

        switch (state)
        {
        case 0:
            // Setup the next pattern
            retries1 = 6;
            retries2 = 6;
            leds_sr_controller1.shift_register->data = 0x0000;
            shift_register_out(&leds_sr, &PORTB);
            latch(&leds_sr, &PORTB);
            _delay_ms(1000);
            uint8_t next_pattern1[PATTERN_SIZE];
            uint8_t next_pattern2[PATTERN_SIZE];
            uint8_t *shuffled1 = shuffle_array(patterns1, PATTERN_SIZE);
            uint8_t *shuffled2 = shuffle_array(patterns2, PATTERN_SIZE);
            for (int i = 0; i < PATTERN_SIZE; i++)
            {
                next_pattern1[i] = shuffled1[i];
                next_pattern2[i] = shuffled2[i];
            }
            for (int i = 0; i < PATTERN_SIZE; i++)
            {
                player1_pattern[i] = next_pattern1[i];
                player2_pattern[i] = next_pattern2[i];
                leds_sr_controller2.shift_register->data = (next_pattern2[i] << 8) | next_pattern1[i];
                shift_register_out(&leds_sr, &PORTB);
                latch(&leds_sr, &PORTB);
                leds_sr_controller2.shift_register->data = 0;
                _delay_ms(1000);
            }
            leds_sr_controller1.shift_register->data = 0x000;
            shift_register_out(&leds_sr, &PORTB);
            latch(&leds_sr, &PORTB);
            _delay_ms(800);

            leds_sr_controller1.shift_register->data = 0x0101;
            shift_register_out(&leds_sr, &PORTB);
            latch(&leds_sr, &PORTB);
            _delay_ms(1000);

            state = 1;
            break;
        case 1:
            // Game loop
            while ((retries1 + retries2) > 0)
            {
                if (retries1 <= 0)
                {
                    leds_sr.data |= 0x00FF;
                    shift_register_out(&leds_sr, &PORTB);
                    latch(&leds_sr, &PORTB);
                }
                if (retries2 <= 0)
                {
                    leds_sr.data |= 0xFF00;
                    shift_register_out(&leds_sr, &PORTB);
                    latch(&leds_sr, &PORTB);
                }
                if (!js_btn_state(&js_btn1))
                {
                    play(D6);
                    retries1--;
                }
                if (!js_btn_state(&js_btn2))
                {
                    play(A4);
                    retries2--;
                }
                uint16_t x = read_adc(&joy_stick1.input_channel);
                if (x >= 800)
                {
                    shift_left(&leds_sr_controller1);
                }
                if (x <= 200)
                {
                    shift_right(&leds_sr_controller1);
                }
                uint16_t y = read_adc(&joy_stick2.input_channel);
                if (y >= 800)
                {
                    shift_left(&leds_sr_controller2);
                }
                if (y <= 200)
                {
                    shift_right(&leds_sr_controller2);
                }

                shift_register_out(&leds_sr, &PORTB);
                latch(&leds_sr, &PORTB);
                _delay_ms(100);
            }
            state = 0;
            break;
        }
    }

    return 0;
}