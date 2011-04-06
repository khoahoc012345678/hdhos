// exception.cc 
//	Entry point into the Nachos kernel from user programs.
//	There are two kinds of things that can cause control to
//	transfer back to here from user code:
//
//	syscall -- The user code explicitly requests to call a procedure
//	in the Nachos kernel.  Right now, the only function we support is
//	"Halt".
//
//	exceptions -- The user code does something that the CPU can't handle.
//	For instance, accessing memory that doesn't exist, arithmetic errors,
//	etc.  
//
//	Interrupts (which can also cause control to transfer from user
//	code into the Nachos kernel) are handled elsewhere.
//
// For now, this only handles the Halt() system call.
// Everything else core dumps.
//
// Copyright (c) 1992-1993 The Regents of the University of California.
// All rights reserved.  See copyright.h for copyright notice and limitation 
// of liability and disclaimer of warranty provisions.
#ifndef SYSCHCONSOLE_H
#define SYSCHCONSOLE_H
#endif
#include "copyright.h"
#include "system.h"
#include "syscall.h"


#define MaxFileLength 320
#define MAX 2222

char* User2System(int virtAddr,int limit);
int System2User (int virtAddr, int len, char* buff);
void IncreaseProgramCounter();  


//----------------------------------------------------------------------
// ExceptionHandler
// 	Entry point into the Nachos kernel.  Called when a user program
//	is executing, and either does a syscall, or generates an addressing
//	or arithmetic exception.
//
// 	For system calls, the following is the calling convention:
//
// 	system call code -- r2
//		arg1 -- r4
//		arg2 -- r5
//		arg3 -- r6
//		arg4 -- r7
//
//	The result of the system call, if any, must be put back into r2. 
//
// And don't forget to increment the pc before returning. (Or else you'll
// loop making the same system call forever!
//
//	"which" is the kind of exception.  The list of possible exceptions 
//	are in machine.h.
//----------------------------------------------------------------------

