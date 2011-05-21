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
#include "SCHandle.h"

#define MaxFileLength 320
#define MAX 2222

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
			printf("NoException");
			IncreasePC() ;
			return ;
		case PageFaultException: 
			printf("PageFaultException");
			IncreasePC() ;
			break;
		case ReadOnlyException: 
			printf("ReadOnlyException");
			IncreasePC() ;
			break;
		case BusErrorException: 
			printf("BusErrorException");
			IncreasePC() ;
			break;
		case AddressErrorException: 
			printf("AddressErrorException");
			IncreasePC() ;
			break;
		case OverflowException: 
			printf("OverflowException");
			IncreasePC() ;
			break;
		case IllegalInstrException: 
			printf("IllegalInstrException");
			IncreasePC() ;
			break;
		case NumExceptionTypes: 
			printf("NumExceptionTypes");
			IncreasePC() ;
			break;
		case SyscallException:
			switch(type)
			{
				case SC_Halt:
					DEBUG('a',"\n Shutdown,initiated by user program.");
					interrupt->Halt();
					break;
				case SC_Exit:
				{
					IncreasePC() ;
					break;
				}
				case SC_Exec:
				{
					IncreasePC() ;
					break;
				}
				case SC_Join:
				{
					IncreasePC() ;
					break;
				}
				case SC_Create:
				{
					doSC_Create();
					IncreasePC() ;
					break;
				}
				case SC_Open:
				{
					IncreasePC() ;
					break;
				}
				case SC_Read:
				{
					doSC_Read();
					IncreasePC() ;
					break;
				}
				case SC_Write:
				{
					doSC_Write();
					IncreasePC() ;
					break;
				}
				case SC_Close:
				{
					doSC_Close();
					IncreasePC() ;
					break;
				}
				case SC_Fork:
				{
					IncreasePC() ;
					break;
				}
				case SC_Yield:
				{
					IncreasePC() ;
					break;
				}
				
				case SC_ReadInt:
				{
					char* buffer = new char [sizeof(int)];
					;				int value = 0;
					int key = gSynchConsole -> Read(buffer, sizeof(int));
					//kt du lieu
					if (key==-1)
						break;
					else
						value = atoi(buffer);		
					machine->WriteRegister(2,value);
					delete buffer;
					IncreasePC() ;
					break; 
				}
				case SC_PrintInt :
				{
					int value = machine->ReadRegister(4); 
					char* buffer = new char [ sizeof(int)];
					sprintf(buffer,"%d",value);
					gSynchConsole->Write(buffer, strlen(buffer));
					delete buffer;
					IncreasePC() ;
					break;
				}
				
				case SC_ReadChar :
				{
					char* c = new char[2];
					int key = gSynchConsole -> Read(c,1);
					if (key==-1)
					{
						break;
					}
					else
					{
						machine->WriteRegister(2,(int)c[0]); //
					}
					delete c;
					IncreasePC() ;
					break;
				}
				
				case SC_PrintChar:
				{
					int virtAddr = machine->ReadRegister(4); 
					char *buffer = new char[2];
					buffer [0] = (char) virtAddr;
					gSynchConsole->Write(buffer, 1);
					delete buffer;
					IncreasePC() ;
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
						nByte = gSynchConsole->Read(buffer, MAX);
						if (nByte > length)
						{
							gSynchConsole->Write("Vuot Qua Do Dai Cho Phep.!!",27);
							nByte = length;
							break;
						}
						break;
					}
					System2User(virtAddr,nByte,buffer) ;
					delete buffer;
					IncreasePC() ;
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
					gSynchConsole->Write(buffer, len);
					IncreasePC() ;
					break;
				}
				
				
			}
		
	}
}

