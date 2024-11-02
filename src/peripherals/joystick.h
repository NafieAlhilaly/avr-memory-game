#include <avr/io.h>
#include <util/delay.h>

/**
 * @struct JoyStick
 * @brief Represents a joystick with an analog input channel.
 */
struct JoyStick
{
    uint8_t *input_channel;
};

/**
 * @struct JoyStickButton
 * @brief Represents a button on the joystick.
 */
struct JoyStickButton
{
    struct JoyStick *JoyStick;
    uint8_t pin;
    uint8_t port;
    uint8_t ddr;
};

/**
 * @brief Initialize the Analog to Digital Converter.
 */
void init_adc();

/**
 * @brief Read the value from the joystick's input channel.
 *
 * @param input_channel Pointer to the ADC input channel.
 * @return The ADC value read from the input channel.
 */
uint16_t read_adc(uint8_t *input_channel);

/**
 * @brief Initialize the joystick button.
 *
 * @param button Pointer to the JoyStickButton structure.
 */
void js_btn_init(struct JoyStickButton *button);

/**
 * @brief Report whether the joystick button is pressed or not.
 *
 * @param button Pointer to the JoyStickButton structure.
 * @return LOW if the button is pressed, otherwise HIGH.
 */
uint8_t js_btn_state(struct JoyStickButton *button);