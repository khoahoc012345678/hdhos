/*
/ Day la chuong trinh chinh chay voi priority = 7;
*/
#include "syscall.h"

void main()
{
	int i = 0;
	int P = 200;
	int pidlow, pidhigh, pidmid;
	//Tao lock	
	test = CreateLock("main");
	if(test == -1)
		Exit(0);
	Acquire("main");
	pidlow = Exec("./test/lower",6);//Chay lower thread voi priority = 6
	//Tao mot khoang thoi gian de lower co the chay duoc den ham can thiet
	while(i<P)
		i++;	
	pidmid = Exec("./test/middle",3);
	pidhigh = Exec("./test/higher",1);
	Release("main");
	Join(pidlow);
	Join(pidmid);
	Join(pidhigh);
	Exit(0);
}