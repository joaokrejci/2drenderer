#include "nearest_neighbour.h"
#include <malloc.h>

unsigned int * nearest_neighbour(
        const unsigned int * origin_buffer,
        int origin_width,
        int origin_height,
        int destination_width,
        int destination_height,
        unsigned int * destination_buffer
)
{
    if (destination_buffer == NULL) {
        destination_buffer = malloc(sizeof(unsigned int *) * destination_width * destination_height);
    }

    int x_ratio = (int) ((origin_width<<16) / destination_width)+1;
    int y_ratio = (int) ((origin_height<<16) / destination_height)+1;

    for (int y = 0; y < destination_height; y++) {
        for (int x = 0; x < destination_width; x++) {
            int px = (x * x_ratio)>>16;
            int py = (y * y_ratio)>>16;

            destination_buffer[x + y * destination_width] = origin_buffer[px + py * origin_width];
        }
    }

    return destination_buffer;
}