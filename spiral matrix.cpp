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



//This is program for spiral matrix. Spiral Matrix is a matrix with
//the middle element as 0 and will be incremented by 1 as it goes out spirally
//eg: n=8
//           4 3 2
//           5 0 1
//           6 7 8


#include<iostream>
#include<cstdlib>
#include<iomanip>
using namespace std;
int n;
 
//returns the direction in which the next element to be filled up in the matrix
int direction(int i, int j, int key)
{
if((abs((n/2)-i)==key) && (abs((n/2)-j)==key))
{
 if(i<(n/2) && j>(n/2))
        return 1;//left
 else if(i<(n/2) && j<(n/2))
        return 2;//down
 else if(i>(n/2) && j<(n/2))
        return 3;//right
 else return -1;
                     }
 else if((abs((n/2)-i)==key) && (abs((n/2)-j)>key) && i>(n/2) && j>(n/2))
      return 0;//up
 
 else return -1;
}
 
int main(){
    int i,j,count=1,temp;
    cout<<"Enter n (<50): ";
    cin>>n;
     
int sp[50][50],key,dir;
 
for(i=0;i<n;i++)
for(j=0;j<n;j++)
sp[i][j]=0;
key=1;
i=n/2;
j=(n/2)+1;
temp=0;
 
while(true)
{
//giving values in the array
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
 
   if(key>n || i<0 || j<0)
   break;
//getting the direction
   temp = direction(i,j,key);
   if((j-(n/2))>key)
   key++;
   count++;
}
 
//outputing
for(i=0;i<n;i++){
for(j=0;j<n;j++)
cout<<std::setw(4)<<sp[i][j];
cout<<"\n";}

return 0;
}
