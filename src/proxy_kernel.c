#include <stdint.h>
#include <sbi.h>
#include <kprintf.h>

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
"This is CSE506 proxy_kernel. Still in beta phase.. \n";
  while (*message)
    sbi_console_putchar(*message++);
  kprintf("Hello world\n");
  int a = 10;
  char b = 'A';
  kprintf("%d %c", a, b);
  sbi_shutdown();
}
