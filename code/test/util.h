#include "syscall.h"
#include "copyright.h"

//Dang Thanh Tung
//ghep chuoi 2 vao chuoi 1
void memset(char* str,int k,int n)
{
	int i;
	for(i = 0; i< n ; i++)
		str[i] = (char)k;
}

//ham mu
int __exp(int cs,int mu)
{
	int sum;
	int i;

	i = 0;
	sum = 1;

	if(mu == 0)
		return 1;

	for(i = 1 ; i <= mu ; ++i)
		sum = sum*cs;
	return sum;
}

//bien doi chuoi thanh so
int __atoi(char* buff)
{
	int i,k;
	int sum;

	sum = 0;
	i = 0;
	k = 0;
	
	//dem
	while (buff[i]!= '\0')
	{
		i++;
	}
	i--;

	while(i >= 0)
	{
		sum = sum + ((buff[i]-48) * __exp(10,k));
		i--;
		k++;
	}
	return sum;
}

//bien doi so thanh chuoi
void __itoa(int so,char* buff)
{
	char temp[10];
	int i,dem,mod;

	dem = 0;
	i = 0;
	mod = 0;
	memset(temp,'\0',10);
	memset(buff,'\0',10);
	do
	{
		mod = so % 10;
		temp[dem] = mod + 48;
		dem++;
		so = so /10;
	}while(so > 0);
	
	dem--;
	while(dem >= 0)
	{
		buff[i] = temp[dem];
		i++;
		dem--;
	}
	buff[i] = '\0';
}

void XoaKyTuDau(char* str)
{
	int i = 0;
	while(str[i] != '\0')
	{
		str[i] = str[i+1];
		i++;
	}
}

int GhepChuoi(char* str1,char* str2)
{
	int dem1 = 0;
	int dem2 = 0;
	//tim do dai 2 chuoi ky tu
	
	while(str1[dem1] != '\0')
		++dem1;
	while(str2[dem2] != '\0')
		++dem2;

	//kiem tra xau 1 con du cho chua xau2 ko
	
	//copy chuoi 2 vao chuoi 1
	dem2 = 0;
	while(str2[dem2] != '\0')
		str1[dem1++] = str2[dem2++];
	str1[dem1] = '\0';
}
//Dang Thanh Tung

void print(char* buf)
{
  char buffer[1024];
  int j = 0 ;
  int i;
  for( i = 0 ; i < 1023 ;)
    {
      buffer[i] = buf[j];
      j ++;
      if (buffer[i] == 0)
        break;
      else if (buffer[i] == '~'){
        buffer[i] = 0;
        break;
      }
      i ++;
      if (i == 1023){
        buffer[i] = 0;
        Write(buffer,1023,ConsoleOutput);
        i = 0;
      }
    }
  Write(buffer,i,ConsoleOutput);
  return;
}

void fprint(char* buf,int id)
{
  char buffer[1024];
  int j = 0 ;
  int i;
  for( i = 0 ; i < 1023 ;)
    {
      buffer[i] = buf[j];
      j ++;
      if (buffer[i] == 0)
        break;
      else if (buffer[i] == '~'){
        buffer[i] = 0;
        break;
      }
      i ++;
      if (i == 1023){
        buffer[i] = 0;
        Write(buffer,1023,id);
        i = 0;
      }
    }
  Write(buffer,i,id);
  return;
}
