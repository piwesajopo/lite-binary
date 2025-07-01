#if defined(_WIN32) // Covers Win32 & Win64
#error "Unsupported OS."
#endif

#if defined(__aarch64__)

const char msg[] = "Hello from ARM64!\n";
// AArch64 syscall numbers
#define SYS_write 64
#define SYS_exit  93

#elif defined(__x86_64__)

const char msg[] = "Hello from x86_64!\n";
// x86_64 syscall numbers
#define SYS_write 1
#define SYS_exit  60

#else
#error "Unsupported architecture. Only AArch64 and x86_64 are supported."
#endif

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
#if defined(__aarch64__)
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
#elif defined(__x86_64__)
    __asm__ volatile (
        "movq %[fd], %%rdi\n"
        "movq %[buf], %%rsi\n"
        "movq %[len], %%rdx\n"
        "movq %[syscall], %%rax\n"
        "syscall\n"
        :
        : [syscall] "i"(SYS_write),
          [fd] "i"(STDOUT_FILENO),
          [buf] "r"(s),
          [len] "r"((unsigned long)len)
        : "rdi", "rsi", "rdx", "rax"
    );
#endif
}

// Custom entry point (no CRT)
void _start() {
    print(msg);

#if defined(__aarch64__)
    // Exit syscall: exit(0)
    __asm__ volatile (
        "mov x8, %[sys_exit]\n"
        "mov x0, #0\n"
        "svc 0\n"
        :
        : [sys_exit] "i"(SYS_exit)
        : "x0", "x8"
    );
#elif defined(__x86_64__)
    // Exit syscall: exit(0)
    __asm__ volatile (
        "movq $0, %%rdi\n"
        "movq %[sys_exit], %%rax\n"
        "syscall\n"
        :
        : [sys_exit] "i"(SYS_exit)
        : "rdi", "rax"
    );
#endif
}
