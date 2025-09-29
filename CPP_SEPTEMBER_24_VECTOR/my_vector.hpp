#ifndef MY_VECTOR
#define MY_VECTOR  
#include <iostream> 


struct MyVector {
    int* data;
    size_t size;
    size_t capacity;

};

void myvector_init(MyVector* v, size_t capacity);
void myvector_init(MyVector* v, size_t size, int value);

void myvector_destroy(MyVector* v);
void myvector_clear(MyVector* v);

size_t myvector_size(const MyVector* v);
size_t myvector_capacity(const MyVector* v);

void myvector_push_back(MyVector* v, int value);
void myvector_pop_back(MyVector* v);

void myvector_insert(MyVector* v, size_t index, int value);
void myvector_erase(MyVector* v, size_t index);

void myvector_print(const MyVector* v);

static void myvector_resize(MyVector* v, size_t new_capacity);

#endif 