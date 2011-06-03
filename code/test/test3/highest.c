#include "syscall.h"

void main()
{
	Acquire("main");
	Release("main");
	
	Acquire("Lockhighest");
	Release("Lockhighest");

	PrintString("Ket Thuc Highest");
	Exit(0);	
}