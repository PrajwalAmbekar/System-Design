# Billing, Integer Safety & Basic C++ Classes

These programs evolve a small billing example from procedural functions, through a debugging session, to a basic object-oriented design using `Product` and `LineItem` classes.

## Contents

| File | Description |
|---|---|
| `code3_billing.cpp` | Initial billing implementation using functions, integer money representation, discount and tax calculation |
| `code3_billing_buggy.cpp` | Debugging session demonstrating integer overflow, integer division, and an uninitialized variable |
| `code4_product_lineitem.cpp` | Object-oriented version using `Product` and `LineItem` classes and class instances |

## Requirements

- C++ compiler with C++23 support
- `g++`
- C++23 standard
- Supported OS: Linux, macOS, or Windows with a suitable C++23 environment

---

## Build and Run

### 1. `code3_billing.cpp`

Compile:

```bash
g++ -std=c++23 code3_billing.cpp -o billing
```

Run:

```bash
./billing
```

Expected output:

```text
Subtotal Rs.70.00
DiscountedAmount Rs.7.00
TaxAmount Rs.11.34
Total Rs.74.34
```

The program stores money in **paise**:

- Keyboard: `1000` paise × `2` = `2000` paise
- Monitor: `2500` paise × `1` = `2500` paise
- Mouse: `500` paise × `5` = `2500` paise
- Subtotal = `7000` paise = `Rs.70.00`
- 10% discount = `Rs.7.00`
- 18% tax on the discounted amount = `Rs.11.34`
- Final total = `Rs.74.34`

---

### 2. `code3_billing_buggy.cpp`

Compile:

```bash
g++ -std=c++23 -Wall -Wextra -g code3_billing_buggy.cpp -o billing_buggy
```

Run:

```bash
./billing_buggy
```

The program does **not have one reliable exact output** because `total` is used before it is initialized.

The intended calculations in the source are:

```text
2 keyboards = 2000 paise
1 monitor   = 2500 paise
total       = 4500 paise
```

However, this line:

```cpp
int total;
```

does not initialize `total`. The subsequent `total += ...` operations therefore read an indeterminate value, resulting in undefined behavior.

The `bulkOrder` calculation also overflows `int`:

```text
2,000,000 × 1,500 = 3,000,000,000
```

which is greater than the maximum guaranteed value of a 32-bit `int` (`2,147,483,647`).

---

### 3. `code4_product_lineitem.cpp`

Compile:

```bash
g++ -std=c++23 code4_product_lineitem.cpp -o product_lineitem
```

Run:

```bash
./product_lineitem
```

Expected output:

```text
Product: Keyboard, Quantity: 1, Total: Rs.10.00
Product: Monitor, Quantity: 1, Total: Rs.25.00
Product: Mouse, Quantity: 1, Total: Rs.5.00
Total Amount: Rs.40.00
```

The quantity behavior is important here.

The constructor contains:

```cpp
quantity_(quantity > 1 ? 1 : quantity)
```

Therefore:

- `2` becomes `1`
- `1` remains `1`
- `5` becomes `1`

So the program prints all three quantities as `1`.

---

## Code Evolution: Code 1 → Code 2 → Code 3

The three programs demonstrate a progression in the billing example.

```text
Code 1
Procedural Billing
      │
      ├── Functions
      ├── long long for money
      ├── Discount
      └── Tax
      │
      ▼
Code 2
Debugging Session
      │
      ├── Uninitialized int
      ├── Integer overflow
      └── Integer division
      │
      ▼
Code 3
Basic Object-Oriented Design
      │
      ├── Product class
      ├── LineItem class
      ├── Objects / instances
      ├── Encapsulation
      ├── Constructors
      └── Member functions
```

### Importance of the third code compared with the first

The third program changes the **structure** of the billing model rather than simply adding more calculations.

| Code 1 | Code 3 |
|---|---|
| Billing data is handled directly in `main()` | Product data belongs to `Product` |
| Billing calculations use standalone functions | Line-item calculation belongs to `LineItem` |
| Product name and price are passed directly to functions | Product state is stored inside an object |
| No class instances | Creates `Product` and `LineItem` objects |
| Focuses mainly on the calculation flow | Begins modeling real entities |
| Functions operate on supplied values | Member functions operate on object state |

The important improvement is **separation of responsibility**:

```text
Product
  ├── name
  └── price

LineItem
  ├── Product
  ├── quantity
  └── total()

main()
  ├── creates objects
  ├── calls object functions
  └── combines totals
```

This is the first step toward organizing a larger program around objects instead of keeping all data and operations directly inside `main()`.

---

# UML / Class Diagram — Code 3

## Class Diagram

