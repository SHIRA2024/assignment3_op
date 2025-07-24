````markdown
# Part 5 – Reactor-based Convex Hull Server

## Description
Part 5 extends the server from Part 4 by introducing the **Reactor pattern** to handle network events (connections, client messages).  
This event-driven architecture makes the server more modular and easier to extend.  
The server still supports both `vector` and `list` implementations for managing points and computing the convex hull (CH).

### Key Differences from Part 4
- **Event-driven architecture** using a `reactor` module (`reactor.cpp`).
- All I/O events (new client connections, messages) are managed through the Reactor.
- The set of commands (`vector`, `list`, `Newgraph`, `Newpoint`, `Removepoint`, `CH`, `quit`) is unchanged.

---

## Build Instructions
From the `part5` folder, run:
```bash
make
````

This will create the binary:

```bash
../ch_part5
```

---

## Running the Server

The server listens on **TCP port 9034**.
You can test it using:

```bash
make test_vector
```

or

```bash
make test_list
```

Both will:

1. Start the server in the background.
2. Send commands from the corresponding test file (`test_part5_vector.txt` or `test_part5_list.txt`) using `nc` (netcat).
3. Print the server output.
4. Stop the server automatically.

To run **both tests** in sequence:

```bash
make run
```

---

## Example (Vector Test)

Example `test_part5_vector.txt`:

```
vector
Newgraph 6
Newpoint 0 0
Newpoint 2 0
Newpoint 2 2
Newpoint 0 2
Newpoint 1 1
CH
Removepoint 1 1
CH
Newpoint 3 1
CH
quit
```

Expected output:

```
Using vector implementation.
New graph created with capacity 6.
Added point (0.000000, 0.000000).
Added point (2.000000, 0.000000).
Added point (2.000000, 2.000000).
Added point (0.000000, 2.000000).
Added point (1.000000, 1.000000).
Hull points:
(0, 0)
(2, 0)
(2, 2)
(0, 2)
4
Removed point (1.000000, 1.000000).
Hull points:
(0, 0)
(2, 0)
(2, 2)
(0, 2)
4
Added point (3.000000, 1.000000).
Hull points:
(0, 0)
(2, 0)
(3, 1)
(2, 2)
(0, 2)
5
```

---

## Valgrind (Memory Check)

For vector test:

```bash
make valgrind_vector
```

For list test:

```bash
make valgrind_list
```

---

## Cleaning

To remove build files:

```bash
make clean
```

```
```
