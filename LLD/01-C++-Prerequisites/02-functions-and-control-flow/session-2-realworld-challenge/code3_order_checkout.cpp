#include <iostream>
#include <iomanip>
#include <String>

class FeeCalculator
{
private:
    long long basePricePaise_;
    int includedKm_;
    long long perKmPaise_;

public:
    FeeCalculator(long long basePricePaise = 2000, int includedKm = 3, long long perKmPaise = 500)
        : basePricePaise_(basePricePaise), includedKm_(includedKm), perKmPaise_(perKmPaise) {}

    long long feeFor(int distance)
    {
        if (distance < 0)
            return -1;
        if (distance < includedKm_)
            return basePricePaise_;
        return basePricePaise_ + (distance - includedKm_) * perKmPaise_;
    }

    bool tryQuote(int distance, long long &outFee, int surgePercent = 100)
    {
        long long fees = feeFor(distance);
        if (fees < 0 || surgePercent < 100)
            return false;
        outFee = fees;
        return true;
    }

    long long totalFees(long long &outfee) { return outfee; }
};

class Logger
{
public:
    void info(const std::string &msg) const { std::cout << "[INFO] " << msg << "\n"; };
    void error(const std::string &err) const { std::cerr << "[ERROR] " << err << "\n"; };
};

class Cart
{
private:
    const Logger &log_;
    long long subtotalPaise_ = 0;
    int lines_ = 0;
    int rejected_ = 0;

    long long unitPaise(int productId)
    {
        if (productId == 1)
            return 19999;
        if (productId == 2)
            return 49900;
        if (productId == 3)
            return 9950;
        return -1;
    };

public:
    explicit Cart(const Logger &log) : log_(log) {};

    bool addLines(int productId, int qty = 1)
    {
        long long units = unitPaise(productId);
        if (units < 0 || qty < 1 || qty > 100)
        {
            ++rejected_;
            log_.error("Rejected line: product " + std::to_string(productId) + " qty " + std::to_string(qty));
            return false;
        }

        subtotalPaise_ += units * qty;
        lines_++;
        log_.info("Added line: product " + std::to_string(productId) + " qty " + std::to_string(productId));
        return true;
    }

    long long subtotalPaise() const { return subtotalPaise_; };
    int lines() const { return lines_; }
    int rejected() const { return rejected_; }

    long long discountPercent(long long subtotalPaise)
    {
        if (subtotalPaise >= 100000)
            return 10;
        if (subtotalPaise >= 50000)
            return 5;
        return 0;
    }

    bool parseInt(const char *text, int &out)
    {
        try
        {
            std::size_t used = 0;
            out = std::stoi(text, &used);
            return text[used] == '\0';
        }
        catch (...)
        {
            return false;
        }
    }

    void printMoney(const char *label, long long paise)
    {
        std::cout << label << "Rs " << paise / 100 << '.'
                  << std::setw(2) << std::setfill('0') << paise % 100 << '\n';
    }
};

int main(int argc, char *argv[])
{
    

    Logger log;
    Cart cart(log);

    if (argc != 3)
    {
        std::cerr << "usage: checkout DISTANCE_KM COUPON_PERCENT  (stdin: 'productId qty', '0 0' ends)\n";
        return 2;
    }
    int km = 0, coupon = 0;
    if (!cart.parseInt(argv[1], km) || !cart.parseInt(argv[2], coupon) || km < 0 || coupon < 0 || coupon > 50)
    {
        log.error("invalid distance or coupon");
        return 3;
    }

    int productId = 0, qty = 0;
    while( std::cin >> productId >> qty){
        if(productId == 0) break;
        cart.addLines(productId,qty);
    }

    if(cart.lines() == 0){
        log.error("empty cart");
        return 4;
    }
    FeeCalculator fees;
    long long fee = 0;
    if (!fees.tryQuote(km, fee)) {                    // defensive: a failed dependency stops checkout
        log.error("cannot quote delivery");
        return 3;
    }
    int tier = cart.discountPercent(cart.subtotalPaise());
    int percent = tier > coupon ? tier : coupon;      // rule: best of tier or coupon, NOT stacked
    long long items = cart.subtotalPaise() * (100 - percent) / 100;
    if (items >= 120000) fee = 0;                     // free delivery threshold

    cart.printMoney("Subtotal: ", cart.subtotalPaise());
    std::cout << "Discount: " << percent << "%\n";
    cart.printMoney("Items:    ", items);
    cart.printMoney("Delivery: ", fee);
    cart.printMoney("Total:    ", items + fee);
    std::cout << "Rejected lines: " << cart.rejected() << "\n";
    return cart.rejected() == 0 ? 0 : 5;
}