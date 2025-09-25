#include "vector_heder.hpp"
  

void myvector_init(MyVector* v, size_t capacity) {
    v->data = new int [capacity];
    v->size = 0;
    v->capacity = capacity;
}
void myvector_init(MyVector* v, size_t size, int value) {
    v->data = new int [size];
    v->size = size;
    v->capacity = size;
    for (int i = 0; i < size; ++i) v->data[i] = value; 
}

void myvector_destroy(MyVector* v) {
    delete[] v->data;
    v->size = 0;
    v->capacity = 0;
}

void myvector_clear(MyVector* v) {
    for (int i = 0; i < v->size; ++i) v->data[i] = 0;
}

size_t myvector_size(const MyVector* v) {
    return v->size;
}

size_t myvector_capacity(const MyVector* v) {
    return v->capacity;
}

void myvector_push_back(MyVector* v, int value) {
    if (v->size == v->capacity) {
        int* tmp = new int[v->size];
        for (size_t i = 0; i < v->size; ++i) tmp[i] = v->data[i];
        delete[] v->data;
        v->data = new int[v->capacity];
        for (size_t i = 0; i < v->size; ++i) v->data[i] = tmp[i];
        delete[] tmp;
    }
    v->data[v->size++] = value;

}

void myvector_pop_back(MyVector* v) {
    --v->size;
}

void myvector_insert(MyVector* v, size_t index, int value) {
    if (index > v->size) {
        std::cout <<"You haven't that much space place";
        return;
    }
    if (v->size == v->capacity) myvector_push_back(v, value);
    else ++v->size;

    for(int i = v->size; i > index; --i) v->data[i] = v->data[i - 1];
    v->data[index] = value;

}

void myvector_erase(MyVector* v, size_t index) {
    if (index >= v->size) {
        std::cout <<"You haven't that much space place";
        return;
    }
    for(int i = index; i+1 < v->size; ++i) v->data[i] = v->data[i + 1];
    --v->size;
}

void myvector_print(const MyVector* v) {
    std::cout << "Your array: ";
    for (int i = 0; i < v->size; ++i){
        std::cout << v->data[i] << " ";
    }
    std::cout << std::endl;
}
