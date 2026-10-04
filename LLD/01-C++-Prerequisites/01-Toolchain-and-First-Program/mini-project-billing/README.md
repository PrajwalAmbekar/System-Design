# Command-Line Billing and Input Parsing

This program extends the invoice design into a command-line billing application. It demonstrates command-line arguments, numeric parsing with `std::stoll`, validation, references, exception handling, formatted output, logging, and the existing `Invoice`/`Logger` relationship.

## Contents

| File | Description |
|---|---|
| `billing.cpp` | Command-line invoice program that parses discount, item prices, and quantities, validates them, calculates the grand total, and reports errors |

## Requirements

- GNU C++ compiler (`g++`)
- C++20 standard
- C++ standard library
- Supported OS: Linux, macOS, or Windows with a suitable `g++` environment

---

## Build and Run

### `billing.cpp`

Compile:

```bash
g++ -std=c++20 -Wall -Wextra -g billing.cpp -o billing
```

Run with valid input:

```bash
./billing 10 19999 2 49900 1
```

Expected output:

```text
       Grand total:  : Rs. 954.71
```

The program receives:

```text
10     → discount percentage
19999  → item 1 price in paise
2      → item 1 quantity
49900  → item 2 price in paise
1      → item 2 quantity
```

The calculation is:

```text
Item 1 = 19999 × 2 = 39998 paise
Item 2 = 49900 × 1 = 49900 paise

Subtotal = 89898 paise

10% discount:
89898 × 90 / 100 = 80908 paise

18% tax:
80908 × 18 / 100 = 14563 paise

Grand total:
80908 + 14563 = 95471 paise
              = Rs. 954.71
```

Because the calculations use `long long` paise, fractional paise are discarded during integer division.

### Invalid numeric input

Run:

```bash
./billing 10 19999 abc
```

Expected output:

```text
[ERROR] bad number near argument 2
```

The program returns exit status `3`.

Here:

```text
argv[1] = "10"
argv[2] = "19999"
argv[3] = "abc"
```

`"abc"` cannot be parsed as a `long long`, so `parseNumber()` returns `false` and the program reports the input error.

---

# Command-Line Input Structure

The program expects this structure:

```text
./billing <discount-percent> <item1-unit-price-paise> <item1-quantity> ...
```

For example:

```text
./billing 10 19999 2 49900 1
```

The arguments are interpreted as:

```text
argv[0] → ./billing
argv[1] → 10
argv[2] → 19999
argv[3] → 2
argv[4] → 49900
argv[5] → 1
```

The program processes the item arguments in pairs:

```text
price + quantity
   │       │
   ▼       ▼
argv[2]  argv[3]

argv[4]  argv[5]
```

The loop:

```text
i = 2
i = 4
i = 6
...
```

moves to the next price/quantity pair using `i += 2`.

---

# Numeric Parsing Flow

The central parsing operation is:

```text
Command-line argument
        │
        ▼
      char*
        │
        ▼
   parseNumber()
        │
        ▼
    std::stoll()
        │
        ▼
   long long value
        │
        ▼
   validation
```

For example:

```text
"19999"
   │
   ▼
std::stoll()
   │
   ├── parsed value = 19999
   └── used = 5
   │
   ▼
text[5] == '\0'
   │
   ▼
true
```

For:

```text
"19999abc"
```

the parser can read the numeric prefix:

```text
19999abc
│────│
 5 characters consumed
```

So:

```text
used = 5
text[used] = 'a'
```

Therefore:

```text
text[used] == '\0'
```

is false.

This prevents the program from accepting an argument that contains a valid number followed by extra characters.

---

# How `parseNumber()` Works

The function is:

```cpp
bool parseNumber(const char* text, long long& out)
```

It has two parameters.

| Parameter | Type | Purpose |
|---|---|---|
| `text` | `const char*` | The command-line text to parse |
| `out` | `long long&` | Reference to the caller's variable where the parsed number is stored |

For example:

```text
long long discount = 0;

parseNumber(argv[1], discount);
```

Before the call:

```text
discount
   │
   ▼
   0
```

Inside `parseNumber()`:

```text
std::stoll(text, &used)
        │
        ▼
     number
        │
        ▼
      out
        │
        ▼
  caller's discount
```

After successful parsing:

```text
discount
   │
   ▼
  10
```

Because `out` is a reference, the function modifies the original `discount` variable.

## `std::size_t used`

`std::size_t` is an unsigned integer type provided by the standard library and commonly used for sizes and indexes.

Here it stores the number of characters consumed by `std::stoll()`.

