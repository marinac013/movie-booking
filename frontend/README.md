# Movie Booking Frontend

The frontend is a C++17 command-line application that connects to the backend
REST API.

## Dependencies

You need:

- CMake 3.20 or newer
- A C++17 compiler and build tools
- Git and an internet connection for CMake to fetch project dependencies
- OpenSSL, UUID, and zlib development libraries

JsonCpp 1.9.5, Drogon 1.9.8, and toml++ 3.4.0 are fetched by CMake.

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

Start the backend first. From this directory, build and launch the frontend:

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build --parallel
./build/bin/movie-booking-frontend
```

With Visual Studio on Windows, run these commands from this directory after
installing the dependencies above:

```powershell
cmake -S . -B build -DCMAKE_TOOLCHAIN_FILE=C:/vcpkg/scripts/buildsystems/vcpkg.cmake
cmake --build build --config Debug
.\build\Debug\movie-booking-frontend.exe
```

The frontend reads `config.toml` from its current working directory. By
default, it connects to the backend at `127.0.0.1:8080`. Change the `ip` and
`port` in `config.toml` if the backend is listening elsewhere.
