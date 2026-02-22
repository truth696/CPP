#pragma once 
#include <iostream>
#include <exception>
#include <initializer_list>
#include <vector>


template <typename T>
class List 
{ 
    struct Node
    {
        Node* prev;
        Node* next;
        T value;
        
        Node() : prev(nullptr), next(nullptr), value() {}
        Node(const T& v, Node* _next = nullptr , Node* _prev = nullptr) : prev(_prev), next(_next), value(v) {}
        Node(T&& v, Node* _next = nullptr , Node* _prev = nullptr) : prev(_prev), next(_next), value(std::move(v)) {}
    };

    Node* sentinel; 
    
    struct iterator 
    {
        Node* curr;
        iterator(Node* tmp = nullptr) : curr(tmp) {}
        iterator(const iterator& oth) : curr(oth.curr) {}

        bool operator!= (iterator oth) const { return this->curr != oth.curr; }

        iterator operator++ () 
        {
            curr = curr->next;
            return *this;
        }

        iterator operator++ (int) 
        {
            iterator nonModify = *this;
            curr = curr->next;
            return nonModify;
        }

        iterator operator-- () 
        {
            curr = curr->prev;
            return *this;
        }
        
        iterator operator-- (int) 
        {
            iterator nonModify = *this;
            curr = curr->prev;
            return nonModify;
        }

        T& operator* () 
        {
            return curr->value;
        }

        bool operator== (iterator pt) const { return curr == pt.curr; }
    };

    size_t size_dll = 0;
public:

    List() : sentinel(new Node{}) {
        sentinel->next = sentinel;
        sentinel->prev = sentinel;
    }

    ~List<T>()
    {
        clear();
        delete sentinel;
    }

    List<T>(const List<T>& other)
    {
        sentinel = new Node();
        
        sentinel->next = sentinel;
        sentinel->prev = sentinel;

        for (Node* node = other.sentinel->next; node != other.sentinel; node = node->next)
        {
            this->push_back(node->value);
        }
    }

    List<T>(List<T>&& other)
    {   
        sentinel =  other.sentinel;
        other.sentinel = new Node();

        other.sentinel->next = other.sentinel;
        other.sentinel->prev = other.sentinel;
    
        size_dll = other.size_dll;
        other.size_dll = 0;
    }

    List<T>(const std::initializer_list<T>& list)
    {
        sentinel = new Node();
        sentinel->next = sentinel;
        sentinel->prev = sentinel;
        for (auto i : list) 
        {
            this->push_back(i);
        }
    }
    
    List<T>(std::vector<T>& vec)
    {
        sentinel = new Node();
        sentinel->next = sentinel;
        sentinel->prev = sentinel;
        for (auto i : vec) 
        {
            this->push_back(i);
        }
    }
    
    List<T>& operator=(const List<T>& other) 
    {
        if (&other == this) return *this;
        clear();
        
        Node* node = other.sentinel->next;
        for (Node* node = other.sentinel->next; node != other.sentinel; node = node->next)
        {
            this->push_back(node->value);
        }

        return *this;
    }

    List<T>& operator=(List<T>&& other)
    {
        if (this == &other) return *this;
        clear();
        delete sentinel;

        sentinel = other.sentinel;
        other.sentinel = new Node();

        other.sentinel->next = other.sentinel;
        other.sentinel->prev = other.sentinel;
    
        size_dll = other.size_dll;
        other.size_dll = 0;

        return *this;
    }

    iterator begin() 
    {
        return iterator(sentinel->next);
    }

    iterator end() 
    {
        return iterator(sentinel);
    }


    void push_front(const T& arg)
    {
        insert(this->begin(), arg);
    }

    void push_front(T&& arg)
    {
        insert(this->begin(), std::move(arg));
    } 
    
    void push_back(const T& arg)
    {
        insert(end(), arg);
    }

    void push_back(T&& arg)
    {
        insert(end(), std::move(arg));
    }
    
    void pop_back()
    {
        try
        {
            Node* node = sentinel->prev;
            
            if (node == sentinel) throw std::out_of_range("list is empty");
            
            node->next->prev = node->prev;
            node->prev->next = node->next;
            
            delete node;
            --size_dll;
        } catch (std::exception& e)
        {
            std::cout << e.what() << std::endl;
        }
    }

