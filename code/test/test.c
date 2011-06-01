 #include "syscall.h"
 int
 main()
 {
	 int newProc,newProc2;
	 newProc = Exec("./test/consoleA",2);
	 if(newProc < 0)
	 {
		 Write("\nCan't not exec ",50,ConsoleOutput);
		 
	 }
	Join(newProc);
	 newProc2 = Exec("./test/createfile",2);
	 if(newProc < 0)
	 {
		 Write("\nCan't not exec ",50,ConsoleOutput);
		 
	 }	 
	Join(newProc2);
	newProc2 = Exec("./test/consoleB",2);
	if(newProc < 0)
	{
		Write("\nCan't not exec ",50,ConsoleOutput);
		
	}	 
	
	Exit(0);
	
	 
 } 
 