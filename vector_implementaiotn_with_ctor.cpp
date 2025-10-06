#include <iostream>
#include <initializer_list>
#include <cstddef>
#include <string>
#include <stdbool.h>

class Vector_my {
private :
    int* data;
    size_t _size;
    size_t _capacity;

public :
    Vector_my () : data (nullptr), _size(0), _capacity(0){ }
    Vector_my (size_t n, int value = 0) : data(new int[n]), _size(n), _capacity(n) { for (int i = 0; i < _size; ++i) data[i] = value; }
    Vector_my (std::initializer_list<int> init ) : data(new int[init.size()]), _size (0), _capacity(init.size()) { for (int value : init) data[_size++] = value; }
    ~Vector_my () {
        delete[]data;
        _size = 0;
        _capacity = 0;
    }
    void new_size (){ 
        if (_capacity == 0) _capacity = 1;
        int* tmp = new int[_capacity*2];
        for (int i = 0; i < _size; ++i) tmp[i] = data[i];
        delete[] data;
        data = tmp;
        _capacity *= 2;
    }

    // void destroy () {
    //     delete[] data;
    //     _size = 0;
    //     _capacity = 0;
    // }

    void push_back (int value) {
        if (_size == _capacity) new_size();
        data[_size++] = value;
    }
    
    void clear () {
        for (int i = 0; i < _size; ++i) data[i] = 0;
        _size = 0;
    }
    
    void pop_back () { --_size; }

    void insert (size_t index, int value) {
        if (index > _size || (_size == 0 && _capacity ==0)) {
           std::cout <<"You haven't that much space place" << std::endl;
            return;
        }
        if (_size == _capacity) new_size();
        for (int i = _size++; i > index; --i) data[i] = data[i - 1];
        data[index] = value; 
    }

    void erase (size_t index){
        if (index >= _size) {
            std::cout <<"You haven't that much space place" << std::endl;
            return;
        }  
        for (int i = index; i+1 < _size; ++i) data[i] = data[i + 1];
        --_size;
    }
    int get_size () const { return _size; }
    int get_cpacity () const { return _capacity; }

};


int main() {
     try {
        Vector_my v; // пустой вектор

        // 1. push_back
        for (int i = 1; i <= 10; ++i) v.push_back(i);

        // 2. insert
        v.insert(0, 100);   // вставка в начало
        v.insert(5, 200);   // вставка в середину
        v.insert(20, 300);  // вставка за пределы — должна вывести ошибку

        // 3. erase
        v.erase(0);   // удаляем первый
        v.erase(4);   // удаляем средний
        v.erase(20);  // удаляем за пределом — должна вывести ошибку

        // 4. pop_back
        v.pop_back(); // удаляем последний

        // 5. clear
        v.clear();    // очищаем вектор

        // 6. push_back после clear
        v.push_back(999);

        // 7. destroy
        // v.destroy();  // очищаем и удаляем память

        std::cout << "✅ Все методы вызваны без падений\n";

    } catch (...) {
        std::cout << "❌ Ошибка при вызове методов\n";
    }

    return 0;
}