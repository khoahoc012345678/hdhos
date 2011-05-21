#include "syscall.h"
int main()
{
	int i;
	for (i = 0; i<254; i++)
	{
		PrintChar((char)i);
	}
	Exit(1);
}
