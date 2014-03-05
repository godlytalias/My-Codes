#include<iostream>
#include<fstream>
using namespace std;

float *init_state; //initial state variable
float *row_mat,*row_mat_copy;
//returns the initial state distribution vector
float* istate_dibn_vec(int i,int n)
{
init_state = new float[n];
for(int j=0;j<n;j++)
 if(j==i)
  init_state[j]=1.0;
 else
  init_state[j]=0.0;
return init_state;
}

//computes the product of matrices m1 & m2 and write the result in res matrix
template <typename T>
void matrix_prod(T *res,T *m1,int c1,T **m2,int r2,int c2)
{
int sum;
if(c1==r2){
 for(int j=0;j<c2;j++){
 sum=0;
  for(int k=0;k<c1;k++)
  sum+=(m1[k]*m2[k][j]);
 res[j]=sum;
 }
}}

void prob_prop_matrix(float **p, float **g, int n, int initstate)
{
//dynamically allocating array for probability distribution matrix
p = new float*[(2*n)-1];
for(int i=0;i<((2*n)-1);i++)
p[i]=new float[n];
//row_mat holds the value of each state distribution vector
row_mat = new float[n];
row_mat_copy = new float[n];

row_mat = istate_dibn_vec(initstate,n);
for(int i=0;i<((2*n)-1);i++)
{
//copying state distribution vector to probability propogation matrix
for(int j=0;j<n;j++){
p[i][j]=row_mat[j];
row_mat_copy[j]=row_mat[j];}
//calculating the state distribution vector for string of next length
matrix_prod(row_mat,row_mat_copy,n,g,n,n);
}
}

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
float **g1,**g2,**p1,**p2;
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

//deleting memory
for(i = 0; i < n1; i++) {
    delete [] g1[i];
}
delete [] g1;
for(i = 0; i < n2; i++) {
    delete [] g2[i];
}
delete [] g2;
for(i = 0; i < n1; i++) {
    delete [] p1[i];
}
delete [] p1;
for(i = 0; i < n2; i++) {
    delete [] p2[i];
}
delete [] p2;
delete [] init_state;
delete [] row_mat;
delete [] row_mat_copy;

return 0;
}
