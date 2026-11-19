# Movie Booking System

A C++17 movie ticket booking application split into a REST API backend and a
command-line frontend. The frontend communicates with the backend over HTTP.


## Dependencies

Both components require CMake 3.20 or newer, a C++17 compiler and build tools,
Git, and an internet connection for CMake to fetch dependencies. They fetch
JsonCpp 1.9.5, Drogon 1.9.8, and toml++ 3.4.0 during configuration. The backend
also fetches GoogleTest 1.15.2 when its tests are enabled. OpenSSL, UUID, and
zlib development libraries are required by the build.

On Ubuntu or Debian, install the common prerequisites with:

```bash
sudo apt update
sudo apt install -y build-essential cmake git ca-certificates \
  uuid-dev libssl-dev zlib1g-dev
```

## Build and run

In separate terminals, configure/build and start the backend, then configure,
build, and start the frontend:

```bash
cd backend
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build --parallel 8
./build/bin/movie-booking-backend
```

```bash
cd frontend
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build --parallel 8
./build/bin/movie-booking-frontend
```

The backend listens on `127.0.0.1:8080` by default.

### Windows

Install Visual Studio 2022 with the **Desktop development with C++** workload,
CMake, Git, and vcpkg. Install OpenSSL and zlib with `vcpkg install openssl
zlib`, then use the vcpkg toolchain file when configuring each component.
Start the backend and frontend from separate PowerShell terminals:

```powershell
cd backend
cmake -S . -B build -DCMAKE_TOOLCHAIN_FILE=C:/vcpkg/scripts/buildsystems/vcpkg.cmake
cmake --build build --config Debug
.\build\Debug\movie-booking-backend.exe
```

```powershell
cd frontend
cmake -S . -B build -DCMAKE_TOOLCHAIN_FILE=C:/vcpkg/scripts/buildsystems/vcpkg.cmake
cmake --build build --config Debug
.\build\Debug\movie-booking-frontend.exe
```

Replace `C:/vcpkg` with your vcpkg installation path. See the backend and
frontend READMEs for detailed dependencies, configuration, and test commands.

## API documentation

Install Doxygen, then generate the HTML documentation from the repository root:

```bash
doxygen Doxyfile
```

To view it on any platform, open `docs/html/index.html` in your browser:
use the browser's **Open File** option and select that file, or drag the file
into an open browser window.
