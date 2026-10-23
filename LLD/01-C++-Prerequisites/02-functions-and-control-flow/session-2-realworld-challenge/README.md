
# order-checkout

A C++20 checkout program that calculates product subtotals, applies the better of a tier discount or coupon, and calculates delivery fees. It also demonstrates input validation, logging, classes, references, and integer-based currency calculations.

## Contents

| File | Description |
|---|---|
| `code3_order_checkout.cpp` | Checkout logic, product catalog, discount calculation, delivery fee calculation, logging, and formatted output |

## Requirements

- **Compiler:** GCC (`g++`) supporting C++20.
- **C++ standard:** C++20, selected using `-std=c++20`.
- **Operating systems:** Windows with a GCC toolchain, Linux, or macOS with a compatible GCC installation.
- **Terminal:** PowerShell on Windows or a compatible shell on other supported systems.

## Build and Run

### Code 1 — `code3_order_checkout.cpp`

**Compile (PowerShell):**

```powershell
g++ -std=c++20 -Wall -Wextra -g code3_order_checkout.cpp -o checkout.exe
```

**Run (PowerShell):**

```powershell
"1 2`n2 1`n9 1`n3 3`n0 0" | .\checkout.exe 8 15
Write-Output "exit=$LASTEXITCODE"
```

The command passes `8` as the delivery distance and `15` as the coupon percentage. The text before the pipe supplies product IDs and quantities to standard input. PowerShell's `` `n `` represents a newline.

**Expected output:**

```text
[INFO]  added product 1 x2
[INFO]  added product 2 x1
[ERROR] rejected line: product 9 qty 1
[INFO]  added product 3 x3
Subtotal: Rs 1096.97
Discount: 15%
Items:    Rs 932.42
Delivery: Rs 45.00
Total:    Rs 977.42
Rejected lines: 1
exit=5
```

The program returns exit code `5` because one product line was rejected. The error message is written to standard error, while the other displayed messages are written to standard output or standard error according to the code.

## Command Reference

| Command part | Meaning | Example |
|---|---|---|
| `g++` | GNU C++ compiler command | `g++` |
| `-std=c++20` | Selects the C++20 language standard | `-std=c++20` |
| `-Wall` | Enables a broad set of common compiler warnings | `-Wall` |
| `-Wextra` | Enables additional compiler warnings | `-Wextra` |
| `-g` | Includes debugging information in the executable | `-g` |
| `code3_order_checkout.cpp` | The source file to compile | `code3_order_checkout.cpp` |
| `-o checkout.exe` | Names the generated executable `checkout.exe` | `-o checkout.exe` |
| `.\checkout.exe` | Runs the executable from the current PowerShell directory | `.\checkout.exe` |
| `8` | First program argument: delivery distance in kilometres | `8` |
| `15` | Second program argument: coupon percentage | `15` |
| `\|` | PowerShell pipeline operator; sends the left command's output to the right command's input | `"input" \| .\checkout.exe 8 15` |
| `` `n `` | Inserts a newline in a PowerShell double-quoted string | ``"1 2`n2 1"`` |
| `Write-Output` | Writes text to the PowerShell output stream | `Write-Output "exit=$LASTEXITCODE"` |
| `$LASTEXITCODE` | Contains the exit code returned by the last native executable | `$LASTEXITCODE` |
| `;` | Separates commands in PowerShell so the next command runs after the preceding one finishes | `command1; command2` |

**Program input format**

| Input | Meaning |
|---|---|
| `DISTANCE_KM` | Non-negative delivery distance supplied as the first command-line argument |
| `COUPON_PERCENT` | Coupon percentage from `0` through `50`, supplied as the second command-line argument |
| `productId qty` | A product ID and quantity pair read from standard input |
| `0 0` | Stops reading product lines when the product ID is `0` |

The program supports product IDs `1`, `2`, and `3`. Quantities must be between `1` and `100`.

## Key Terms

### Program Structure

