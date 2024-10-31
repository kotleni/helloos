#ifndef H_KERNEL
#define H_KERNEL

#include <kernel.h>

#include <drv/canvas.h>
#include <drv/keyboard.h>
#include <drv/serial.h>

#include <misc/string.h>
#include <misc/ports.h>
#include <misc/malloc.h>

#include <defines.h>
#include <multiboot.h>
// WARN: #include <stdio2.h>

/**
 * (Kernel) Print a formatted string.
 * %s, %c, %x, %d, %%
 *
 * @param fmt Formatted string to print
 * @param ... Additional arguments to format
 */
int kprintf(char *fmt, ...);
void kpanic(char* message);
void kassert(bool is_ok, char* fail_message);
void kreadl(char* input);

void _putch(char ch);
void _puts(char *str);
void _newline();

#endif