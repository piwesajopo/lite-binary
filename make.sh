# Compile normal Hello World
./docker-run.sh gcc stdhello.c -o stdhello

# Compile nomain
./docker-run.sh gcc -fno-builtin -nostartfiles -nostdlib -static -Wl,-e,_start litehello.c -o litehello

# Run nomain
./docker-run.sh ./litehello
