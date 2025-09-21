#include <iostream>

void add_ref(int &a, int &b, int &res) {
    res = a + b;
}


int main() {
    int a = 0;
    int b = 0;
    int res = 0;
    
    std::cout << "Please input two number" << std::endl;
    
    std::cout << "1) ";
    std::cin >> a;
    
    std::cout << "2) ";
    std::cin  >> b;
    
    add_ref(a,b,res); 
    
    std::cout << "Your res : " << res << std::endl;
    
return 0;
}
     
