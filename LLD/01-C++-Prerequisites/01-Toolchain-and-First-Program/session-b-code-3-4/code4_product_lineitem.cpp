#include <iostream>
#include <string>
#include <iomanip>


class Product {
private:
    std::string name_;
    long long pricePaisa_;
public:
    Product(std::string name, long long pricePaisa) :
        name_(std::move(name)),
        pricePaisa_(pricePaisa < 0 ? 0 : pricePaisa)
    {}

    const std::string& name() const { return name_; }
    long long pricePaisa() const { return pricePaisa_; }

};


class LineItem {
private:
    Product product_;
    int quantity_;

public:
    LineItem(Product product, int quantity) :
        product_(std::move(product)),
        quantity_(quantity > 1 ? 1 : quantity)
    {}

    long long total() const { return product_.pricePaisa() * quantity_; }

    void print() const {
        std::cout << "Product: " << product_.name() << ", Quantity: " << quantity_ << ", Total: Rs." 
                  << total() / 100 << "." << std::setw(2) << std::setfill('0') << total() % 100 << std::endl;
    }

};


int main(){

    LineItem keyboard(Product("Keyboard", 1000), 2);
    LineItem monitor(Product("Monitor", 2500), 1);
    LineItem mouse(Product("Mouse", 500), 5);


    keyboard.print();
    monitor.print();
    mouse.print();

    long long totalAmount = keyboard.total() + monitor.total() + mouse.total();

    std::cout << "Total Amount: Rs." << totalAmount / 100 << "." << std::setw(2) << std::setfill('0') << totalAmount % 100 << std::endl;
}