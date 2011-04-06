
#include "syscall.h"
#include "copyright.h"

#define maxlen 32
int main()
{
	int len;
	char filename[maxlen+1];
char* name = "test.txt";
len = Create(name)	;
if (len == -1)
{
Write("testing exec\n",13,ConsoleOutput);

}
else
{
Write("testing fail\n",13,ConsoleOutput);

}
Halt();	
	return 0;
}
