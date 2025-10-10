#include <iostream>
#include <numeric>


class Rational {
    private:
        int _num;
        int _denum;
        void reduce_helper() { 
            int tmp = std::gcd(this->_num, this->_denum);
            this->_num /= tmp;
            this->_denum /= tmp;
        }
    public:
        //Default constructor
        Rational () : _num(0), _denum(1) {}
        //Construcot with Paramters 
        Rational (int num) : _num(num) , _denum(0) {}
        Rational (int num, int denum);
        //Move/Copy constructor
        Rational (const Rational& oth) : _num(oth._num), _denum (oth._denum) {};
        Rational (Rational&& oth) : _num(oth._num), _denum (oth._denum) {};
        //Assign operator
        Rational& operator= (Rational&& oth);
        Rational& operator=(const Rational& oth);
        //Destructor
        ~Rational () = default;
        //Unar operator
        Rational operator+() const;
        Rational  operator-() const;
        bool operator !() const;
        Rational& operator++();
        Rational& operator--();
        Rational operator++(int);
        Rational operator--(int);
        //Binary arifemtic operator
        Rational& operator+=(const Rational& oth);
        Rational& operator-=(const Rational& oth);
        Rational& operator*=(const Rational& oth);
        Rational& operator/=(const Rational& oth);
        //Binary arithmetic operators NoMemFun
        friend Rational operator+(Rational rhs, const Rational& oth);
        friend Rational operator-(Rational rhs, const Rational& oth);
        friend Rational operator*(Rational rhs, const Rational& oth);
        friend Rational operator/(Rational rhs, const Rational& oth);
        //Comparison operators operators NoMemFun
        friend bool operator==(const Rational& lhs, const Rational& rhs); 
        friend bool operator!=(const Rational& lhs, const Rational& rhs); 
        friend bool operator<(const Rational& lhs, const Rational& rhs); 
        friend bool operator>(const Rational& lhs, const Rational& rhs); 
        friend bool operator<=(const Rational& lhs, const Rational& rhs); 
        friend bool operator>=(const Rational& lhs, const Rational& rhs);
        //Stream operators NoMemFun
        friend std::istream& operator>>(std::istream& is, Rational& r);
        friend std::ostream& operator<<(std::ostream& os, const Rational& r);
        //Getter MemFun
        int numerator() const noexcept { return _num; }
        int denominator() const noexcept { return _denum; }
        // Optional conversions MemFun
        explicit operator double() const {
            return this->_num / this->_denum;
        }
};

