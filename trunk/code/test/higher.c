#include "syscall.h"

void main()
{
	Acquire("main");
	Release("main");
	
	Acquire("Lockhigher");
	Release("Lockhigher");

	Write("Ket Thuc Higher Halt May",50,ConsoleOutput);
	Halt();
	
}