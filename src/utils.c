#include "utils.h"
#include <stddef.h>

uint8_t *shuffle_array(uint8_t *array, uint8_t size)
{
    // Seed the random number generator
    srand(time(NULL));
    for (uint8_t i = size - 1; i > 0; i--)
    {
        // Generate a random index within the range [0, i]
        uint8_t j = rand() % (i + 1);

        // Swap the current element with the element at the random index
        uint8_t temp = array[i];
        array[i] = array[j];
        array[j] = temp;
    }

    return array;
}