
# Decide on a package manager

mkdir build
cmake -B build -G Ninja .

ln -sf build/compile_commands.json compile_commands.json


