# delivery-fee-basics

Two C++20 programs demonstrate delivery fee calculations using functions and classes. The examples cover conditional logic, loops, integer-based money calculations, constructors, function overloading, references, and basic error handling.

## Contents

| File | Description |
|---|---|
| `code1_delivery_fee_basics.cpp` | Calculates delivery fees using functions, conditional statements, and loops. Demonstrates pass-by-value and free-delivery eligibility. |
| `code2_fee_calculator.cpp` | Implements a configurable delivery fee calculator using a class, constructor defaults, overloaded member functions, and reference-based output parameters. |

## Requirements

- **Compiler:** GCC (`g++`) with C++20 support.
- **C++ standard:** C++20, selected using `-std=c++20`.
- **Operating systems:** Linux, macOS, or Windows with a compatible GCC installation, such as MinGW-w64.
- **Terminal:** Required to compile and execute the programs.

## Build and Run

### 1. `code1_delivery_fee_basics.cpp`

Compile:

```bash
g++ -std=c++20 -Wall -Wextra -g code1_delivery_fee_basics.cpp -o deliveryFees
```

Run:

```bash
./deliveryFees
```

Expected output:

```text
0 km: 2000 paise
5 km: 3000 paise
10 km: 5500 paise
15 km: 9500 paise
-2 km: invalid
farthest within 6000 paise: 10 km
fee after tryToRaiseFee: 3000
free delivery for 1200 rupees? true
```

### 2. `code2_fee_calculator.cpp`

Compile:

```bash
g++ -std=c++20 -Wall -Wextra -g code2_fee_calculator.cpp -o feeCalculator
```

Run:

```bash
./feeCalculator
```

Expected output:

```text
2 km  standard 2000  premium 3000
8 km  standard 4500  premium 4200
14 km  standard 7500  premium 6600
20 km  standard 10500  premium 9000
surge 150% at 8 km: 6750
quote rejected
orders afforded: 4, budget left: 2000
```

## Command Reference

| Command part | Meaning | Example |
|---|---|---|
| `g++` | Invokes the GNU C++ compiler. | `g++ code.cpp` |
| `-std=c++20` | Selects the C++20 language standard. | `-std=c++20` |
| `-Wall` | Enables a broad set of commonly useful compiler warnings. | `-Wall` |
| `-Wextra` | Enables additional warnings beyond those selected by `-Wall`. | `-Wextra` |
| `-g` | Includes debugging information in the compiled output. | `-g` |
| `code1_delivery_fee_basics.cpp` | Specifies the source file to compile. | `code1_delivery_fee_basics.cpp` |
| `code2_fee_calculator.cpp` | Specifies the second source file to compile. | `code2_fee_calculator.cpp` |
| `-o` | Specifies the name of the generated executable. | `-o deliveryFees` |
| `deliveryFees` | Executable generated for the first program. | `./deliveryFees` |
| `feeCalculator` | Executable generated for the second program. | `./feeCalculator` |
| `./program` | Runs an executable located in the current directory on Unix-like systems. | `./deliveryFees` |

## Key Terms

### Program Structure

