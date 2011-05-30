 #include "syscall.h"
 int
 main()
 {
	 SpaceId newProc,newProc2;
	 newProc = Exec("./test/consoleA",2);
	 if(newProc < 0)
	 {
		 Write("\nCan't not exec ",50,ConsoleOutput);
		 
	 }
	 Join(newProc);
	 newProc2 = Exec("./test/consoleB",1);
	 if(newProc < 0)
	 {
		 Write("\nCan't not exec ",50,ConsoleOutput);
		 
	 }
	 
	 Join(newProc2);
	
	 
 } 
 