    void pop_front()
    {
        try 
        {
            Node* node = sentinel->next;

            if(node == sentinel) throw std::out_of_range("list is empty");

            node->prev->next = node->next;
            node->next->prev = node->prev;
            
            delete node;
            --size_dll;
        } catch (std::exception& e)
        {
            std::cout << e.what() << std::endl;
        }
    }


    iterator insert(iterator pos, iterator first, iterator last) 
    {
        int i{};
        iterator ret;

        for (;first != last; ++first, ++i) 
        {
            auto curr = first.curr;
            auto it = insert(pos, curr->value);

            if (!i) ret = it;
        }

        return ret;
    }

    iterator insert(iterator pos, const T& val) 
    {
        Node* curr = pos.curr;
        Node* newNode = new Node(val, curr, curr->prev);
        
        curr->prev->next = newNode;
        curr->prev = newNode;
        ++size_dll;

        return iterator(newNode);
    }
    
    iterator insert(iterator pos, T&& val) 
    {
        Node* curr = pos.curr;
        Node* newNode = new Node(std::move(val), curr, curr->prev);
        
        curr->prev->next = newNode;
        curr->prev = newNode;
        ++size_dll;

        return iterator(newNode);
    }
    

    void insert(size_t pos, const T& arg) 
    {
        try 
        {
            if (pos > size()) throw std::invalid_argument("Incorrect index"); 
            if (!pos)
            {
                push_front(arg);
                return;
            }
            if (pos == size_dll)
            {
                push_back(arg);
                return;
            }  

            Node* node = sentinel->next;
            for (size_t i{}; i < pos; ++i) node = node->next;

            Node* tmp = new Node(arg);
            
            tmp->prev = node->prev;
            node->prev->next = tmp;
            tmp->next = node;
            node->prev = tmp;

            ++size_dll;
        } catch(std::exception& e)
        {
            std::cout << e.what() << std::endl;
        } 
    }
    void insert(size_t pos, T&& arg)
    {
        try 
        {
            if (pos > size_dll) throw std::invalid_argument("Incorrect index"); 
            if (!pos)
            {
                push_front(std::move(arg));
                return;
            }
            if (pos == size_dll)
            {
                push_back(std::move(arg));
                return;
            }  

            Node* node = sentinel->next;
            for (size_t i{}; i < pos; ++i) node = node->next;

            Node* tmp = new Node(std::move(arg));
            
            tmp->prev = node->prev;
            node->prev->next = tmp;
            tmp->next = node;
            node->prev = tmp;

            ++size_dll;
        } catch(std::exception& e)
        {
            std::cout << e.what() << std::endl;
        } 
    }

    iterator erase(iterator first, iterator last) 
    {
        while (first != last)
        {
            first = erase(first);
        }
        return last;
    }

    iterator erase(iterator pos)
    {
        if (pos.curr == sentinel) return end();

        auto node = pos.curr;
        auto ret = pos.curr->next;

        node->prev->next = node->next;
        node->next->prev = node->prev;

        delete node;
        --size_dll;

        return iterator(ret);
    }

    void erase(size_t pos) {
        try 
        {
            if (pos >= size_dll) throw std::out_of_range("Inccorect index");

            if (pos == 0) { 
                pop_front(); 
                return; 
            }
            if (pos + 1 == size_dll) { 
                pop_back(); 
                return; 
            }
            
            Node* node = sentinel->next;

            for (size_t i{}; i < pos; ++i) node = node->next;

            node->prev->next = node->next;
            node->next->prev = node->prev;

            delete node;
            --size_dll;
        } catch (std::exception& e) 
        {
            std::cout << e.what() << std::endl;
        }
    }

    void swap(
        List<T>& oth
    )
    {
        std::swap(sentinel, oth.sentinel);
        std::swap(size_dll, oth.size_dll);
    }
    
    size_t size() { return size_dll; }

    bool empty() { return size_dll == 0;}
    
    void clear()
    {
        Node* node = sentinel->next;
        while (node != sentinel)
        {
            Node* nxt = node->next;
            delete node;
            node = nxt;
        }
        sentinel->next = sentinel;
        sentinel->prev = sentinel;
        size_dll = 0;
    }

    T& back() {
        if (sentinel->prev == sentinel) throw std::out_of_range("list is empty");
        return sentinel->prev->value; 
    }

    const T& back() const {
        if (sentinel->prev == sentinel) throw std::out_of_range("list is empty");
        return sentinel->prev->value; 
    }

};