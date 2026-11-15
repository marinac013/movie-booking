cmake -S . -B build -DBUILD_TESTING=ON
cmake --build build --parallel 8
ctest --test-dir build --output-on-failure