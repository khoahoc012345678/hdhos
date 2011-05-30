#ifndef FDIN_H
#define FDIN_H

#include "FDBase.h"

class FDIn : public FDBase
{
public:
	FDIn();
	virtual ~FDIn();

	int fdRead(char *buffer, int charcount);
	int fdWrite(char *buffer, int charcount);
	int fdSeek(int pos);
};

#endif
