#include "SCHandle.h"
//#include "./FileManagement/FDTable.h"
#define MaxFileLength 32
int doSC_Create()
{
	int virtAddr; 
	char* filename; 
	
	virtAddr = machine->ReadRegister(4); 
	filename = User2System(virtAddr,MaxFileLength+1);  
	if (filename == NULL) 
	{ 				  
		machine->WriteRegister(2,-1);
		delete filename; 
		return -1; 
	} 
	if (!fileSystem->Create(filename,0)) 
	{ 
		machine->WriteRegister(2,-1); 
		delete filename; 
		return -1; 
	} 
	machine->WriteRegister(2,0); 
	delete filename; 
	return 0;
}
int doSC_Open()
{
	return 0;
}
int doSC_Close()
{
	return 0;
}
int doSC_Read()
{
	return 0;
}
int doSC_Write()
{
	return 0;
}
int doSC_Seek()
{
	return 0;
}

/* 
 * NOTE: Multi-Programming
 */

int doSC_Halt()
{
	DEBUG('a',"\n Shutdown,initiated by user program.");
	interrupt->Halt();
}
/* Exec gọi thực thi một chương trình mới trong một system thread mới
 *  -1 nếu bị lỗi và thành công thì trả về Process SpaceID 
 */
int doSC_Exec()
{
	printf("\n\n--> Calling SC_Exec.");
	int virtAddr = machine->ReadRegister(4);
	char* filename = User2System(virtAddr,MaxFileLength+1);
	int priority = machine->ReadRegister(5);
	OpenFile *executable = fileSystem->Open(filename);
	if (executable == NULL) 
	{ 				  
		machine->WriteRegister(2,-1);
		delete filename; 
		return -1; 
	} 
	int pid = processTab->ExecUpdate(filename,priority);
	machine->WriteRegister(2,pid);
	printf("\n*****************End SC_Exec******************\n");
	return 0;
}
int doSC_Join()
{
	printf("\n\n--> Calling SC_Join.");
	int id = machine->ReadRegister(4);
	
	int ec = processTab->JoinUpdate(id);
	
	machine->WriteRegister(2,ec);
	printf("\n*******************End SC_Join******************\n");
	return 0;
}
int doSC_Fork()
{
	return 0;
}
int doSC_Yield()
{
	return 0;
}
int doSC_Exit()
{
	DEBUG('f', "\n\n--> Calling SC_Exit.");
	printf("\n\n Calling SC_Exit.");
	int exitStatus = machine->ReadRegister(4);
	int pid = currentThread->processID; //pid la cua tien trinh can thoat
	
	// if process exited with error, print error
	if (exitStatus != 0)
		printf("\nProcess %s exited with error level %d",currentThread->getName(),exitStatus);
	
	processTab->ExitUpdate(exitStatus);
	
	currentThread->space->~AddrSpace();
	currentThread->Finish();
	return 0;
}
int doSC_CreateLock()
{
	return 0;
}
int doSC_Acquire()
{
	return 0;
}
int doSC_Release()
{
	return 0;
}


// Input: - User space address (int) 
//  - Limit of buffer (int) 
// Output:- Buffer (char*) 
// Purpose: Copy buffer from User memory space to System memory space 
char* User2System(int virtAddr,int limit) 
{ 
     int i;// index 
     int oneChar; 
     char* kernelBuf = NULL; 
     kernelBuf = new char[limit +1];//need for terminal string 
     if (kernelBuf == NULL) 
     return kernelBuf; 
     memset(kernelBuf,0,limit+1); 
     //printf("\n Filename u2s:"); 
     for (i = 0 ; i < limit ;i++) 
     { 
          machine->ReadMem(virtAddr+i,1,&oneChar); 
          kernelBuf[i] = (char)oneChar; 
          //printf("%c",kernelBuf[i]); 
          if (oneChar == 0) 
		break; 
     } 
     return kernelBuf; 
} 

// Input: - User space address (int) 
//       - Limit of buffer (int) 
//       - Buffer (char[]) 
// Output:- Number of bytes copied (int) 
// Purpose: Copy buffer from System memory space to User  memory space 
int   System2User(int virtAddr,int len,char* buffer) 
{ 
  if (len < 0) return -1; 
     if (len == 0)return len; 
     int i = 0; 
     int oneChar = 0 ; 
    do{ 
     oneChar= (int) buffer[i]; 
     machine->WriteMem(virtAddr+i,1,oneChar); 
     i ++; 
   }while(i < len && oneChar != 0); 
  return i; 
}

int slen(int virtAddr)
{
	return 0;
}

void IncreasePC()
{
	int iPc;
	iPc = machine->ReadRegister(PCReg);
	machine->WriteRegister(PrevPCReg, iPc);
	iPc = machine->ReadRegister(NextPCReg);
	machine->WriteRegister(PCReg, iPc);
	iPc += 4;
	machine->WriteRegister(NextPCReg, iPc);
}
int IsValid(char* fName)
{
	return 0;
}
