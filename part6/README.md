# Part 6 – Multi-Client Reactor-based Convex Hull Server

## Description
Part 6 extends the server from Part 5 to support *multiple clients simultaneously*.  
The server continues to use the *Reactor pattern* for event-driven I/O but now manages multiple client connections in parallel.

It still supports both vector and list implementations for managing points and computing the convex hull (CH).

### Key Differences from Part 5
- *Multi-client support*: Each connected client can issue commands independently.
- The server maintains the same command set (vector, list, Newgraph, Newpoint, Removepoint, CH, quit).
- The quit command (from any client) stops the server and closes all connections.

---

## Build Instructions
From the part6 folder, run:
bash
make

This will create the binary:
bash
../ch_part6


---

## Running the Server
The server listens on *TCP port 9034*.

You can test it using:
bash
make test_vector

or
bash
make test_list


Both commands will:
1. Start the server in the background.
2. Send commands from the corresponding test file (test_part6_vector.txt or test_part6_list.txt) using nc (netcat).
3. Print the server output.
4. Stop the server automatically.

To run *both tests* in sequence:
bash
make run


---

## Example (Vector Test)
Example test_part6_vector.txt:

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


Expected output:

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
Server shutting down...


---

## Testing Multi-Client Behavior
You can open multiple nc sessions:
bash
nc localhost 9034

Each connected client can send commands such as Newpoint, CH, etc., and see results.  
Sending quit from any client will stop the server.

---

## Valgrind (Memory Check)
Run with vector test file:
bash
valgrind --leak-check=full ../ch_part6 < ../test_part6_vector.txt


---

## Cleaning
To remove build files:
bash
make clean


---