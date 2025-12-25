#include <iostream>
#include <vector>
#include <string>
#include "SharedPointer.hpp"
#include "UniquePointer.hpp"

static int id = 0;

class Author {
    std::vector<shared_ptr<Author>> authors;
    std::string name;
};

class Book{
    int _id;
    std::string title;
    shared_ptr<Author> author;
public:
    Book(std::string _title = "Unknow", Author* _author = nullptr) : title(_title), author(_author) {
        _id = ++id;
    }
};

class Shelf{
    unique_ptr<Book> books;
public:
    Shelf(Book* _book = nullptr) : books(_book) {}
};

class Library{
    unique_ptr<Shelf> shelf;
public:
    void addNewShelf() noexcept;
    void removeShelf(int index) noexcept;
    void addBook (int index) noexcept;
    void removeBook(std::string title) noexcept;
    Book* findBook(std::string title) noexcept;
    void transferBook(std::string title) noexcept;
    void replaceBook(int id) noexcept;
    int countOfAutor(std::string name) noexcept;

};