| Term | Meaning | Example from code |
|---|---|---|
| `main()` | Entry point where program execution begins. | `int main()` |
| Function | A named block of code that performs a task and may return a value. | `deliveryFeePaise()` |
| Parameter | A named input received by a function. | `int distanceKm` |
| Argument | A value supplied when calling a function. | `printFee(-2)` |
| Function call | Executes a function using the supplied arguments. | `printFee(km)` |
| `if` | Executes a block when its condition is true. | `if (distanceKm < 0)` |
| `return` | Ends a function and optionally returns a value. | `return -1;` |
| `for` | Repeats a block using initialization, a condition, and an update expression. | `for (int km = 0; km <= 15; km += 5)` |
| `while` | Repeats a block while its condition remains true. | `while (deliveryFeePaise(km + 1) <= 6000)` |
| `class` | Defines a type that groups data and member functions. | `class FeeCalculator` |
| `private` | Restricts direct access to class members from outside the class. | `private:` |
| `public` | Makes class members accessible from outside the class. | `public:` |
| Constructor | Initializes an object when it is created. | `FeeCalculator(...)` |
| Function overloading | Allows functions with the same name to have different parameter lists. | `feeFor(int)` and `feeFor(int, int)` |
| `const` member function | Promises not to modify the object's non-mutable data members through that member function. | `long long feeFor(int distanceKm) const` |
| Pass by value | Passes a copy of an argument to a parameter. | `tryToRaiseFee(long long fee)` |
| Reference parameter | Lets a function access the caller's existing variable through a reference. | `long long& outFee` |
| Output parameter | A parameter used to provide a result to the caller. | `tryQuote(..., outFee, ...)` |
| Sentinel value | A special value used to indicate a condition such as failure. | `return -1;` |
| Early return | Exits a function before reaching its end. | `if (fee < 0) return;` |
| `bool` result | Represents a true-or-false result. | `qualifiesForFreeDelivery(120000)` |
| `void` result | Indicates that a function does not return a value. | `void printFee(int distanceKm)` |
| `&&` | Logical AND; both conditions must be true. | `standard.tryQuote(8, fee) && fee <= budget` |

### Data Types

| Type | Stores | Typical size | Example |
|---|---|---|---|
| `int` | Whole numbers within the implementation's supported range. | Commonly 4 bytes | `int distanceKm` |
| `long long` | Integer values with a guaranteed minimum range of at least 64 bits. | Commonly 8 bytes | `long long fee` |
| `bool` | A logical value: `true` or `false`. | Commonly 1 byte | `bool qualifiesForFreeDelivery(...)` |
| `void` | No return value. | Not applicable | `void printFee(...)` |

*Typical sizes are implementation-dependent; the sizes shown are common, not universal.*

### Keywords and Operators

| Term | Meaning | Example from code |
|---|---|---|
| `#include` | Preprocessor directive that includes a header. | `#include <iostream>` |
| `long long` | Declares an integer type with a wider minimum range than `int`. | `long long fee` |
| `int` | Declares an integer variable or parameter. | `int km = 0` |
| `bool` | Declares a Boolean result or variable. | `bool qualifiesForFreeDelivery(...)` |
| `void` | Specifies that a function returns no value. | `void tryToRaiseFee(...)` |
| `class` | Introduces a class definition. | `class FeeCalculator` |
| `private` | Begins the private access section of a class. | `private:` |
| `public` | Begins the public access section of a class. | `public:` |
| `return` | Returns a value or exits a function. | `return baseFeePaise_;` |
| `const` | Restricts modification through a member function or reference as applicable. | `feeFor(int distanceKm) const` |
| `if` | Tests a condition. | `if (distanceKm <= includedKm_)` |
| `for` | Starts a counted loop. | `for (int km = 2; km <= 20; km += 6)` |
| `while` | Starts a condition-controlled loop. | `while (standard.tryQuote(8, fee) && fee <= budget)` |
| `=` | Assignment or initialization operator. | `long long fee = 3000;` |
| `<` | Tests whether the left operand is smaller than the right operand. | `distanceKm < 0` |
| `<=` | Tests whether the left operand is smaller than or equal to the right operand. | `distanceKm <= 3` |
| `>=` | Tests whether the left operand is greater than or equal to the right operand. | `orderPaise >= 99900` |
| `>` | Tests whether the left operand is greater than the right operand. | `surgePercent < 100` is used to reject values below 100. |
| `+` | Adds values. | `baseFeePaise_ + (distanceKm - includedKm_) * perKmPaise_` |
| `-` | Subtracts values or negates a numeric value. | `distanceKm - includedKm_` |
| `*` | Multiplies values. | `fee * surgePercent` |
| `/` | Divides values; integer operands produce integer division. | `fee * surgePercent / 100` |
| `+=` | Adds a value to a variable and stores the result in that variable. | `budget -= fee` uses the related compound-assignment operator. |
| `-=` | Subtracts a value from a variable and stores the result. | `budget -= fee` |
| `++` | Increments a variable by one. | `++km` |
| `!` | Logical NOT; reverses a Boolean result. | `if (!standard.tryQuote(-5, fee))` |
| `&` | In a parameter declaration, denotes a reference when used after a type. | `long long& outFee` |
| `::` | Scope-resolution operator used to identify a name in a namespace or class scope. | `std::cout`, `FeeCalculator::feeFor` |
| `<<` | Stream insertion operator; sends data to an output stream. | `std::cout << "quote rejected\n";` |
| `{}` | Braces delimit blocks and class/function bodies; braces can also be used for initialization in C++. | `int main() { ... }` |
| `()` | Used for function declarations, calls, and grouping expressions. | `printFee(-2)` |
| `;` | Ends a statement or declaration. | `return 0;` |
| `//` | Begins a single-line comment. | `//To compile this file` |
| `100` | Integer literal used as the baseline surge percentage. | `surgePercent = 100` |
| `-1` | Negative integer literal used as an invalid-result sentinel. | `return -1;` |

