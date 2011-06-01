#include "syscall.h"
#include "util.h"

int
main()
{
    SpaceId newProc;
    char prompt[10], ch[2], buffer[60];
    char temp[60];
    int i;       

    temp[0] = '.';
    temp[1] = '/';
    temp[2] = 't';
    temp[3] = 'e';
    temp[4] = 's';
    temp[5] = 't';
    temp[6] = '/';

//    prompt[0] = '\n';
    prompt[0] = '[';
    prompt[1] = '-';
    prompt[2] = '-';
    prompt[3] = ']';
    prompt[4] = '#';	   

    do//while(1)
    {
	Write("\n", 3, ConsoleOutput);
	Write(prompt, 10, ConsoleOutput);
		
	Read(buffer,10, ConsoleInput); 
	if(buffer[0] == '0')
		break;
	if(buffer[0] == '&')
	{
		XoaKyTuDau(buffer);
		GhepChuoi(temp,buffer);
		newProc = Exec(temp,2);
		if(newProc < 0)
		{
			Write("\nCan't not exec ",50,ConsoleOutput);
			memset(buffer,0,60);
			memset(temp,0,60);
		    temp[0] = '.';
		    temp[1] = '/';
		    temp[2] = 't';
		    temp[3] = 'e';
		    temp[4] = 's';
		    temp[5] = 't';
		    temp[6] = '/';
			continue;
		}
	}
	else
	{
		GhepChuoi(temp,buffer);
//		newProc = Exec("./test/cat");
		newProc = Exec(temp,2);
		if(newProc < 0)
		{
			Write("\nCan't not exec ",50,ConsoleOutput);
			memset(buffer,0,60);
			memset(temp,0,60);
		    temp[0] = '.';
		    temp[1] = '/';
		    temp[2] = 't';
		    temp[3] = 'e';
		    temp[4] = 's';
		    temp[5] = 't';
		    temp[6] = '/';

			continue;
		}
		Join(newProc);
	}
	memset(buffer,0,60);
	memset(temp,0,60);
    temp[0] = '.';
    temp[1] = '/';
    temp[2] = 't';
    temp[3] = 'e';
    temp[4] = 's';
    temp[5] = 't';
    temp[6] = '/';

  }while(1);
//	Halt();
  Exit(0);
}

