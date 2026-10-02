# Invoice Logging and Object Relationships

This session evolves the billing design from Code 1's procedural billing, through Code 2's debugging of unsafe arithmetic, and Code 3's composition-based `Product`/`LineItem` model to Code 4's `Invoice` and `Logger` design. The main focus is object relationships: Code 3 uses composition, while Code 4 uses an externally created `Logger` through a reference-based association.

## Contents

| File | Description |
|---|---|
| `code5_invoice_logger.cpp` | Invoice processing with validation, logging, discount/tax calculation, and a reference to an external `Logger` object |

## Requirements

- GNU C++ compiler (`g++`)
- C++23 standard
- A terminal capable of displaying standard output and standard error
- Supported OS: Linux, macOS, or Windows with a suitable C++23 environment

---

## Build and Run

### `code5_invoice_logger.cpp`

Compile:

```bash
g++ -std=c++23 code5_invoice_logger.cpp -o invoice_logger
```

Run:

```bash
./invoice_logger
```

Expected terminal output:

```text
[INFO]: Added item: Keyboard with unit price: 1000 and quantity: 2
[INFO]: Added item: Monitor with unit price: 2500 and quantity: 1
[INFO]: Added item: Mouse with unit price: 500 and quantity: 5
[ERROR]: Rejected item: FaultyItem with unit price: -100 and quantity: 1
Grand Total Rs.74.34
```

The program returns exit status `1` because the final condition checks whether `itemCount()` equals `4`, while only three items are successfully added.

The billing calculation is:

```text
Subtotal       = 2000 + 2500 + 2500
               = 7000 paise
               = Rs.70.00

10% discount   = Rs.7.00
Discounted     = Rs.63.00

18% tax        = Rs.11.34

Grand Total    = Rs.74.34
```

---

# Code Evolution: Code 1 → Code 2 → Code 3 → Code 4

The same billing problem is progressively reorganized across the sessions.

```text
┌─────────────────────────────────────────────────────────────┐
│ CODE 1 — Procedural Billing                                 │
│                                                             │
│ main()                                                      │
│  ├── subtotal                                               │
│  ├── lineTotal()                                            │
│  ├── applyDiscount()                                        │
│  └── printBill()                                            │
│                                                             │
│ Focus: calculations and functions                           │
└──────────────────────────────┬──────────────────────────────┘
                               │
                               ▼
┌─────────────────────────────────────────────────────────────┐
│ CODE 2 — Debugging Session                                  │
│                                                             │
│ Identifies problems with:                                   │
│  ├── uninitialized int                                      │
│  ├── integer overflow                                       │
│  └── integer division                                       │
│                                                             │
│ Focus: understanding incorrect/unsafe arithmetic            │
└──────────────────────────────┬──────────────────────────────┘
                               │
                               ▼
┌─────────────────────────────────────────────────────────────┐
│ CODE 3 — Product + LineItem                                 │
│                                                             │
│ Product                                                     │
│    ▲                                                        │
│    │ contains                                               │
│    │                                                        │
│ LineItem                                                    │
│                                                             │
│ Focus: classes, objects and composition                     │
└──────────────────────────────┬──────────────────────────────┘
                               │
                               ▼
┌─────────────────────────────────────────────────────────────┐
│ CODE 4 — Invoice + Logger                                   │
│                                                             │
│ Logger ◄──────── Invoice                                    │
│          reference                                          │
│                                                             │
│ Logger is created externally by main().                     │
│ Invoice receives and uses that Logger.                      │
│                                                             │
│ Focus: association, dependency and object collaboration     │
└─────────────────────────────────────────────────────────────┘
```

## Design Evolution

| Stage | Main design idea | Relationship |
|---|---|---|
| Code 1 | Functions operate on billing values | No class relationship |
| Code 2 | Existing implementation is examined for bugs | Debugging and type/arithmetic behavior |
| Code 3 | `LineItem` contains a `Product` object | **Composition** |
| Code 4 | `Invoice` uses an externally created `Logger` | **Association / dependency** |

### Code 3: Composition

In Code 3, `LineItem` contains:

```text
LineItem
    │
    └── product_ : Product
```

`product_` is a `Product` object stored directly inside the `LineItem`.

The `Product` therefore forms part of the state of the `LineItem`.

```text
LineItem
┌─────────────────────┐
│ product_ : Product  │
│ quantity_ : int     │
└─────────────────────┘
```

