#include <iostream>
#include <string>
#include <iomanip>


class Logger { // Logger class to handle logging of information and errors
public:
     void info(const std::string& message) const {//Why const? Because we don't want to modify the state of the Logger object when logging information. Logging should not change the state of the logger. ie the logging format should be same for all the loggers. So we are making the function const to ensure that the state of the logger is not modified when logging information.
        std::cerr << "[INFO]: " << message << std::endl;
     }

     void error(const std::string& message) const{
        std::cerr << "[ERROR]: " << message<< std::endl;//cerr is used to print error messages to the standard error stream. It is used here to print error messages related to invoice processing, such as when an item is rejected due to invalid price or quantity. Using cerr allows error messages to be separated from regular output, making it easier to identify and handle errors in the program.
     }

};

class Invoice{
private:
    const Logger& logger_;// Reference to a Logger object for logging information and errors related to invoice processing. The logger is passed as a reference to avoid copying and to ensure that the same logger instance is used throughout the Invoice class.
    long long subtotalPaisa_ = 0;
    int itemCount_ = 0;
    static const int TAX_PERCENT = 18;

public: 
    explicit Invoice(const Logger& logger) : logger_(logger) {};//explicit constructor to initialize the Invoice object with a reference to a Logger object. The explicit keyword prevents implicit conversions, ensuring that the constructor is only called when an Invoice object is explicitly created with a Logger reference.like if we have a function that takes an Invoice object as a parameter, we cannot pass a Logger object directly to that function. We would need to create an Invoice object first and then pass it to the function. This helps to avoid accidental conversions and makes the code more readable and maintainable. And conversion such as Invoice invoice = logger; is not allowed. We have to explicitly call the constructor like Invoice invoice(logger);. This helps to avoid accidental conversions and makes the code more readable and maintainable. the accidental conversion are what? ans: Accidental conversions refer to situations where an object of one type is implicitly converted to another type without the programmer's intention. This can lead to unexpected behavior or bugs in the code. For example, if the constructor of the Invoice class was not marked as explicit, it would allow implicit conversions from a Logger object to an Invoice object. This means that if a function expected an Invoice object as a parameter, a Logger object could be passed instead, leading to confusion and potential errors in the program's logic. By marking the constructor as explicit, we prevent such implicit conversions and ensure that the programmer must explicitly create an Invoice object when needed, making the code clearer and less prone to errors.     

    //logger_(logger) hre logger_ is pointing to logger object which is passed to the constructor. So logger_ is a reference to the logger object which is passed to the constructor. So we can use logger_ to log information and errors related to invoice processing. The logger_ is a const reference, so we cannot modify the state of the logger object through logger_. We can only call const member functions of the logger object through logger_. This ensures that the state of the logger object is not modified when logging information and errors related to invoice processing. So inlogger_ nothing is there still just it is pointer to logger object.

    bool addItem(const std::string& name, long long unitPaisa, int quantity){
        if(unitPaisa < 0 || quantity <=0 ){
            logger_.error("Rejected item: " + name + " with unit price: " + std::to_string(unitPaisa) + " and quantity: " + std::to_string(quantity));// actually here we are using the logger_ where in constructor we just pointing to logger but hre we actually passing the error message to the logger object which is passed to the constructor. So logger_ is a reference to the logger object which is passed to the constructor. So we can use logger_ to log information and errors related to invoice processing. The logger_ is a const reference, so we cannot modify the state of the logger object through logger_. We can only call const member functions of the logger object through logger_. This ensures that the state of the logger object is not modified when logging information and errors related to invoice processing. So in logger_ nothing is there still just it is pointer to logger object.
            return false;
        }
        subtotalPaisa_ += unitPaisa * quantity;
        ++itemCount_;//pre-increment rather than post-increment because pre-increment is generally more efficient than post-increment for simple types like int. Pre-increment increments the value and returns the incremented value, while post-increment creates a temporary copy of the original value, increments the original value, and then returns the temporary copy. In this case, we don't need the original value, so pre-increment is more efficient.
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
    Logger logger; // Create a Logger object to handle logging of information and errors related to invoice processing .
    Invoice invoice(logger);// Create an Invoice object and pass the Logger object to it. The Invoice object will use the Logger object to log information and errors related to invoice processing.

    invoice.addItem("Keyboard", 1000, 2); // 2 keyboard of Rs.10.00 each
    invoice.addItem("Monitor", 2500, 1); // 1 monitor of Rs.25.00 each
    invoice.addItem("Mouse", 500, 5); // 5 mouse of Rs.5.00 each
    invoice.addItem("FaultyItem", -100, 1); // This item will be rejected due to negative price

    invoice.printInvoice("Grand Total", invoice.grandTotal(10)); // Calculate and print the grand total with a 10% discount

    return invoice.itemCount() == 4 ? 0 : 1; // Return 0 if all items were added successfully, otherwise return 1
}


//To compile and run the code, you can use the following commands in your terminal:
            // g++ -std=c++23 code5_invoice_logger.cpp -o invoice_logger
            // ./invoice_logger
// the flow is like 
 // pass logger -> invoice(just logger_ points to logger object) -> just the main logger is body and logger_ is outsider pointing to it and then we are using logger_ to log the error and info messages. like it just like logger and logger_ both are same but logger_ is just pointing to logger object which is passed to the constructor of invoice. So we can use logger_ to log information and errors related to invoice processing. The logger_ is a const reference, so we cannot modify the state of the logger object through logger_. We can only call const member functions of the logger object through logger_. This ensures that the state of the logger object is not modified when logging information and errors related to invoice processing. So in logger_ nothing is there still just it is pointer to logger object.