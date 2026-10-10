# cpp-function-basics-and-loops

This repository demonstrates C++ function basics, return types, conditional logic, parameter passing, function overloading, default arguments, and loops. The programs use a ticket-pricing example to illustrate function reuse, validation, discounts, and budget-based iteration.

## Contents

| File | Description |
|---|---|
| `code1_function_basics.cpp` | Function definitions, parameters, return values, conditional statements, sentinel values, and pass-by-value |
| `code2_loops_overloads_defaults.cpp` | Function overloading, default arguments, `std::string`, `for` loops, `while` loops, `break`, and `continue` |

## Requirements

- **Compiler:** GCC (`g++`) or another compatible C++ compiler.
- **C++ standard:** C++20.
- **Supported environments:** Linux, macOS, Windows with MinGW, or Windows Subsystem for Linux (WSL).
- **Terminal:** A shell that supports the commands shown below.

## Build and Run

### 1. Function Basics

**File:** `code1_function_basics.cpp`

Compile:

```bash
g++ -std=c++20 -Wall -Wextra -g code1_function_basics.cpp -o functions
```

Run:

```bash
./functions
```

Expected output:

```text
square(7) = 49
age 3: 0 paise
age 30: 30000 paise
age 65: 15000 paise
age -4: invalid
x after tryToChange = 10
```

### 2. Loops, Overloading, and Default Arguments

**File:** `code2_loops_overloads_defaults.cpp`

Before compiling, ensure that the definitions of `isEligibleForDiscount(int)` and `ticketPricePaise(int)` from the first file are included in this file. The pasted snippet contains a placeholder for these definitions.

Compile:

```bash
g++ -std=c++20 -Wall -Wextra -g code2_loops_overloads_defaults.cpp -o loopsOverloads
```

Run:

```bash
./loopsOverloads
```

Expected output:

```text
============================
Price table
============================
----------------------------
Member view
----------------------------
age 0: 0 / member 0
age 10: 15000 / member 12000
age 20: 30000 / member 24000
age 30: 30000 / member 24000
age 40: 30000 / member 24000
age 50: 30000 / member 24000
age 60: 15000 / member 12000
age 70: 15000 / member 12000
paid categories: 7
member tickets sold: 4, budget left: 4000
```

## Command Reference

| Command component | Meaning | Example |
|---|---|---|
| `g++` | Invokes the GNU C++ compiler. | `g++ source.cpp` |
| `-std=c++20` | Selects the C++20 language standard. | `-std=c++20` |
| `-Wall` | Enables a broad set of common compiler warnings. It does not enable every possible warning. | `-Wall` |
| `-Wextra` | Enables additional warnings beyond those covered by `-Wall`. | `-Wextra` |
| `-g` | Includes debugging information in the compiled executable. | `-g` |
| `code1_function_basics.cpp` | Specifies the source file to compile. | `g++ code1_function_basics.cpp` |
| `code2_loops_overloads_defaults.cpp` | Specifies the second source file to compile. | `g++ code2_loops_overloads_defaults.cpp` |
| `-o` | Specifies the name of the output executable. | `-o functions` |
| `functions` | The executable name chosen for the first program. | `-o functions` |
| `loopsOverloads` | The executable name chosen for the second program. | `-o loopsOverloads` |
| `./functions` | Runs the executable named `functions` in the current directory. | `./functions` |
| `./loopsOverloads` | Runs the executable named `loopsOverloads` in the current directory. | `./loopsOverloads` |
| `./` | Refers to the current directory in a Unix-like shell. | `./functions` |

## Key Terms

### Program Structure

