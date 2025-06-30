# Ultra Lightweight Binary Example

This is an example of how to generate a binary of minimal size by using de GNU C Compiler.
This example assumes you are running this on a machine aarch64 (i.e. Apple Silicon).

## Requirements

The code in this example uses aarch64 assembly code, so it will run on this specific architecture.

If you are using Apple Silicon you will need to have docker installed and download the gcc image.

To download gcc using docker execute the command:

```shell
docker pull gcc
```

## Compiling on Apple Silicon:

On MacOS you will run into several limitations when trying to compile the example code properly.
For that reason a `make.sh` script is included here that uses docker gcc image to compile the program.

The script will compile both `litehello.c` and `stdhello.c` and will also proceed to run the `litehello` binary.

## Compiling on Linux ARM:

If you are running this on a Linux ARM machine, just use the following gcc command:

```shell
gcc -fno-builtin -nostartfiles -nostdlib -static -Wl,-e,_start litehello.c -o litehello
```

To see how small is the generated binary compared to a normal C program, you can compile the included traditional example:

```shell
gcc stdhello.c -o stdhello
```
