mkdir build
conan install . --profile ./profile --output-folder=build --build=missing
cmake -B build -G Ninja .
