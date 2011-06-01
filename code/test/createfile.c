  #include "syscall.h"
  void
  main ()
  {
	 char fileCreate[32];
	  //Write("Nhap vao ten file :\n",32,ConsoleOutput);
	 int num = Read(fileCreate,32,ConsoleInput);
		Write ("aaaaaaa",32,ConsoleOutput);
	 Create(fileCreate);
}