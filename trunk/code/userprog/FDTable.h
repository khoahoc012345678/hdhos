#ifndef FDTABLE_H
#define FDTABLE_H

#include "bitmap.h"
#include "FDBase.h"

#define MAXFILE 10

class FDTable
{
private:
	BitMap bm;
	FDBase *fTable[MAXFILE];
public:
	FDTable();
	~FDTable();
	void  createCout();
	void  createCin();
	
 	int FindFreeSlot();	
	bool IsExistID(int id);	
	
	int fdCreate();
	int fdOpen(int virAddr, int type, int id, OpenFile *of);
	int fdClose(int id);

	int fdRead(char *buffer, int charCount, int id);
	int fdWrite(char *buffer, int charCount, int id);
	int fdSeek(int pos, int id);
};

#endif
