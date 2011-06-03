#include "syscall.h"

void main()
{
	Acquire("main");
	Release("main");
	
	Acquire("Lockhighest");
	Release("Lockhighest");

	Write("Ket Thuc Highest",50,ConsoleOutput);
	Exit(0);	
}