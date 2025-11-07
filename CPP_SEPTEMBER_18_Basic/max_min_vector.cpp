#include <iostream> 
#include <vector>

int max (const std::vector <int>& arr) {
    int max = arr[0];
    for (int i = 0; i < arr.size(); ++i) {
        if (max < arr[i]) {
            max = arr[i];
        }
    }
return max;
}

int min (const std::vector <int>& arr) {
    int min = arr[0];
    for (int i = 0; i < arr.size();++i) {
        if (min > arr[i]) {
            min = arr[i];
        }
    }
return min;
}



int main () {
    int size = 0;   
    
    std::cout << "Please input size for arr" << std::endl;
    std::cin >> size;
     
    std::vector <int> arr(size);
    
    std::cout << "Please input " << size << " numbers for array" << std::endl;
    for (int i = 0; i < size; ++i) {
        std::cout << i+1 << ") ";
        std::cin >> arr[i];
    }
    
    int max_res = max(arr);
    int min_res = min(arr);
    
    std::cout << "Your max: " << max_res << std::endl;
    std::cout << "Your min: " << min_res << std::endl;

return 0;
}
