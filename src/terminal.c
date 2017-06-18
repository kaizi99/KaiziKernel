#include "terminal.h"

volatile uint16_t* vga_buffer = (uint16_t*)0xB8000;
const int TERM_COLS = 80;
const int TERM_ROWS = 25;

int term_x;
int term_y;

uint8_t term_color = 0x0F;

void term_clear()
{
  for (term_x = 0; term_x < TERM_COLS; term_x++)
  {
    for (term_y = 0; term_y < TERM_ROWS; term_y++)
    {
      size_t index = (TERM_COLS * term_y) + term_x;
      vga_buffer[index] = ((uint16_t)term_color << 8) | ' ';
    }
  }
  term_x = 0;
  term_y = 0;
}

void term_putc(char c)
{
  switch (c)
  {
  case '\n':
    term_x = 0;
    term_y++;
    break;
  default: ;
    size_t index = (TERM_COLS * term_y) + term_x;
    vga_buffer[index] = ((uint16_t)term_color << 8) | c;
    term_x++;
    break;
  }

  if (term_x > TERM_COLS)
  {
    term_x = 0;
    term_y++;
  }

  if (term_y > TERM_ROWS)
  {
    term_clear();
  }
}

void term_print(const char* str)
{
  for (size_t i = 0; str[i] != '\0'; i++)
    term_putc(str[i]);
}
