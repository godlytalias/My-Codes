#include<iostream>
#include<math.h>
#include<unistd.h>
#include <sys/ioctl.h>
struct winsize w;
using namespace std;

int main()
{
float j;
int d=1;
ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
//getting diameter from user and checking whether it is a multiple of 10
while(d%10!=0){
cout<<"Enter the diameter (multiple of 10)  :  ";
cin>>d;
//checking whether the terminal of user is big enough to draw the figure
if(w.ws_col<(d*2))
{
cout<<"FIGURE WITH ENTERED DIAMETER CAN'T BE DRAWN IN YOUR TERMINAL\n\a";
d=1;
}
}
//incrementing virtual y co-ordinate
for(float i=0;i<=d;i++)
{
j=0;
//incrementing virtual x co-ordinate
while(j<=d)
{
//checking whether the point can be a part of the circle of given diameter
if(pow(((d/2)-i),2)+pow(((d/2)-j),2)==(pow(d,2)/4))
cout<<"*";
//checking for the position of eyes
else if(i==((d/2)-(d/8)) && (j==((d/2)+(d/4)) || j==((d/2)-(d/4))))
cout<<"O";
//checking for the position of mouth
else if(i==((d/2)+(d/6)) && j<((d/2)+(d/4)) && j>=((d/2)-(d/4)))
cout<<"__";
//leave blank if none of the conditions is true
else
cout<<"  ";
j++;
}
cout<<"\n";
}

return 0;
}
