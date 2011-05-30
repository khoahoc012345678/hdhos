#include "Lock.h"

LockTable::LockTable() {
	for (int i = 0; i< 10; i++)
		ltab[i] = new Lock ("ltab34343");
	bm  = new BitMap (10);
} 
LockTable:: ~LockTable() {
	if (bm != NULL)
		delete bm;
	for (int i = 0; i< 10; i++)
		if (ltab[i]!=NULL)
			delete ltab[i];
}

int LockTable::MakeLock(char* dbgName) {
	int slot = bm->Find();
	int i;
	if (slot < 0)
	{
		printf ("\nKhong con slot de tao lock");
		return -1;
	}
	for (i = 0; i<10; i++)
	{
		if (ltab[i]!=NULL)
			if (strcmp(ltab[i]->getName(),dbgName) == 0){
				printf("\nlock moi tao trung ten voi lock cu");
				return -1;
			}
	}
	ltab[i]->setName (dbgName);	
	return 0;
}
int LockTable::Aquire (char* dbgName) {
	int i,slot;
	for (i = 0; i<10; i++)
	{
		if (ltab[i]!=NULL)
			if (strcmp(ltab[i]->getName(),dbgName) == 0){
				slot = i;
				break;
			}
	}
	if (i = 10)
	{
		printf("\nsai ten hoac lock chua duoc tao");
		return -1;
	}
	ltab[i]->Acquire();
	return 0;
}
int LockTable::Release(char* dbgName){
	int i,slot;
	for (i = 0; i<10; i++)
	{
		if (ltab[i]!=NULL)
			if (strcmp(ltab[i]->getName(),dbgName) == 0){
				slot = i;
				break;
			}
	}
	if (i = 10)
	{
		printf("\nsai ten hoac lock chua duoc tao");
		return -1;
	}
	ltab[i]->Release();
	return 0;
}