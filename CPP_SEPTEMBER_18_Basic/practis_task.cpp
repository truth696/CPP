#include <iostream>
#include <vector>


int main () {
    int res_max;
    int res_min;
    int size = 0;
    
    std::cout << "Please input number for size " << std::endl;
    std::cin >> size;

    std::vector <int> arr (size);

    std::cout << "Please input " << size << " numbers for array" << std::endl;
    for (int i = 0; i < size; ++i) {
        std::cout << i+1 << ") ";
        std::cin >> arr[i];
    }

    int max = arr[0];
    int min = arr[0];
    
    for (int i = 0; i < size; ++i) {
        if (max < arr[i]) max = arr[i];
        if (min > arr[i]) min = arr[i];
    }
    
    std::cout << "Your max : " << max << std::endl;
    std::cout << "Your min : " << min << std::endl;
    
return 0;
}
