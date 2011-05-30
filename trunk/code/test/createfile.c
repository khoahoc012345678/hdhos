  #include "syscall.h"
  void
  main ()
  {
	  char fileCreate[32];
	  Write("Nhap vao ten file :\n",30,ConsoleOutput);
	  Read(fileCreate,32,ConsoleInput);
	  Create(fileCreate);
}