#ifndef FDOUT_H
#define FDOUT_H

#include "FDBase.h"

class FDOut : public FDBase
{
public:
	FDOut();
	virtual ~FDOut();

	int fdRead(char *buffer, int charcount);
	int fdWrite(char *buffer, int charcount);
	int fdSeek(int pos);
};

#endif
