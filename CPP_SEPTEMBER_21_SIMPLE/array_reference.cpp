#include <iostream>
#include <vector>

int main() {
    int size = 0;
    int index = 0;

    std::cout << "Please input size : " << std::endl;
    std::cin >> size;

    std::vector<int> arr(size);
    
    std::cout << "Please input index for number: " << std::endl;
    std::cin >> index;

    for (;index > size || index < 0;) {
        std::cout << "Please inpput correct index" << std::endl;
        std::cin >> index;
    }
    
    int &r = arr[index];
    int change = 0;
    
    std::cout << "PLease input number for change" << std::endl;
    std::cin >> change;
    
     std::cout << "This is your array before change : ";
     for (int i = 0; i < size; ++i) {
         std::cout << arr[i] << " " ;
     }
    
    r = change;
    std::cout << "\n";
    std::cout << "This is your array after change : ";
    for (int i = 0; i < size; ++i) {
        std::cout << arr[i] << " " ;
    } 
    
return 0;
}
