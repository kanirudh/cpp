mkdir -p build
conan install . --profile ./profile --output-folder=build --build=missing
cmake -DCMAKE_TOOLCHAIN_FILE="build/conan_toolchain.cmake" -DCMAKE_BUILD_TYPE="Release" -B build -G Ninja .
