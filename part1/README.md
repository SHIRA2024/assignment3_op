# Part 1 – Static Convex Hull

## Description
Part 1 computes the **Convex Hull (CH)** of a fixed set of 2D points using the **Graham Scan** algorithm. It outputs the points forming the convex hull in **counterclockwise (CCW)** order and calculates the **area of the hull** using the Shoelace formula.

## Input Format
The input is provided via a text file, e.g., `test_part1.txt`:
```
<number_of_points> x1 y1 x2 y2 ... xn yn
```
Example:
```
5 1 1 5 1 8 5 12 1 15 5
```

## Build Instructions
From the `part1` folder, run:
```
make
```
This will create the binary:
```
../ch_part1
```

## Running
To run the program using the test file:
```
../ch_part1 < ../test_part1.txt
```
You can also use the Makefile shortcut:
```
make run
```

## Example
For the input:
```
5 1 1 5 1 8 5 12 1 15 5
```
The expected output is:
```
Hull points:
(1, 1)
(12, 1)
(15, 5)
(8, 5)
36.000000
```

## Valgrind (Memory Check)
To run with Valgrind:
```
make valgrind
```

## Cleaning
To remove build files:
```
make clean
```
