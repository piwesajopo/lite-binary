#ifndef __aarch64__
#error "This code only supports AArch64 syscalls."
#endif

#define SYS_write 64 // AArch64 syscall: write
#define SYS_exit  93 // AArch64 syscall: exit
#define STDOUT_FILENO 1 // File descriptor number for standard output

// Simple strlen (no libc)
unsigned strlen(const char *s) {
    if (!s) return 0;
    unsigned len = 0;
    while (s[len]) len++;
    return len;
}

// Print a string using syscall
void print(const char *s) {
    unsigned len = strlen(s);

    __asm__ volatile (
        "mov x8, %[syscall]\n"   // syscall number (write)
        "mov x0, %[fd]\n"        // fd (stdout)
        "mov x1, %[buf]\n"       // buf (string)
        "mov x2, %[len]\n"       // len
        "svc 0\n"
        :
        : [syscall] "i"(SYS_write),
          [fd] "i"(STDOUT_FILENO),
          [buf] "r"(s),
          [len] "r"(len)
        : "x0", "x1", "x2", "x8"
    );
}

// Custom entry point (no CRT)
void _start() {
    const char msg[] = "Hello from ARM64!\n";
    print(msg);

    // Exit syscall: exit(0)
    __asm__ volatile (
        "mov x8, %[sys_exit]\n"
        "mov x0, #0\n"
        "svc 0\n"
        :
        : [sys_exit] "i"(SYS_exit)
        : "x0", "x8"
    );
}
