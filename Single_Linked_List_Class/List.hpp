#include <iostream>
#include <initializer_list>

class SingleList {
    private:
    struct Node {
        int val;
        Node* next;
        Node (int _val = 0, Node* _next = nullptr) : val(_val), next(_next) {}
    };
    Node* head;
    void copy (const SingleList& rhs);
    public:
    SingleList() : head(nullptr) {}
    SingleList(std::initializer_list<int> init);
    SingleList(const SingleList& oth);
    SingleList& operator=(const SingleList& oth);
    SingleList(SingleList&& oth);
    SingleList& operator=(SingleList&& oth);
    ~SingleList () { clear();}
    
    void clear ();
    void push_back(int _val);
    void push_front(int _val);
    void pop_back();
    void pop_front();
    int size() const;
   
    SingleList operator+(const SingleList& rhs);
    SingleList& operator+=(const SingleList& oth);
    bool operator==(const SingleList& oth) const;
    bool operator!=(const SingleList& oth) const;
    
    int& operator[](size_t index);
    bool operator!() const;
    
    SingleList& operator++();
    SingleList operator++(int);
    SingleList& operator--();
    SingleList operator--(int);
    
    friend std::ostream& operator<<(std::ostream& os, const SingleList& oth);
    friend std::istream& operator>>(std::istream& rhs, SingleList& oth);

    explicit operator bool() const;
    operator std::vector<int>() const;


};
