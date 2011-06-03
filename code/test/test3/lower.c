#include "syscall.h"

void main()
{	
	int i = 0;
	CreateLock("Lockhigher");
	CreateLock("Lockhighest");
	Acquire("Lockhigher");
	Acquire("Lockhighest");
	Acquire("main");
	Release("main");
	for(i = 0;i<1000;i++)
		PrintChar('A');
	PrintString("Ket Thuc Lower Release Lock");
	Release("Lock");
	Exit(0);
}