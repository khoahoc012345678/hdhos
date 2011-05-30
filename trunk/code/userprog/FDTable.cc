#include "FDTable.h"
#include "FDIn.h"
#include "FDOut.h"
#include "FDRo.h"
#include "FDRw.h"

#define RWFILE 0
#define ROFILE 1

FDTable::FDTable() : bm(MAXFILE)
{
	FDIn *inp = new FDIn();
	FDOut *outp = new FDOut();

	fTable[0] = (FDBase *) inp;
	fTable[1] = (FDBase *) outp;
	bm.Mark(0);
	bm.Mark(1);

	for (int i = 2; i < MAXFILE; i++)
		fTable[i] = NULL;
}

FDTable::~FDTable()
{
	delete []fTable;
}

// Purpose : them 1 item vao bang fTable
int FDTable::fdOpen(int virtAddr, int t, int i, OpenFile *of)
{
	int vA = virtAddr;
	int type = t;
	int id = i;
	FDRw *rw;
	FDRo *ro;

	switch(type)
	{
		case RWFILE:
			rw = new FDRw(of);
			fTable[id] = (FDBase*) rw;
			break;
		case ROFILE:
			ro = new FDRo(of);
			fTable[id] = (FDBase*) ro;
			break;
		default:
			printf("\n FDTable:OpenFileError - unknow file type %d",type);
			break;
	}

	return id;
}

int FDTable::fdClose(int id)
{
	bm.Clear(id);
	delete fTable[id];
	fTable[id] = NULL;

	return 0;
}

int FDTable::fdRead(char *buffer, int charcount, int id)
{
	int rs = fTable[id]->fdRead(buffer, charcount);
	return rs;
}

int FDTable::fdWrite(char *buffer, int charcount, int id)
{
	int rs = fTable[id]->fdWrite(buffer, charcount);
	return rs;
}

int FDTable::fdSeek(int pos, int id)
{
	int rs = fTable[id]->fdSeek(pos);
	return rs;
}

// Tim vi tri con trong trong table
int FDTable::FindFreeSlot()
{
	return bm.Find();
}

// Kiem tra xem tai id co file duoc mo hay chua
bool FDTable::IsExistID(int id)
{
	return bm.Test(id);
}
