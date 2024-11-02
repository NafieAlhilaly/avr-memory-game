#include <avr/io.h>
#include <util/delay.h>
#include "shift_register.h"

#define ONE 0x00f9
#define TWO 0x00a4
#define THREE 0x0030
#define FOUR 0x0099
#define FIVE 0x0012
#define SIX 0x0002
#define SEVEN 0x0078
#define EIGHT 0x0000
#define NINE 0x0090
#define ZERO 0x0040

#define DISPLAY_DIGIT_ONE 0x0100
#define DISPLAY_DIGIT_TWO 0x0200
#define DISPLAY_DIGIT_THREE 0x0400
#define DISPLAY_DIGIT_FOUR 0x0800

/**
 * @brief Shifts out a 16-bit data to the 7-segment display.
 *
 * This function sends a 16-bit data to the shift register which controls the
 * 7-segment display. The data includes both the digit to be displayed and the
 * value to be shown on that digit.
 *
 * @param data The 16-bit data to be shifted out to the display.
 */
void displayShiftOut(uint16_t data);