```text
┌──────────────────────────────────┐
│             Product              │
├──────────────────────────────────┤
│ - name_ : std::string            │
│ - pricePaisa_ : long long        │
├──────────────────────────────────┤
│ + Product(name, pricePaisa)      │
│ + name() : const std::string&    │
│ + pricePaisa() : long long       │
└──────────────────┬───────────────┘
                   │
                   │ contains
                   │
                   ▼
┌──────────────────────────────────┐
│            LineItem              │
├──────────────────────────────────┤
│ - product_ : Product             │
│ - quantity_ : int                │
├──────────────────────────────────┤
│ + LineItem(product, quantity)    │
│ + total() : long long            │
│ + print() : void                 │
└──────────────────┬───────────────┘
                   │
                   │ creates / uses
                   ▼
                 main()
```

## Object Creation Flow

The important creation sequence in `main()` is:

```text
main()
 │
 ├── Product("Keyboard", 1000)
 │       │
 │       ▼
 │   temporary Product object
 │       │
 │       ▼
 │   passed to LineItem constructor
 │       │
 │       ▼
 │   keyboard LineItem object
 │
 ├── Product("Monitor", 2500)
 │       │
 │       ▼
 │   temporary Product object
 │       │
 │       ▼
 │   monitor LineItem object
 │
 └── Product("Mouse", 500)
         │
         ▼
     temporary Product object
         │
         ▼
     mouse LineItem object
```

### Instance Creation

These declarations create three `LineItem` instances:

```text
LineItem keyboard(...)
LineItem monitor(...)
LineItem mouse(...)
```

Each `LineItem` contains its own `Product` object and its own quantity.

```text
keyboard
 ├── product_
 │    ├── name_ = "Keyboard"
 │    └── pricePaisa_ = 1000
 └── quantity_ = 1

monitor
 ├── product_
 │    ├── name_ = "Monitor"
 │    └── pricePaisa_ = 2500
 └── quantity_ = 1

mouse
 ├── product_
 │    ├── name_ = "Mouse"
 │    └── pricePaisa_ = 500
 └── quantity_ = 1
```

## Runtime Flow

```text
                    main()
                      │
          ┌───────────┼───────────┐
          │           │           │
          ▼           ▼           ▼
      keyboard     monitor      mouse
      LineItem     LineItem     LineItem
          │           │           │
          ▼           ▼           ▼
      keyboard.    monitor.     mouse.
       print()      print()      print()
          │           │           │
          └───────────┼───────────┘
                      │
                      ▼
             keyboard.total()
                      +
             monitor.total()
                      +
               mouse.total()
                      │
                      ▼
              totalAmount
                      │
                      ▼
                std::cout
```

---

## Command Reference

| Command Part | Meaning | Example |
|---|---|---|
| `g++` | GNU C++ compiler command | `g++ ...` |
| `-std=c++23` | Compile using the C++23 language standard | `-std=c++23` |
| `-Wall` | Enable a broad set of compiler warnings | `-Wall` |
| `-Wextra` | Enable additional compiler warnings | `-Wextra` |
| `-g` | Include debugging information in the executable | `-g` |
| `code3_billing.cpp` | Input C++ source file | `code3_billing.cpp` |
| `code3_billing_buggy.cpp` | Input C++ source file | `code3_billing_buggy.cpp` |
| `code4_product_lineitem.cpp` | Input C++ source file | `code4_product_lineitem.cpp` |
| `-o` | Specifies the name of the generated executable | `-o billing` |
| `billing` | Output executable name | `-o billing` |
| `billing_buggy` | Output executable name | `-o billing_buggy` |
| `product_lineitem` | Output executable name | `-o product_lineitem` |
| `./billing` | Runs the `billing` executable from the current directory | `./billing` |
| `./billing_buggy` | Runs the `billing_buggy` executable | `./billing_buggy` |
| `./product_lineitem` | Runs the `product_lineitem` executable | `./product_lineitem` |

---

## Key Terms

### Program Structure

| Term | Meaning | Example from the code |
|---|---|---|
| `main` | Entry point of the C++ program | `int main()` |
| Function | Named block of code that performs an operation | `applyDiscount(...)` |
| Parameter | Value received by a function | `int discountPercent` |
| Return value | Value produced by a function | `return paisa * ...` |
| `return` | Ends a function and optionally provides a value | `return 0;` |
| `class` | Defines a user-created type containing data and functions | `class Product` |
| Object / instance | A concrete object created from a class | `LineItem keyboard(...)` |
| Constructor | Special member function used when an object is created | `Product(...)` |
| Member function | Function belonging to a class | `total()`, `print()` |
| Getter | Member function used to access stored data | `name()` |
| `private` | Restricts direct access to class members | `private:` |
| `public` | Makes class members accessible from outside the class | `public:` |
| `const` | Indicates that the function does not modify the object | `total() const` |

### Data Types

| Type | Stores | Typical size | Example |
|---|---|---:|---|
| `int` | Whole-number values | Typically 4 bytes | `int quantity_` |
| `long long` | Larger whole-number values | Typically 8 bytes | `long long pricePaisa_` |
| `double` | Floating-point values | Typically 8 bytes | `double average` |
| `void` | No value | N/A | `void print()` |
| `char*` | Pointer to character data | Platform-dependent | `char* argv[]` |
| `const char*` | Pointer to character data that cannot be modified through the pointer | Platform-dependent | `const char* label` |
| `std::string` | Text | Implementation-dependent | `std::string name_` |

