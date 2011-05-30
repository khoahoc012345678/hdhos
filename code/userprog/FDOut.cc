#include "FDOut.h"
#include "system.h"

FDOut::FDOut()
{
}

FDOut::~FDOut()
{
}

int FDOut::fdRead(char *buffer, int charcount)
{
	return -1;
}

int FDOut::fdWrite(char *buffer, int charcount)
{
	int rs = gSynchConsole->Write(buffer, charcount);
	return rs;
}

int FDOut::fdSeek(int pos)
{
	printf("Seek on console is invalid!\n");
	return -1;
}