This is represented as **composition** in the UML model because `LineItem` contains the `Product` object by value.

### Code 4: Logger Association

Code 4 changes the relationship.

`Logger` is created in `main()`:

```text
main()
  │
  ├── creates Logger
  │
  └── creates Invoice(logger)
                    │
                    ▼
               logger_
                    │
                    ▼
              existing Logger
```

`Invoice` does not create the `Logger` and does not store a `Logger` object by value.

Instead:

```cpp
const Logger& logger_;
```

means that `Invoice` holds a reference to the existing `Logger`.

Therefore:

```text
main()
 │
 │ creates
 ▼
Logger
 │
 │ passed by reference
 ▼
Invoice
 │
 │ logger_
 ▼
same Logger object
```

There is **no composition** between `Invoice` and `Logger`.

The lifetime of the `Logger` object is controlled by the object created in `main()`, not by `Invoice`.

---

# UML Class Diagram

## Code 4 Class Diagram

```text
┌──────────────────────────────────────────────┐
│                   Logger                     │
├──────────────────────────────────────────────┤
│                                              │
├──────────────────────────────────────────────┤
│ + info(message : const std::string&) : void │
│ + error(message : const std::string&) : void│
└───────────────────────▲──────────────────────┘
                        │
                        │ association
                        │ const reference
                        │
┌───────────────────────┴──────────────────────┐
│                  Invoice                     │
├──────────────────────────────────────────────┤
│ - logger_ : const Logger&                    │
│ - subtotalPaisa_ : long long = 0             │
│ - itemCount_ : int = 0                       │
│ - TAX_PERCENT : static const int = 18        │
├──────────────────────────────────────────────┤
│ + Invoice(logger : const Logger&)            │
│ + addItem(name : const std::string&,         │
│           unitPaisa : long long,             │
│           quantity : int) : bool             │
│ + itemCount() : int                          │
│ + grandTotal(discountPercent : int) :        │
│   long long                                  │
│ + printInvoice(label : const char*,          │
│                paisa : long long) : void     │
└──────────────────────────────────────────────┘
```

## Relationship Meaning

```text
             const Logger&
Logger ─────────────────────────── Invoice
        association / uses
```

The important point is that the arrow does **not** represent ownership.

```text
Logger object
     │
     │ created by
     ▼
   main()
     │
     │ passed to
     ▼
Invoice
     │
     └── logger_ ───────────────► same Logger object
```

`Invoice` can call:

```text
logger_.info(...)
logger_.error(...)
```

but it does not create or destroy the `Logger` object.

### Association vs Dependency in this Code

The code demonstrates a **reference-based association** because `Invoice` stores:

```cpp
const Logger& logger_;
```

It also demonstrates dependency because `Invoice` uses the `Logger` type and its functions to perform logging.

For this particular UML class diagram, the stored reference is the important relationship to show as the association.

```text
                 creates
main() ─────────────────────────► Logger
  │
  │ passes Logger reference
  ▼
Invoice ────────────────────────► Logger
          association
          const reference
```

There is therefore no composition diamond between `Invoice` and `Logger`.

---

# Object Creation and Runtime Flow

## Step 1 — Create Logger

```text
main()
  │
  ▼
Logger logger;
  │
  ▼
Logger object created
```

## Step 2 — Create Invoice

```text
Invoice invoice(logger);
             │
             │ reference passed
             ▼
        Logger object

             │
             ▼
       logger_ refers to
       the same Logger
```

No new `Logger` object is created inside `Invoice`.

## Step 3 — Add Valid Items

```text
invoice.addItem("Keyboard", 1000, 2)
              │
              ├── validation passes
              ├── subtotalPaisa_ += 2000
              ├── itemCount_ becomes 1
              └── logger_.info(...)

invoice.addItem("Monitor", 2500, 1)
              │
              ├── validation passes
              ├── subtotalPaisa_ += 2500
              ├── itemCount_ becomes 2
              └── logger_.info(...)

invoice.addItem("Mouse", 500, 5)
              │
              ├── validation passes
              ├── subtotalPaisa_ += 2500
              ├── itemCount_ becomes 3
              └── logger_.info(...)
```

## Step 4 — Reject Invalid Item

```text
invoice.addItem("FaultyItem", -100, 1)
              │
              ▼
      unitPaisa < 0
              │
              ▼
          rejected
              │
              ├── logger_.error(...)
              ├── return false
              └── itemCount_ remains 3
```

