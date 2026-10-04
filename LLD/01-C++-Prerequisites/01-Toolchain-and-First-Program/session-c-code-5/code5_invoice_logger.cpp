#include <iostream>
#include <string>
#include <iomanip>


class Logger {
public:
     void info(const std::string& message) const {
        std::cerr << "[INFO]: " << message << std::endl;
     }

     void error(const std::string& message) const{
        std::cerr << "[ERROR]: " << message<< std::endl;
     }

};

class Invoice{
private:
    const Logger& logger_;
    long long subtotalPaisa_ = 0;
    int itemCount_ = 0;
    static const int TAX_PERCENT = 18;

public: 
    explicit Invoice(const Logger& logger) : logger_(logger) {}

    bool addItem(const std::string& name, long long unitPaisa, int quantity){
        if(unitPaisa < 0 || quantity <=0 ){
            logger_.error("Rejected item: " + name + " with unit price: " + std::to_string(unitPaisa) + " and quantity: " + std::to_string(quantity));
            return false;
        }
        subtotalPaisa_ += unitPaisa * quantity;
        ++itemCount_;
        logger_.info("Added item: " + name + " with unit price: " + std::to_string(unitPaisa) + " and quantity: " + std::to_string(quantity));
        return true;
    }

    int itemCount() const {
        return itemCount_;
    }

    long long grandTotal(int discountPercent) const {
        long long discountedAmount = subtotalPaisa_ * (100 - discountPercent) / 100;
        long long taxAmount = discountedAmount * TAX_PERCENT / 100;
        return discountedAmount + taxAmount;
    }

    void printInvoice(const char* label,long long paisa) const{
        std::cout << label << " Rs." << paisa / 100 << "." << std::setw(2) << std::setfill('0') << paisa % 100 << std::endl;
    }
};

int main(){
    Logger logger;
    Invoice invoice(logger);

    invoice.addItem("Keyboard", 1000, 2);
    invoice.addItem("Monitor", 2500, 1);
    invoice.addItem("Mouse", 500, 5);
    invoice.addItem("FaultyItem", -100, 1);

    invoice.printInvoice("Grand Total", invoice.grandTotal(10));

    return invoice.itemCount() == 4 ? 0 : 1;
}