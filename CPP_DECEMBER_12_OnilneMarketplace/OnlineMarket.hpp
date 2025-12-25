#include <iostream>
#include "OnlineMarketProduct.hpp"


class Product{
protected:
    Categories main_type;
    Categories specialization_type;
    int id;
    double price;
    std::string seller_username;
    std::string description;
public:
    void display() const noexcept;
    inline Categories GetMainType() const noexcept { return main_type; }
    inline Categories GetSpecType() const noexcept { return specialization_type; }
    inline int GetId() const noexcept { return id; }
    inline double GetPrice() const noexcept {return price;}
    inline std::string GetDescription() const noexcept { return description; }
    Product(const Categories& main, const Categories& spec, double price, const std::string& name, const std::string& description) : main_type(main), specialization_type(spec), price(price), seller_username(name), description(description) { id = ++product_id;}
};

class Platform{
protected:
    std::vector<Product*> products;

public:
    virtual void AddProduct(Product* product) noexcept;
    virtual void RemoveProduct(Product* product);
    virtual void display() const noexcept;
    friend void menu();
};

class User : public Platform{
    double balance;
    std::string username;
    Role role;
    Country country;
    int id;
    Order* order;
    std::vector<Order*> orders_assem;
public:
    User(std::string username = "Unknow", const Role role, const Country country = Country::Armenia, double balance) noexcept: username(username), role(role), country(country), balance(balance){ 
        if (role == Role::Customer) id = ++customer_id;
        else id = ++seller_id;
    }
    virtual void AddProduct(Product* product) noexcept override ; 
    virtual void RemoveProduct(Product* product) noexcept override;
    void newOrder() noexcept;
    void display() const noexcept override;
    void pay() noexcept;
    inline double getBalance() const noexcept { return balance; }
    inline int getid() const noexcept {return id;}
    inline Role getrole() const noexcept { return role;}
};

class Order{
    std::vector <Product* > basket;
    double price;
    std::string customer_username;
    std::string seller_username;
    bool payed;
    bool assembl;
    Status status;
    Country where;
    void ProggresStatus() noexcept;
public:
    Order(const Country& where = Country::Armenia) : where(where), status(Status::Assembling), payed(false) { };
    void display() noexcept;
    void addProduct(Product* product);
    void calculate();
    Country getCountry() const noexcept { return where; }
    void checkStatus()  noexcept;
    friend class User;
};