#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

typedef struct dynamic_array
{
    unsigned char *data;
    unsigned int data_size;
    unsigned int length;

    unsigned long __alloc_size;
} dynamic_array_t;


dynamic_array_t create_dynamic_array(unsigned int data_size);
void delete_dynamic_array(dynamic_array_t *arr);
void dynamic_array_insert(dynamic_array_t *arr, unsigned char *elements, unsigned int n);
void dynamic_array_remove(dynamic_array_t *arr, int position);

#endif