#ifndef PCB_H
#define PCB_H
#include "thread.h"
#include "synch.h"
class PCB{
private:
	Semaphore *joinsem;//semaphore cho quá trình join
	Semaphore *exitsem;//semaphore cho quá trình exit
	Semaphore *mutex;
	int	exitcode;
	Thread	*thread;
	int	pid;
	int	numwait ;// số tiến trình đã join
public:
	int	parentID; //ID của tiến trình cha
	char 	*filename;//luu filename cua tien trinh ,phuc vu cho ham Fork
	PCB(int id);
	~PCB();
	int Exec(char *filename,int pid);// nạp chƣơng trình có tên lƣu trong biến filename và //processID sẽ là pid
	int GetID() {return pid;}
	int GetNumWait();
	void JoinWait();
	void ExitWait();
	void JoinRelease();
	void ExitRelease();
	void IncNumWait();
	void DecNumWait();
	void SetExitCode(int ec){exitcode = ec;}
	int GetExitCode(){return exitcode;}
};
#endif

