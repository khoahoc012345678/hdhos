 #include "syscall.h"
 #include "copyright.h"
 int main()
 {
	 int pid1 ,pid2,pid3;
	 pid1 = Exec ("./test/help",1);
	 Join(pid1);
	 //pid2 = Exec ("./test/help",1);
	 //Join(pid2);
	 //pid3 = Exec ("./test/help",1);
	 //Join(pid3);
	 Exit(-1);
 }