# Movie Booking Backend

The backend is a C++17 REST API built with CMake and Drogon.

## Dependencies

You need:

- CMake 3.20 or newer
- A C++17 compiler and build tools
- Git and an internet connection for CMake to fetch project dependencies
- OpenSSL, UUID, and zlib development libraries

JsonCpp 1.9.5, Drogon 1.9.8, and toml++ 3.4.0 are fetched by CMake. GoogleTest
1.15.2 is fetched when tests are enabled.

On Ubuntu or Debian, install the build tools and system libraries with:

```bash
sudo apt update
sudo apt install -y build-essential cmake git ca-certificates \
  uuid-dev libssl-dev zlib1g-dev
```

On Windows, install Visual Studio 2022 with the **Desktop development with C++**
workload, CMake, and Git. Install OpenSSL and zlib for your target architecture
(for example, with vcpkg), then configure with the vcpkg CMake toolchain file:

```powershell
vcpkg install openssl zlib
cmake -S . -B build -DCMAKE_TOOLCHAIN_FILE=C:/vcpkg/scripts/buildsystems/vcpkg.cmake
```

Replace `C:/vcpkg` with your vcpkg installation path. JsonCpp, Drogon, and
toml++ are still fetched by CMake.

## Build and run

From this directory:

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build --parallel 8
./build/bin/movie-booking-backend
```

With Visual Studio on Windows, run these commands from this directory after
installing the dependencies above:

```powershell
cmake -S . -B build -DCMAKE_TOOLCHAIN_FILE=C:/vcpkg/scripts/buildsystems/vcpkg.cmake
cmake --build build --config Debug
.\build\Debug\movie-booking-backend.exe
```

The server reads `config.toml` from its current working directory. By default,
it listens on `127.0.0.1:8080`. Check that it is responding with:

```bash
curl http://127.0.0.1:8080/api/health
```

## Run tests

Tests are disabled by default. Configure and run them with:

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug -DBUILD_TESTING=ON
cmake --build build --parallel 8
ctest --test-dir build --output-on-failure
```

For a Visual Studio multi-configuration build, use:

```powershell
cmake -S . -B build -DBUILD_TESTING=ON -DCMAKE_TOOLCHAIN_FILE=C:/vcpkg/scripts/buildsystems/vcpkg.cmake
cmake --build build --config Debug
ctest --test-dir build -C Debug --output-on-failure
```

## Run in Docker

The Dockerfile builds the backend image from this directory. The server must
listen on all container interfaces for a published Docker port to reach it.
Set `ip` to `0.0.0.0` in `config.toml` before building the image:

```toml
[server]
ip = "0.0.0.0"
port = 8080
threads = 4
```

Build and run the container from the repository root:

```bash
docker build -t movie-booking-backend ./backend
docker run --rm --name movie-booking-backend -p 8080:8080 movie-booking-backend
```

Then check the health endpoint from the host:

```bash
curl http://127.0.0.1:8080/api/health
```

`EXPOSE 8080` documents the container port; `-p 8080:8080` publishes it on the
host. To stop the container, press Ctrl+C in the terminal running it.

## Configuration

Edit `config.toml` to set the server IP address, port, and worker thread count.
The frontend has its own `config.toml` for the backend address it connects to.

## REST API

| Method | Endpoint | Purpose |
|---|---|---|
| GET | `/api/health` | Server health |
| GET | `/api/movies` | List movies |
| GET | `/api/movies/{id}` | Movie details |
| GET | `/api/movies/{id}/theaters` | Theaters showing a movie |
| GET | `/api/movies/{id}/screenings` | Screenings for a movie |
| GET | `/api/theaters/{id}/screenings` | Screenings at a theater |
| GET | `/api/screenings/{id}/seats` | Available seats |
| POST | `/api/screenings/{id}/bookings` | Book seats |
| GET | `/api/bookings/{id}` | Retrieve a booking |
