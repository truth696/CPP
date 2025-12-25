#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include "OnlineMarket.hpp"

std::string tostringcountry(Country tmp) {
    switch (tmp) {
        case Country::Armenia : return "Armenia";
        case Country::Russia : return "Russia";
        case Country::France : return "France";
        case Country::Italy : return "Italy";
        case Country::Spain : return "Spain";
        case Country::Georgia : return "Georgia";
    }
}

std::string tostring(Categories tmp) noexcept{
    switch (tmp){
        case Categories::Accessories : return "Accessories";
        case Categories::Auto_parts : return "Auto parts";
        case Categories::Books : return "Books";
        case Categories::Clothes : return "Clothes";
        case Categories::Cosmetic : return "Cosmetic";
        case Categories::Electronics : return "Electronics";
        case Categories::Entertainment : return "Entertainment";
        case Categories::Household_items : return "Household items";
        case Categories::Jewelry : return "Jewelry";
        case Categories::Meal : return "Meal";
        case Categories::Medicines : return "Medicines";
        case Categories::Optics : return "Optics";
        case Categories::Perfume : return "Perfume";
        case Categories::Self_care : return "Self care";
        case Categories::Watch : return "Watch";
        case Categories::Men_watches : return "Men watches";
        case Categories::Women_watches : return "Women watches";
        case Categories::Man_Deodorant : return "Man Deodorant";
        case Categories::Woman_Deodorant : return "Woman Deodorant";
        case Categories::Shampoo : return "Shampoo";
        case Categories::Tweezers : return "Tweezers";
        case Categories::Razor : return "Razor";
        case Categories::Man_Perfume : return "Man Perfume";
        case Categories::Woman_Perfume : return "Woman Perfume";
        case Categories::Glasses : return "Glasses";
        case Categories::Lenses : return "Lenses";
        case Categories::Frames : return "Frames";
        case Categories::Pills : return "Pills";
        case Categories::Syrups : return "Syrups";
        case Categories::Powders : return "Powders";
        case Categories::Candies : return "Candies";
        case Categories::Chips : return "Chips";
        case Categories::Culinary_product : return "Culinary product";
        case Categories::Fruits : return "Fruitsoduct";
        case Categories::Vegetables : return "Vegetables";
        case Categories::Rings : return "Rings";
        case Categories::Necklace : return "Necklace";
        case Categories::Earrings : return "Earrings";
        case Categories::Washing_machine : return "Washing machine";
        case Categories::Fridge : return "Fridge";
        case Categories::Vacuum_cleaner : return "Vacuum_cleaner";
        case Categories::Set_of_forks_and_spoons : return "Set of forks and spoons";
        case Categories::Mugs : return "Mugs";
        case Categories::Firecrackers : return "Firecrackers";
        case Categories::Toys : return "Toys";
        case Categories::Phones : return "Phones";
        case Categories::Laptop : return "Laptop";
        case Categories::TV : return "TV";
        case Categories::Speaker : return "Speaker";
        case Categories::Lipstick : return "Lipstick";
        case Categories::Mascara : return "Mascara";
        case Categories::Pencil : return "Pencil";
        case Categories::Man_tops : return "Man tops";
        case Categories::Woman_tops : return "Woman tops";
        case Categories::Kids_tops : return "Kids tops";
        case Categories::Man_pants : return "Man pants";
        case Categories::Woman_pants : return "Woman pants";
        case Categories::Kids_pants : return "Kids pants";
        case Categories::Man_bags : return "Man bags";
        case Categories::Woman_bags : return "Woman bags";
        case Categories::Kids_bags : return "Kids bags";
        case Categories::Man_shoes : return "Man shoes";
        case Categories::Woman_shoes : return "Woman shoes";
        case Categories::Kids_shoes : return "Kids shoes";
        case Categories::Plot_points : return "Plot_points";
        case Categories::Comics : return "Comics";
        case Categories::Spare_parts : return "Spare parts";
        case Categories::Consumables : return "Consumables";
        case Categories::Phone_cases : return "Phone cases";
        case Categories::Laptop_cases : return "Laptop cases";
        case Categories::Phone_Chargers : return "Phone Chargers";
        case Categories::Laptop_Chargers : return "Laptop Chargers";
        case Categories::Phone_Coasters : return "Phone Coasters";
        case Categories::Laptop_Coasters : return "Laptop Coasters";
    }
} 

void Product::display() const noexcept {
    std::cout << "Username of seller > " << this->seller_username << " | "<< "Main type > " << tostring(main_type) << " | " << "Spectialization type of product > " << tostring(this->specialization_type) << " | " << "Product's id > " << this->id << " | " << "Product's price > " << this->price <<  std::endl;
}

