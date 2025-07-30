# Part 10 – Multi-client Convex Hull Server (Reactor + Proactor)

This project implements a concurrent server that computes the convex hull of a set of 2D points, using two I/O multiplexing models: **Reactor** and **Proactor**. The server supports both `vector` and `list` data structures to store the points.

## 📁 Project Structure

```
part10/
│
├── Makefile                   # Build and test automation
├── test_vector.txt            # Input commands to test vector implementation
├── test_list.txt              # Input commands to test list implementation
│
├── include/                   # Header files
│   └── *.hpp
│
├── src/
│   ├── core/                  # Logic for managing the state of the point set
│   │   └── State.cpp
│   ├── geom/                  # Geometric algorithms (e.g., convex hull)
│   │   └── Hull.cpp
│   ├── proactor/              # Proactor model logic
│   │   └── proactor.cpp
│   ├── reactor/               # Reactor model logic
│   │   └── reactor.cpp
│   ├── server/                # Server entry points for each model
│   │   ├── server_proactor.cpp
│   │   └── server_reactor.cpp
│   ├── commands.cpp           # Command parsing and processing logic
│   ├── globals.cpp            # Shared global variables (mutex, condition variables)
│   ├── monitor.cpp            # Monitor thread to print convex hull if needed
│   └── main.cpp               # Common main logic
```

## ⚙️ Build Instructions

In order to compile the project, simply run:

```bash
make
```

This builds two executables:
- `server_reactor` – Reactor-based multi-client server
- `server_proactor` – Proactor-based multi-client server

## ▶️ Run Tests Automatically

Run the following to test both vector and list implementations:

```bash
make run
```

This will:
1. Kill any previous instance on port 9035
2. Launch the `server_reactor` in background
3. Send `test_vector.txt` and `test_list.txt` using `netcat (nc)`
4. Print the output to the terminal

You can also run individual tests:

```bash
make test_vector
make test_list
```

## 🧪 What Part 10 Implements

- Multi-threaded convex hull server with support for multiple clients.
- Uses **Reactor** and **Proactor** I/O handling models.
- Handles commands like:
  - `use vector` / `use list`
  - `new <size>` – creates new point set
  - `add x y` – adds point
  - `remove x y` – removes point
  - `ch` – computes and returns convex hull
- Proper synchronization with `pthread_mutex_t` and `pthread_cond_t`
- Background monitor thread that listens for updates.

## 📦 Requirements

Ensure the following tools are installed:
- `g++` with C++17 support
- `make`
- `nc` (netcat)
- `fuser` (used to release the port)

You can install missing tools with:

```bash
sudo apt update
sudo apt install netcat psmisc
```

---


To run the tests:

Run make test_vector to test the vector implementation.

Run make test_list to test the list implementation.

