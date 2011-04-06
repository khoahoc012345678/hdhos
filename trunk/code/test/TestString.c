#include "syscall.h"
#include "copyright.h"


int main()
{
	char chuoinhap [60];
	ReadString(chuoinhap,60);
	PrintString(chuoinhap);
	Halt();	

}
