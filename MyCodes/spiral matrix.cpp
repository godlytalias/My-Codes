/*PROGRAM TO PRINT A SPIRAL ARRAY*/

/*

Copyright (c) 2013 GODLY T.ALIAS

   This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
    
 */



#include<iostream>
#include<cstdlib>
#include<iomanip>
using namespace std;
int n;

int direction(int i, int j, int key)
{
if((abs((n/2)-i)==key) && (abs((n/2)-j)==key))
{
 if(i<(n/2) && j>(n/2))
        return 1;
 else if(i<(n/2) && j<(n/2))
        return 2;
 else if(i>(n/2) && j<(n/2))
        return 3;
 else return -1;
                     }
 else if((abs((n/2)-i)==key) && (abs((n/2)-j)>key) && i>(n/2) && j>(n/2))
      return 0;
      
 else return -1;
}

int main(){
    int i,j,count=1,temp;
    cout<<"Enter n : ";
    cin>>n;
    
int sp[20][20],key,dir;

for(i=0;i<n;i++)
for(j=0;j<n;j++)
sp[i][j]=0;
key=1;
i=n/2;
j=(n/2)+1;
temp=0;

while(true)
{
   sp[i][j]=count;        
 if(temp!=-1)
   dir=temp;
      switch(dir){
      case 0://up
           i--;
           break;
      case 1://left
           j--;
           break;
      case 2://down
           i++;
           break;
      case 3://right
           j++;
           break;
      default:
              break;
              }

   if(key>n)
   break;
   temp = direction(i,j,key);
   if((j-(n/2))>key)
   key++;
   count++;
}


for(i=0;i<n;i++){
for(j=0;j<n;j++)
cout<<std::setw(4)<<sp[i][j];
cout<<"\n";}

cin>>n;
return 0;
}
