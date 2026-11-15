# Movie Booking Frontend

Standalone command-line application for the Movie Booking System.

The frontend communicates with the backend through its REST API.

## Requirements

- C++17 compiler
- CMake 3.2 or newer
- Drogon HTTP framework

## Build

From the frontend directory:

```bash
cmake -S . -B build
cmake --build build
```

## Running

Start the backend first.

The frontend connects to:

http://127.0.0.1:8080

Then launch the frontend executable.