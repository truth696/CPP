#include <string>
#include <iostream>

class Drink;
class Order;
class Customer;
class Barista;

class CoffeeShop {
private:
    std::string shopName;
    std::vector<Drink*> menu;
    std::vector<Barista*> baristas;
    std::vector<Customer*> queue;  

public:
    //for gpt
    const std::vector<Drink*>& getMenu() const { return menu; }
    const std::vector<Barista*>& getBaristas() const { return baristas; }
    const std::vector<Customer*>& getQueue() const { return queue; }
    CoffeeShop() = default;
    CoffeeShop(const std::string& name) : shopName(name) {}
    
     void setName(const std::string& newName);
     void addDrink(Drink* drink);
    
    void removeDrink(const std::string& drinkName);
    void showMenu() const;
    
     void hireBarista(Barista* _barista);
     void fireBarista(Barista* _barista);
     void showBaristas() const; 
    
    void addCustomerToQueue(Customer* customer);
    void serveNextCustomer();
    
    void showQueue() const;
    void constructMenu();
    
    void displayShopInfo() const;
    
     std::string getName () const;
};

class Customer {
private:
    std::string name;
    double balance;
    Order* currentOrder; 

public:
    Customer() = default;
    Customer(const std::string& _name, double _balance) : name(_name), balance(_balance){}


     std::string getName() const;
     double getBalance() const;
     void setBalance(double newBalance);

    void placeOrder(Order* order);
    void payOrder(Order* order);
    void viewOrder() const; 

    void display() const;
    Order* getOrder();
};
//finish
class Order {
private:
    int orderId;
    std::vector<Drink> drinks;
    double totalPrice;
    bool isPrepared;
    bool isPaid;

public:

    Order() = default;

    Order(int id) : orderId(id), totalPrice(0), isPrepared(false), isPaid(false) {}

     int getOrderId() const;
     double getTotalPrice() const;
     bool getIsPrepared() const;
     bool getIsPaid() const;


     void addDrink(const Drink& drink);
    void removeDrink(int index);
    void calculateTotalPrice();


     void markPrepared();
     void markPaid();

    void displayOrder() const;
    
};
//finish 
class Drink {
public:
    enum class Size { Small, Medium, Big };

private:
    std::string name;
    Size volume;
    double price;

public:

    Drink() = default;
    Drink(const std::string& _name, Size _volume, double _price) : name (_name), volume(_volume), price(_price) {}

    std::string getName() const ;
    Size getVolume() const ;
    double getPrice() const ;

    void setName(const std::string& newName);
    void setVolume(Size newVolume);
    void setPrice(double newPrice);

    void display() const;
};
//finish
class Barista {
private:
    std::string name;

public:

    Barista() = default;
    Barista(const std::string& _name) : name(_name) {}

    std::string getName() const;
    void setName(const std::string& newName) ;

    void prepareOrder(Order* order);
    void greetCustomer() const;
};
//finish

