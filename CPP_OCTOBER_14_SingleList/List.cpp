#include "List.hpp"
#include <initializer_list>

SingleList::SingleList(std::initializer_list<int> init) {
    Node dummy;
    Node* tmp = &dummy;
    for (int i : init) {
        tmp->next = new Node(i);
        tmp = tmp->next;
    }

    this->head = dummy.next;
}

void SingleList::copy (const SingleList& rhs){
    Node* tmp = rhs.head;
    Node dummy;

    Node* tmp2 = &dummy;
    while (tmp){
        tmp2->next = new Node(tmp->val);
        tmp2 = tmp2->next;
        tmp = tmp->next;
    }
    this->head = dummy.next;

}

SingleList::SingleList(const SingleList &oth) {
    this->copy(oth);
}

SingleList& SingleList::operator=(const SingleList &oth) {
    if (&oth != this){
        this->clear();
        this->copy(oth);
    }
    return *this;
}

void SingleList::push_back(int _val) {
    if (!head) {
        head = new Node (_val);
    } else {
        Node* tmp = head;
        while (tmp->next) tmp = tmp->next;
        tmp->next = new Node(_val);
    }
}

void SingleList::push_front(int _val = 0) {
    Node* tmp = head;
    Node* tmp2 = new Node(_val);
    
    tmp2->next = tmp;
    head = tmp2; 
}

void SingleList::pop_back() {
    if (!head) return; 
    if (!head->next) {      
        delete head;
        head = nullptr;
        return;
    }
    if (head){
        Node* tmp = head;
        Node* tmp2 = tmp;
        while (tmp->next){
            tmp2 = tmp;
            tmp = tmp->next;
        }
        delete tmp;
        tmp2->next = nullptr;
    }
}

int SingleList::size() const {
    Node* tmp = head;
    int count = 0;
    while (tmp){
        ++count;
        tmp = tmp->next;
    }
    return count;
}

void SingleList::pop_front(){
    if(head) {
        Node* tmp = head;
        head = head->next;
        delete tmp;
    }   
}

void SingleList::clear() {
    Node* tmp = this->head;
    while (tmp){
        Node* tmp2 = tmp->next;
        delete tmp;
        tmp = tmp2;
    }
    head = nullptr;
}

SingleList::SingleList(SingleList &&oth) {
    this->head = oth.head;
    oth.head = nullptr;
}

SingleList& SingleList::operator=(SingleList &&oth) {
    this->head = oth.head;
    oth.head = nullptr;
    return *this;
}

SingleList operator+(const SingleList& rhs, const SingleList& oth){
    SingleList obj;
    SingleList::Node dummy;
    SingleList::Node* tmp_r = rhs.head;
    SingleList::Node* tmp_o =oth.head;
    SingleList::Node* tmp2 = &dummy;
    if (!tmp_o) return obj = rhs;
    if (!tmp_r) return obj = oth;

    while (tmp_r){
        tmp2->next = new SingleList::Node(tmp_r->val);
        tmp2 = tmp2->next;
        tmp_r = tmp_r->next;
    }

    while (tmp_o){
        tmp2->next = new SingleList::Node(tmp_o->val);
        tmp2 = tmp2->next;
        tmp_o = tmp_o->next;
    }

    obj.head = dummy.next;
    return obj;
}

SingleList& operator+=(SingleList& rhs, const SingleList& oth) {
    if (oth.head == nullptr) return rhs;

    SingleList::Node* tmp = oth.head;
    SingleList::Node* tmp2 = rhs.head;
    if (rhs.head == nullptr){
        rhs.head = new SingleList::Node(tmp->val);
        tmp2 = rhs.head;
        tmp = tmp->next;
        while (tmp){
            tmp2->next = new SingleList::Node(tmp->val);
            tmp2 = tmp2->next;
            tmp = tmp->next;
        }
        return rhs;
    } 
    while (tmp2->next)  tmp2 = tmp2->next;
    
    while (tmp) {
        tmp2->next = new SingleList::Node(tmp->val);
        tmp2 = tmp2->next;
        tmp = tmp->next;
    }
    
    return rhs;
}

bool operator==(const SingleList& rhs, const SingleList& oth) {
    SingleList::Node* tmp = rhs.head;
    SingleList::Node* tmp2 = oth.head;
    if (rhs.size() != oth.size()) return false;

    while(tmp && tmp2) {
        if (tmp->val != tmp2->val) return false;
        tmp = tmp->next;
        tmp2 = tmp2->next;
    }
    
    return true;
}

bool operator!=(const SingleList& rhs, const SingleList& oth) {
    SingleList::Node* tmp = rhs.head;
    SingleList::Node* tmp2 = oth.head;
    if (rhs.size() != oth.size()) return true;

    while (tmp && tmp2) {
        if (tmp->val != tmp2->val) return true;
        tmp = tmp->next;
        tmp2 = tmp2->next;
    }

    return false;
}

int& SingleList::operator[](size_t index) {
    Node* tmp = head;
    int i = 0;
    while (tmp) {
        if (i == index){
            return tmp->val;
        }
        tmp = tmp->next;
        ++i;
    }
    std::cout << "Your index a larger size" << std::endl;
    std::exit(10);
}

bool SingleList::operator! () const {
    if(!head) return true;
    return false;
}

SingleList& SingleList::operator++() {
    this->push_back(0);
    return *this;
}

SingleList SingleList::operator++(int) {
    SingleList obj;
        obj.copy(*this);
    this->push_back(0);
    return obj;
}

SingleList& SingleList::operator--() {
    if (!head) return *this;
    Node* tmp = this->head;
    Node* tmp2;

    while (tmp->next){
        tmp2 = tmp;
        tmp = tmp->next;
    }    
    
    delete tmp;
    tmp2->next = nullptr;
    
    return *this;
}

SingleList SingleList::operator--(int) {
    if (!head) return *this;
    Node* tmp = this->head;
    Node* tmp2;

    SingleList obj;
    obj.copy(*this);

    while (tmp->next){
        tmp2 = tmp;
        tmp = tmp->next;
    }    
    
    delete tmp;
    tmp2->next = nullptr;
    
    return obj;
}

std::ostream& operator<<(std::ostream& rhs, const SingleList& oth){
    SingleList::Node* tmp = oth.head;
    while(tmp) {
        rhs << tmp->val << " ";
        tmp = tmp->next;
    }
    return rhs;
}

std::istream& operator>>(std::istream& rhs, SingleList& oth) {
    int val;
    oth.clear();

    while (rhs >> val) {
        oth.push_back(val);
    }

    return rhs;
}

SingleList::operator std::vector<int>() const {
    Node* tmp = head;
    std::vector<int> vec;
    while (tmp) {
        vec.push_back(tmp->val);
        tmp = tmp->next;
    }
    return vec;
}

SingleList::operator bool() const{
    if(!head) return false;
    return true;
}







