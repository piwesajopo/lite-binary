# This script will compile multiplat-hello.c
# This version supports x86/64 architecture for Linux-Like operating systems.

# Compile nomain
./docker-run.sh gcc -fno-builtin -nostartfiles -nostdlib -static -Wl,-e,_start multiplat-hello.c -o multihello

# Run nomain
./docker-run.sh ./multihello