void Order::ProggresStatus() noexcept {
    try{
        if (status == Status::Delivered) throw std::overflow_error("Your order already deliverd");
        else if (status == Status::Assembling) status = Status::On_the_way;
        else if (status == Status::On_the_way) status = Status::Delivered;
        if (status == Status::On_the_way) std::cout << "Your status > On the way" << std::endl;
        else std::cout << "Your status > Delivered" << std::endl;
    } catch(std::exception& e) {
        std::cout << e.what() << std::endl;
    }
}

void Platform::AddProduct(Product* product) noexcept{
    if (product) products.push_back(product);
} 

void Platform::RemoveProduct(Product* product) noexcept{
    try{
        for (int i{}; i < products.size(); ++i){
            if (products[i]->GetId() == product_id) {
                products.erase(products.begin() + i);
                std::cout << "Your product was successfully deleted" << std::endl;
                return;
            }
        }
        throw std::invalid_argument ("We haven't product in list");
    } catch (std::exception& e) {
        std::cout << e.what() << std::endl;
    }
    
}

void User::AddProduct(Product* product) noexcept{
    if (role == Role::Seller && product) products.push_back(product);
    if (role == Role::Customer && product) {
        for(int i{}; i < products.size(); ++i){
            if (products[i]->GetId() == product->GetId()) {
                order->basket.push_back(product);
                products.erase(products.begin() + i);
            return;
            } 
        }
    }
}

void User::RemoveProduct(Product* product) noexcept{
    try{
        if (order->basket.empty()) throw std::invalid_argument("You're basket are empty");
            for(int i{}; i < order->basket.size(); ++i){
                if (product->GetId() == order->basket[i]->GetId()) {
                    if (!order->assembl)order->basket.erase(order->basket.begin() + i);
                    else throw std::invalid_argument("Please create new order, beacause this already ont the way");
                    if (role == Role::Customer) products.push_back(product);
                    order->calculate();
                    return;
                } 
            }
        throw std::invalid_argument("You haven't this product in your basket");
    }catch (std::exception& e) {
        std::cout << e.what() << std::endl;
    }
}

void Order::calculate() {
    price = 0;
    for(int i{}; i < basket.size(); ++i) price += basket[i]->GetPrice();
}

void Order::addProduct(Product* ptr) noexcept {
    if (ptr) basket.push_back(ptr);
    calculate();
}

void Order::display() noexcept {
    try{
        if (basket.empty()) throw std::underflow_error("You're basket are empty");
        for (int i{}; i < basket.size(); ++i) basket[i]->display();
        std::cout << "Where product delivery" << tostringcountry(where) << std::endl;
        calculate();
        std::cout << "Price for all products > " << price << std::endl;
        std::cout << "Count of Products > " << basket.size() << std::endl;
    } catch(std::exception& e) {
        std::cout << e.what() << std::endl;
    }
}

void Order::checkStatus()  noexcept{
    this->ProggresStatus();
}

void User::pay() noexcept{
    try{
        if(balance < order->price) throw std::underflow_error("You haven't enough moeney");
        balance -= order->price;
        order->payed = true;
        std::cout << "Your order is on the way" << std::endl;
        order->ProggresStatus();
        orders_assem.push_back(order);
        
    }catch(std::exception& e){
        std::cout << e.what() << std::endl;;
    }
}

void User::display() const noexcept {
    for (int i{}; i < order->basket.size(); ++i) {
        std::cout << "Your Basket" << i+1 << std::endl;
        if(!orders_assem[i]->assembl) display();
        std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
    }
    for (int i{}; i < orders_assem.size(); ++i) {
        std::cout << "Your Orders on the way" << i+1 << std::endl;
        if(orders_assem[i]->assembl) display();
        std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
    }
    std::cout << "Order's count that on the way > " << orders_assem.size() << std::endl;

}


void Platform::display() const noexcept {
    if (products.empty()) {
        std::cout << "Market is empty" << std::endl;
        return;
    }
    for (Product* ptr : products) ptr->display();
}



void User::newOrder() noexcept{}

