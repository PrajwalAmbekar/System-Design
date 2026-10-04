#include <iostream>
#include <string>
#include <iomanip>

const int kUsageError = 2;
const int kInputError = 3;

bool parseNumber(const char* text, long long& out)
{
    try
    {
        std::size_t used = 0;
        out = std::stoll(text, &used);
        return text[used] == '\0';
    }
    catch (...)
    {
        return false;
    }
}

class Logger
{
public:
    void info(const std::string& msg) const { std::cerr << "[INFO] " << msg << std::endl; };
    void error(const std::string& msg) const { std::cerr << "[ERROR] " << msg << std::endl; };
};

class Invoice
{
private:
    const Logger& logger_;
    long long subtotalPaise_ = 0;
    int itemCount_ = 0;
    static const int TAX_PERCENT = 18;

public:
    explicit Invoice(const Logger& logger) : logger_(logger) {};

    bool addItem(const std::string& name, long long unitPaise, int qty)
    {
        if (unitPaise < 0 || qty <= 0)
        {
            logger_.error("Invalid item parameters" + name);
            return false;
        }
        subtotalPaise_ += unitPaise * qty;
        ++itemCount_;
        return true;
    }

    long long grandTotal(int discountPercent) const
    {
        long long discounted = subtotalPaise_ * (100 - discountPercent) / 100;
        return discounted + discounted * TAX_PERCENT / 100;
    };

    int itemCount() const { return itemCount_; };
};

void printMoney(const char *label, long long paise)
{
    std::cout << std::setw(20) << std::left << label << " : Rs. " << std::fixed << std::setprecision(2) << paise / 100.0 << std::endl;
}

int main(int argc, char* argv[])
{
    Logger log;

    if (argc < 4 || (argc - 2) % 2 != 0)
    {
        std::cerr << "Usage: " << argv[0] << " <discount-percent>  <item1-unit-price-paise> <item1-quantity> ...]" << std::endl;
        return kUsageError;
    }

    long long discount = 0;

    if (!parseNumber(argv[1], discount) || discount < 0 || discount > 100)
    {
        log.error("Invalid discount percentage & must be between 0 and 100");
        return kInputError;
    }

    Invoice invoice(log);

    for (int i = 2; i + 1 < argc; i += 2)
    {
        long long price = 0, qty = 0;

        if (!parseNumber(argv[i], price) || !parseNumber(argv[i + 1], qty) || price > 1000000000 || qty > 1000000)
        {
            log.error("bad number near argument " + std::to_string(i));
            return kInputError;
        }

        std::string name = "item" + std::to_string((i - 2) / 2 + 1);

        if (!invoice.addItem(name, price, static_cast<int>(qty)))
        {
            return kInputError;
        }
    }

    printMoney("Grand total: ", invoice.grandTotal(static_cast<int>(discount)));

    return 0;
}