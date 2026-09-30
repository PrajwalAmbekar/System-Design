# cpp-fundamentals

Small C++ programs covering the basics: program entry point and command-line arguments, the compilation pipeline, headers and the `std` namespace, built-in data types, type deduction, and variable initialization.

## Contents

| File | Description |
|------|-------------|
| `code1.cpp` | Command-line arguments (`argc`, `argv`) and compilation stages |
| `code2.cpp` | Data types, `sizeof`, `auto`, floating-point behavior, output formatting, initialization |

## Requirements

- g++ with C++23 support (`-std=c++23`)
- Linux, macOS, or WSL

## Build and Run

### code1

```bash
g++ -std=c++23 -o code1 code1.cpp
./code1 arg1 arg2 arg3
```

Output:

```text
Hello world!
Argument count: 4
 argv[0] = ./code1
 argv[1] = arg1
 argv[2] = arg2
 argv[3] = arg3
```

### code2

```bash
g++ -std=c++23 -o code2 code2.cpp
./code2
```

Output (`sizeof` values are platform-dependent):

```text
sizeof(int) = 4 bytes
sizeof(double) = 8 bytes
sizeof(bool) = 1 bytes
sizeof(char) = 1 bytes
Total: $599.97
Exact: $3.50
Ratio: 3
0.1 + 0.2 = 0.30000000000000004441
isPaid: true
Next grade: B
Grade: BCode:66
```

## Command Reference

Every part of the commands used above:

| Term | Meaning |
|------|---------|
| `g++` | The GNU C++ compiler. Turns `.cpp` source files into a runnable program. |
| `code1.cpp` | The input source file. |
| `-o code1` | **o**utput. Names the generated file `code1`. Without it, g++ creates `a.out`. |
| `-std=c++23` | Compile using the C++23 language standard. |
| `-Wall` | **W**arnings **all**. Enables the most common warnings (unused variables, suspicious code). |
| `-Wextra` | Enables additional warnings that `-Wall` does not cover. |
| `-E` | Stop after **preprocessing**. Output is source code with headers and macros expanded. |
| `-S` | Stop after **compiling to assembly**. Output is human-readable assembly. |
| `-c` | **C**ompile and assemble only, without **linking**. Output is an object file. |
| `./code1` | Run the program `code1` located in the current directory (`.` means "here"). |
| `arg1 arg2 arg3` | Command-line arguments passed to the program. They arrive in `argv`. |

## Compilation Stages

`code1.cpp` can be built step by step to inspect each stage of the pipeline:

```bash
g++ -std=c++23 -Wall -Wextra -E code1.cpp -o code1.i   # preprocess
g++ -std=c++23 -Wall -Wextra -S code1.cpp -o code1.s   # compile to assembly
g++ -std=c++23 -Wall -Wextra -c code1.cpp -o code1.o   # assemble to object file
```

| Flag | Output | Contents |
|------|--------|----------|
| `-E` | `code1.i` | Preprocessed source (headers and macros expanded) |
| `-S` | `code1.s` | Assembly |
| `-c` | `code1.o` | Object file (machine code, not linked) |

Full pipeline: `source (.cpp)` → preprocess → compile → assemble → link → `executable`

## Key Terms

### Program structure

| Term | Meaning | Example |
|------|---------|---------|
| `main()` | Entry point. Every C++ program starts executing here. | `int main(){ ... }` |
| `argc` | **Arg**ument **c**ount. Number of command-line arguments, including the program name. | `argc` is `4` for `./code1 arg1 arg2 arg3` |
| `argv` | **Arg**ument **v**ector. Array of the arguments as text. `argv[0]` is the program name. | `argv[1]` is `"arg1"` |
| `return 0;` | Ends `main`. `0` means success, any non-zero value signals an error. | `return 0;` |
| `for` loop | Repeats a block a fixed number of times. | `for(int i = 0; i < argc; ++i)` |
| `++i` | Increases `i` by 1. | |
| `if` | Runs a block only when a condition is true. | `if(argc < 1)` |

### Data types

