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
	const char* message = "This is CSE506 proxy_kernel. Still in beta phase.. \n";
	while (*message)
		sbi_console_putchar(*message++);
	kprintf("Welcome To SBU Unix on RISC V\n");
	memory_block_info mb;

	sbi_query_memory(sbi_hart_id(), &mb);
	kprintf("Memory Info : %p %x %x\n", mb.base, mb.size, mb.node_id);
	while (1) {
		char ch;
		ch = sbi_console_getchar();
		//sbi_console_putchar(ch);
	}
	sbi_shutdown();
}
