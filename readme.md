A lightweight, header-only, zero-allocation string manipulation library written in pure, standard C. 

This library brings modern systems-programming string-view mechanics to C, allowing you to slice, trim, and tokenize strings with total memory safety and **zero runtime heap allocations (`malloc`)**.

## Features
* **Zero Allocations:** All structural modifications happen instantly via \(O(1)\) pointer arithmetic.
* **Header-Only:** Drop `string_view.h` into your project and start coding immediately.
* **Memory Safe:** Immutability guards prevent structural out-of-bounds reads and memory corruption bugs.
* **Modern Utilities:** Built-in fast whitespace trimming and an optimized non-allocating tokenization/string-splitting engine.

## Quick Start
```c
#include "string_view.h"

int main() {
    // Initialize safely from a raw string literal
    stringView csv_row = SV("   Apple  , Banana ,   Cherry   ");

    while (csv_row.start_index < csv_row.end_index) {
        // Tokenize without allocating memory
        stringView token = split_by_delim(&csv_row, ',');
        trim_left_sv(&token);
        trim_right_sv(&token);

        print_sv(&token); // Prints: Apple, Banana, Cherry sequentially
        printf("\n");
    }
    return 0;
}
```
