#include "Coffee_Shop.hpp"

void Customer::setBalance(double newBalance) {
    if (newBalance >= 0) balance = newBalance;
    else std::cout << "You cannot have negative balance" << std::endl;
}

void Drink::display() const {
    std::cout << "Drink name: " << name << std::endl;
    std::cout << "Drink volume: ";
    switch (volume) {
        case Size::Small:
            std::cout << "Small" << std::endl;
            break;
        case Size::Medium:
            std::cout << "Medium" << std::endl;
            break;
        case Size::Big:
            std::cout << "Big" << std::endl;
            break;
    }
    std::cout << "Drink price: " << price << std::endl;
}

void Order::removeDrink(int index) {
    if (index < 0 || index >= drinks.size()) {
        std::cout << "Please input correct index";
        return;
    }
    for (int i = index; i < drinks.size() - 1; ++i) drinks[i] = drinks[i + 1];
    drinks.pop_back();
    calculateTotalPrice();
}   

void Customer::payOrder(Order* order){
    if (!order) {
        std::cout << "No orer to pay" << std::endl;
        return ;
    }
    order->calculateTotalPrice();
    if (balance < order->getTotalPrice() ) {
        std::cout << "You don't have enough money";
        return;
    }
    
    balance -= order->getTotalPrice(); 
    order->markPaid();
    std::cout << "Succesful " << "Your balance: " << balance << std::endl;
}

void Customer::viewOrder() const {
    if (currentOrder) currentOrder->displayOrder(); 
    else std::cout << "You haven't order" << std::endl; 
}

void Order::displayOrder() const {
    std::cout << "Drinks :" << std::endl;
    for (int i = 0; i < drinks.size(); ++i) drinks[i].display();
    std::cout << "Total price" << totalPrice << std::endl;
    if (!isPrepared) std::cout << "Your order while don't preprare" << std::endl;
    if (!isPaid) std::cout << "YOur order don't paid";
}

void Customer::placeOrder(Order* order) {
    // std::cout << "Hello. Please choose:" << std::endl;
    // int choose = 1;
    // while (choose != 0) {
    //     std::cout << "Add Drink - 1" << std::endl;
    //     std::cout << "Remove Drink - 2" << std::endl;
    //     std::cout << "Continue / Exit - 0" << std::endl;
    //     std::cin >> choose;

    //     if (choose == 0) break;
        
    //     switch (choose) {
    //         case 1: {
    //             std::string _name;
    //             double price;
    //             Drink::Size size = Drink::Size::Small;

    //             std::cout << "Please enter your drink name: " << std::endl;
    //             std::cin >> _name;

    //             std::cout << "Please input your drink price: " << std::endl;
    //             std::cin >> price;

    //             std::cout << "Please choose size for your drink:\nSmall - 0\nMedium - 1\nBig - 2\n";
    //             int sizeChoose = 0;
    //             std::cin >> sizeChoose;

    //             switch (sizeChoose) {
    //                 case 0: size = Drink::Size::Small; 
    //                 break;
                    
    //                 case 1: size = Drink::Size::Medium; 
    //                 break;
                    
    //                 case 2: size = Drink::Size::Big; 
    //                 break;
                    
    //                 default:
    //                     std::cout << "Incorrect number :( Default size is Small" << std::endl;
    //                     size = Drink::Size::Small;
    //             }
    //             Drink drink(_name, size, price);
    //             order->addDrink(drink);
    //             break;
    //         }
    //         case 2: {
    //             int index = 0;
    //             std::cout << "Please input index" << std::endl;
    //             std::cin >> index;
    //             order->removeDrink(index);
    //             break;
    //         }
    //         default:
    //             std::cout << "Unknown option\n";
    //             break;
    //     }

    //     currentOrder = order;
    // }
    currentOrder = order;
}

void CoffeeShop::removeDrink(const std::string& drinkName) {
    if (menu.empty()) {
        std::cout << "Menu is empty" << std::endl;
        return;
    }
    for (int i = 0; i < menu.size(); ++i) {
        if (drinkName == menu[i]->getName()) {
            delete menu[i];
            menu.erase(menu.begin() + i);
            return;
        }
    }
    std::cout << "We haven't drink with this name, nigger" << std::endl;
}

