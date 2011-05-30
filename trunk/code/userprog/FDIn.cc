#include "FDIn.h"
#include "system.h"

FDIn::FDIn()
{
}

FDIn::~FDIn()
{
}

int FDIn::fdRead(char *buffer, int charcount)
{
	int rs = gSynchConsole->Read(buffer, charcount);
	return rs;
}

int FDIn::fdWrite(char *buffer, int charcount)
{
	return -1;
}

int FDIn::fdSeek(int pos)
{
	printf("Seek on console is invalid!\n");
	return -1;
}
