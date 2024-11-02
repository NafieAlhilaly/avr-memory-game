#include "shift_register.h"

const uint8_t bit_masks[6] = {BIT_0, BIT_1, BIT_2, BIT_3, BIT_4, BIT_5};

void init_sr(struct ShiftRegister *shift_register, uint8_t *ddr)
{
    *ddr |= (1 << shift_register->data_pin) | (1 << shift_register->clock_pin) | (1 << shift_register->latch_pin);
}

void shift_right(struct ShiftRegisterController *controller)
{
    uint8_t byte = (controller->shift_register->data >> (8 * controller->byte_position)) & 0xFF;
    byte = byte >> 1;

    if (byte < bit_masks[controller->start_bit])
    {
        byte = bit_masks[controller->end_bit - 1];
    }
    controller->shift_register->data = (controller->shift_register->data & ~(0xFF << (8 * controller->byte_position))) | (byte << (8 * controller->byte_position));
}

void shift_left(struct ShiftRegisterController *controller)
{
    uint8_t byte = (controller->shift_register->data >> (8 * controller->byte_position)) & 0xFF;
    byte = byte << 1;

    if (byte >= bit_masks[controller->end_bit])
    {
        byte = bit_masks[controller->start_bit];
    }
    controller->shift_register->data = (controller->shift_register->data & ~(0xFF << (8 * controller->byte_position))) | (byte << (8 * controller->byte_position));
}
void shift_register_out(struct ShiftRegister *shift_register, uint8_t *output_pin)
{
    for (int i = 0; i < 16; i++)
    {
        if (shift_register->data & (1 << (15 - i)))
        {
            *output_pin |= (1 << shift_register->data_pin);
        }
        else
        {
            *output_pin &= ~(1 << shift_register->data_pin);
        }
        *output_pin |= (1 << shift_register->clock_pin);
        _delay_us(1);
        *output_pin &= ~(1 << shift_register->clock_pin);
    }
}

void latch(struct ShiftRegister *shift_register, uint8_t *output_pin)
{
    *output_pin |= (1 << shift_register->latch_pin);
    _delay_us(1);
    *output_pin &= ~(1 << shift_register->latch_pin);
}