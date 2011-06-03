#include "syscall.h"

void main()
{
	Acquire("main");
	Release("main");
	
	Acquire("Lock");
	Release("Lock");

	Write("Ket Thuc High Halt May",50,ConsoleOutput);
	Halt();
	
}