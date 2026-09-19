#include "util/vector.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void vector_init(Vector* vector, int element_size) {
    vector->element_size = element_size;
    vector->count = 0;
    vector->capacity = 1;
    vector->data = malloc(element_size);
}

Vector * vector_new(int element_size) {
    Vector * vector = malloc(sizeof(Vector));
    vector_init(vector, element_size);
    return vector;
}

void * vector_get(Vector* vector, int index) {
    void*  a = (void *) &vector->data[vector->element_size * index];
    return a;
}

void vector_set(Vector* vector, int index, void * item) {
    char * in_data = (char*)item;
    char * data = vector->data;
    memcpy(data + index * vector->element_size, in_data, vector->element_size);
}

void vector_set_end(Vector* vector, void * item) {
    char * in_data = (char*)item;
    char * data = vector->data;
    memcpy(data + (vector->count-1) * vector->element_size, in_data, vector->element_size);
}

void * vector_get_end(Vector* vector) {
    return vector_get(vector, vector->count - 1);
}

void * vector_push(Vector* vector) {
    if (vector->count >= vector->capacity) {
        void * re = realloc(vector->data, vector->capacity * 2 * vector->element_size);
        if (re == NULL) {
            printf("ERROR reallocing vector");
            exit(1);
        }
        vector->data = re;
        vector->capacity = vector->capacity*2;
    }
    vector->count++;
    return vector_get_end(vector);
}

void vector_remove(Vector* vector, int index) {
    int i;
    for (i = index; i < vector->count-1; ++i) {
        vector_set(vector, i, vector_get(vector, i + 1));
    }
    vector->count--;
}

inline void vector_pop(Vector* vector) {
    vector->count--;
}

void vector_delete(Vector* vector) {
    vector_deinit(vector);
    free(vector);
    vector = NULL;
}

void vector_deinit(Vector* vector) {
    free(vector->data);
}