#include <iostream>
#include <exception>
#include <initializer_list>
#include <vector>


template <typename T>
class List 
{
    struct Node
    {
        Node* prev = nullptr;
        Node* next = nullptr;
        T value;

        Node(const T& v) : value(v) {}
        Node(T&& v) : value(std::move(v)) {}
    };

    Node* head = nullptr;
    Node* taile = nullptr;
    size_t size_dll = 0;
public:

    List() = default;

    ~List<T>() { clear(); }

    List<T>(
        const List<T>& other
    )
    {
        Node* node = other.head;
        while(node)
        {
            this->push_back(node->value);
            node = node->next;
        }
    }

    List<T>(
        List<T>&& other
    ) : head(other.head),
        taile(other.taile) ,
        size_dll(other.size_dll)
    {
        other.head = other.taile = nullptr;
        other.size_dll = 0;
    }

    List<T>(
        const std::initializer_list<T>& list
    )
    {
        for (auto i : list) 
        {
            this->push_back(i);
        }
    }
    
    List<T>(
        std::vector<T>& vec
    )
    {
        for (auto i : vec) 
        {
            this->push_back(i);
        }
    }
    
    List<T>& operator=(
        const List<T>& other
    ) 
    {
        if (&other == this) return *this;
        clear();
        
        Node* node = other.head;
        while(node)
        {
            this->push_back(node->value);
            node = node->next;
        }

        return *this;
    }

    List<T>& operator=(
        List<T>&& other
    )
    {
        if (this == &other) return * this;
        clear();

        head = other.head;
        taile = other.taile;
        size_dll = other.size_dll;

        other.head = other.taile = nullptr;
        other.size_dll = 0;

        return *this;
    }

    void push_front(
        const T& arg
    )
    {
        Node* node = new Node(arg);
        if (!head && !taile) head = taile = node;
        else 
        {
            head->prev = node;
            node->next = head;
            head = node;
        }
        ++size_dll;
    }

    void push_front(
        T&& arg
    )
    {
        Node* node = new Node(std::move(arg));
        if (!head && !taile) head = taile = node;
        else 
        {
            head->prev = node;
            node->next = head;
            head = node;
        }
        ++size_dll;
    } 
    
    void push_back(
        const T& arg
    )
    {
        Node* node = new Node(arg);
        if (!head && !taile) head = taile = node;
        else 
        {
            taile->next = node;
            node->prev = taile;
            taile = node;
        }
        ++size_dll;
    }
    void push_back(
        T&& arg
    )
    {
        Node* node = new Node(arg);
        if (!head && !taile) head = taile = node;
        else 
        {
            taile->next = node;
            node->prev = taile;
            taile = node;
        }
        ++size_dll;
    }
    
    void pop_back()
    {
        try
        {
            if (!taile) throw std::out_of_range("list is empty");
            else 
            {
                Node* node = taile;
                taile = taile->prev;

                if (taile) taile->next = nullptr;
                else head  = nullptr;
                
                delete node;
                --size_dll;
            }
        } catch (std::exception& e)
        {
            std::cout << e.what() << std::endl;
        }
    }
    void pop_front()
    {
        try 
        {
            if (!head) throw std::out_of_range("list is empty");
            Node* node = head;

            head = head->next;
            if(head) head->prev = nullptr;
            else taile = nullptr;

            delete node;
            --size_dll;

        } catch (std::exception& e)
        {
            std::cout << e.what() << std::endl;
        }
    }
    
    void insert(
        size_t pos, const T& arg
    ) 
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

            Node* node = head;
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
    void insert(
        size_t pos, T&& arg
    )
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

            Node* node = head;
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
            
            Node* node = head;

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
        std::swap(head, oth.head);
        std::swap(taile, oth.taile);
        std::swap(size_dll, oth.size_dll);
    }
    
    size_t size() { return size_dll; }

    bool empty() { return size_dll == 0;}
    
    void clear()
    {
        Node* node = head;
        while (node)
        {
            Node* nxt = node->next;
            delete node;
            node = nxt;
        }
        head = taile = nullptr;
        size_dll = 0;
    }

    T& back() {
        if (!taile) std::out_of_range("list is empty");
        return taile->value; 
    }

    const T& back() const {
        if (!taile) std::out_of_range("list is empty");
        return taile->value; 
    }

};