```cpp
std::size_t used = 0;
```

After parsing:

```text
"19999"
 │
 └────── 5 characters consumed

used = 5
```

It is used as an index:

```cpp
text[used]
```

to inspect the character immediately after the parsed number.

## `std::stoll()`

`std::stoll()` means **string to long long**.

It converts numeric text into a `long long`.

```text
"19999"
   │
   ▼
std::stoll()
   │
   ▼
19999
```

Its second argument:

```cpp
&used
```

allows the function to report how many characters were consumed.

## Why `&used`?

`used` is a local variable inside `parseNumber()`.

The `&` here is the **address-of operator**. It gives `std::stoll()` access to `used` so that the function can write the number of consumed characters into it.

This is different from:

```cpp
long long& out
```

where `&` declares a reference parameter.

---

# Parsing Success and Failure

The function has two possible paths.

## Successful parsing

```text
"19999"
   │
   ▼
std::stoll()
   │
   ├── out = 19999
   └── used = 5
   │
   ▼
text[5] == '\0'
   │
   ▼
true
```

## Parsing failure

```text
"abc"
   │
   ▼
std::stoll()
   │
   ▼
exception
   │
   ▼
catch (...)
   │
   ▼
return false
```

The `try`/`catch` block prevents a parsing exception from escaping `parseNumber()`.

---

# Input Validation Flow

The program validates input at several levels.

```text
Command-line arguments
          │
          ▼
   Argument count check
          │
       valid?
      /      \
    no        yes
    │          │
    ▼          ▼
usage error  parse discount
               │
            valid?
           /      \
         no        yes
         │          │
         ▼          ▼
    input error   parse items
                      │
                      ▼
               validate numbers
                      │
                      ▼
                addItem()
                      │
                      ▼
               calculate total
```

## Discount validation

```cpp
discount < 0 || discount > 100
```

The discount must be between `0` and `100`.

If not:

```text
kInputError = 3
```

is returned.

## Item validation

Each price and quantity must successfully parse.

The program also limits:

```text
price <= 1,000,000,000
quantity <= 1,000,000
```

The `Invoice::addItem()` function additionally rejects:

```text
unitPaise < 0
quantity <= 0
```

---

# Object Flow

The program retains the object relationship introduced in the previous session.

```text
main()
  │
  ├── creates Logger
  │
  ▼
Logger log
  │
  │ passed by reference
  ▼
Invoice invoice(log)
  │
  └── logger_ refers to the same Logger
```

The relationship is:

```text
Logger ◄──────── Invoice
          const reference
```

`Invoice` does not create another `Logger`.

When invalid input is detected inside `Invoice`, it uses:

```text
logger_.error(...)
```

to communicate through the existing `Logger`.

---

# Item Creation Flow

For:

```bash
./billing 10 19999 2 49900 1
```

the loop processes:

```text
i = 2
 │
 ├── argv[2] → price = 19999
 ├── argv[3] → qty   = 2
 └── name = "item1"

i = 4
 │
 ├── argv[4] → price = 49900
 ├── argv[5] → qty   = 1
 └── name = "item2"
```

The name expression:

```cpp
std::string name = "item" + std::to_string((i - 2) / 2 + 1);
```

generates sequential item names.

| `i` | Calculation | Result |
|---:|---|---|
| `2` | `(2 - 2) / 2 + 1` | `item1` |
| `4` | `(4 - 2) / 2 + 1` | `item2` |
| `6` | `(6 - 2) / 2 + 1` | `item3` |

The expression uses integer division because `i`, `2`, and `1` are integers.

---

# Money Formatting

The program stores money as integer paise internally but prints it as rupees.

The output function uses:

```text
paise / 100.0
```

so the value becomes a floating-point number for display.

For example:

```text
95471 paise
     │
     ▼
954.71
```

The output formatting is then:

```text
std::fixed
     │
     ▼
fixed decimal notation

std::setprecision(2)
     │
     ▼
exactly 2 digits after decimal

std::setw(20)
     │
     ▼
minimum field width of 20

std::left
     │
     ▼
left-align the label
```

---

## Command Reference

