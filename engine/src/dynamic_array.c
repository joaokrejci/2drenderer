#include <stdlib.h>
#include <memory.h>

#include "dynamic_array.h"

#define ALLOC_STEP 64

dynamic_array_t create_dynamic_array(unsigned int data_size)
{
    dynamic_array_t array;
    array.data = NULL;
    array.length = 0;
    array.data_size = data_size;
    array.__alloc_size = 0;

    return array;
}

void delete_dynamic_array(dynamic_array_t *arr)
{
    free(arr->data);
}

void dynamic_array_insert(dynamic_array_t *arr, unsigned char *elements, unsigned int n)
{
    if(arr->__alloc_size > arr->length + n) {
        unsigned char *insert_position = &arr->data[arr->length * arr->data_size];
        memcpy(insert_position, elements, n * arr->data_size);

        arr->length += n;
        return;
    }

    arr->__alloc_size += ALLOC_STEP * arr->data_size;
    arr->data = realloc(arr->data, arr->__alloc_size);
    if (arr->data == NULL) {
        arr->__alloc_size = 0;
    }
    dynamic_array_insert(arr, elements, n);
}

void dynamic_array_remove(dynamic_array_t *arr, int position)
{
    if(position == 0) {
        arr->data = &arr->data[arr->data_size];
    }
    else if(position != arr->length -1) {
        unsigned char * element_position = arr->data + position * arr->data_size;
        unsigned char * next_position = arr->data + (position + 1) * arr->data_size;

        memmove(element_position, next_position, (arr->length - position - 1) * arr->data_size);
    }

    arr->length--;

    if (arr->__alloc_size - ALLOC_STEP >= arr->length) {
        arr->__alloc_size -= ALLOC_STEP * arr->data_size;
        arr->data = realloc(arr->data, arr->__alloc_size);
    }
}
