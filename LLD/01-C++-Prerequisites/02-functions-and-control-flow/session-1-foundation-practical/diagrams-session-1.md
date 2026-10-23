# Day 2 · Session 1 — Diagrams

## 1. Class Diagram — Code 2 (`FeeCalculator`)

```mermaid
classDiagram
    direction TB

    class FeeCalculator {
        -long long baseFeePaise_
        -int includedKm_
        -long long perKmPaise_
        +FeeCalculator(baseFeePaise, includedKm, perKmPaise)
        +feeFor(distanceKm) long long
        +feeFor(distanceKm, surgePercent) long long
        +tryQuote(distanceKm, outFee, surgePercent) bool
    }

    class main {
        <<function>>
    }

    main ..> FeeCalculator : creates and uses
```

### Explanation

- `-` represents private members.
- `+` represents public members.
- `feeFor()` is overloaded because two methods share the same name but accept different parameters.
- The dashed arrow represents a dependency: `main` uses `FeeCalculator` but does not inherit from it.

---

## 2. Flowchart — Code 2 (`tryQuote`)

```mermaid
flowchart TD
    A([Start]) --> B[Create FeeCalculator]
    B --> C[Set distanceKm and surgePercent]
    C --> D[Call tryQuote]
    D --> E{Is surgePercent less than 100?}

    E -- Yes --> F[Return false]
    E -- No --> G[Call feeFor distanceKm and surgePercent]

    G --> H{Is distanceKm negative?}
    H -- Yes --> I[Return invalid fee -1]
    H -- No --> J{Is distanceKm within includedKm?}

    J -- Yes --> K[Fee equals base fee]
    J -- No --> L[Calculate extra distance charge]

    L --> M[Add extra charge to base fee]
    K --> N[Apply surge percentage]
    M --> N

    N --> O[Store calculated fee in outFee]
    O --> P[Return true]

    F --> Q([End])
    I --> Q
    P --> Q
```

### Explanation

1. `main` creates a `FeeCalculator` object.
2. `main` calls `tryQuote()` with the distance, output variable, and surge percentage.
3. If the surge percentage is below 100, the quote fails.
4. Otherwise, `tryQuote()` calls the overloaded `feeFor()` method.
5. A negative distance produces an invalid fee.
6. If the distance is within the included kilometres, the base fee applies.
7. Otherwise, an additional distance charge is calculated.
8. The surge percentage is applied, the result is stored in `outFee`, and the function returns `true`.

> Note: Verify these branches against your actual C++ implementation before treating this as an exact flowchart.

---

## 3. Call Graph — Code 1

```mermaid
flowchart TD
    A([main]) --> B[printFee]
    B --> C[deliveryFeePaise]
    C --> D[Calculate delivery fee]
    D --> B
    B --> E[Print formatted fee]
    E --> F([End])
```

### Explanation

- `main()` calls `printFee()`.
- `printFee()` calls `deliveryFeePaise()`.
- The calculated fee is then formatted and printed.

---

## 4. Relationships

| Relationship | Used? | Explanation |
|---|---|---|
| Dependency | Yes | `main` uses `FeeCalculator`. |
| Inheritance | No | No class derives from another class. |
| Composition | No | No owned part-object is shown in this example. |
| Aggregation | No | No whole–part relationship is shown. |
| Association | No explicit association | No persistent object-to-object relationship is represented. |

**Learning note:** Composition will be introduced in Session 2.