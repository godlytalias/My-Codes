#include<iostream>
using namespace std;
#include<stdio.h>
#include<string.h>

int arr[100][100];
int len;

int ret_v(int i, int j)
{
int count =0;
int p=i;
while(arr[i][j]==1 && i<len && j<len && i!=(len-j-1))
{

count++;
i++;
j++;
}
if(count>1)
while(arr[i][j]==1 && i<len && j<len && i>=p)
{
count++;
i--;
j++;
}

if(i==(p-1))
return count;
else
return 1;
}


int main()
{
int length=0,temp,pos;
char string[100];
cout<<"Input the string : ";
gets(string);
len=strlen(string);
for(int i=0;i<len;i++)
for(int j=0;j<len;j++)
if(string[j]==string[len-i-1])
arr[i][j]=1;
else
arr[i][j]=0;

for(int i=0;i<len;i++)
for(int j=0;j<len;j++)
{
 temp=ret_v(i,j);
 if(temp>length)
 {
	length=temp;
	pos=j;
 }
}

cout<<"\nLength of Longest Paliendrome = "<<length<<"\n";
cout<<"Paliendrome : ";
for(int i=pos;i<pos+length;i++)
cout<<string[i];
cout<<"\n";
return 0;
}
