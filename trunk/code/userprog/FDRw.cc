#include "FDRw.h"

FDRw::FDRw()
{
	of = NULL;
}
FDRw::FDRw(OpenFile *openF)
{
	of = openF;
}

FDRw::~FDRw()
{
	delete of;
}

int FDRw::fdRead(char *buffer, int charcount)
{
	int rs = of->Read(buffer, charcount);
	return rs;
}

int FDRw::fdWrite(char *buffer, int charcount)
{
	int rs = of->Write(buffer, charcount);
	return rs;
}

int FDRw::fdSeek(int pos)
{
	int rs = -1;//of->Seek(pos);
	return rs;
}
