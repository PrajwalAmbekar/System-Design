#include <iomanip>
#include <iostream>
#include <string>

// Logger writes to stderr so stdout carries only the bill (pipe-friendly).
class Logger {
public:
    void info(const std::string& msg) const { std::cerr << "[INFO]  " << msg << "\n"; }
    void error(const std::string& msg) const { std::cerr << "[ERROR] " << msg << "\n"; }
};

// Bill is a plain result: fixed after construction, so it cannot become inconsistent.
class Bill {
private:
    int netUnits_;
    long long energyPaise_;
    long long fixedPaise_;
    long long taxPaise_;

public:
    Bill(int netUnits, long long energyPaise, long long fixedPaise, long long taxPaise)
        : netUnits_(netUnits), energyPaise_(energyPaise), fixedPaise_(fixedPaise), taxPaise_(taxPaise) {}

    int netUnits() const { return netUnits_; }
    long long energyPaise() const { return energyPaise_; }
    long long fixedPaise() const { return fixedPaise_; }
    long long taxPaise() const { return taxPaise_; }
    long long totalPaise() const { return energyPaise_ + fixedPaise_ + taxPaise_; }
};

// Tariff owns ALL pricing rules. It does no printing and no parsing.
class Tariff {
private:
    int slab1Limit_;
    int slab2Limit_;
    long long rate1_;
    long long rate2_;
    long long rate3_;
    long long fixedPaise_;
    int taxPercent_;

    // Tiered: each unit pays the rate of ITS OWN slab, not the slab the total lands in.
    long long energyPaise(int netUnits) const {
        int remaining = netUnits;

        int inSlab1 = remaining < slab1Limit_ ? remaining : slab1Limit_;
        remaining -= inSlab1;

        int slab2Size = slab2Limit_ - slab1Limit_;
        int inSlab2 = remaining < slab2Size ? remaining : slab2Size;
        remaining -= inSlab2;

        return inSlab1 * rate1_ + inSlab2 * rate2_ + remaining * rate3_;
    }

public:
    explicit Tariff(int slab1Limit = 100, int slab2Limit = 300, long long rate1 = 400,
                    long long rate2 = 700, long long rate3 = 1000, long long fixedPaise = 5000,
                    int taxPercent = 5)
        : slab1Limit_(slab1Limit), slab2Limit_(slab2Limit), rate1_(rate1), rate2_(rate2),
          rate3_(rate3), fixedPaise_(fixedPaise), taxPercent_(taxPercent) {}

    Bill billFor(int units, int solarUnits) const {
        int net = units - solarUnits;
        if (net < 0) net = 0;  // surplus solar is not paid out in this version
        long long energy = energyPaise(net);
        long long tax = (energy + fixedPaise_) * taxPercent_ / 100;  // multiply first, divide last
        return Bill(net, energy, fixedPaise_, tax);
    }

    // Overload reuses the main one, so the rules exist in exactly one place.
    Bill billFor(int units) const { return billFor(units, 0); }
};

// Parsing and printing live OUTSIDE the domain classes.
bool parseInt(const char* text, int& out) {
    try {
        std::size_t used = 0;
        out = std::stoi(text, &used);
        return text[used] == '\0';  // rejects "12abc"
    } catch (...) {
        return false;  // "abc" or a number too large for int
    }
}

void printMoney(const char* label, long long paise) {
    std::cout << label << "Rs " << paise / 100 << '.' << std::setw(2) << std::setfill('0')
              << paise % 100 << '\n';
}

int main(int argc, char* argv[]) {
    Logger log;

    if (argc < 2 || argc > 3) {  // argv[0] is the program name, so valid argc is 2 or 3
        std::cerr << "usage: bill UNITS [SOLAR_UNITS]\n";
        return 2;
    }

    int units = 0;
    int solar = 0;
    bool ok = parseInt(argv[1], units) && units >= 0 && units <= 100000;
    if (ok && argc == 3) {
        ok = parseInt(argv[2], solar) && solar >= 0 && solar <= 100000;
    }
    if (!ok) {
        log.error("units must be integers in 0..100000");
        return 3;
    }

    Tariff tariff;
    Bill bill = (argc == 3) ? tariff.billFor(units, solar) : tariff.billFor(units);

    std::cout << "Net units: " << bill.netUnits() << "\n";
    printMoney("Energy:    ", bill.energyPaise());
    printMoney("Fixed:     ", bill.fixedPaise());
    printMoney("Tax:       ", bill.taxPaise());
    printMoney("Total:     ", bill.totalPaise());
    return 0;
}