  #include "syscall.h"
  void
  main ()
  {
	 char fileCreate[32];
	 Write("Nhap vao ten file :\n",32,ConsoleOutput);
	 Read(fileCreate,32,ConsoleInput);
	 Create(fileCreate);
}