| Term | Meaning | Example from the code |
|---|---|---|
| `main()` | Entry point where program execution begins. | `int main()` |
| Function | A named block of code that performs a task and may return a value. | `square(int n)` |
| Parameter | A variable declared in a function's parameter list. | `int age` |
| Argument | A value supplied when calling a function. | `square(7)` |
| Function call | Executes a function with the supplied arguments. | `printPrice(30)` |
| Return type | Specifies the type of value a function returns, or `void` if it returns no value. | `long long ticketPricePaise(int age)` |
| `return` | Returns a value from a function or exits the function. | `return -1;` |
| `void` | Indicates that a function does not return a value. | `void printPrice(int age)` |
| Function overloading | Allows functions to share a name when their parameter lists differ. | `ticketPricePaise(age, true)` |
| Default argument | Supplies a parameter value when the caller omits that argument. | `int width = 28` |
| Pass-by-value | Passes a copy of an argument into a function. Changes to the parameter do not change the caller's variable. | `tryToChange(x)` |
| `if` | Executes a block when a condition is true. | `if (age < 0)` |
| `for` | Repeats a block using initialization, a condition, and an update expression. | `for (int age = 0; age <= 70; age += 10)` |
| `while` | Repeats a block while its condition remains true. | `while (true)` |
| `break` | Immediately exits the nearest enclosing loop. | `break;` |
| `continue` | Skips the remainder of the current loop iteration and proceeds to the next iteration. | `continue;` |
| Sentinel value | A special return value used to indicate a condition such as invalid input. It must be interpreted by the caller. | `return -1;` |
| Early return | Exits a function before reaching its final statement. | `return;` inside `printPrice()` |

### Data Types

Typical sizes below assume a common modern GCC target. Exact sizes depend on the platform and implementation.

| Type | Stores | Typical size | Example |
|---|---|---|---|
| `int` | Integer values | 4 bytes | `int age` |
| `bool` | A Boolean value: `true` or `false` | 1 byte | `bool isMember` |
| `long long` | A signed integer with a range of at least 64 bits | 8 bytes | `long long budget` |
| `void` | No return value | Not applicable | `void printPrice(int age)` |
| `char` | A character value | 1 byte | `char fill` |
| `std::string` | A sequence of characters | Variable; the object size is implementation-dependent | `std::string(width, fill)` |

### Keywords and Operators

| Term | Meaning | Example from the code |
|---|---|---|
| `#include` | Preprocessor directive that makes a header's declarations available to the source file. | `#include <iostream>` |
| `int` | Declares an integer type. | `int x = 10;` |
| `bool` | Declares a Boolean type. | `bool isMember` |
| `long long` | Declares a long-long integer type. | `long long price` |
| `void` | Declares a function with no return value. | `void tryToChange(int n)` |
| `char` | Declares a character type. | `char fill = '='` |
| `const` | Prevents modification through the declared const reference. | `const std::string& title` |
| `if` | Conditional execution keyword. | `if (price < 0)` |
| `for` | Loop keyword. | `for (int age = 0; age <= 70; age += 10)` |
| `while` | Loop keyword. | `while (true)` |
| `true` | Boolean literal representing truth. | `while (true)` |
| `return` | Returns a result or exits a function. | `return 30000;` |
| `break` | Exits a loop. | `break;` |
| `continue` | Advances to the next loop iteration. | `continue;` |
| `=` | Assignment operator; also used to provide default argument values. | `int sold = 0;` |
| `<` | Less-than comparison operator. | `age < 5` |
| `>=` | Greater-than-or-equal comparison operator. | `age >= 60` |
| `>` | Greater-than comparison operator. | `price > budget` |
| `||` | Logical OR; true when at least one condition is true. | `age < 12 || age >= 60` |
| `*` | Multiplication operator. | `n * n` |
| `/` | Division operator. With integer operands, the fractional part is discarded. | `base * 80 / 100` |
| `-` | Subtraction operator or unary negation, depending on context. | `budget -= price` and `return -1;` |
| `+=` | Adds a value to a variable and assigns the result back. | `age += 10` |
| `-=` | Subtracts a value from a variable and assigns the result back. | `budget -= price` |
| `++` | Increments a variable by one. | `++paidCount` |
| `? :` | Conditional operator that selects one of two expressions. | `isMember ? base * 80 / 100 : base` |
| `<<` | Stream insertion operator used to send output to a stream. | `std::cout << price` |
| `&` | In a reference declaration, indicates that the parameter refers to an existing object rather than creating a copy. | `const std::string& title` |
| `::` | Scope resolution operator used to identify names belonging to a namespace or class. | `std::cout` |
| `{}` | Braces delimit a function body or a block of statements. | `if (age < 0) { ... }` |
| `()` | Parentheses enclose function parameters, function arguments, and conditions. | `square(7)` |
| `;` | Terminates a C++ statement or declaration. | `return 0;` |
| `,` | Separates parameters, arguments, or declarations. | `printHeader("Member view", '-')` |

