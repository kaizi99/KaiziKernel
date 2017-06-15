#include "terminal.h"

void kernelMain()
{
  term_clear();
  term_print("Hello World!");
  while(1);
}
