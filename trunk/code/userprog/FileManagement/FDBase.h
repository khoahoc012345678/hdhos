#ifndef FDBASE_H
#define FDBASE_H

class FDBase
{
public:
	FDBase();
	virtual ~FDBase();

	virtual int fdRead(char *buffer, int charcount) = 0;
	virtual int fdWrite(char *buffer, int charcount) = 0;
	virtual int fdSeek(int pos) = 0;
	// No fdOpen, no fdClose
};

#endif