#include <iostream>
#include <cmath>
#include <limits>
#include <stdexcept>    


double SafeSqrt(double fnumber, bool* error) {
    double min = std::numeric_limits<double>::min();
    try{ 
        if (fnumber == min) throw std::underflow_error("Your number already is minimum");
        *error = false;
        return sqrt(fnumber);
    } catch(std::exception& e) {
        std::cout << e.what() << std::endl;
        *error = true;
    }
}

double SafePower(double fnumber, double snumber, bool* error) {
    double max = std::numeric_limits<double>::max();
    try {
        if (log(max) < snumber && (fnumber != 0 && fnumber != 1)) throw std::overflow_error("Your power is more then double max");
        if (fnumber == max && (fnumber != 0 && fnumber != 1)) throw std::overflow_error("Your number is already maximum");
        *error = false;
        return pow(fnumber, snumber);
    } catch (std::exception& e){
        std::cout << e.what() << std::endl;
        *error = true;
    }
}

double SafeLog(double fnumber, bool* error) {
    double min = std::numeric_limits<double>::min();
    try{
        if (fnumber == min) throw std::underflow_error("Your numver alreeady a minimum");
        return log(fnumber);
        *error = false;
    } catch(std::exception& e){
        std::cout << e.what() << std::endl;
        *error = true;
    }
}

double SafeAdd(double fnumber, double snumber, bool* error ) {
    double max = std::numeric_limits<double>::max();
    try {
        if (max == fnumber || max == snumber && (fnumber != 0 && snumber != 0)) throw std::overflow_error("Your number is more then double");
        if ((max - fnumber) < snumber) throw std::overflow_error("Your numbers sum is more then double max");
        *error = false;
        return fnumber + snumber;
    } catch (std::exception& e) {
        std::cout << e.what() << std::endl;
        *error = true;
    }
}

double SafeSub(double fnumber, double snumber, bool* error ) {
    double max = std::numeric_limits<double>::max();
    try {
        if (fnumber == max || snumber == max && (fnumber != 0 && snumber != 0)) throw std::underflow_error ("Your number is fewer then double min");
        if ((fnumber + max) < snumber) throw std::underflow_error("Your substinace is fewer then double min");
        *error = false;
        return fnumber - snumber;
    } catch (std::exception& e){
        std::cout << e.what() << std::endl;
        *error = true;
    }
}

double SafeMul(double fnumber, double snumber, bool* error ) {
    double max = std::numeric_limits<double>::max();
    try {
        if (max == fnumber || max == snumber && (fnumber != 0 && snumber != 0 && fnumber != 1 && snumber != 1)) throw std::overflow_error("Your number is more then double");
        if (max / snumber < fnumber) throw std::overflow_error("Your numbers product is more then double max");
        *error = false;
        return fnumber * snumber;
    } catch (std::exception& e) {
        std::cout << e.what() << std::endl;
        *error = true;
    }
}

double SafeDiv(double fnumber, double snumber, bool* error ) {
    double max = std::numeric_limits<double>::max();
    try {
        if (snumber == 0) throw std::domain_error("You can't divide by zero");
        if (max == fnumber || max == snumber && (fnumber != 0 && fnumber != 1 && snumber != 1)) throw std::underflow_error("Your number is fewer then double min");
        if (max / snumber < fnumber) throw std::underflow_error("Your numbers division is fewer then double min");
        *error = false;
        return fnumber / snumber;
    } catch (std::exception& e) {
        std::cout << e.what() << std::endl;
        *error = true;
    }
}

void CoutWithCast (double number, bool* error) {
    long long cpy = number;
    double check = number - cpy;
    if (number <= std::numeric_limits<long long>::max() && (!error) && (!check)) std::cout << "Your result: " << (long long)number << std::endl;
    else if (!*error)std::cout << "Your result: " << number << std::endl;
    else std::cout << "You gave a error" << std::endl;
    *error = false;
}

double MakeAction(char action, double fnumber, double snumber, bool* error){
    switch (action) {
            case '+':
                return SafeAdd(fnumber, snumber, error);
                break;
            case '-':
                return SafeSub(fnumber, snumber, error);
                break;
            case '*':
                return SafeMul(fnumber, snumber, error);
                break;
            case '/':
                return SafeDiv(fnumber, snumber, error);
                break;
            case 'L':
                return SafeLog(fnumber, error);
                break;
            case 'l':
                return SafeLog(fnumber, error);
                break;
            case 'p':
                return SafePower(fnumber, snumber, error);
                break;
            case 'P':
                return SafePower(fnumber, snumber, error);
                break;
            case 'S':
                return SafeSqrt(fnumber, error);
                break;
            case 's':
                return SafeSqrt(fnumber, error);
                break;

        }
}

char Interface(char action, double* fnumber, double* snumber){
    std::string check;
    std::cout << "Please input action" << std::endl;
    std::cout << "For exaple : +, -,  /,  *, log, power, sqrt" << std::endl;
    std::cout << "If you want quit inpu Q / q" << std::endl;
    std::cout << "> ";
    std::cin >> check;
    action = check[0];
    if (action == 'q' || action == 'Q') return action;
    while (action != '+' && action != '-' && action != '/' && action != '*' && action!= 'p' && action!= 'P' && action != 'l' && action!= 'L'&& action != 's' && action!= 'S' && action != 'q' && action != 'Q'){
        std::cout << "Please input correct action" << std::endl;
        std::cout << "For exaple : +, -,  /,  *, log, power, sqrt" << std::endl;
        std::cout << "> ";
        std::cin >> check;
        action = check[0];
    }
    std::cout << "Please input first number" << std::endl;
    std::cout << "> ";
    std::cin >> *fnumber;
    
    if (action == 'l' || action == 'L' || action == 'S' || action == 's') return action;
    std::cout << "Please input second number" << std::endl;
    std::cout << "> ";
    std::cin >> *snumber;
    
    return action;
}

bool continue_program(char action) {
    while ((action != 'N' && action != 'n') && (action != 'Y' && action != 'y') && (action != 'q' && action != 'Q')){
        std::cout << "Please input correct answer" << std::endl;
        std::cout << "For example: Yes / yes, No / no" << std::endl;
        getchar();
        std::cin >> action;
    }
    if (action == 'N' || action == 'n' || action == 'q' || action == 'Q') return false;
    return true;
}

void menu() {
    double fnumber = 0; 
    double snumber = 0;
    double res = 0;
    char action;
    bool error = 0;
    while (1) {
        action = Interface(action, &fnumber, &snumber);
        if (action == 'q' || action == 'Q') return;
        res = MakeAction(action, fnumber, snumber, &error);
        CoutWithCast(res, &error);
        // if (!continue_program(action)) return;
    }
}


int main() {
    menu();
}