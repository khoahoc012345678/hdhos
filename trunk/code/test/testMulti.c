 #include "syscall.h"
 #include "copyright.h"
 int main()
 {
	 int pid = Exec ("./test/help",1);
	 Join(pid);
 }