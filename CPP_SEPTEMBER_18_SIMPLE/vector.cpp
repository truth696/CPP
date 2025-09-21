#include <iostream> 
#include <vector>

int sum (const std::vector<int>& arr) {
    int x =0;
    for (int i = 0; i < arr.size(); ++i) {
        x += arr[i];
    }
return x;
}

int main() {
    
    int size;

    std::cout << "Please input size for array ";
    std::cin >> size;
    
    std::vector<int> arr(size);

    std::cout << "Please input " << size << " number for array" << std::endl;
    
    for (int i = 0; i < size; ++i) {
        std::cout << i+1 << ") ";
        std::cin >> arr[i];
    } 
    
    int res = sum(arr);

    std::cout << "Your results " << sum(arr) << std::endl;
    
return 0;
}
     
