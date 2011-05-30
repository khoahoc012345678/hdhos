#ifndef FDRW_H
#define FDRW_H

#include "openfile.h"
#include "FDBase.h"

class FDRw : public FDBase
{
private:
	OpenFile *of;
public:
	FDRw();
	FDRw(OpenFile *openF);
	virtual ~FDRw();

	int fdRead(char *buffer, int charcount);
	int fdWrite(char *buffer, int charcount);
	int fdSeek(int pos);
};

#endif