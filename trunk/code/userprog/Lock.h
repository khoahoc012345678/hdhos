 #ifndef LOCK_H
 #define LOCK_H
 #include "thread.h"
 #include "synch.h"
#include "bitmap.h"
 class LockTable {
	BitMap *bm;
	Lock *ltab[10];
 public:
	 LockTable(); 
	 ~LockTable();
	 int MakeLock(char* dbgName);
	 int Aquire (char* dbgName);
	 int Release(char* dbgName);
};
 
 #endif