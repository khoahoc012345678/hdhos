#ifndef FDRO_H
#define FDRO_H

#include "openfile.h"
#include "FDBase.h"

class FDRo : public FDBase
{
private:
	OpenFile *of;
public:
	FDRo();
	FDRo(OpenFile *openF);
	virtual ~FDRo();

	int fdRead(char *buffer, int charcount);
	int fdWrite(char *buffer, int charcount);
	int fdSeek(int pos);
};

#endif