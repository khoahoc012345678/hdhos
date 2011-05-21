#ifndef SCHANDLE_H
#define SCHANDLE_H
#include "system.h"

int doSC_Create();
int doSC_Open();
int doSC_Close();
int doSC_Read();
int doSC_Write();
int doSC_Seek();

int doSC_Halt();
int doSC_Exec();
int doSC_Join();
int doSC_Fork();
int doSC_Yield();
int doSC_Exit();
int doSC_CreateLock();
int doSC_Acquire();
int doSC_Release();

char* User2System(int virtAddr,int limit);
int System2User(int virtAddr,int len,char* buffer);
int slen(int virtAddr);
void IncreasePC();
int IsValid(char* fName);

#endif