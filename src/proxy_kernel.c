#include <stdint.h>
#include <sbi.h>

asm (".globl _start\n\
  _start: la sp, stack\n\
  j entry\n\
  .pushsection .rodata\n\
  .align 4\n\
  .skip 4096\n\
  stack:\n\
  .popsection");

void entry()
{
  const char* message =
"This is bbl's proxy_kernel. Still in beta phase. \n";
  while (*message)
    sbi_console_putchar(*message++);
  sbi_shutdown();
}
