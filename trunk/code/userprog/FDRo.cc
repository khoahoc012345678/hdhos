#include "FDRo.h"

FDRo::FDRo()
{
	of = NULL;
}

FDRo::FDRo(OpenFile *openF)
{
	of = openF;
}

FDRo::~FDRo()
{
	delete of;
}

int FDRo::fdRead(char *buffer, int charcount)
{
	int rs = of->Read(buffer, charcount);
	return rs;
}

int FDRo::fdWrite(char *buffer, int charcount)
{
	return -1;
}

int FDRo::fdSeek(int pos)
{
	int rs = -1;// of->Seek(pos);
	return rs;
}