void menu() {
    int action = -1;
    std::string username;
    double balance = 0;
    Role role;
    int country;
    Platform plt;
    plt.products.push_back(&Product(Categories::Electronics, Categories::Phones, 1200, "iPhone 17 Pro Max", "1TB, Black, SIM & ESIM"));
    plt.products.push_back(&Product(Categories::Electronics, Categories::Laptop, 1450, "MacBook Pro", "512GB, Black, 16GB DRAM, 120hz"));
    plt.products.push_back(&Product(Categories::Electronics, Categories::Laptop, 1050, "MacBook Air", "256GB, Black, 8GB DRAM, 60hz"));
    plt.products.push_back(&Product(Categories::Books, Categories::Comics, 10, "Spider - Man No Way Home", "After Peter's exposure, magic destroys the multiverse: three Spider-Men save the villains, Mae dies, and the world forgets Peter at the cost of sacrifice, love, and loneliness."));
    plt.products.push_back(&Product(Categories::Household_items, Categories::Washing_machine, 450, "Bosch WLS2846SME", "Maximum load for washing: 8 kg Maximum spin speed: 1400 rpm Overall dimensions (HxWxD): 85 x 59.5 x 47 cm Weight: 62.6 kg"));
    while(true) {
        std::cout << std::setw(70) << "---- OnlineMarket ----" << std::endl;   
        std::cout << std::setw(60) << "Please choose action"<< std::endl;;
        std::cout << std::setw(65) <<"[0] Continue as Custormer" << std::endl;;
        std::cout << std::setw(62) <<"[1] Continue as Seller" << std::endl;;
        std::cout << std::setw(48) <<"[2] Quit" << std::endl;;
        std::cout << std::setw(42) << "> ";
        std::cin >> action;
        while (action != 1 && action != 0 && action != 2){
            std::cout << std::setw(60) << "Please input correct number" << std::endl;
            std::cout << std::setw(65) <<"[0] Continue as Custormer" << std::endl;;
            std::cout << std::setw(62) <<"[1] Continue as Seller" << std::endl;;
            std::cout << std::setw(48) <<"[2] Quit" << std::endl;;
            std::cout << std::setw(42) << "> ";
            std::cin >> action;
        }  
        if (action == 2) return;
        if (action) role = Role::Seller;
        else role = Role::Customer;
         std::cout << std::setw(66) <<"Please input your username" << std::endl;
        std::cout << std::setw(42) << "> ";
        std::cin >> username;
        std::cout << std::setw(66) << "Please choose your country" << std::endl;
        std::cout << std::setw(42) << "[0] " << "Russia"  << std::setw(22) << "[3] " << "Italy" << std::endl;
        std::cout << std::setw(42) << "[1] " << "Armenia"  <<  std::setw(21) << "[4] " << "Spain " << std::endl;
        std::cout << std::setw(42) << "[2] " << "France" << std::setw(22) << "[5] " << "Georgia" << std::endl;
        std::cout << std::setw(42) << "> ";
        std::cin  >> country;
        while (country < 0 && country > 5) {
            std::cout << std::setw(66) << "Please inout correct number" << std::endl;
            std::cout << std::setw(42) << "[0] " << "Russia"  << std::setw(22) << "[3] " << "Italy" << std::endl;
            std::cout << std::setw(42) << "[1] " << "Armenia"  <<  std::setw(21) << "[4] " << "Spain " << std::endl;
            std::cout << std::setw(42) << "[2] " << "France" << std::setw(22) << "[5] " << "Georgia" << std::endl;
            std::cout << std::setw(42) << "> " << std::endl;
            std::cin >> country;
        }
        std::cout << std::setw(60) << "Please input your balance" << std::endl;
        std::cout << std::setw(42) << "> ";
        std::cin >> balance;
        while(balance < 0) {
            std::cout << "Please input correct number " << std::endl;
            std::cout << std::setw(42) << "> ";
            std::cin >> balance;
        }
        User user(username ,role, country, balance);
        action = 0;
        while (true) {
            switch (action) {
                case 0:
                    std::cout << "Please choose action" << std::endl;
                    if (role == Role::Customer){
                        std::cout << "[1] Market" << std::endl;
                        std::cout << "[2] User info" << std::endl;
                        std::cout << "[3] Show baskets" << std::endl;
                        std::cout << "[4] Show orders" << std::endl; 
                    } else {
                        std::cout << "[1] Market" << std::endl;
                        std::cout << "[2] User info" << std::endl;
                    }
                    std::cin >> action;
                    while ()//check
                case 1:
                    plt.display();
                    if (role == Role::Customer) std::cout << "[0] Add the basket" << std::endl;
                    if (role == Role::Seller) std::cout << "[0] Add the market" <<   std::endl; 
                    std::cout << "[1] Back" << std::endl;
                    if (action == 1) action = 0;
                    break; 
                
                    



            }
        }
    }

}


