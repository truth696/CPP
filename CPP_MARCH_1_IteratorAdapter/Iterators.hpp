#include <iostream>

template <typename container>
class back_insert_iterator
{
    private:
        container* cont;

    public:
        explicit back_insert_iterator(container& _cont) : cont(_cont) {}
        back_insert_iterator operator++() { return *this; }
        back_insert_iterator operator++(int) { return *this; }
        back_insert_iterator operator*() { return *this; }
        back_insert_iterator operator= (const typename container::value_type& val) { cont->push_back(val); return *this; }

};

template <typename container>
auto back_insertor(const container& cont)
{
    return back_insert_iterator(cont);
} 

template <typename container>
class front_insert_iterator
{
    private:
        container* cont;

    public:
        explicit front_insert_iterator(container& _cont) : cont(_cont) {}
        front_insert_iterator& operator++() { return *this; }
        front_insert_iterator operator++(int) { return *this; }
        front_insert_iterator& operator*() { return *this; }
        front_insert_iterator& operator= (const typename container::value_type& val) { cont->push_front(val); return *this; }
};

template <typename container>
auto fornt_insetor(const container& cont)
{
    return front_insert_iterator(cont);
} 

template <typename container>
class insert_iterator
{
    private:
    container* cont;
    typename container::iterator it;
    
    public:
    explicit insert_iterator(container& _cont,  typename container::iterator _it) : cont(_cont), it(_it) {}
    insert_iterator& operator++() { return *this; }
    insert_iterator operator++(int) { return *this; }
    insert_iterator& operator*() { return *this; }
    insert_iterator& operator= (const typename container::value_type& val) { cont->insert(it++,val); return *this; }
};

template <typename container>
auto insert_iterator_f(const container& cont, typename container::iterator it)
{
    return insert_iterator(cont, it);
} 

template <typename iterator>
class move_iterator
{
    iterator it;

    public:
        explicit move_iterator(iterator _it) : it(_it) {}

        move_iterator& operator++() { ++it; return *this; }
        move_iterator operator++(int)
        { 
            auto tmp = *this; 
            ++it;
            return tmp;
        }
        auto operator*() -> decltype(std::move(*it))
        { return std::move(*it); }

        bool operator==(move_iterator& mvi) { return it == mvi.it; }
        bool operator!=(move_iterator& mvi) { return it != mvi.it; }
};

