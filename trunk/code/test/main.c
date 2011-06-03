/*
/ Day la chuong trinh chinh chay voi priority = 7;
*/
#include "syscall.h"

void main()
{
	int i = 0;
	int P = 200;
	int pidlow, pidhigher, pidhighest, pidmid;
	//Tao lock	
	int test = CreateLock("main");
	if(test == -1)
		Exit(0);
	Acquire("main");
	pidlow = Exec("./test/lower",6);//Chay lower thread voi priority = 6
	//Tao mot khoang thoi gian de lower co the chay duoc den ham can thiet
	while(i<P)
		i++;	
	pidmid = Exec("./test/middle",4);
	pidhigher = Exec("./test/higher",2);
	//Tao mot khoang thoi gian doi highest
	i = 0;	
	while(i<P)
		i++;	
	pidhighest = Exec("./test/highest",1);
	Release("main");
	Join(pidlow);
	Join(pidmid);
	Join(pidhigher);
	Join(pidhighest);
	Exit(0);
}