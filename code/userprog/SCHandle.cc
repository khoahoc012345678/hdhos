#include "SCHandle.h"
#include "FDTable.h"
#define MaxFileLength 32
#define dbgFile 'f'

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

int doSC_Open()	{return 0;}
int doSC_Close() {return 0;}
int doSC_Read()
{
	int virtAddr = machine->ReadRegister(4);
	
	int size = machine->ReadRegister(5);
	int id = machine->ReadRegister(6);
	char* buffer = User2System(virtAddr,size);
	
	if (size <= 0)
	{
		printf("\nSC_ReadError: unexpected buffer size: %d",size);
		return -1;
	}
	
	if (id < 0 || id >= MAXFILE)
	{
		printf("\n ReadError: Unexpected file id: %d",id);
		return -1;
	}
	if (!currentThread->fTab->IsExistID(id)){
		printf("\n ReadError: reading file id %d is not opened",id);
		return -1;
	}
	//int rs = gSynchConsole->Read(buffer,size);
	int rs = currentThread->fTab->fdRead(buffer,size,id);
	System2User(virtAddr,rs,buffer) ;
	
	return rs;
}
int doSC_Write()
{
	int virtAddr = machine->ReadRegister(4);
	int size = machine->ReadRegister(5);
	int id = machine->ReadRegister(6);
	char* buffer = User2System(virtAddr,size);
	
	if (size < 0)
	{
		printf("\nSC_WriteError: unexpected buffer size: %d",size);
		return -1;
	}
	else if (size == 0)
		return 0;
	
	if (id < 0 || id >= MAXFILE)
	{
		printf("\n WriteError: Unexpected file id: %d",id);
		return -1;
	}
	if (!currentThread->fTab->IsExistID(id)){
		printf("\n WriteError: writing file id %d is not opened",id);
		return -1;
	}
	//int rs = gSynchConsole->Write(buffer,size);
	int rs = currentThread->fTab->fdWrite(buffer,size,id);
	machine->WriteRegister(2,rs);
	
	return rs;
}
int doSC_Seek(){return 0;}

/* 
 * NOTE: Multi-Programming
 */

/*  SpaceID Exec(char* name, int priority) 
 *  Gọi thực thi một chương trình mới trong một system thread mới
 *  Trả về -1 nếu  bị lỗi , thành công trả về process SpaceID
 */
int doSC_Exec()
{
	//printf("\n\n--> Calling SC_Exec.");
	
	int virtAddr = machine->ReadRegister(4);
	char* filename = User2System(virtAddr,MaxFileLength+1);
	
	int priority = machine->ReadRegister(5);
	
	//Kiểm tra file thực thi có tồn tại 
	OpenFile *executable = fileSystem->Open(filename);
	if (executable == NULL) { 				  
		machine->WriteRegister(2,-1);
		delete filename; 
		return -1; 
	}
	
	int PID = processTab->ExecUpdate(filename,priority);
	machine->WriteRegister(2,PID);
	
	//printf("\n--> Kết thúc exec PID = %d \n",PID);
	return 0;
}
/*  int Join(SpaceID id)
 *  Join tiến trình con vào tiến trình cha 
 *  ExitCode = 0 nếu thành công | ExitCode = -1 nếu bị lỗi 
 */ 
int doSC_Join()
{
	int PID = machine->ReadRegister(4);
	//printf("\n\n--> Bat dau join PID: %d",PID);
	int ExitCode = processTab->JoinUpdate(PID);
	
	machine->WriteRegister(2,ExitCode);
	//printf("\n--> Ket thuc join PID: %d, ExitCode: %d",PID,ExitCode);
	return 0;
}

/* void Exit(int exitCode)
 * exitCode = 0 nếu chương trình kết thúc thành công
 * exitCode != 0 nếu lỗi
 */
int doSC_Exit()
{
	DEBUG('f', "\n\n--> Calling SC_Exit.");
	//printf("\n\n Calling SC_Exit.");
	int exitStatus = machine->ReadRegister(4);
	int pid = currentThread->processID; //pid la cua tien trinh can thoat
	
	// if process exited with error, print error
	if (exitStatus != 0)
		printf("\n--> Process %s exited with exitStatus %d",currentThread->getName(),exitStatus);
	
	processTab->ExitUpdate(exitStatus);
	
	currentThread->space->~AddrSpace();
	currentThread->Finish();
	return 0;
}
/* int CreateLock(char* name)
 * trả về 0 nếu thành công 
 * 	-1 nế thất bại 
 */
int doSC_CreateLock()
{
	int virtAddr = machine->ReadRegister(4);
	char* name = User2System(virtAddr,MaxFileLength+1);
	if(name == NULL)
	{
		printf("\ndoSC_CreateLock :: name = NULL");
		machine->WriteRegister(2,-1);
		return -1;
	}
	int kq = semTab->Create(name,1);
	if (kq == -1)
	{
		printf ("\nFail to create lock name %s", name);
		machine->WriteRegister (2,-1);
		return -1;
	}
	machine->WriteRegister(2,0);
	return 0;
}
/* int Acquire(char* name)
 * trả về 0 nếu thành công 
 * 	-1 nế thất bại 
 */
int doSC_Acquire()
{
	int virtAddr = machine->ReadRegister(4);
	char* name = User2System(virtAddr,MaxFileLength+1);
	if(name == NULL)
	{
		printf("\ndoSC_Acquire :: name = NULL");
		machine->WriteRegister(2,-1);
		return -1;
	}
	int kq = semTab->Wait(name);
	if (kq == -1)
	{
		printf ("\nFail to create lock name %s", name);
		machine->WriteRegister (2,-1);
		return -1;
	}
	machine->WriteRegister(2,0);
	return 0;
}

/* int Release(char* name)
 * trả về 0 nếu thành công 
 * 	-1 nế thất bại  
 */
int doSC_Release()
{
	int virtAddr = machine->ReadRegister(4);
	char* name = User2System(virtAddr,MaxFileLength+1);
	if(name == NULL)
	{
		printf("\ndoSC_Release :: name = NULL");
		machine->WriteRegister(2,-1);
		return -1;
	}
	int kq = semTab->Signal(name);
	if (kq == -1)
	{
		printf ("\nFail to create lock name %s", name);
		machine->WriteRegister (2,-1);
		return -1;
	}
	machine->WriteRegister(2,0);
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
