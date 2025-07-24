# Part 4 – Convex Hull Server (TCP)

## Description
Part 4 extends Part 3 by implementing a **TCP server** that accepts commands from a client (e.g., `nc` or netcat) over port **9034**.  
The server supports both `std::vector` and `std::list` implementations for dynamic Convex Hull computation.

### Key Features
- **Client-server model:** The server waits for a client to connect and processes commands.
- **Dynamic Convex Hull:** Supports adding/removing points and computing the convex hull area.
- **Multiple clients:** Handles new connections via `select()`.
- **Clean shutdown:** The command `quit` disconnects the current client.

---

## Supported Commands
- `vector` / `list` – Selects the container implementation (must be the first command).
- `Newgraph n` – Creates a new graph with capacity for `n` points.
- `Newpoint x y` – Adds a point `(x, y)`.
- `Removepoint x y` – Removes a point `(x, y)` if it exists.
- `CH` – Computes and prints the convex hull points and area.
- `quit` – Disconnects the client.

---

## Build Instructions
From the `part4` folder, run:
```
make
```
This will create the server binary:
```
../ch_part4
```

---

## Running the Server
Start the server:
```
../ch_part4
```
It will listen on **port 9034** and display:
```
Server running on port 9034...
```

---

## Running Tests with Makefile
You can use predefined test files and `nc` to simulate a client:
```
make test_vector
```
or
```
make test_list
```
These commands:
1. Start the server in the background.
2. Send commands from `../test_part4_vector.txt` or `../test_part4_list.txt`.
3. Stop the server after the test.

---

## Manual Testing (Client Mode)
You can connect manually using `nc`:
```
nc localhost 9034
```
Then type commands like:
```
vector
Newgraph 5
Newpoint 1 1
Newpoint 5 1
Newpoint 8 5
Newpoint 12 1
Newpoint 15 5
CH
quit
```

---

## Example (Vector Test)
Example `test_part4_vector.txt`:
```
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
quit
```

Expected output:
```
Using vector implementation.
New graph created with capacity 5.
Added point (1.000000, 1.000000).
Added point (5.000000, 1.000000).
Added point (8.000000, 5.000000).
Added point (12.000000, 1.000000).
Added point (15.000000, 5.000000).
Hull points:
(1, 1)
(12, 1)
(15, 5)
(8, 5)
36.000000
Removed point (5.000000, 1.000000).
Hull points:
(1, 1)
(12, 1)
(15, 5)
(8, 5)
36.000000
```

---

## Valgrind (Memory Check)
For vector test:
```
make valgrind_vector
```
For list test:
```
make valgrind_list
```

---

## Cleaning
To remove build files:
```
make clean
```
