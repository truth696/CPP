#include <iostream>
#include <string>
#include <cstring>

void swap (std::string &a){
    int j = a.length() - 1;
    for (int i = 0; i < j; ++i){
        char tmp = a[i];
        a[i] = a[j];
        a[j] = tmp;
        --j;
    }
}

int main() {
    
    std::string sentence;
    
    std::cout << "Please input your sentence" << std::endl;
    std::cin >> sentence;
    
    std::cout << "Before - " << sentence << std::endl;
    swap(sentence);
    std::cout << "After _ " << sentence << std::endl;
    
return 0;
} 
