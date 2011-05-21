#include "pcb.h"
#include "system.h"

PCB::PCB(int id)
{
	joinsem = new Semaphore ("joinsem",0);
	exitsem = new Semaphore ("exitsem",0);
	mutex = new Semaphore ("mutex",1);
	thread = NULL;
	this->pid = id;
	this->parentID = currentThread->processID;
	this->numwait = 0;
	this->exitcode = 0;
	this->parentID = 0;
}

PCB::~PCB()
{
	printf("~PCB(); ID Thread = %d",currentThread->processID);
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
		thread->Finish();	
	}	
}

int PCB::Exec(char *filename,int pid)
{
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
	this->thread->Fork(NewStartProcess,pid);
	mutex->V();
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

void PCB::ExitWait()
{
	exitsem->P();
}

void PCB::JoinRelease()
{
	joinsem->V();
}

void PCB::ExitRelease()
{
	exitsem->V();
}

void PCB::IncNumWait()
{
	mutex->P();
	numwait++;
	mutex->V();
}

void PCB::DecNumWait()
{
	mutex->P();
	if (numwait > 0)
		numwait--;
	mutex->V();
}