# Part 8 – Proactor Template

## Description
Part 8 introduces a **Proactor pattern** by implementing a reusable library.
Unlike the Reactor, where a central loop waits for events, the **Proactor starts a new thread per connection** using `pthread_create`.

## Provided Interface

### Header: `proactor.hpp`

```cpp
typedef void* (*proactorFunc)(int);

pthread_t startProactor(int sockfd, proactorFunc threadFunc);
int stopProactor(pthread_t tid);
```

## File Structure

```
part8/
├── include/
│   └── proactor/
│       └── proactor.hpp
├── src/
│   └── proactor/
│       └── proactor.cpp
├── Makefile
└── README.md
```

## Build Instructions

To compile and test that the `proactor` module builds correctly:

```bash
make
```

This will compile `proactor.cpp` and output an object file (`proactor.o`).

To clean build artifacts:

```bash
make clean
```

## Notes

- This part does **not** contain a working server.
- The `proactor` library will be used in **Part 9** to implement a full threaded server.
