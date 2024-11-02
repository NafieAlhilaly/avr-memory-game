#include <avr/io.h>
#include <util/delay.h>

#define SOUND_PIN PORTB1 ///< Pin used for sound output.
#define SOUND_DDR DDB1   ///< Data Direction Register bit for sound output pin.

#define A4_FREQ 440  ///< Frequency of note A4 in Hz.
#define A5_FREQ 880  ///< Frequency of note A5 in Hz.
#define A6_FREQ 1760 ///< Frequency of note A6 in Hz.
#define C5_FREQ 523  ///< Frequency of note C5 in Hz.
#define C6_FREQ 1047 ///< Frequency of note C6 in Hz.
#define D6_FREQ 1175 ///< Frequency of note D6 in Hz.
#define E6_FREQ 1319 ///< Frequency of note E6 in Hz.

#define TIMER1_PRESCALER (uint8_t)8 ///< Prescaler value for Timer1.

/**
 * @brief Initialize the sound peripheral.
 *
 * This function sets up the data direction register for the sound output pin.
 *
 * @param ddr Pointer to the Data Direction Register.
 * @param port Port bit for the sound output pin.
 */
void init_sound(uint8_t *ddr, uint8_t port);

/**
 * @brief Play a tone.
 *
 * This function plays a tone with the specified frequency.
 *
 * @param tone The frequency of the tone to play.
 */
void play(uint16_t tone);