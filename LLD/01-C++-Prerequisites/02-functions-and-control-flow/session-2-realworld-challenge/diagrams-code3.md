
# Code 3 — Order Checkout

## 1. Class Diagram (Mermaid)

```mermaid
classDiagram
    direction LR

    class Logger {
        +info(msg: string) void
        +error(err: string) void
    }

    class Cart {
        -log_: const Logger&
        -subtotalPaise_: long long
        -lines_: int
        -rejected_: int
        -unitPricePaise(productId: int)$ long long
        +Cart(log: const Logger&)
        +addLine(productId: int, qty: int = 1) bool
        +subtotalPaise() long long
        +lines() int
        +rejected() int
    }

    class FeeCalculator {
        -baseFeePaise_: long long
        -includedKm_: int
        -perKmPaise_: long long
        +FeeCalculator(baseFeePaise = 2000, includedKm = 3, perKmPaise = 500)
        +feeFor(km: int) long long
        +tryQuote(km: int, outFee: long long&, surgePercent: int = 100) bool
    }

    class CheckoutFunctions {
        <<namespace-like grouping>>
        +discountPercentFor(subtotalPaise: long long) int
        +parseInt(text: const char*, out: int&) bool
        +printMoney(label: const char*, paise: long long) void
    }

    class Main {
        <<function>>
        +main(argc: int, argv: char**) int
    }

    Cart --> "1" Logger : references / logs through
    Main ..> Logger : creates
    Main ..> Cart : creates and uses
    Main ..> FeeCalculator : creates and uses
    Main ..> CheckoutFunctions : calls functions
```

**Relationship notes**

- `Cart --> Logger`: `Cart` stores a reference to a `Logger`; it does not own the logger.
- `Main ..> Cart`: `main()` creates a cart and adds product lines.
- `Main ..> FeeCalculator`: `main()` requests a delivery quote.
- `Main ..> CheckoutFunctions`: `main()` calls the standalone parsing, discount, and money-formatting functions.
- There is no inheritance relationship in this implementation.

> `CheckoutFunctions` and `Main` are diagram-only groupings to make the relationships readable. They are not actual C++ classes. The three utility functions are standalone functions, and `main()` is a free function.

## 2. Class Relationship Diagram

```mermaid
flowchart TD
    MAIN["main()"]
    LOG["Logger"]
    CART["Cart"]
    FEE["FeeCalculator"]
    UTIL["Standalone Functions"]

    MAIN -->|"creates"| LOG
    MAIN -->|"creates and uses"| CART
    MAIN -->|"creates and calls"| FEE
    MAIN -->|"calls"| UTIL

    CART -->|"holds a reference to"| LOG

    UTIL --- PARSE["parseInt()"]
    UTIL --- DISCOUNT["discountPercentFor()"]
    UTIL --- MONEY["printMoney()"]

    classDef entry fill:#dbeafe,stroke:#2563eb,color:#111827
    classDef component fill:#dcfce7,stroke:#16a34a,color:#111827
    classDef helper fill:#fef3c7,stroke:#d97706,color:#111827

    class MAIN entry
    class LOG,CART,FEE component
    class UTIL,PARSE,DISCOUNT,MONEY helper
```

## 3. Checkout Execution Flow

```mermaid
flowchart TD
    A(["Start: main(argc, argv)"])
    B{"Exactly 2 command-line arguments?"}
    C["Print usage to stderr"]
    D["Exit code 2"]
    E["Parse distance and coupon"]
    F{"Parsing succeeds and values are valid?"}
    G["Log invalid distance or coupon"]
    H["Exit code 3"]
    I["Create Logger and Cart"]
    J["Read productId and qty from stdin"]
    K{"Input read successfully?"}
    L{"productId == 0?"}
    M["Cart.addLine(productId, qty)"]
    N{"Cart has at least one accepted line?"}
    O["Log empty cart"]
    P["Exit code 4"]
    Q["Create FeeCalculator"]
    R["Call tryQuote(km, fee)"]
    S{"Delivery quote succeeds?"}
    T["Log cannot quote delivery"]
    U["Exit code 3"]
    V["Calculate tier discount"]
    W["Choose max(tier, coupon)"]
    X["Calculate discounted item total"]
    Y{"Items >= 120000 paise?"}
    Z["Set delivery fee to zero"]
    AA["Print subtotal, discount, items, delivery and total"]
    AB{"Rejected lines == 0?"}
    AC["Exit code 0"]
    AD["Exit code 5"]

    A --> B
    B -- No --> C --> D
    B -- Yes --> E --> F
    F -- No --> G --> H
    F -- Yes --> I --> J --> K
    K -- Yes --> L
    L -- Yes --> N
    L -- No --> M --> J
    K -- No / EOF --> N
    N -- No --> O --> P
    N -- Yes --> Q --> R --> S
    S -- No --> T --> U
    S -- Yes --> V --> W --> X --> Y
    Y -- Yes --> Z --> AA
    Y -- No --> AA
    AA --> AB
    AB -- Yes --> AC
    AB -- No --> AD
```

## 4. Cart Line Validation Flow

```mermaid
flowchart TD
    A(["addLine(productId, qty)"])
    B["Look up unit price"]
    C{"Known product and 1 <= qty <= 100?"}
    D["Increment rejected counter"]
    E["Log rejected line"]
    F["Return false"]
    G["Add unit price × quantity to subtotal"]
    H["Increment accepted line counter"]
    I["Log accepted line"]
    J["Return true"]

    A --> B --> C
    C -- No --> D --> E --> F
    C -- Yes --> G --> H --> I --> J
```

## 5. Delivery Fee Calculation Flow

```mermaid
flowchart TD
    A(["feeFor(km)"])
    B{"km < 0?"}
    C["Return -1"]
    D{"km <= includedKm?"}
    E["Return base fee"]
    F["Calculate base fee + extra km × per-km fee"]
    G["Return calculated fee"]
    H(["tryQuote(km, outFee, surgePercent)"])
    I["Call feeFor(km)"]
    J{"Fee valid and surgePercent >= 100?"}
    K["Return false"]
    L["Calculate fee × surgePercent / 100"]
    M["Store result in outFee"]
    N["Return true"]

    A --> B
    B -- Yes --> C
    B -- No --> D
    D -- Yes --> E
    D -- No --> F --> G
    H --> I --> J
    J -- No --> K
    J -- Yes --> L --> M --> N
```

## 6. Important Business Rules

| Rule | Implementation |
|---|---|
| Valid products | IDs `1`, `2`, and `3` |
| Valid quantity | `1` to `100` |
| Base delivery fee | ₹20 for up to and including 3 km |
| Additional distance | ₹5 per kilometre beyond 3 km |
| Coupon limit | `0%` to `50%` |
| Discount selection | Higher of tier discount or coupon; no stacking |
| Tier discounts | 5% at ₹500 or more; 10% at ₹1,000 or more |
| Free delivery | Discounted item total of at least ₹1,200 |
| Rejected lines | Logged and counted; program eventually returns exit code `5` if any were rejected |
| Currency | Stored as integer paise |

## 7. Important Implementation Notes

- `Logger`, `Cart`, and `FeeCalculator` are actual C++ classes.
- `discountPercentFor()`, `parseInt()`, and `printMoney()` are standalone functions.
- `main()` controls the checkout process and handles the exit codes.
- `Cart` keeps a reference to `Logger`; the logger must remain alive for as long as the cart uses it.
- `tryQuote()` supports a surge percentage, but `main()` uses its default of `100%`.
- The input loop ends when the product ID is `0`, input reaches EOF, or extraction fails.
