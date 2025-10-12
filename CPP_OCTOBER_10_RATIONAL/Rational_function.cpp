#include <Rational.hpp>
#include <iostream>

Rational::Rational(int num, int denum) {
    if (denum == 0) std::cout << "Your denum can't be 0" << std::endl;
    if (denum != 0) {
        if (denum < 0) {
        denum *= -1;
        num *= -1;
        }
        _num = num;
        _denum = denum;
        this->reduce_helper();
    }
}

Rational& Rational::operator=(const Rational& oth) {
    if (this!= &oth) {
        _num = oth._num;
        _denum = oth._denum;
    }
    return *this;
}

Rational& Rational::operator=(Rational&& oth){
    if (this != &oth){
        _num = oth._num;
        _denum = oth._denum;
    }
    oth._num = 0;
    oth._denum = 1;
    return *this;
}

Rational::Rational (Rational&& oth){
    oth._num = 0;
    oth._denum = 0;
}

Rational Rational::operator+() const{
    Rational tmp(_num, _denum);
    return tmp;
}

Rational Rational::operator-() const {
    Rational tmp(_num, _denum);
    tmp._num *= -1;
    return tmp;
}

Rational& Rational::operator++(){
    _num += _denum;
    this->reduce_helper();
    return *this;
}

Rational Rational::operator++(int){
    Rational tmp(_num, _denum);
    _num += _denum;
    this->reduce_helper();
    return tmp;
}

Rational& Rational::operator--(){
    _num -= _denum;
    this->reduce_helper();
    return *this;
}

Rational Rational::operator--(int){
    Rational tmp(_num, _denum);
    _num -= _denum;
    tmp.reduce_helper();
    return tmp;
}

bool Rational::operator !() const {
    return _num == 0;
}

Rational& Rational::operator+=(const Rational& oth) {
    if (oth._denum == this->_denum) {
        this->_num += oth._num;
        this->reduce_helper();
        return *this;
    }
    this->_num *= oth._denum;
    this->_denum *= oth._denum;
    this->_num += oth._num * this->_denum;
    this->reduce_helper();
    return *this;
}

Rational& Rational::operator-=(const Rational& oth) {
    if (oth._denum == this->_denum) {
        this->_num -= oth._num;
        this->reduce_helper();
        return *this;
    }
    this->_num *= oth._denum;
    this->_denum *= oth._denum;
    this->_num -= oth._num * this->_denum;
    this->reduce_helper();
    return *this;
}

Rational& Rational::operator*=(const Rational& oth) {
    _num *= oth._num;
    _denum *= oth._denum;
    this->reduce_helper();
    return *this;
} 

Rational& Rational::operator/=(const Rational& oth) {
    if (oth._num == 0) {
        std::cout << "Your num cannot be 0" << std::exit;
    }
    _num *= oth._denum;
    _denum *= oth._num;
    this->reduce_helper();
    return *this;
}

Rational operator+(Rational rhs, const Rational& oth) {
    Rational tmp;
    if (oth._denum == rhs._denum) {
        tmp = Rational(rhs._num + oth._num, rhs._denum);
    } else {
        tmp = Rational((rhs._num * oth._denum) + (rhs._denum * oth._num), rhs._denum * oth._denum);
    }
    tmp.reduce_helper();
    return tmp;
}

Rational operator-(Rational rhs, const Rational& oth){
    if (oth._denum == rhs._denum) {
        Rational tmp (rhs._num - oth._num, rhs._denum);
        tmp.reduce_helper();
        return tmp;
    }
    Rational tmp ((rhs._num * oth._denum) - (rhs._denum * oth._num), rhs._denum * oth._denum);
    tmp.reduce_helper();
    return tmp;
}

Rational operator*(Rational rhs, const Rational& oth){
    Rational tmp ( rhs._num * oth._num, rhs._denum * oth._denum);
    tmp.reduce_helper();
    return tmp;
}

Rational operator/(Rational rhs, const Rational& oth) {
    if (oth._num == 0) {
        std::cout << "Your num cannot be 0" << std::exit;
    }
    Rational tmp ( rhs._num * oth._denum, rhs._denum * oth._num);
    tmp.reduce_helper();
    return tmp;
}

bool operator==(const Rational& lhs, const Rational& rhs) {
    int tmp = lhs._num / lhs._denum;
    int tmp2 = rhs._num / rhs._denum;
    return tmp == tmp2;
}

bool operator!=(const Rational& lhs, const Rational& rhs) {
    int tmp = lhs._num / lhs._denum;
    int tmp2 = rhs._num / rhs._denum;
    return tmp != tmp2;
}

bool operator<(const Rational& lhs, const Rational& rhs) {
    int tmp = lhs._num / lhs._denum;
    int tmp2 = rhs._num / rhs._denum;
    return tmp < tmp2;
}

bool operator>(const Rational& lhs, const Rational& rhs) {
    int tmp = lhs._num / lhs._denum;
    int tmp2 = rhs._num / rhs._denum;
    return tmp > tmp2;
}

bool operator<=(const Rational& lhs, const Rational& rhs) {
    int tmp = lhs._num / lhs._denum;
    int tmp2 = rhs._num / rhs._denum;
    return tmp <= tmp2;
}

bool operator>=(const Rational& lhs, const Rational& rhs) {
    int tmp = lhs._num / lhs._denum;
    int tmp2 = rhs._num / rhs._denum;
    return tmp >= tmp2;
}

std::istream& operator>>(std::istream& is, Rational& r){
    is >> r._num;
    is >> r._denum;
    return is;
}

std::ostream& operator<<(std::ostream& os, const Rational& r){
    os << "Rational" << r._num << "/" << r._denum << std::endl;
    return os;
}