| Type | Stores | Typical size | Example |
|------|--------|--------------|---------|
| `int` | Whole numbers | 4 bytes | `int quantity = 3;` |
| `double` | Decimal numbers (about 15 digits of precision) | 8 bytes | `double price = 199.99;` |
| `bool` | `true` or `false` | 1 byte | `bool isPaid = true;` |
| `char` | A single character, stored as a number (ASCII code) | 1 byte | `char grade = 'A';` |

Sizes depend on the platform, which is why the program prints them with `sizeof`.

### Keywords and operators

| Term | Meaning | Example |
|------|---------|---------|
| `sizeof` | Gives the size of a type or variable in bytes. | `sizeof(int)` |
| `auto` | The compiler deduces the variable's type from its initial value. The variable must be initialized. | `auto total = quantity * price;` gives `double` |
| `static_cast<T>(x)` | Explicitly converts `x` to type `T`. Checked at compile time. | `static_cast<int>(nextGrade)` turns `'B'` into `66` |
| `::` | Scope resolution operator. Accesses a name inside a namespace. | `std::cout` |
| `<<` | Stream insertion operator. Sends a value to the output stream. Can be chained. | `std::cout << "Total: " << total;` |
| `{}` | Brace initialization. Empty braces set the variable to zero. Rejects lossy conversions. | `int safe{};` |

### Standard library names

| Name | Header | Meaning |
|------|--------|---------|
| `#include` | none (preprocessor directive) | Copies the contents of a header file into the source before compiling. |
| `std` | none (namespace) | The namespace that holds all standard library names. |
| `std::cout` | `<iostream>` | Standard output stream (prints to the terminal). |
| `std::endl` | `<iostream>` | Ends the line and flushes the output. |
| `std::fixed` | `<iostream>` | Prints decimals in fixed-point form (no scientific notation). |
| `std::setprecision(n)` | `<iomanip>` | Sets how many digits are printed. With `std::fixed`, it sets digits after the decimal point. |
| `std::boolalpha` | `<iostream>` | Prints `bool` values as `true`/`false` instead of `1`/`0`. |

## Initialization

| Form | Example | Result |
|------|---------|--------|
| Uninitialized | `int junk;` | Indeterminate value; reading it is undefined behavior |
| Copy initialization | `int quantity = 3;` | Set to `3` |
| Brace initialization (empty) | `int safe{};` | Value-initialized to `0` |
| Brace initialization (narrowing) | `int bad{3.9};` | Compile error: narrowing conversion not allowed |

## Topics Covered

- `main(int argc, char* argv[])` and command-line arguments
- Compilation stages and compiler flags (`-std`, `-o`, `-Wall`, `-Wextra`, `-E`, `-S`, `-c`)
- Preprocessor `#include` and standard headers (`<iostream>`, `<iomanip>`)
- `std` namespace and the `::` scope resolution operator
- Stream output with `std::cout`, `<<` and `std::endl`
- Fundamental types: `int`, `double`, `bool`, `char`
- `sizeof` and type sizes
- `auto` type deduction
- Integer vs floating-point division
- Floating-point precision
- Stream formatting: `std::fixed`, `std::setprecision`, `std::boolalpha`
- Character arithmetic and `static_cast`
- Default, copy and brace initialization

## Notes

- `argv[0]` is always the program name, so `argc` is at least 1.
- Integer division truncates: `7 / 2` is `3`, while `7 / 2.0` is `3.5`.
- `0.1 + 0.2` is not exactly `0.3` in binary floating-point.
- `std::fixed` and `std::setprecision` stay active on `std::cout` until changed again.
- `'A' + 1` is computed as an `int` (`66`) and converted back to `char` (`'B'`) on assignment.
- Brace initialization rejects narrowing conversions: `int x{3.9};` does not compile, while `int x = 3.9;` silently truncates to `3`.
- Reading an uninitialized variable is undefined behavior.
- `code2.cpp` compiles with unused-variable warnings under `-Wall -Wextra` (`count`, `junk`, `safe`). These are intentional for demonstration.
