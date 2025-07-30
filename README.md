# OPS3 – Multi-Part Convex Hull Project

This repository contains a **multi-stage C++ project** that incrementally builds a system for computing the **convex hull** of a set of 2D points, while gradually adding networking and concurrency capabilities.

---

## 📂 Project Structure

```
ops3/
│
├── part1/   # Basic convex hull calculation
├── part2/   # Convex hull with state management
├── part3/   # Extended state and geometry handling
├── part4/   # First server version
├── part5/   # Reactor-based server
├── part6/   # Multi-client reactor server
├── part7/   # Extended testing for vector/list
├── part8/   # Proactor module
├── part9/   # Proactor-based server
├── part10/  # Final combined reactor + proactor servers
├── Makefile # Recursive Makefile to build all parts
```

---

## 🛠 Building the Entire Project

To **build all parts at once**, run from the project root:

```bash
make
```

The root `Makefile` will:
1. Enter each `partN` directory
2. Run its local `Makefile`
3. Build the corresponding binaries

If you see:
```
Nothing to be done for 'all'
```
It means that part has already been compiled and no changes were detected.

---

## ▶ Running Part 10 (Final Version)

Part 10 contains **two separate multi-client server implementations**:

- **Reactor-based server** → `server_reactor`
- **Proactor-based server** → `server_proactor`

### Run tests for `vector` implementation:
```bash
cd part10
make test_vector
```

### Run tests for `list` implementation:
```bash
cd part10
make test_list
```

> ⚠️ In Part 10, tests are run **separately** for `vector` and `list`.  
> The `make run` option is not used.

---

## 🧪 Test Files

Each part that supports automated testing has its own `.txt` test files (e.g., `test_vector.txt`, `test_list.txt`).  
These are sent to the server using `netcat (nc)` in the test targets.

---

## 📦 Requirements

Make sure the following tools are installed:

```bash
sudo apt update
sudo apt install g++ make netcat psmisc
```

- **g++** → C++17 compiler
- **make** → Build automation
- **netcat (nc)** → Send test commands to the server
- **psmisc (fuser/pkill)** → Kill processes using the server port

---

## ✅ Summary

- Use `make` in the root to build **everything**.
- Use `make test_vector` / `make test_list` in `part10` to run final server tests.
- Earlier parts demonstrate incremental development from simple geometry to fully concurrent servers.
