#include<iostream>
#include<fstream>
using namespace std;

int n1=0,n2=0;

struct mapping
{
int map_ver;
};

mapping **map_g;

//check whether the two matrices m1 & m2 are equal
bool eq_matrix(float **m1,float **m2)
{
if(n1!=n2)
 return false;
for(int i=0;i<n1;i++)
 for(int j=0;j<n1;j++)
  {
   if(m1[i][map_g[0][j].map_ver]!=m2[i][map_g[1][j].map_ver])
    return false;
  } 
return true;
}

//merge the partitions made by the mergesort
void merge(float **a,int s1,int e1,int s2,int e2,int mat)
{
int i,j,l,temp;
 if(s1<e2 && (e1+1)==s2)
 {
  i=s1;
  j=s2;
  while(i<=e1 && j<=e2)
  {
   l=0;
   while((a[l][map_g[mat][i].map_ver]==a[l][map_g[mat][j].map_ver]) && l<(n1-1))
   l++;
   if(a[l][map_g[mat][i].map_ver]<a[l][map_g[mat][j].map_ver])
   i++;
   else if(a[l][map_g[mat][i].map_ver]>=a[l][map_g[mat][j].map_ver])
    {
     temp = map_g[mat][j].map_ver;
     for(int k=j;k>i;k--)
     map_g[mat][k].map_ver=map_g[mat][k-1].map_ver;
     map_g[mat][i].map_ver=temp;
     j++;
    }
  }
 }
}

//mergesort the matrix a and write the mapping to g_map[mat]
void mergesort(float **a,int start, int end,int mat)
{
if(start<(end-1))
 {
 mergesort(a,start,(start+end)/2,mat);
 mergesort(a,((start+end)/2)+1,end,mat);
 merge(a,start,(start+end)/2,((start+end)/2)+1,end,mat);
 }
else
 merge(a,start,start,end,end,mat);
}

bool isotest(float **p1,float **p2,float **a1,float **a2)
{
mergesort(p1,0,n1-1,0);
mergesort(p2,0,n2-1,1);
return eq_matrix(p1,p2);
}

float *row_mat,*row_mat_copy;
//returns the initial state distribution vector
void istate_dibn_vec(float* init_state, int i,int n)
{
for(int j=0;j<n;j++)
 if(j==i)
  init_state[j]=1.0;
 else
  init_state[j]=0.0;
}

//computes the product of matrices m1 & m2 and write the result in res matrix
template <typename T>
void matrix_prod(T *res,T *m1,int c1,T **m2,int r2,int c2)
{
float sum;
if(c1==r2){
 for(int j=0;j<c2;j++){
 sum=0;
  for(int k=0;k<c1;k++)
  sum+=(m1[k]*m2[k][j]);
 res[j]=sum;
 }
}}

//calculates the probability propogation matrix for the initial state initstate
float** prob_prop_matrix(float **p, float **g, int n, int initstate)
{
//dynamically allocating array for probability distribution matrix
p = new float*[(2*n)-1];
for(int i=0;i<((2*n)-1);i++)
p[i]=new float[n];
//row_mat holds the value of each state distribution vector
row_mat = new float[n];
row_mat_copy = new float[n];
//writes the initial state vector to the row_mat
istate_dibn_vec(row_mat,initstate,n);

for(int i=0;i<((2*n)-1);i++)
{
//copying state distribution vector to probability propogation matrix
for(int j=0;j<n;j++){
p[i][j]=row_mat[j];
row_mat_copy[j]=row_mat[j];}
//calculating the state distribution vector for string of next length
matrix_prod(row_mat,row_mat_copy,n,g,n,n);
}

delete [] row_mat;
delete [] row_mat_copy;
return p;
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
int i,j,deg=0,pi,pj;
float **g1,**g2,**p1=NULL,**p2=NULL,**b1,**b2;
char ch;
bool iso=false;
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
map_g = new mapping*[2];
map_g[0]=new mapping[n1];

g1 = new float*[n1];
b1 = new float*[n1];
for(i=0;i<n1;i++){
g1[i]=new float[n1];
b1[i]=new float[n1];
map_g[0][i].map_ver=i;
}

fseek(read1,0,SEEK_SET);
for(i=0;i<n1;i++)
for(j=0;j<n1;j++){
fscanf(read1,"%f",&g1[i][j]);
b1[i][j]=g1[i][j];
}

fclose(read1);
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
map_g[1]=new mapping[n2];

g2 = new float*[n2];
b2 = new float*[n2];

for(i=0;i<n2;i++){
g2[i]=new float[n2];
b2[i]=new float[n2];
map_g[1][i].map_ver = i;
}

fseek(read2,0,SEEK_SET);
for(i=0;i<n2;i++)
for(j=0;j<n2;j++){
fscanf(read2,"%f",&g2[i][j]);
b2[i][j]=g2[i][j];
}

fclose(read2);
//computing probability distribution matrices of both graphs
prob_dibn(b1,n1);
prob_dibn(b2,n2);

if(n1==n2) //if number of vertices of both graphs are not equal then not isomorphic
{
 pi=1;
 iso=false;
 while(pi<n1 && iso==false)
 {
  p1=prob_prop_matrix(p1,b1,n1,pi);
  pj=1;
  while(pj<n2 && iso==false)
  {
   p2=prob_prop_matrix(p2,b2,n2,pj);
   iso = isotest(p1,p2,g1,g2);
   pj++;
   //deleting the memory for the probability propogation matrix
   for(i = 0; i < (2*n2)-1; i++) {
    delete [] p2[i];
   }
   delete [] p2;
  }
  pi++;
  //deleting the memory for probability propogation matrix
  for(i = 0; i < (2*n1)-1; i++) {
    delete [] p1[i];
  }
  delete [] p1;
 }
}
else
 iso=false;



//deleting memory allocated for arrays
for(i = 0; i < n1; i++) {
    delete [] g1[i];
}
delete [] g1;
for(i = 0; i < n2; i++) {
    delete [] g2[i];
}
delete [] g2;
for(i = 0; i < n1; i++) {
    delete [] b1[i];
}
delete [] b1;
for(i = 0; i < n2; i++) {
    delete [] b2[i];
}
delete [] b2;
for(i=0;i<=1;i++)  {
    delete [] map_g[i];
}
delete [] map_g;

return 0;
}
