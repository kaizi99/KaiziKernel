#include <stddef.h>
#include <stdint.h>

volatile uint16_t* vga_buffer;
uint8_t term_color;

void term_clear();
void term_putc(char c);
void term_print(const char* str);
