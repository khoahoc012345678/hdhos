#include "pcb.h"
#include "system.h"

PCB::PCB()
{
	this->pid = 0;
	this->parentID = -1;
	this->numwait = 0;
	this->exitcode = 0;
	this->thread = NULL;
	this->joinsem = new Semaphore("joinsem",0);
	this->exitsem = new Semaphore("exitsem",0);
	this->mutex = new Semaphore("multex",1);
}

PCB::PCB(int id)
{
	//printf ("\n--> Khoi tao PCB[%d]",id);
	joinsem = new Semaphore ("joinsem",0);
	exitsem = new Semaphore ("exitsem",0);
	mutex = new Semaphore ("mutex",1);
	thread = NULL;
	this->pid = id;
	this->parentID = currentThread->processID;
	this->numwait = 0;
	this->exitcode = 0;
	this->parentID = 0;
	//printf ("\n--> End Khoi tao PCB[%d]",id);
}

PCB::~PCB()
{
	//printf ("\n--> Huy PCB");
	//printf("~PCB(); ID Thread = %d",currentThread->processID);
	if (joinsem!=NULL){
		delete joinsem;
	}	
	if(exitsem!=NULL){
		delete exitsem;
	}	
	if(mutex!=NULL){
		delete mutex;
	}	
	if (thread!=NULL){
		thread->FreeSpace();
// 		if(pid == 0){//exit main process
//  		interrupt->Halt();
// 		}
		thread->Finish();	
	}
	//printf ("\n--> End Huy PCB");
}

int PCB::Exec(char *filename,int pid)
{
	//printf ("\n--> PCB[id]-->Exec");
	mutex->P();
	
	this->thread = new Thread(filename);
	if(this->thread == NULL)
	{
		printf ("Lack memory to create new thread!!!");
		return -1;
	}
	//NOTE: can 1 mang chua ten file cho moi thread danh dau bang PID de truyen tham so vao NewStartProcess
	this->thread->processID = pid;
	this->parentID = currentThread->processID;
	this->thread->priority = this->priority;
	this->thread->Fork(StartProcess,pid);
	mutex->V();
	//printf ("\n-->Ket thuc PCB[id]-->Exec");
	return pid;
}

int PCB::GetNumWait()
{
	return numwait;
}

void PCB::JoinWait()
{
	joinsem->P();
}

void PCB::JoinRelease()
{
	joinsem->V();
}

void PCB::ExitWait()
{
	exitsem->P();
}
void PCB::ExitRelease()
{
	exitsem->V();
}

void PCB::IncNumWait()
{
	mutex->P();
	numwait = numwait + 1;
	mutex->V();
}

void PCB::DecNumWait()
{
	mutex->P();
	if (numwait > 0)
		numwait = numwait - 1;
	mutex->V();
}