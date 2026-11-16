# Movie Booking System

A C++17 movie ticket booking application split into a REST API backend and a
command-line frontend. The frontend communicates with the backend over HTTP.

## Project structure

```text
movie_booking/
├── backend/
│   ├── include/       Backend headers, grouped by API, domain, repos, and services
│   ├── src/           Backend implementation
│   ├── tests/         Backend unit tests
│   ├── config.toml    Backend configuration
│   ├── CMakeLists.txt
│   ├── build.sh
│   └── README.md      Backend-specific details
└── frontend/
    ├── include/       Frontend headers and API/config helpers
    ├── src/           CLI, menu, and HTTP client implementation
    ├── config.toml    Backend connection settings
    ├── CMakeLists.txt
    ├── build.sh
    └── README.md      Frontend-specific details
```

The backend owns the booking domain and REST API. The frontend presents the
booking workflow in the terminal and calls that API. Each component has its own
CMake project and build script.
