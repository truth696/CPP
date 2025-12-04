#include <string>
#include <iostream>


void nitialization_cardNumber() {
    unsigned long long copy = 1110011010101010;
    std::string temprary_card;
    std::string res;
    int i = 4;
    while (copy > 0) {
        while (i > 0){
            temprary_card.push_back((copy % 10) + '0');
            --i;
            copy /= 10;
        }
        i = 4; 
        if (copy > 0)temprary_card.push_back(' ');
    }
    for (int i = temprary_card.length(); i >= 0; --i) {
        res.push_back(temprary_card[i]);
    }

    std::cout << res << std::endl;
}

int main() {
    nitialization_cardNumber();
}