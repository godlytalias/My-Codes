#include<iostream>
#include<fstream>
using namespace std;

//returns the degree of a vertix
int degree(float **m,int row,int n)
{
int deg=0;
for(int i=0;i<n;i++)
deg+=m[row][i];
return deg;
}

//computing the probability distribution matrices
void prob_dibn(float **m,int n)
{
int deg;
for(int i=0;i<n;i++){
 deg = degree(m,i,n);
 for(int j=0;j<n;j++)
 {
 m[i][j]/=deg;
 }
}
}

int main()
{
int i,j,n1=0,n2=0,deg=0;
float **g1,**g2;
char ch;
ch=' ';
FILE *read1 = fopen("g1","r");
//reading the adjacent matrix of Graph 1
//first checking the no: of elements in a row
while(ch!='\n')
{
ch = fgetc(read1);
if(ch==' ')
n1++;
}
n1++;

//dynamically allocating array
g1 = new float*[n1];
for(i=0;i<n1;i++)
g1[i]=new float[n1];

fseek(read1,0,SEEK_SET);
for(i=0;i<n1;i++)
for(j=0;j<n1;j++)
fscanf(read1,"%f",&g1[i][j]);

ch=' ';

FILE *read2 = fopen("g2","r");
//reading the adjacent matrix of Graph 2
//first checking the no: of elements in a row
while(ch!='\n')
{
ch = fgetc(read2);
if(ch==' ')
n2++;
}
n2++;

//dynamically allocating array
g2 = new float*[n2];
for(i=0;i<n2;i++)
g2[i]=new float[n2];

fseek(read2,0,SEEK_SET);
for(i=0;i<n2;i++)
for(j=0;j<n2;j++)
fscanf(read2,"%f",&g2[i][j]);

//computing probability distribution matrices of both graphs
prob_dibn(g1,n1);
prob_dibn(g2,n2);

fclose(read1);
fclose(read2);

//deleting memory for graph 1 & graph 2
for(i = 0; i < n1; i++) {
    delete [] g1[i];
}
delete [] g1;
for(i = 0; i < n2; i++) {
    delete [] g2[i];
}
delete [] g2;

return 0;
}