void CoffeeShop::serveNextCustomer () {
    if (queue.empty()) {
        std::cout << "Queue is empty" << std::endl;
        return;
    }
    if (baristas.empty()) {
        std::cout << "We haven't baristas sorry, nigger" << std::endl;
        return;
    }

    if (queue[0] && queue[0]->getOrder() && baristas[0]) {
        baristas[0]->prepareOrder(queue[0]->getOrder());
    } else std::cout << "Customer haven't order" << std::endl;
    queue.erase(queue.begin());
}

void CoffeeShop::constructMenu() {
    addDrink (new Drink ("Espresso", Drink::Size::Small, 3.0));
    addDrink (new Drink ("Cappuccino", Drink::Size::Medium, 4.0));
    addDrink (new Drink ("Green Tea", Drink::Size::Medium, 3.0));
    
} 

void CoffeeShop::displayShopInfo() const {
    std::cout << "Coffee shop name: " << getName() << std::endl;
    std::cout << "Our menu: " << std::endl;
    for (int i = 0; i < menu.size(); ++i) menu[i]->display();
    for (int i = 0; i < queue.size(); ++i) std::cout << queue[i]->getName() << std::endl;
}

void Order::calculateTotalPrice (){
    totalPrice = 0.0;
    for (int i = 0; i < drinks.size(); ++i) totalPrice += drinks[i].getPrice();
}

void CoffeeShop::setName(const std::string& newName) { shopName = newName; }

void CoffeeShop::addDrink(Drink* drink) {menu.push_back(drink);}

void CoffeeShop::showMenu() const {
    if (menu.empty()) {
        std::cout << "Menu is empty" << std::endl;
        return;
    }
    for (int i = 0; i < menu.size(); ++i) menu[i]->display();
}

void CoffeeShop::hireBarista(Barista* _barista) { baristas.push_back(_barista); }

void CoffeeShop::fireBarista(Barista* _barista) { 
    for (int i = 0; i < baristas.size(); ++i){
        if (baristas[i]->getName() == _barista->getName()){
            delete baristas[i];
            baristas.erase(baristas.begin() + i);
            return;
        }
    }
    std::cout << "Barista not found" << std::endl;
}

void CoffeeShop::showBaristas() const { 
    if (baristas.empty()) {
        std::cout << "We haven't baristas" << std::endl;
        return;
    }
    for (int i = 0; i < baristas.size(); ++i) std::cout << baristas[i]->getName() << std::endl; }

void CoffeeShop::addCustomerToQueue(Customer* customer) { queue.push_back(customer); }

void CoffeeShop::showQueue() const {
    if (queue.empty()) {
        std::cout << "We haven't queue" << std::endl;
        return;
    } 
    for (int i = 0; i < queue.size(); ++i) queue[i]->display(); }

std::string CoffeeShop::getName() const { return shopName; }


std::string Customer::getName() const { return name; }

double Customer::getBalance() const { return balance; }

void Customer::display() const { 
    if(!currentOrder) {
        std::cout << "You haven't order" << std::endl;
        return;
    }
    currentOrder->displayOrder(); }

Order* Customer::getOrder() { return currentOrder; }


int Order::getOrderId() const { return orderId; }

double Order::getTotalPrice() const { return totalPrice; }

bool Order::getIsPrepared() const { return isPrepared; }

bool Order::getIsPaid() const { return isPaid; }

void Order::addDrink(const Drink& drink) {
    drinks.push_back(drink);
    calculateTotalPrice();
}

void Order::markPrepared() { isPrepared = true; }

void Order::markPaid() { isPaid = true; }

std::string Drink::getName() const { return name; }

Drink::Size Drink::getVolume() const { return volume; }

double Drink::getPrice() const { return price; }

void Drink::setName(const std::string& newName) { name = newName; }

void Drink::setVolume(Size newVolume) { volume = newVolume; }

void Drink::setPrice(double newPrice) { price = newPrice; }

std::string Barista::getName() const { return name; }

void Barista::setName(const std::string& newName) { name = newName; }

void Barista::prepareOrder(Order* order) {
    if (!order) {
        std::cout << "No order to prepare" << std::endl;
        return;
    }
    if (order->getIsPrepared()) std::cout << "Your order was prepared" << std::endl;
    else order->markPrepared();
}

void Barista::greetCustomer() const {
    std::cout << "Hello dear customer!" << std::endl;
}