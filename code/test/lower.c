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
		Write("A",2,ConsoleOutput);
	Write("Ket Thuc Lower Release Lock",50,ConsoleOutput);
	Release("Lock");
	Exit(0);
}