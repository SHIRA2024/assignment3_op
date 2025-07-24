# Part 2 – Dynamic Convex Hull with Profiling
## Description
This part extends Part 1 by:
- Supporting dynamic point addition and removal.
- Computing the Convex Hull (CH) using both `std::vector` and `std::list` containers.
- Profiling operations (`addPoint`, `removePoint`, `computeCH`) and printing their timings to `stderr`.
- Reading commands directly from a test file (no interactive prompt).
### Supported Commands
- `vector` / `list` – The first line of the test file specifies the implementation.
- `Newgraph n` – Create a new graph with capacity for `n` points.
- `Newpoint x y` – Add a point `(x, y)`.
- `Removepoint x y` – Remove point `(x, y)` if it exists.
- `CH` – Compute and print the convex hull area with 6 decimal places.
## Build Instructions
From the `part2` folder, run:
    make
This will create the binary:
    ../ch_part2
## Running
There are two test files provided:
- `test_part2_vector.txt`
- `test_part2_list.txt`
Run with vector test file:
    ../ch_part2 < ../test_part2_vector.txt
Run with list test file:
    ../ch_part2 < ../test_part2_list.txt
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
Profiling logs (time measurements) appear on `stderr`.
## Valgrind (Memory Check)
Run with vector test file:
    make valgrind_vector
Run with list test file:
    make valgrind_list
## Cleaning
To remove build files:
    make clean