### Standard Library Names

| Name | Header | Meaning |
|---|---|---|
| `std::cout` | `<iostream>` | Standard output stream used to print results to the terminal. |
| `std::boolalpha` | `<iostream>` | Stream manipulator that prints Boolean values as `true` or `false` instead of `1` or `0`. |

## Initialization

| Form | Example | Result |
|---|---|---|
| Direct initialization with a value | `long long fee(3000);` | Creates `fee` with the value `3000`. |
| Copy initialization | `long long fee = 3000;` | Creates `fee` with the value `3000`. |
| Default constructor arguments | `FeeCalculator standard;` | Initializes the calculator with a base fee of `2000` paise, `3` included kilometres, and `500` paise per additional kilometre. |
| Constructor with custom arguments | `FeeCalculator premium(3000, 5, 400);` | Initializes the calculator with a base fee of `3000` paise, `5` included kilometres, and `400` paise per additional kilometre. |
| Member initializer list | `: baseFeePaise_(baseFeePaise), includedKm_(includedKm), perKmPaise_(perKmPaise)` | Initializes the class data members using constructor parameters. |
| Default function argument | `int surgePercent = 100` | Uses a surge percentage of `100` when the caller omits that argument. |
| Reference parameter | `long long& outFee` | Binds the parameter to the caller's existing variable rather than creating a separate `long long` object. |

## Topics Covered

- Writing functions with return types and parameters.
- Returning values from functions and using `void` functions.
- Conditional statements and early returns.
- `for` and `while` loops.
- Integer-based monetary calculations using paise.
- Free-delivery eligibility using a Boolean result.
- Pass-by-value behavior.
- Class definition and private/public access control.
- Constructors with default arguments.
- Member initializer lists.
- Function overloading and reuse of an existing overload.
- `const` member functions.
- Reference-based output parameters and Boolean success indicators.
- Invalid input handling with a sentinel value.
- Comparing configurable pricing rules.
- Stream output and Boolean formatting.
- Compiling and running C++20 programs with GCC warning and debugging flags.

## Notes

- All delivery fees and budgets are represented as integer paise. For example, `2000` paise equals ₹20.
- The free-delivery threshold is `99900` paise, equivalent to ₹999.
- In `code1_delivery_fee_basics.cpp`, the fee is ₹20 for distances up to 3 km, ₹5 per additional kilometre through 10 km, and ₹8 per kilometre beyond 10 km.
- In `code2_fee_calculator.cpp`, the configured per-kilometre rate applies to every kilometre beyond the included distance. Its pricing rules are not identical to those in the first program.
- `tryToRaiseFee()` modifies only its local copy of `fee`. The caller's original value remains unchanged.
- `tryQuote()` leaves `outFee` unchanged when the quote fails and returns `false`. Callers should check the Boolean result before using the output as a new quote.
- The surge calculation uses integer arithmetic. If the multiplication result is not divisible by `100`, the division truncates the fractional part.
- The `while` loop in the first program checks the next distance before incrementing `km`; this produces a farthest affordable distance of 10 km for a 6000-paise budget.
- The second program can afford four 8 km standard-price orders from a 20000-paise budget, leaving 2000 paise.
- Both programs compile without warnings under the specified GCC command on a typical GCC implementation that supports C++20.