| Command Part | Meaning | Example |
|---|---|---|
| `g++` | GNU C++ compiler | `g++ ...` |
| `-std=c++20` | Compiles using the C++20 language standard | `-std=c++20` |
| `-Wall` | Enables a broad set of compiler warnings | `-Wall` |
| `-Wextra` | Enables additional compiler warnings | `-Wextra` |
| `-g` | Adds debugging information to the executable | `-g` |
| `billing.cpp` | Input C++ source file | `billing.cpp` |
| `-o` | Specifies the output executable name | `-o billing` |
| `billing` | Name of the generated executable | `billing` |
| `./billing` | Runs the executable from the current directory | `./billing` |
| `10` | Discount percentage argument | `./billing 10 ...` |
| `19999` | Item unit price in paise | `./billing 10 19999 ...` |
| `2` | Item quantity | `./billing 10 19999 2 ...` |
| `49900` | Second item unit price in paise | `./billing 10 19999 2 49900 1` |
| `1` | Second item quantity | `./billing 10 19999 2 49900 1` |
| `abc` | Invalid numeric argument used to demonstrate parsing failure | `./billing 10 19999 abc` |

---

## Key Terms

### Program Structure

| Term | Meaning | Example from the code |
|---|---|---|
| `main` | Entry point of the program | `int main(int argc, char* argv[])` |
| `argc` | Number of command-line arguments | `argc < 4` |
| `argv` | Array containing command-line arguments | `argv[1]` |
| Function | Named block of code performing an operation | `parseNumber()` |
| Parameter | Value supplied to a function | `const char* text` |
| `if` | Executes a block when a condition is true | `if (unitPaise < 0 || qty <= 0)` |
| `for` | Repeats code while its condition remains true | `for (int i = 2; ...)` |
| `try` | Begins a block where an exception may be handled | `try { ... }` |
| `catch` | Handles an exception from a `try` block | `catch (...)` |
| `return` | Ends a function and optionally returns a value | `return kInputError` |
| Class | Defines a user-created type | `class Invoice` |
| Object / instance | Concrete object created from a class | `Invoice invoice(log)` |
| Constructor | Initializes an object when it is created | `Invoice(const Logger& logger)` |
| Reference | Another name for an existing object | `long long& out` |

### Data Types

| Type | Stores | Typical size | Example |
|---|---|---:|---|
| `bool` | `true` or `false` | Typically 1 byte | `bool parseNumber(...)` |
| `int` | Whole-number values | Typically 4 bytes | `int itemCount_` |
| `long long` | Larger whole-number values | Typically 8 bytes | `long long subtotalPaise_` |
| `std::size_t` | Sizes and indexes | Implementation-dependent | `std::size_t used` |
| `std::string` | Text | Implementation-dependent | `std::string name` |
| `char*` | Pointer to character data | Platform-dependent | `char* argv[]` |
| `const char*` | Pointer to character data that cannot be modified through it | Platform-dependent | `const char* text` |
| `void` | No value | N/A | `void printMoney(...)` |

### Keywords and Operators

| Term | Meaning | Example from the code |
|---|---|---|
| `const` | Prevents modification through the specified variable/reference/function | `const Logger& logger_` |
| `class` | Defines a class | `class Logger` |
| `private` | Begins private class members | `private:` |
| `public` | Begins publicly accessible class members | `public:` |
| `explicit` | Prevents implicit conversion through a constructor | `explicit Invoice(...)` |
| `static` | Makes a class member belong to the class rather than each object | `static const int TAX_PERCENT` |
| `try` | Begins exception-handling block | `try` |
| `catch` | Handles an exception | `catch (...)` |
| `return` | Returns from a function | `return false` |
| `static_cast` | Explicitly converts a value to another type | `static_cast<int>(qty)` |
| `&` | Declares a reference or obtains an address depending on context | `long long& out`, `&used` |
| `*` | Multiplication operator | `unitPaise * qty` |
| `/` | Division operator | `discounted / 100` |
| `%` | Remainder operator | `(argc - 2) % 2` |
| `+` | Addition or string concatenation | `"item" + std::to_string(...)` |
| `-` | Subtraction | `i - 2` |
| `+=` | Adds a value to an existing variable | `subtotalPaise_ += unitPaise * qty` |
| `++` | Increments a value by one | `++itemCount_` |
| `<` | Less-than comparison | `discount < 0` |
| `>` | Greater-than comparison | `discount > 100` |
| `<=` | Less-than-or-equal comparison | `qty <= 0` |
| `==` | Equality comparison | `text[used] == '\0'` |
| `||` | Logical OR | `unitPaise < 0 || qty <= 0` |
| `.` | Accesses a member through an object | `invoice.addItem(...)` |
| `[]` | Accesses an element by index | `argv[1]`, `text[used]` |
| `()` | Function call or parameter list | `parseNumber(...)` |
| `{}` | Defines a block | `if (...) { ... }` |
| `::` | Scope resolution used to access names inside `std` | `std::stoll` |
| `<<` | Inserts data into an output stream | `std::cout << ...` |
| `...` | Catch-all exception handler | `catch (...)` |

