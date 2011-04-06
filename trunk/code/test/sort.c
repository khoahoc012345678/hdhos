#include "syscall.h"

int A[105];
int main()
{
    int n = ReadInt ();
    if (n>100)
    {
	    PrintString("Qua Dai, EXIT!!!");
	    Exit(1);	
    }
    else
    {
    	int i, j, tmp;
	PrintString("Moi nhap cac phan tu:\n");
    	for (i = 0; i < n; i++)	
	{	
     	   	A[i] = ReadInt();
	}
    	for (i = 0; i < n - 2; i++)
	{
       		for (j = n-1; j >i; j--)
		{
		   	if (A[j] < A[j - 1]) 
			{
	      			tmp = A[j];
	      			A[j] = A[j - 1];
	      			A[j - 1] = tmp;
    	   		}
		}
	}
	
    	for (i = 0; i < n; i++)		
     	   	PrintInt(A[i]);
   }
     Exit(1);	
}
