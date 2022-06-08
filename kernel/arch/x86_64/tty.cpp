#include <stddef.h>
#include <stdint.h>
#include "vga.h"
#include "string.h"

static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;
static uint16_t *const VGA_MEMORY = (uint16_t *) 0xB8000;

static size_t terminal_row;
static size_t terminal_column;
static volatile uint8_t terminal_color;
static volatile uint16_t *terminal_buffer;

void terminal_initialize() {
    terminal_row = 0;
    terminal_column = 0;

    terminal_color = vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);

    terminal_buffer = VGA_MEMORY;
    for (size_t y = 0; y < VGA_HEIGHT; y++) {
        for (size_t x = 0; x < VGA_WIDTH; x++) {
            const size_t index = y * VGA_WIDTH + x;
            terminal_buffer[index] = vga_entry(' ', terminal_color);
        }
    }
}

void terminal_setcolor(uint8_t color) {
    terminal_color = color;
}

void terminal_putentryat(unsigned char c, uint8_t color, size_t x, size_t y) {
    const size_t index = y * VGA_WIDTH + x;
    terminal_buffer[index] = vga_entry(c, color);
}

void terminal_scroll(int line) {
    memmove((void *) terminal_buffer, (const void *) (terminal_buffer + (line * VGA_WIDTH)),
            VGA_WIDTH * (line + 1) * (VGA_HEIGHT - 1));
}

void terminal_delete_last_line() {
    unsigned long x;
    for (x = 0; x < VGA_WIDTH; x++) {
        volatile const size_t index = (VGA_HEIGHT - 1) * VGA_WIDTH + x;
        terminal_buffer[index] = 0x0;
    }
}

void terminal_putchar(char c) {
    unsigned long line;
    unsigned char uc = c;

    terminal_putentryat(uc, terminal_color, terminal_column, terminal_row);
    terminal_column++;
    if (terminal_column == VGA_WIDTH) {
        terminal_column = 0;
        terminal_row++;
        if (terminal_row == VGA_HEIGHT - 1) {
            terminal_scroll(1);
            terminal_row = VGA_HEIGHT - 2;
            terminal_delete_last_line();
        }
    }
}

void terminal_write(const char *data, size_t size) {
    for (size_t i = 0; i < size; i++) {
        terminal_putchar(data[i]);
    }
}

void terminal_writestring(const char *data) {
    terminal_write(data, strlen(data));
}