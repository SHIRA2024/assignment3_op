# Part 9 – Proactor-based Convex Hull Server

## Description
Part 9 builds a fully working server using the **Proactor pattern**.
Instead of a central event loop, the server starts a new thread per connection using the reusable `proactor` module (implemented in Part 8).

## Highlights

- Uses the `Proactor` to spawn a thread for each incoming connection.
- Each thread handles one client using a shared `State` object protected by a mutex.
- Clients can select between `vector` and `list` implementations for managing points and computing the convex hull (CH).

---

## File Structure

```
part9/
├── include/
│   └── proactor/
│       └── proactor.hpp
├── src/
│   ├── proactor/
│   │   └── proactor.cpp
│   ├── core/
│   │   └── State.cpp
│   ├── geom/
│   │   └── Hull.cpp
│   └── server_part9.cpp
├── Makefile
└── README.md
```

---

## Build Instructions

```bash
make
```

This will compile and produce the binary:
```
../ch_part9
```

---

## Running the Server

Test with vector implementation:
```bash
make test_vector
```

Test with list implementation:
```bash
make test_list
```

Run both:
```bash
make run
```

The test files must be located at:
- `../test_part9_vector.txt`
- `../test_part9_list.txt`

---

## Notes

- Each client connection is handled in a separate thread.
- Access to shared `State` is synchronized using a `pthread_mutex_t`.
- Server listens on port `9034`.

---

## Cleaning

```bash
make clean
```

Removes the compiled binary.