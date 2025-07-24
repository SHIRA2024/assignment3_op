# Part 7 – Threaded Convex Hull Server

## Description
Part 7 extends the Convex Hull server by replacing the `select()`-based event loop (used in Part 4)  
with a **multi-threaded TCP server**. Each client is handled in a **separate thread** using `pthread_create`.

### Key Features
- Server runs on **TCP port 9034**
- Each connected client is served concurrently in its own thread
- All clients share a **single graph instance**, protected by a `pthread_mutex`
- Supported commands (same as before):
  - `vector` / `list`
  - `Newgraph n`
  - `Newpoint x y`
  - `Removepoint x y`
  - `CH`
  - `quit` (disconnects the client)

---

## Build Instructions
From the `part7` folder, run:

```bash
make
```

This creates the binary:

```bash
../ch_part7
```

---

## Running the Server

To start the server manually:

```bash
../ch_part7
```

---

## Automatic Test with Makefile

To test the vector implementation using predefined test file:

```bash
make test_vector
```

To test the list implementation:

```bash
make test_list
```

To run both tests (vector and list) in sequence:

```bash
make run
```

This will:
1. Kill any previous server on port 9034
2. Start the server in the background
3. Send commands from the relevant test file via `nc`
4. Terminate the server after the test

---

## Example Test File: `test_part7_vector.txt`

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

Expected output includes:
- Confirmation of point additions/removals
- CH output showing updated hull points
- Area value after each CH command

---

## Valgrind (Memory Check)

```bash
make valgrind
```

---

## Clean Build Files

```bash
make clean
```