## Step 5 — Calculate Grand Total

```text
subtotalPaisa_
      │
      ▼
10% discount
      │
      ▼
discountedAmount
      │
      ▼
18% tax
      │
      ▼
discountedAmount + taxAmount
      │
      ▼
Rs.74.34
```

## Step 6 — Program Exit

```text
invoice.itemCount()
        │
        ▼
       3
        │
        ▼
3 == 4
        │
        ▼
     false
        │
        ▼
return 1
```

---

## Command Reference

| Command Part | Meaning | Example |
|---|---|---|
| `g++` | GNU C++ compiler | `g++ ...` |
| `-std=c++23` | Selects the C++23 language standard | `-std=c++23` |
| `code5_invoice_logger.cpp` | C++ source file passed to the compiler | `g++ ... code5_invoice_logger.cpp ...` |
| `-o` | Specifies the output executable name | `-o invoice_logger` |
| `invoice_logger` | Name of the generated executable | `-o invoice_logger` |
| `./invoice_logger` | Runs the executable in the current directory | `./invoice_logger` |

---

## Key Terms

### Program Structure

| Term | Meaning | Example from the code |
|---|---|---|
| `main` | Entry point of the program | `int main()` |
| `class` | Defines a user-created type | `class Logger` |
| Function | Named operation that can receive parameters and return a value | `addItem(...)` |
| Parameter | Value supplied to a function | `int discountPercent` |
| Constructor | Special member function used when an object is created | `Invoice(const Logger& logger)` |
| Member function | Function belonging to a class | `grandTotal()` |
| `if` | Executes a block when a condition is true | `if(unitPaisa < 0 || quantity <=0)` |
| `return` | Ends a function and optionally returns a value | `return false` |
| Object / instance | Concrete object created from a class | `Logger logger` |
| Reference | Another name referring to an existing object | `const Logger& logger_` |

### Data Types

| Type | Stores | Typical size | Example |
|---|---|---:|---|
| `bool` | `true` or `false` | Typically 1 byte | `bool addItem(...)` |
| `int` | Whole-number values | Typically 4 bytes | `int itemCount_` |
| `long long` | Larger whole-number values | Typically 8 bytes | `long long subtotalPaisa_` |
| `void` | No value | N/A | `void printInvoice(...)` |
| `std::string` | Text | Implementation-dependent | `const std::string& message` |
| `const char*` | Pointer to character data that cannot be modified through the pointer | Platform-dependent | `const char* label` |

### Keywords and Operators

| Term | Meaning | Example from the code |
|---|---|---|
| `class` | Defines a class type | `class Invoice` |
| `private` | Begins members accessible only from the class | `private:` |
| `public` | Begins members accessible from outside the class | `public:` |
| `const` | Prevents modification through the specified object/reference or function | `const Logger& logger_` |
| `explicit` | Prevents implicit conversion through a constructor | `explicit Invoice(...)` |
| `static` | Makes a class member belong to the class rather than each object | `static const int TAX_PERCENT` |
| `return` | Returns control/value from a function | `return true` |
| `::` | Scope resolution operator used to access names in `std` | `std::cout` |
| `&` | Declares a reference | `const Logger& logger_` |
| `=` | Initializes or assigns a value | `subtotalPaisa_ = 0` |
| `+=` | Adds a value to an existing variable | `subtotalPaisa_ += unitPaisa * quantity` |
| `++` | Increments a value by one | `++itemCount_` |
| `*` | Multiplication | `unitPaisa * quantity` |
| `/` | Division | `discountedAmount / 100` |
| `%` | Remainder | `paisa % 100` |
| `+` | Addition or string concatenation | `"Rejected item: " + name` |
| `-` | Subtraction | `100 - discountPercent` |
| `<` | Less-than comparison | `unitPaisa < 0` |
| `<=` | Less-than-or-equal comparison | `quantity <= 0` |
| `==` | Equality comparison | `itemCount() == 4` |
| `||` | Logical OR | `unitPaisa < 0 || quantity <=0` |
| `.` | Accesses a member through an object | `invoice.addItem(...)` |
| `()` | Calls a function or supplies constructor/function parameters | `invoice.itemCount()` |
| `{}` | Defines a class/function/block body | `class Logger { ... }` |
| `<<` | Inserts data into an output stream | `std::cerr << "[INFO]: "` |

