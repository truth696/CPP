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
public:

    size_t size_dll = 0;

    struct iterator 
    {
    private:
        Node* curr;
    public:
        iterator(Node* tmp = nullptr) : curr(tmp) {}
        iterator(const iterator& oth) : curr(oth.curr) {}
        
        T& operator* () { return curr->value; }
        
        iterator operator++ () { curr = curr->next; return *this; }
        iterator operator++ (int);
        
        iterator operator-- () { curr = curr->prev; return *this; }
        iterator operator-- (int);
        
        bool operator!= (iterator oth) const { return this->curr != oth.curr; }
        bool operator== (iterator pt) const { return curr == pt.curr; }
        
        friend class List<T>;
        friend class reverse_iterator;
    };

    struct const_iterator 
    {
    private:
        Node* curr;
    public:
        const_iterator(Node* tmp = nullptr) : curr(tmp) {}
        const_iterator(const const_iterator& oth) : curr(oth.curr) {}

        const T& operator* () const { return curr->value; }
        
        const_iterator operator++ () { curr = curr->next; return *this; }
        const_iterator operator++ (int);
        
        const_iterator operator-- () { curr = curr->prev; return *this; }
        const_iterator operator-- (int);
        
        bool operator!= (const_iterator oth) const { return this->curr != oth.curr; }
        bool operator== (const_iterator pt) const { return curr == pt.curr; }
        
        friend class List<T>;
    };

    struct reverse_iterator 
    {
    private:
        iterator it;
        reverse_iterator(const iterator& oth): it(oth) {}
    public:
        reverse_iterator(Node* tmp = nullptr) : it(tmp) {}
        reverse_iterator(const reverse_iterator& oth) : it(oth.it) {}

        T& operator* () { return it.curr->prev->value; }
        
        reverse_iterator operator++ () { it.curr = it.curr->prev; return *this; }
        reverse_iterator operator++ (int);

        reverse_iterator operator-- ();
        reverse_iterator operator-- (int);
        
        bool operator!= (reverse_iterator oth) const { return this->it.curr != oth.it.curr; }
        bool operator== (reverse_iterator pt) const { return it.curr == pt.it.curr; }
        
        friend class List<T>;
    };

    struct const_reverse_iterator 
    {
    private:
        iterator it;
        const_reverse_iterator(const iterator& oth): it(oth) {}
    public:
        const_reverse_iterator(Node* tmp = nullptr) : it(tmp) {}
        const_reverse_iterator(const const_reverse_iterator& oth) : it(oth.it) {}

        const T& operator* () { return it.curr->prev->value; }
        
        const_reverse_iterator operator++ () { it.curr = it.curr->prev; return *this; }
        const_reverse_iterator operator++ (int);

        const_reverse_iterator operator-- ();
        const_reverse_iterator operator-- (int);
        
        bool operator!= (const_reverse_iterator oth) const { return this->it.curr != oth.it.curr; }
        bool operator== (const_reverse_iterator pt) const { return it.curr == pt.it.curr; }
        
        friend class List<T>;
    };

