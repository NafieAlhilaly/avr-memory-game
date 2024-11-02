#include <stdint.h>
#include <util/delay.h>

#define BIT_0 1
#define BIT_1 2
#define BIT_2 4
#define BIT_3 8
#define BIT_4 16
#define BIT_5 32

/**
 * @brief Represents a shift register,
 * or multiple shift register connected serially,
 * adjust `data` type size based on the desired usage,
 * here its using `uint16_t` with two shift registers.
 */
struct ShiftRegister
{
    uint16_t data;
    uint8_t data_pin;
    uint8_t clock_pin;
    uint8_t latch_pin;
};

/**
 * @brief Controls a byte within a shift register by its position from a
 * `start_bit` to `end_bit`.
 */
struct ShiftRegisterController
{
    struct ShiftRegister *shift_register;
    uint8_t byte_position;
    uint8_t start_bit;
    uint8_t end_bit;
};

/**
 * @brief Initializes the shift register.
 *
 * @param shift_register Pointer to the shift register structure.
 * @param ddr Pointer to the Data Direction Register.
 */
void init_sr(struct ShiftRegister *shift_register, uint8_t *ddr);

/**
 * @brief Shifts only the selected byte by `ShiftRegisterController` to the right.
 *
 * @param controller Pointer to the SRByteController structure.
 */
void shift_right(struct ShiftRegisterController *controller);

/**
 * @brief Shifts only the selected byte by `ShiftRegisterController` to the to the left.
 *
 * @param controller Pointer to the SRByteController structure.
 */
void shift_left(struct ShiftRegisterController *controller);

/**
 * @brief Shifts out the data from the shift register.
 *
 * @param shift_register Pointer to the shift register structure.
 * @param output_port Pointer to the output port register.
 */
void shift_register_out(struct ShiftRegister *shift_register, uint8_t *output_port);

/**
 * @brief Latches the data in the shift register.
 *
 * @param shift_register Pointer to the shift register structure.
 * @param output_pin Pointer to the output pin register.
 */
void latch(struct ShiftRegister *shift_register, uint8_t *output_pin);