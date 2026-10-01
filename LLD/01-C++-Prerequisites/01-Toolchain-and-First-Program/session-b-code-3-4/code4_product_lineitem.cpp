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
        pricePaisa_(pricePaisa < 0 ? 0 : pricePaisa) // Ensure price is non-negative
    {}// Constructor initializes product name and price, ensuring price is non-negative

    const std::string& name() const { return name_; } // Getter for product name
    long long pricePaisa() const { return pricePaisa_; } // Getter for product price in paisa

};


class LineItem {
private:
    Product product_;
    int quantity_;

public:
    LineItem(Product product, int quantity) :
        product_(std::move(product)),
        quantity_(quantity > 1 ? 1 : quantity) // Ensure quantity is positive
    {}// Constructor initializes line item with product and quantity

    long long total() const { return product_.pricePaisa() * quantity_; } // Calculate total price for the line item

    void print() const {
        std::cout << "Product: " << product_.name() << ", Quantity: " << quantity_ << ", Total: Rs." 
                  << total() / 100 << "." << std::setw(2) << std::setfill('0') << total() % 100 << std::endl;
    } // Print line item details including product name, quantity, and total price

};



int main(){

    LineItem keyboard(Product("Keyboard", 1000), 2); // Create a line item for 2 keyboards priced at Rs.10.00 each
    LineItem monitor(Product("Monitor", 2500), 1); // Create a line item for 1 monitor priced at Rs.25.00 each
    LineItem mouse(Product("Mouse", 500), 5); // Create a line item for 5 mice priced at Rs.5.00 each


    keyboard.print(); // Print details of the keyboard line item
    monitor.print(); // Print details of the monitor line item  
    mouse.print(); // Print details of the mouse line item

    long long totalAmount = keyboard.total() + monitor.total() + mouse.total(); // Calculate total amount for all line items

    std::cout << "Total Amount: Rs." << totalAmount / 100 << "." << std::setw(2) << std::setfill('0') << totalAmount % 100 << std::endl; // Print the total amount in rupees and paisa
}



//To compile and run the code, you can use the following commands in your terminal:
            // g++ -std=c++23 code4_product_lineitem.cpp -o product_lineitem
            // ./product_lineitem

// The Flow of the Code: IN uml from sequence diagram in box format