public:

    ~List<T>() { clear(); delete sentinel; }
    List() : sentinel(new Node{}) { sentinel->next = sentinel; sentinel->prev = sentinel; }

    List<T>(const List<T>& other);
    List<T>(List<T>&& other);

    List<T>(const std::initializer_list<T>& list);
    List<T>(std::vector<T>& vec);
    
    List<T>& operator=(const List<T>& other);
    List<T>& operator=(List<T>&& other);
    
    template <typename... U>
    void emplace_back(U&&...);
    template <typename... U>
    void emplace_front(U&&...);
    
    void push_front(const T& arg) { insert(this->begin(), arg); }
    void push_front(T&& arg) { insert(this->begin(), std::move(arg)); } 
    
    void push_back(const T& arg) { insert(end(), arg); }
    void push_back(T&& arg) { insert(end(), std::move(arg)); }
    
    void pop_back();
    void pop_front();
    
    void insert(size_t pos, const T& arg);
    void insert(size_t pos, T&& arg);
    
    T& back();
    const T& back() const;
    
    void erase(size_t pos);
    
    void swap(List<T>& oth) { std::swap(sentinel, oth.sentinel); std::swap(size_dll, oth.size_dll); }
    
    size_t size() { return size_dll; }
    
    bool empty() { return size_dll == 0;}
    
    void clear();
    
    iterator begin() const { return iterator(sentinel->next); }
    iterator end() const { return iterator(sentinel); }
    
    const_iterator cbegin() const { return const_iterator(sentinel->next); }
    const_iterator cend() const { return const_iterator(sentinel); }
    
    reverse_iterator rbegin() const { return reverse_iterator(sentinel); }
    reverse_iterator rend() const { return reverse_iterator(sentinel->next); }
    
    const_reverse_iterator crbegin() const { return const_reverse_iterator(sentinel); }
    const_reverse_iterator crend() const { return const_reverse_iterator(sentinel->next); }   

    iterator insert(iterator pos, const T& val);
    iterator insert(iterator pos, T&& val);
    iterator insert(iterator pos, iterator first, iterator last);
    iterator erase(iterator pos);
    iterator erase(iterator first, iterator last);
    template <typename... U>
    iterator emplace(iterator it, U&&... args);
    
    const_iterator insert(const_iterator pos, const T& val);
    const_iterator insert(const_iterator pos, T&& val) ;
    const_iterator insert(const_iterator pos, const_iterator first, const_iterator last);
    const_iterator erase(const_iterator pos);
    const_iterator erase(const_iterator first, const_iterator last);
    template <typename... U>
    const_iterator emplace(const_iterator it, U&&... args);
    
    reverse_iterator insert(reverse_iterator pos, const T& val);
    reverse_iterator insert(reverse_iterator pos, T&& val);
    reverse_iterator insert(reverse_iterator pos, reverse_iterator first, reverse_iterator last);
    reverse_iterator erase(reverse_iterator pos);
    reverse_iterator erase(reverse_iterator first, reverse_iterator last);
    template <typename... U>
    reverse_iterator emplace(reverse_iterator it, U&&... args);

    const_reverse_iterator insert(const_reverse_iterator pos, const T& val);
    const_reverse_iterator insert(const_reverse_iterator pos, T&& val);
    const_reverse_iterator insert(const_reverse_iterator pos, const_reverse_iterator first, const_reverse_iterator last);
    const_reverse_iterator erase(const_reverse_iterator pos);
    const_reverse_iterator erase(const_reverse_iterator first, const_reverse_iterator last);
    template <typename... U>
    const_reverse_iterator emplace(const_reverse_iterator it, U&&... args);

};


template <typename T>
List<T>::List(const List<T>& other)
{
    sentinel = new Node();
    
    sentinel->next = sentinel;
    sentinel->prev = sentinel;
    
    for (Node* node = other.sentinel->next; node != other.sentinel; node = node->next)
    {
        this->push_back(node->value);
    }
}

template <typename T>
List<T>::List(List<T>&& other) 
{
    sentinel =  other.sentinel;
    other.sentinel = new Node();

    other.sentinel->next = other.sentinel;
    other.sentinel->prev = other.sentinel;

    size_dll = other.size_dll;
    other.size_dll = 0;
}

template <typename T>
List<T>::List(const std::initializer_list<T>& list)
{
    sentinel = new Node();
    sentinel->next = sentinel;
    sentinel->prev = sentinel;
    for (auto i : list) 
    {
        this->push_back(i);
    }
}

template <typename T>
List<T>::List(std::vector<T>& vec)
{
    sentinel = new Node();
    sentinel->next = sentinel;
    sentinel->prev = sentinel;
    for (auto i : vec) this->push_back(i); 
}

template <typename T>
List<T>& List<T>::operator=(const List<T>& other) 
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

template <typename T>
List<T>& List<T>::operator=(List<T>&& other)
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

template <typename T>
void List<T>::pop_back()
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

template <typename T>
void List<T>::pop_front()
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

template <typename T>
void List<T>::insert(size_t pos, const T& arg) 
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

template <typename T>
void List<T>::insert(size_t pos, T&& arg)
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

