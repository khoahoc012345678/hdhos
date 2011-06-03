#include "syscall.h"

void main()
{
	Acquire("main");
	Release("main");
	while(1);
	Exit(0);
}