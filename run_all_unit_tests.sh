mkdir build/tests

cmake -S . -B build/tests
cmake -S ./tests -B build/tests
cmake --build build/tests

cd build/tests
ctest --output-on-failure
