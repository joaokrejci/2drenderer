#ifndef NEAREST_NEIGHBOUR_H
#define NEAREST_NEIGHBOUR_H

unsigned int * nearest_neighbour(
        const unsigned int * origin_buffer,
        int origin_width,
        int origin_height,
        int destination_width,
        int destination_height,
        unsigned int * destination_buffer
);

#endif