| Term | Meaning | Example |
|---|---|---|
| `main` | Entry point of the program | `int main(int argc, char* argv[])` |
| `argc` | Number of command-line arguments, including the executable name | `argc != 3` |
| `argv` | Array of command-line argument strings | `argv[1]`, `argv[2]` |
| `if` | Executes a block when a condition is true | `if (cart.lines() == 0)` |
| `else` | Provides an alternative branch | `else return -1;` |
| `while` | Repeats a block while a condition remains true | `while (std::cin >> productId >> qty)` |
| `return` | Ends a function and optionally returns a value | `return 3;` |
| Function | Named block of code that can accept arguments and return a result | `discountPercentFor(...)` |
| Class | Defines a type containing data and member functions | `class Cart` |
| Constructor | Initializes an object when it is created | `Cart(const Logger& log)` |
| Member function | Function associated with a class | `cart.addLine(productId, qty)` |
| Reference parameter | Allows a function to access an existing object through a reference | `long long& outFee` |
| `const` member function | Promises not to modify the object's ordinary member state | `feeFor(int km) const` |
| `std::cin` | Reads input from standard input | `std::cin >> productId >> qty` |
| `std::cout` | Writes output to standard output | `std::cout << "Discount: "` |
| `std::cerr` | Writes diagnostic output to standard error | `std::cerr << "[ERROR] "` |

### Data Types

| Type | Stores | Typical size | Example |
|---|---|---|---|
| `int` | Whole numbers | Commonly 4 bytes; implementation-dependent | `int km = 0` |
| `long long` | Larger-range integer values | At least 8 bytes | `long long subtotalPaise_ = 0` |
| `bool` | `true` or `false` | Commonly 1 byte; implementation-dependent | `bool tryQuote(...)` |
| `char` | A character or small integer value | Commonly 1 byte | `char* argv[]` |
| `void` | No return value | Not applicable | `void printMoney(...)` |
| `std::string` | A sequence of characters | Size depends on the object and implementation | `const std::string& msg` |
| `std::size_t` | Unsigned integer type used for sizes and indexing | Implementation-dependent | `std::size_t used = 0` |

### Keywords and Operators

| Term | Meaning | Example from the code |
|---|---|---|
| `class` | Declares a class | `class FeeCalculator` |
| `private` | Restricts direct access to class members | `private:` |
| `public` | Makes class members accessible through the class interface | `public:` |
| `static` | Declares a class member that does not require an individual object | `static long long unitPricePaise(int productId)` |
| `const` | Prevents modification through the declared variable, reference, or member function | `const Logger& log_` |
| `explicit` | Prevents unintended implicit conversion through a single-argument constructor | `explicit Cart(const Logger& log)` |
| `long long&` | Declares a reference to a `long long` object | `long long& outFee` |
| `::` | Scope-resolution operator used to identify a name in a scope | `std::cout`, `Cart::` |
| `.` | Accesses a member through an object | `cart.addLine(...)` |
| `&` | Declares a reference in a declaration | `const Logger& log` |
| `=` | Assigns a value or supplies a default argument, depending on context | `int km = 0` |
| `==` | Tests equality | `productId == 0` |
| `!=` | Tests inequality | `argc != 3` |
| `<` | Tests whether one value is smaller than another | `qty < 1` |
| `>` | Tests whether one value is greater than another | `qty > 100` |
| `>=` | Tests whether a value is greater than or equal to another | `subtotalPaise >= 100000` |
| `++` | Increments a value by one | `++rejected_` |
| `+` | Adds numbers or concatenates strings | `unit * qty`, `"product " + std::to_string(productId)` |
| `-` | Subtracts values or negates a value | `100 - percent`, `return -1` |
| `*` | Multiplies values | `unit * qty` |
| `/` | Divides values | `paise / 100` |
| `%` | Returns the remainder after integer division | `paise % 100` |
| `<<` | Stream insertion operator; sends data to an output stream | `std::cout << label` |
| `>>` | Stream extraction operator; reads data from an input stream | `std::cin >> productId >> qty` |
| `!` | Logical NOT; reverses a Boolean condition | `!parseInt(argv[1], km)` |
| `&&` | Logical AND; true when both conditions are true | `km < 0 || coupon < 0` uses `||`, not `&&` |
| `||` | Logical OR; true when at least one condition is true | `coupon < 0 || coupon > 50` |
| `{}` | Delimits a block or initializes a variable or object | `if (...) { ... }` |
| `()` | Groups expressions or contains function parameters and arguments | `feeFor(km)` |
| `[]` | Accesses an array element | `argv[1]` |
| `;` | Terminates a C++ statement | `return 0;` |
| `:` | Introduces a constructor initializer list or separates conditional branches in other constructs | `: log_(log)` |
| `?` | Part of the conditional expression operator when used with `:` | Not used as a conditional expression in this code |

