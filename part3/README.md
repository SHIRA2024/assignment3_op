# Part 3 – Interactive Convex Hull
## Description
Part 3 builds upon Part 2 by adding **interactive usage**.  
While Part 2 runs commands from a test file for profiling, Part 3 can:
- Accept **manual commands** from the user (interactive mode).
- Still process **test files** like Part 2, using the same command format.
The convex hull (CH) is computed dynamically using either `std::vector` or `std::list`, depending on the selected implementation.
### Supported Commands
- `vector` / `list` – Choose the implementation (first input line or typed command).
- `Newgraph n` – Create a new graph with capacity for `n` points.
- `Newpoint x y` – Add a point `(x, y)`.
- `Removepoint x y` – Remove point `(x, y)` if it exists.
- `CH` – Compute and print the convex hull area with 6 decimal places.
## Build Instructions
From the `part3` folder, run:
    make
This will create the binary:
    ../ch_part3
## Running (Interactive Mode)
To start Part 3 in interactive mode, run:
    ../ch_part3
Example session:
    Choose implementation: vector or list
    vector
    Newgraph 5
    Newpoint 1 1
    Newpoint 5 1
    Newpoint 8 5
    Newpoint 12 1
    Newpoint 15 5
    CH
    Removepoint 5 1
    CH
The program will keep accepting commands until you press `Ctrl+D` (end-of-input).
## Running with Test Files
Part 3 can still run with the same test files as Part 2:
    ../ch_part3 < ../test_part2_vector.txt
or
    ../ch_part3 < ../test_part2_list.txt
You can also use the Makefile shortcuts:
    make run_vector
    make run_list
## Example (Vector Test)
Example `test_part2_vector.txt`:
    vector
    Newgraph 5
    Newpoint 1 1
    Newpoint 5 1
    Newpoint 8 5
    Newpoint 12 1
    Newpoint 15 5
    CH
    Removepoint 5 1
    CH
Expected output:
    Hull points:
    (1, 1)
    (12, 1)
    (15, 5)
    (8, 5)
    36.000000
    Hull points:
    (1, 1)
    (12, 1)
    (15, 5)
    (8, 5)
    36.000000
## Valgrind (Memory Check)
For vector test:
    make valgrind_vector
For list test:
    make valgrind_list
## Cleaning
To remove build files:
    make clean