### Keywords and Operators

| Term | Meaning | Example from the code |
|---|---|---|
| `const` | Prevents modification of a declared value or object through the specified interface | `const int TAX_PERCENT` |
| `class` | Defines a class type | `class Product` |
| `private` | Starts the private section of a class | `private:` |
| `public` | Starts the public section of a class | `public:` |
| `return` | Returns control/value from a function | `return paisa * ...` |
| `if` | Executes code conditionally | `quantity > 1 ? 1 : quantity` uses the conditional operator instead |
| `? :` | Conditional operator; selects one of two expressions | `pricePaisa < 0 ? 0 : pricePaisa` |
| `::` | Scope resolution operator used to access names inside a namespace | `std::cout` |
| `.` | Accesses a member through an object | `keyboard.print()` |
| `*` | Multiplication operator | `unitPaisa * qty` |
| `/` | Division operator | `paisa / 100` |
| `%` | Remainder operator | `paisa % 100` |
| `+=` | Adds a value to an existing variable | `subtotal += lineTotal(...)` |
| `-` | Subtraction operator | `subtotal - finalDiscountedAmount` |
| `>` | Greater-than comparison | `quantity > 1` |
| `<` | Less-than comparison | `pricePaisa < 0` |
| `<<` | Stream insertion operator used with output streams | `std::cout << label` |
| `()` | Function call / parameter list syntax | `keyboard.print()` |
| `{}` | Defines a block or initializes a class member/body | `class Product { ... }` |
| `&` | Reference declarator | `const std::string& name()` |
| `std::move` | Converts its argument to an rvalue reference for moving | `std::move(name)` |

### Standard Library Names

| Name | Header | Meaning |
|---|---|---|
| `std::cout` | `<iostream>` | Standard output stream |
| `std::endl` | `<iostream>` | Inserts a newline and flushes the output stream |
| `std::string` | `<string>` | Standard string type |
| `std::move` | `<string>` | Used to move the supplied object/value |
| `std::setw` | `<iomanip>` | Sets the minimum width for the next formatted output |
| `std::setfill` | `<iomanip>` | Sets the character used to fill extra output width |

---

## Initialization

| Form | Example | Result |
|---|---|---|
| Variable initialization | `const int discountPercent = 10` | Creates an integer constant initialized to `10` |
| Object initialization | `LineItem keyboard(Product("Keyboard", 1000), 2)` | Creates a `LineItem` object |
| Constructor member initialization | `name_(std::move(name))` | Initializes `name_` using the constructor argument |
| Conditional initialization | `pricePaisa_(pricePaisa < 0 ? 0 : pricePaisa)` | Stores `0` for a negative price; otherwise stores the supplied price |
| Zero initialization | `long long subtotal = 0` | Starts `subtotal` at `0` |

---

## Topics Covered

- Procedural billing calculations
- Functions and parameters
- `long long` for integer money representation
- Integer arithmetic
- Integer division
- Floating-point conversion
- Integer overflow
- Uninitialized local variables
- Compiler warnings with `-Wall -Wextra`
- Debug information with `-g`
- Classes and objects
- Constructors
- Private data members
- Public member functions
- Encapsulation through member functions
- Getter functions
- Object composition through `LineItem` containing `Product`
- Conditional operator
- `std::string`
- `std::move`
- Formatted output using `std::setw` and `std::setfill`
- Basic UML/class/object flow

---

## Notes

- In `code3_billing.cpp`, money is represented as **paise using `long long`**, avoiding floating-point representation for the billing calculations.
- `1000` paise represents `Rs.10.00`.
- Integer division discards the fractional part. In Code 2, `total / 3` performs integer division because both operands are integers.
- `double average` does not make `total / 3` floating-point automatically; the division happens before the result is assigned to `average`.
- `int bulkOrder = 2000000 * 1500` can overflow because both operands are `int` and the mathematical result is `3,000,000,000`.
- `int total;` in Code 2 leaves the local variable uninitialized. Reading it through `total += ...` produces undefined behavior.
- `-Wall -Wextra` can diagnose some issues, including use of an uninitialized variable in cases where the compiler can detect the problem. Compiler diagnostics can vary by compiler version and optimization settings.
- In Code 3, the quantity expression does not enforce positivity. It maps every quantity greater than `1` to `1`.
- Therefore, the `keyboard` quantity becomes `1` instead of `2`, and the `mouse` quantity becomes `1` instead of `5`.
- The exact size of `int`, `long long`, and pointers is implementation-dependent. The commonly used sizes shown in the data-type table are typical, not guaranteed by the C++ standard.
- Code 3 introduces object-based organization: `Product` represents product information, while `LineItem` represents a product together with a quantity and its calculated total.

---