### Standard Library Names

| Name | Header | Meaning |
|---|---|---|
| `std::cout` | `<iostream>` | Standard output stream |
| `std::cerr` | `<iostream>` | Standard error stream |
| `std::cin` | `<iostream>` | Standard input stream |
| `std::string` | `<string>` | String type |
| `std::to_string` | `<string>` | Converts supported numeric values to strings |
| `std::stoi` | `<string>` | Converts a string to an `int`, optionally reporting how many characters were consumed |
| `std::size_t` | `<string>` (also available through other standard headers) | Unsigned type used for string positions and sizes |
| `std::setw` | `<iomanip>` | Sets the minimum width for the next formatted output field |
| `std::setfill` | `<iomanip>` | Sets the character used to fill output padding |

## Initialization

| Form | Example | Result |
|---|---|---|
| Copy initialization | `int km = 0;` | Creates an integer initialized to zero |
| In-class member initialization | `long long subtotalPaise_ = 0;` | Initializes the member when an object is created, unless another applicable initialization overrides it |
| Constructor initializer list | `: baseFeePaise_(baseFeePaise), includedKm_(includedKm), perKmPaise_(perKmPaise)` | Initializes data members from constructor parameters |
| Default arguments | `int qty = 1` | Uses quantity `1` when the caller omits that argument |
| Default constructor arguments | `FeeCalculator fees;` | Uses the fee calculator's default values |
| Reference initialization | `const Logger& log_` | Binds the reference member to an existing `Logger` object |

## Topics Covered

- C++ classes, private data members, and public interfaces.
- Constructors, constructor initializer lists, default arguments, and `explicit`.
- References and `const` member functions.
- Input validation and command-line arguments.
- Standard input, standard output, and standard error.
- Logging with a dedicated `Logger` class.
- Product catalog lookup and cart subtotal calculation.
- Discount tiers and coupon selection without stacking.
- Delivery fee calculation and free-delivery threshold.
- Integer-based currency calculations in paise.
- String conversion and parsing with `std::stoi`.
- Formatted money output using `std::setw` and `std::setfill`.
- Exit codes used to report different failure conditions.

## Notes

- All currency values are stored as integer paise, avoiding floating-point representation for the stored amounts.
- `feeFor()` charges the base delivery fee for distances up to and including the included distance of `3 km`; each additional kilometre adds ₹5.
- `tryQuote()` accepts a surge percentage of at least `100`. Its default is `100`, and the fee is multiplied by the surge percentage before integer division by `100`.
- The checkout chooses the greater of the tier discount and coupon percentage. The two discounts are not stacked.
- A coupon must be between `0%` and `50%`.
- Product IDs `1`, `2`, and `3` have unit prices of ₹199.99, ₹499.00, and ₹99.50, respectively.
- Unknown products and quantities outside the range `1`–`100` are rejected. Rejected lines increment the rejection counter without changing the subtotal.
- Delivery is free when the discounted item total is at least ₹1,200.
- Integer division truncates the fractional part. For the non-negative amounts used by this checkout, discount calculations round down to the nearest paise.
- `std::setw(2)` sets a minimum width of two characters for the next output field. `std::setfill('0')` makes padding use zeros.
- The input loop stops when it reads a product ID of `0`, encounters end-of-file, or fails to read numeric input.
- Exit codes are `0` for success, `2` for incorrect argument count, `3` for invalid arguments or delivery quotation failure, `4` for an empty cart, and `5` when at least one line was rejected.
- With `-Wall -Wextra`, the shown source is not expected to produce a warning solely from its declared variables or parameters.


