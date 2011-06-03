#include "syscall.h"

void main()
{
	Acquire("main");
	Release("main");
	
	Acquire("Lockhigher");
	Release("Lockhigher");

	PrintString("Ket Thuc Higher Halt May");
	Halt();
	
}