void
ExceptionHandler(ExceptionType which)
{
    int type = machine->ReadRegister(2);
switch (which)
{
	case NoException:
		return ;
	case PageFaultException: 
		break;
	case ReadOnlyException: 
		break;
	case BusErrorException: 
		break;
	case AddressErrorException: 
		break;
	case OverflowException: 
		break;
	case IllegalInstrException: 
		break;
	case NumExceptionTypes: 
		break;
	case SyscallException:
		switch(type)
		{
			case SC_Halt:
				DEBUG('a',"\n Shutdown,initiated by user program.");
				interrupt->Halt();
				break;
			
			 case SC_Create:
			    { 
				int virtAddr; 
				char* filename; 
				 
				DEBUG('a',"\n SC_Create call ..."); 
				DEBUG('a',"\n Reading virtual address of filename"); 
				virtAddr = machine->ReadRegister(4); 
				DEBUG ('a',"\n Reading filename."); 
				filename = User2System(virtAddr,MaxFileLength+1);  
				if (filename == NULL) 
				{ 				  
				     DEBUG('a',"\n Not enough memory in system"); 
				     machine->WriteRegister(2,-1);
				     delete filename; 
				     return; 
				} 
				DEBUG('a',"\n Finish reading filename."); 
				if (!fileSystem->Create(filename,0)) 
				{ 
				     machine->WriteRegister(2,-1); 
				     delete filename; 
				     return; 
				} 
				machine->WriteRegister(2,0); 
				delete filename; 
				return; 
			} 
			case SC_ReadInt:
			{
				char* buffer = new char [MAX];
;				int kq = 0,MuMuoi = 1;
				int key = MySynchConsole -> Read(buffer,MAX);
				//kt du lieu
				if (key==-1)
					break;
				else
					for (int i=key-1;i>=0;i--)
					{
						if ((buffer[i]<'0') | (buffer[i]>'9') )
						{
							MySynchConsole->Write("error: Sai Kieu!!!",18);
							machine->WriteRegister(2,0); 
							break;
						}
						//chuyen tu char* -> int
						for (int j=0; j<key-i-1; j++)
						{
							MuMuoi=MuMuoi*10;
						}
						kq=kq+((int)buffer[i] - 48)*MuMuoi;
						MuMuoi = 1;
					
					}
				
				machine->WriteRegister(2,kq); //
				delete buffer;
				break; 
			}
			case SC_PrintInt :
			{
				int virtAddr = machine->ReadRegister(4); 
				char* buffer = new char [MAX];
				//chuyen tu int -> char*
				int len = 0;
				while (virtAddr != 0)
				{
					buffer[len] = (char) (virtAddr%10 + 48);
					virtAddr=virtAddr/10;
					len++;
				}
				//dao nguoc chuoi
				char c;
				for (int i=0; i<len/2; i++)
				{
					c = buffer[i];
					buffer[i]=buffer[len-i-1];
					buffer[len-i-1]=c;
						
				}
				MySynchConsole->Write("\n\tSo Nhan Duoc:\t",16);
				MySynchConsole->Write(buffer, len);
				MySynchConsole->Write("\n", 1);
				delete buffer;
				break;
			}
			
			case SC_ReadChar :
			{
				char* c = new char[2];
				int key = MySynchConsole -> Read(c,1);
				if (key==-1)
				{
					break;
				}
				else
				{
					machine->WriteRegister(2,(int)c[0]); //
				}
				delete c;
				break;
			}
				
			case SC_PrintChar:
			{
				int virtAddr = machine->ReadRegister(4); 
				char *buffer = new char[2];
				buffer [0] = (char) virtAddr;
				MySynchConsole->Write("\n\tKy tu Nhan Duoc:\t",20);
				MySynchConsole->Write(buffer, 1);
				MySynchConsole->Write("\n", 1);
				delete buffer;
				break;
			
			}
			case SC_ReadString:
			{
				int virtAddr = machine->ReadRegister(4); 
				int length = machine->ReadRegister(5); 
				char *buffer = new char [MAX];
				int nByte;
				while (1)
				{
					nByte = MySynchConsole->Read(buffer, MAX);
					if (nByte > length)
					{
						MySynchConsole->Write("Vuot Qua Do Dai Cho Phep.!!",27);
						nByte = length;
						break;
					}
					break;
				}
				int Number_of_bytes_copied = System2User(virtAddr,nByte,buffer) ;
				if (Number_of_bytes_copied==nByte)
					MySynchConsole->Write("copy complete!!",15);
				else
					MySynchConsole->Write("thieu du lieu",14);
				delete buffer;
				break;
			}
			case SC_PrintString:
			{
				int virtAddr = machine->ReadRegister(4);
				char* buffer = new char[MAX];
				buffer = User2System(virtAddr,MAX+1);  
				int len = 0;
				while(buffer[len++] != '\0');
			
				if (buffer == NULL) 
				{ 
				     printf("\n Not enough memory in system"); 
				     machine->WriteRegister(2,-1);
				     delete buffer; 
				     return; 
				} 
				MySynchConsole->Write("\n\tChuoi Nhan Duoc:\n",19);
				MySynchConsole->Write(buffer, len);
				MySynchConsole->Write("\n", 1);
				break;
			}				
			default:
			{
				printf("\nLoi default: Unexpected user mode exception (%d %d)",which,type);
				ASSERT(FALSE);
				interrupt->Halt();
				
			}
		}
		IncreaseProgramCounter() ;
		break;
	}
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

void IncreaseProgramCounter() 
{
  int iPc;
  iPc = machine->ReadRegister(PCReg);
  machine->WriteRegister(PrevPCReg, iPc);
  iPc = machine->ReadRegister(NextPCReg);
  machine->WriteRegister(PCReg, iPc);
  iPc += 4;
  machine->WriteRegister(NextPCReg, iPc);
}
