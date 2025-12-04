#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>


class BankAccount;

class BankException: std::exception {
protected:
    std::string msg;
public:
    BankException(std::string msg = "Unknow Error") : msg(msg) {}
    const char* what() const noexcept override {
        return &msg[0];
    }
};

class Bank{
protected:
    std::vector<BankAccount* > accounts;
public:
    inline static std::string initialization_cardNumber();
    void transfer(std::string fCardNumber, std::string sCardNumber, double count_of_money);
    void createCheking(std::string name, double money);
    void createSaving(std::string name, double money);
    // double operator[](std::string CardNumber);
};

class AccoutNotFoud: public BankException{
public:
    AccoutNotFoud(std::string msg): BankException(msg) {}
};

class InsufficiantFunds: public BankException {
public:
    InsufficiantFunds(std::string msg): BankException(msg) {}
};

class NegativeAmount: public BankException{
public:
    NegativeAmount(std::string msg): BankException(msg) {}
};


class BankAccount{
protected:
    std::string cardNumber;
    double balance;
    std::string Name;
public:
    virtual ~BankAccount() = default;
    virtual void withdraw(double number);
    virtual void deposit(double number);
    inline double getBalance() const noexcept { return balance; } 
    inline std::string getCardNumber() const noexcept { return cardNumber; } 
    virtual void display() const = 0;
    BankAccount(std::string name, double money = 1000) : Name(name), balance(money), cardNumber(Bank::initialization_cardNumber()) {}
};

class CheckingAccount: public BankAccount{
private:
    double overdraft;
public:
    CheckingAccount(std::string name = "Unknow", double money = 1000) : BankAccount(name, money) , overdraft(1000) { }
    virtual void withdraw(double number) override;
    virtual void display() const override;
    inline double getOverDraft() const noexcept { return overdraft; }
};

class SavingsAccount: public BankAccount {
private:
    double rate;
public:
    virtual void withdraw(double number) override;
    virtual void deposit(double number) override;
    virtual void display() const override;
    SavingsAccount(std::string name = "Unknow", double money = 1000) : BankAccount(name, money) , rate(2) { }
};

