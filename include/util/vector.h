#ifndef NICANDRA_VECTOR_H
#define NICANDRA_VECTOR_H

// An array which items can be added and removed from.
typedef struct Vector Vector;
struct Vector {
    void * data;
    int element_size;
    int count;
    int capacity;
};

// Initializes a vector given a size for each element. If this was a vector of ints, this would be the size of int (4 bytes)
void vector_init(Vector* vector, int element_size);

// Allocates a vector and initializes it given an element size
Vector * vector_new(int element_size);

// Cleans up heap allocated memory in a vector.
void vector_deinit(Vector* vector);

// Deletes an allocated vector and its contents. Cleans up heap allocated memory in the vector.
void vector_delete(Vector* vector);

// Gets an element in the vector at an index.
void * vector_get(Vector* vector, int index);

// Sets an element in the vector at an index.
void vector_set(Vector* vector, int index, void * item);

// Sets an element at the end of the vector.
void vector_set_end(Vector* vector, void * item);

// Gets the element at the end of the vector.
void * vector_get_end(Vector* vector);

// Adds an element at the end of the vector.
void * vector_push(Vector* vector) ;

// Removes an element at a given index. Has to shift all elements,
// consider structuring your code to use pop instead.
void vector_remove(Vector* vector, int index);

// Removes an element at the end. Very efficient.
void vector_pop(Vector* vector);


#endif //NICANDRA_VECTOR_H
