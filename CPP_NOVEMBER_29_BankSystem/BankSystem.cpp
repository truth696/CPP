#include "BankSystem.hpp"

static unsigned long long card_number = 44039405928593726;


void BankAccount::withdraw(double number) {
    try{
        if(balance <= 0) throw InsufficiantFunds("You haven't enough money");
        if (number < 0) throw NegativeAmount("Your amount is negative");
        balance -= number;
    } catch(BankException& e){
        std::cout << e.what() << std::endl;
    }
}
void BankAccount::deposit(double number) {
    try{
        if (number < 0) throw NegativeAmount("Your amount of money is negative");  
        balance += number ;
    } catch (BankException& e){
        std::cout << e.what() << std::endl; 
    }
}

inline std::string Bank::initialization_cardNumber() {
    unsigned long long copy = card_number;
    std::string temprary_card;
    std::string res;
    int i = 4;
    while (copy > 0) {
        while (i-- > 0){
            temprary_card.push_back((copy % 10) + '0');
            copy /= 10;
        }
        i = 4; 
        if (copy > 0)temprary_card.push_back(' ');
    }
    for (int i = temprary_card.length(); i >= 0; --i) {
        res.push_back(temprary_card[i]);
    }
    ++card_number;
    return res;
}

void Bank::createCheking (std::string name, double money) {
    try {
        if(money < 0) throw NegativeAmount("Your amount of money is negative");
        CheckingAccount *ptr = new CheckingAccount(name, money);
        accounts.push_back(ptr);
    } catch(BankException& e){
        std::cout << e.what() << std::endl;
    }
}


void Bank::createSaving(std::string name, double money) {
    try {
        if(money < 0) throw NegativeAmount("Your amount of money is negative");
        SavingsAccount *ptr = new SavingsAccount(name, money);
        accounts.push_back(ptr);
    } catch(BankException& e){
        std::cout << e.what() << std::endl;
    }
}


void Bank::transfer(std::string fCardNumber, std::string sCardNumber, double count_of_money) {
    try{
        if (count_of_money < 0)throw NegativeAmount ("Your number is negative");
        int i = 0;
        int j = 0;
        std::string action;
        bool fhave = false;  
        bool shave = false;
        for (i = 0; i < accounts.size(); ++i) if(accounts[i]->getCardNumber() == fCardNumber) fhave = true;
        for (j = 0; j < accounts.size(); ++j) if(accounts[i]->getCardNumber() == sCardNumber) shave = true;
        if (fhave && shave){
            try{ 
                if(accounts[i]->getBalance() < count_of_money) throw InsufficiantFunds("You haven't enough money");
                accounts[j]->deposit(count_of_money);
                accounts[i]->withdraw(count_of_money);
                std::cout << "Successful" << std::endl;
            } catch (BankException& e) {
                std::cout << e.what() << std::endl;
                std::cout << "You haven't enough money, maybe do you want borrow money from a bank?" << std::endl;
                std::cout << "For example: Yes, No" << std::endl;
                std::cin >> action;
                while(action != "yes" && action != "Yes" && action != "N" && action != "no"){
                    std::cout << "Please input correct answer" << std::endl;
                    std::cout << "For example: Yes, No" << std::endl;
                    std::cin >> action;
                }
                try{
                    if (action == "no" || action == "No") throw InsufficiantFunds("You haven't enough funds");
                    if (count_of_money > accounts[i]->getBalance() + 1000 ) throw InsufficiantFunds("You haven't enough money");
                    accounts[i]->withdraw(count_of_money);
                } catch (BankException& e){
                    std::cout << e.what() << std::endl; 
                }
            } 
        }  else {
            try {
                if (!fhave) throw AccoutNotFoud ("We haven't card with this number");
            } catch (BankException& e) {
                std::cout << e.what() << fCardNumber << std::endl;
            }
            try {
                if (!shave) throw AccoutNotFoud ("We haven't card with this number");
            } catch (BankException& e) {
                std::cout << e.what() << sCardNumber << std::endl;
            }
        }
    } catch (BankException& e){
        std::cout << e.what() << std::endl;
    }
}

void CheckingAccount::withdraw (double number) {
    try {
        if (number < 0) throw NegativeAmount("Your number is negative");
        balance -= number;
        overdraft -= number;
    } catch (BankException& e){
        std::cout << e.what() << std::endl;
    }
}


void CheckingAccount::display() const{
    std::cout << "Your balance > " << balance << std::endl;
    std::cout << "Your overdraft > " << overdraft << std::endl;
    std::cout << "Your card number > " << cardNumber << std::endl;
}

void SavingsAccount::display() const{
    std::cout << "Your balance > " << balance << std::endl;
    std::cout << "Your rate  > " << rate << std::endl;
    std::cout << "Your card number > " << cardNumber << std::endl;
}

void SavingsAccount::withdraw(double number) {
    try{
        if(balance <= 0) throw InsufficiantFunds("You haven't enough money");
        if (number < 0) throw NegativeAmount("Your amount is negative");
        balance -= number;
    } catch(BankException& e){
        std::cout << e.what() << std::endl;
    }
}

void SavingsAccount::deposit(double number) {
    try{
        if (number < 0) NegativeAmount("Your number is negative");
        balance += number + (number * rate / 100);
    } catch(BankException& e) {
        std::cout << e.what() << std::endl;
    }

}