### Standard Library Names

| Name | Header | Meaning |
|---|---|---|
| `std::cout` | `<iostream>` | Standard output stream |
| `std::cerr` | `<iostream>` | Standard error stream |
| `std::endl` | `<iostream>` | Inserts a newline and flushes the stream |
| `std::string` | `<string>` | Standard string type |
| `std::to_string` | `<string>` | Converts a numeric value to a string |
| `std::setw` | `<iomanip>` | Sets the minimum output width for the next formatted value |
| `std::setfill` | `<iomanip>` | Sets the character used to fill extra output width |

---

## Initialization

| Form | Example | Result |
|---|---|---|
| Object initialization | `Logger logger;` | Creates a `Logger` object |
| Constructor initialization | `Invoice invoice(logger);` | Creates an `Invoice` using the existing `Logger` object |
| Reference member initialization | `logger_(logger)` | Makes `logger_` refer to the supplied `Logger` object |
| Default member initialization | `subtotalPaisa_ = 0` | Initializes the invoice subtotal to zero |
| Default member initialization | `itemCount_ = 0` | Initializes the item count to zero |
| Static constant initialization | `static const int TAX_PERCENT = 18` | Defines the invoice tax percentage as `18` |

---

## Topics Covered

- Evolution from procedural billing to object-oriented design
- Classes and objects
- `Logger` and `Invoice` classes
- Constructors
- `explicit` constructors
- Reference members
- `const` references
- Association between objects
- Dependency through use of another class
- Composition from the previous `Product`/`LineItem` design
- Difference between composition and reference-based association
- Object creation in `main()`
- Passing an existing object to a constructor
- Object collaboration
- Encapsulation using `private` data members and `public` member functions
- Input validation
- Boolean return values
- Logging through `std::cerr`
- Standard output through `std::cout`
- Discount and tax calculation
- Integer money representation using paise
- Conditional program exit status

---

## Notes

- `Logger logger;` creates the actual `Logger` object in `main()`.
- `Invoice invoice(logger);` passes that existing object to the `Invoice` constructor.
- `logger_` is a `const Logger&`, so it refers to the existing `Logger`; it is not a pointer and does not create another `Logger`.
- `Invoice` does not own the `Logger` object. The `Logger` is created outside `Invoice`.
- Because `logger_` is a `const` reference, `Invoice` can use the `const` member functions `info()` and `error()` without modifying the `Logger` object through that reference.
- `Logger::info()` and `Logger::error()` are marked `const`, meaning those member functions do not modify the `Logger` object's state.
- The first three `addItem()` calls succeed, producing an item count of `3`.
- The fourth item has a negative price, so it is rejected.
- The rejected item does not modify `subtotalPaisa_` or `itemCount_`.
- The grand total is `Rs.74.34`.
- `return invoice.itemCount() == 4 ? 0 : 1;` returns `1` because the item count is `3`.
- `std::cerr` is used for the logging messages, while `std::cout` is used for the final invoice output.
- `TAX_PERCENT` is a static constant belonging to the `Invoice` class rather than an individual invoice object.
- The `explicit` constructor prevents a `Logger` object from being implicitly converted into an `Invoice`.
- `++itemCount_` increments the item count. For this `int`, there is no practical efficiency advantage over post-increment when the result is not used.
- The exact sizes of `int`, `long long`, and pointers are implementation-dependent.

---

# Design Summary: Code 3 vs Code 4

| Aspect | Code 3 | Code 4 |
|---|---|---|
| Main classes | `Product`, `LineItem` | `Logger`, `Invoice` |
| Main relationship | `LineItem` contains `Product` | `Invoice` refers to `Logger` |
| Relationship type | Composition | Association / dependency |
| Object ownership | `LineItem` stores its own `Product` | `Invoice` does not own `Logger` |
| Object creation | `Product` objects are supplied to `LineItem` | `Logger` is created independently in `main()` |
| Main purpose | Model product + quantity | Separate invoice processing from logging |
| Collaboration | `LineItem` uses its contained `Product` | `Invoice` collaborates with external `Logger` |

The key architectural change is:

```text
CODE 3

LineItem
   │
   └── Product
       composition


CODE 4

main()
 ├── Logger
 │
 └── Invoice
       │
       └──────────► Logger
          reference / association
```

The design is moving from simply **containing objects** toward **objects collaborating with other independently created objects**.

---