### Standard Library Names

| Name | Header | Meaning |
|---|---|---|
| `std::cout` | `<iostream>` | Standard output stream used to print text and values. |
| `std::string` | `<string>` | String type provided by the C++ standard library. |
| `std::string(count, ch)` | `<string>` | Constructs a string containing `count` repetitions of the character `ch`. |
| `std::` | Namespace qualifier | Identifies names belonging to the C++ standard library namespace. |

## Initialization

| Form | Example | Result |
|---|---|---|
| Integer initialization | `int x = 10;` | Creates `x` with the value `10`. |
| Counter initialization | `int paidCount = 0;` | Starts the counter at zero. |
| Boolean parameter | `bool isMember` | Receives a Boolean argument from the caller. |
| Loop initialization | `int age = 0` in the `for` loop | Creates the loop counter and initializes it to zero. |
| Default character argument | `char fill = '='` | Uses `'='` when the caller omits the `fill` argument. |
| Default integer argument | `int width = 28` | Uses a width of 28 when the caller omits the `width` argument. |
| Const reference parameter | `const std::string& title` | Refers to the supplied string without copying it and prevents modification through this reference. |

## Topics Covered

- Defining and calling functions.
- Function parameters, arguments, and return types.
- Boolean-returning functions and conditional logic.
- Input validation using a sentinel return value.
- Reusing functions instead of duplicating pricing rules.
- Pass-by-value and its effect on caller variables.
- Function overloading and compile-time overload selection.
- Default arguments and parameter ordering.
- Const references for string parameters.
- Output formatting using `std::cout`.
- Repetition using `for` and `while`.
- Loop control using `break` and `continue`.
- Integer arithmetic for calculating member discounts.
- Counting paid ticket categories and managing a ticket budget.

## Notes

- The pricing functions return `-1` for negative ages. Callers must check for this value before treating the result as a valid price.
- Ages below 5 receive free tickets. Ages below 12 or at least 60 qualify for the discount. Other valid ages pay the regular price.
- Prices are expressed in paise: `15000` paise equals ₹150, and `30000` paise equals ₹300.
- Member pricing applies a 20% discount using `base * 80 / 100`. All operands are integers, so integer division discards any fractional part.
- `tryToChange(int n)` modifies only its local copy. Consequently, `x` remains `10` after `tryToChange(x)`.
- The two-argument `ticketPricePaise(int age, bool isMember)` overload calls the one-argument version to reuse its pricing rules.
- In the `for` loop, the age-zero category is free and excluded from `paidCount` by `continue`. The remaining seven categories are counted.
- The budget loop sells four member tickets at `24000` paise each, leaving `4000` paise.
- `printHeader("x", 40)` would convert `40` to a `char` for the `fill` parameter; it does not skip the second parameter to set `width`.
- The first program's corrected executable name is `functions`, matching its run command.
- The second program must include the pricing functions it calls before it can compile successfully.
- With the supplied implementations, no unused-variable warning is expected from the listed `-Wall -Wextra` options.

## Next

- **Pass-by-reference:** Learn how to let a function modify the caller's variable by accepting a reference parameter instead of a copy.