template <typename T>
void List<T>::erase(size_t pos) 
{
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

template <typename T>
void List<T>::clear()
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

template <typename T>
T& List<T>::back() {
    if (sentinel->prev == sentinel) throw std::out_of_range("list is empty");
    return sentinel->prev->value; 
}

template <typename T>
const T& List<T>::back() const {
    if (sentinel->prev == sentinel) throw std::out_of_range("list is empty");
    return sentinel->prev->value; 
}

template <typename T>
template <typename... U>
List<T>::iterator List<T>::emplace(iterator it, U&&... args) {
    Node* curr = it.curr;
    Node* newNode = new Node(T(std::forward<U>(args)...), curr, curr->prev);
    
    curr->prev->next = newNode;
    curr->prev = newNode;
    ++size_dll;

    return iterator(newNode);
}

template <typename T>
template <typename... U>
void List<T>::emplace_front(U&&... args)
{
    insert(begin(), T(std::forward<U>(args)...));
}

template <typename T>
template <typename... U>
void List<T>::emplace_back(U&&... args)
{
    insert(end(), T(std::forward<U>(args)...));
}


template <typename T>
typename List<T>::iterator List<T>::iterator::operator-- (int) 
{
    iterator nonModify = *this;
    curr = curr->prev;
    return nonModify;
}

template <typename T>
typename List<T>::iterator List<T>::iterator::operator++ (int) 
{
    iterator nonModify = *this;
    curr = curr->next;
    return nonModify;
}

template <typename T>
typename List<T>::iterator List<T>::insert(iterator pos, iterator first, iterator last) 
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

template <typename T>
typename List<T>::iterator List<T>::insert(iterator pos, const T& val) 
{
    Node* curr = pos.curr;
    Node* newNode = new Node(val, curr, curr->prev);
    
    curr->prev->next = newNode;
    curr->prev = newNode;
    ++size_dll;

    return iterator(newNode);
}

template <typename T>
typename List<T>::iterator List<T>::insert(iterator pos, T&& val) 
{
    Node* curr = pos.curr;
    Node* newNode = new Node(std::move(val), curr, curr->prev);
    
    curr->prev->next = newNode;
    curr->prev = newNode;
    ++size_dll;

    return iterator(newNode);
}

template <typename T>
typename List<T>::iterator List<T>::erase(iterator first, iterator last) 
{
    while (first != last)
    {
        first = erase(first);
    }
    return last;
}

template <typename T>
typename List<T>::iterator List<T>::erase(iterator pos)
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

template <typename T>
template <typename... U>
typename List<T>::const_iterator List<T>::emplace(const_iterator it, U&&... args)
{
    return insert(it, T(std::forward<U>(args)...));
}

template <typename T>
typename List<T>::const_iterator List<T>::const_iterator::operator++ (int) 
{
    List<T>::const_iterator nonModify = *this;
    curr = curr->next;
    return nonModify;
}

template <typename T>
typename List<T>::const_iterator List<T>::const_iterator::operator-- (int) 
{
    const_iterator nonModify = *this;
    curr = curr->prev;
    return nonModify;
}

template <typename T>
typename List<T>::const_iterator List<T>::insert(const_iterator pos, const_iterator first, const_iterator last)
{
    int i{};
    const_iterator ret;

    for (;first != last; ++first, ++i) 
    {
        auto curr = first.curr;
        auto it = insert(pos, curr->value);

        if (!i) ret = it;
    }

    return ret;
}

template <typename T>
typename List<T>::const_iterator List<T>::insert(const_iterator pos, const T& val)
{
    Node* curr = pos.curr;
    Node* newNode = new Node(val, curr, curr->prev);
    
    curr->prev->next = newNode;
    curr->prev = newNode;
    ++size_dll;

    return const_iterator(newNode);
}

template <typename T>
typename List<T>::const_iterator List<T>::insert(const_iterator pos, T&& val) 
{
    Node* curr = pos.curr;
    Node* newNode = new Node(std::move(val), curr, curr->prev);
    
    curr->prev->next = newNode;
    curr->prev = newNode;
    ++size_dll;

    return const_iterator(newNode);
}

template <typename T>
typename List<T>::const_iterator List<T>::erase(const_iterator first, const_iterator last) 
{
    while (first != last)
    {
        first = erase(first);
    }
    return last;
}

template <typename T>
typename List<T>::const_iterator List<T>::erase(const_iterator pos)
{
    if (pos.curr == sentinel) return end();

    auto node = pos.curr;
    auto ret = pos.curr->next;

    node->prev->next = node->next;
    node->next->prev = node->prev;

    delete node;
    --size_dll;

    return const_iterator(ret);
}

template <typename T>
typename List<T>::reverse_iterator List<T>::reverse_iterator::operator++ (int) 
{
    reverse_iterator nonModify = *this;
    it.curr = it.curr->prev;
    return nonModify;
}

template <typename T>
typename List<T>::reverse_iterator List<T>::reverse_iterator::operator-- () 
{
    it.curr = it.curr->next;
    return *this;
}

template <typename T>
typename List<T>::reverse_iterator List<T>::reverse_iterator::operator-- (int) 
{
    reverse_iterator nonModify = *this;
    it.curr = it.curr->next;
    return nonModify;
}

template<typename T>
typename List<T>::reverse_iterator List<T>::insert(reverse_iterator pos, reverse_iterator first, reverse_iterator last) 
{
    int i{};

    auto base_pos = pos.it;
    auto base_first = first.it;
    auto base_last = last.it;

    auto ret = insert(base_pos, base_first, base_last);

    return reverse_iterator(ret);
}

template <typename T>
typename List<T>::reverse_iterator List<T>::insert(reverse_iterator pos, const T& val)
{
    Node* curr = pos.it.curr;
    Node* newNode = new Node(val, curr, curr->prev);
    curr->prev->next = newNode;
    curr->prev = newNode;
    ++size_dll;

    return reverse_iterator (newNode);
}

template <typename T>
typename List<T>::reverse_iterator List<T>::insert(reverse_iterator pos, T&& val) 
{
    Node* curr = pos.it.curr;
    Node* newNode = new Node(std::move(val), curr, curr->prev);
    
    curr->prev->next = newNode;
    curr->prev = newNode;
    ++size_dll;

    return reverse_iterator(newNode);
}

template <typename T>
typename List<T>::reverse_iterator List<T>::erase(reverse_iterator first, reverse_iterator last) 
{
    auto ffirst = first.it;
    auto llast = last.it;
    
    return reverse_iterator(erase(ffirst, llast));
}

template <typename T>
typename List<T>::reverse_iterator List<T>::erase(reverse_iterator pos)
{
    auto ppos = pos.it;
    return reverse_iterator(erase(--ppos));
}

template <typename T>
template <typename... U>
typename List<T>::reverse_iterator List<T>::emplace(reverse_iterator it, U&&... args)
{
    return insert(it, T(std::forward<U>(args)...));
}

template <typename T>
typename List<T>::const_reverse_iterator List<T>::const_reverse_iterator::operator++ (int) 
{
    const_reverse_iterator nonModify = *this;
    it.curr = it.curr->prev;
    return nonModify;
}

template <typename T>
typename List<T>::const_reverse_iterator List<T>::const_reverse_iterator::operator-- () 
{
    it.curr = it.curr->next;
    return *this;
}

template <typename T>
typename List<T>::const_reverse_iterator List<T>::const_reverse_iterator::operator-- (int) 
{
    const_reverse_iterator nonModify = *this;
    it.curr = it.curr->next;
    return nonModify;
}

template <typename T>
typename List<T>::const_reverse_iterator List<T>::insert(const_reverse_iterator pos, const_reverse_iterator first, const_reverse_iterator last) 
{
    int i{};
    
    auto base_pos = pos.it;
    auto base_first = first.it;
    auto base_last = last.it;
    
    auto ret = insert(base_pos, base_first, base_last);
    
    return const_reverse_iterator(ret);
}

template <typename T>
typename List<T>::const_reverse_iterator List<T>::insert(const_reverse_iterator pos, const T& val)
{
    Node* curr = pos.it.curr;
    Node* newNode = new Node(val, curr, curr->prev);
    
    curr->prev->next = newNode;
    curr->prev = newNode;
    ++size_dll;

    return const_reverse_iterator(newNode);
}

template <typename T>
typename List<T>::const_reverse_iterator List<T>::insert(const_reverse_iterator pos, T&& val) 
{
    Node* curr = pos.it.curr;
    Node* newNode = new Node(std::move(val), curr, curr->prev);
    
    curr->prev->next = newNode;
    curr->prev = newNode;
    ++size_dll;

    return const_reverse_iterator(newNode);
}

template <typename T>
typename List<T>::const_reverse_iterator List<T>::erase(const_reverse_iterator first, const_reverse_iterator last) 
{
    auto ffirst = first.it;
    auto llast = last.it;
    
    return erase(ffirst, llast);
}

template <typename T>
typename List<T>::const_reverse_iterator List<T>::erase(const_reverse_iterator pos)
{
    auto ret = pos.it.curr;
    auto ppos = pos.it;
    erase(ppos);

    return const_reverse_iterator(ret);
}

template <typename T>
template <typename... U>
typename List<T>::const_reverse_iterator List<T>::emplace(const_reverse_iterator it, U&&... args)
{
    return insert(it, T(std::forward<U>(args)...));
}