### Standard Library Names

| Name | Header | Meaning |
|---|---|---|
| `std::cout` | `<iostream>` | Standard output stream |
| `std::cerr` | `<iostream>` | Standard error stream |
| `std::endl` | `<iostream>` | Inserts a newline and flushes the stream |
| `std::string` | `<string>` | Standard string type |
| `std::stoll` | `<string>` | Converts a string to `long long` and can report consumed characters |
| `std::to_string` | `<string>` | Converts a numeric value to a string |
| `std::size_t` | Standard library | Unsigned integer type commonly used for sizes and indexes |
| `std::setw` | `<iomanip>` | Sets the minimum field width for the next output |
| `std::left` | `<iomanip>` | Left-aligns formatted output within its field |
| `std::fixed` | `<iomanip>` | Uses fixed-point notation for floating-point output |
| `std::setprecision` | `<iomanip>` | Controls the number of digits after the decimal when used with `fixed` |

---

## Initialization

| Form | Example | Result |
|---|---|---|
| Constant initialization | `const int kUsageError = 2` | Creates an integer constant with value `2` |
| Constant initialization | `const int kInputError = 3` | Creates an integer constant with value `3` |
| Zero initialization | `long long discount = 0` | Starts `discount` at zero |
| Multiple variable initialization | `long long price = 0, qty = 0` | Initializes both variables to zero |
| Default member initialization | `long long subtotalPaise_ = 0` | Starts the invoice subtotal at zero |
| Default member initialization | `int itemCount_ = 0` | Starts the item count at zero |
| Constructor initialization | `Invoice(const Logger& logger) : logger_(logger)` | Initializes the reference member to refer to the supplied `Logger` |
| Object initialization | `Logger log` | Creates a `Logger` object |
| Object initialization | `Invoice invoice(log)` | Creates an `Invoice` using the existing `Logger` |

---

## Topics Covered

- Command-line arguments
- `argc` and `argv`
- Command-line input validation
- Numeric string parsing
- `std::stoll`
- `std::size_t`
- Reference parameters
- Address-of operator
- Exception handling with `try` and `catch`
- Validation of parsed values
- Error codes
- `static_cast`
- Integer arithmetic using paise
- Integer division and truncation
- Floating-point formatting
- `std::setw`
- `std::left`
- `std::fixed`
- `std::setprecision`
- `std::cout` and `std::cerr`
- `Logger` and `Invoice` classes
- Constructor dependency through a reference
- `explicit` constructor
- Static class constant
- Input-driven invoice construction
- Basic loop-based argument processing

---

## Notes

- `kUsageError` is `2` and is returned when the command-line argument structure is invalid.
- `kInputError` is `3` and is returned when a supplied value cannot be parsed or fails validation.
- `parseNumber()` returns `true` only when the entire supplied text represents a valid parsed number.
- `std::stoll()` may parse a valid numeric prefix, so `text[used] == '\0'` is used to reject extra characters after the number.
- `long long& out` allows `parseNumber()` to write the parsed result directly into the caller's variable.
- `&used` passes the address of the local `used` variable to `std::stoll()` so the function can report how many characters it consumed.
- `catch (...)` catches any exception thrown during the parsing operation and converts it into `false`.
- The discount is validated to be between `0` and `100`.
- Each item price is limited to `1,000,000,000` paise and each quantity to `1,000,000`.
- `static_cast<int>(qty)` explicitly converts the parsed `long long` quantity to `int` after the code has already checked that the quantity does not exceed `1,000,000`.
- `std::string name = "item" + std::to_string(...)` generates sequential names such as `item1`, `item2`, and `item3`.
- The loop processes price and quantity in pairs by increasing `i` by `2`.
- `grandTotal()` performs the discount and tax calculations using integer paise. Integer division truncates fractional paise.
- `paise / 100.0` uses `100.0`, rather than `100`, so the final display calculation is floating-point.
- `std::fixed` together with `std::setprecision(2)` produces exactly two digits after the decimal point.
- `std::setw(20)` specifies a minimum width; it does not truncate text longer than the width.
- `std::left` causes the label to be left-aligned within that width.
- `std::cerr` is used for errors, while `std::cout` is used for the final billing output.
- `Invoice` stores a `const Logger&`, so it refers to the externally created `Logger` object rather than creating another logger.
- The exact sizes of `int`, `long long`, `std::size_t`, and pointers are implementation-dependent.
- The source includes no `-Werror`, so compiler warnings do not automatically turn into compilation errors.

---
