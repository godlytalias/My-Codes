// Copyright (c) 2014 Godly T.Alias
//
// This is a free software; you can redistribute it and/or modify it
// under the terms of the GNU Lesser General Public License
// as published by the Free Software Foundation,
// either version 3 of the License, or (at your option) any later version.

#include<iostream>
#include<conio.h>
#include<fstream>
#include<cuda.h>
#include<cuda_runtime.h>
using namespace std;

int n1=0,n2=0;

struct mapping
{
int map_ver;
};

mapping *map_g;
float *gpu_g1,*gpu_g2,*gpu_p1;

//merge the partitions made by the mergesort
void merge(float *a,int s1,int e1,int s2,int e2,int mat)
{
int i,j,l,temp;
 if(s1<e2 && (e1+1)==s2)
 {
  i=s1;
  j=s2;
  while(i<=e1 && j<=e2)
  {
   l=0;
   while((a[l*n1+(map_g[mat*n1+i].map_ver)]==a[l*n1+(map_g[mat*n1+j].map_ver)]) && l<(n1-1))
   l++;
   if(a[l*n1+(map_g[mat*n1+i].map_ver)]<a[l*n1+(map_g[mat*n1+j].map_ver)])
   i++;
   else if(a[l*n1+(map_g[mat*n1+i].map_ver)]>=a[l*n1+(map_g[mat*n1+j].map_ver)])
    {
     temp = map_g[mat*n1+j].map_ver;
     for(int k=j;k>i;k--)
     map_g[mat*n1+k].map_ver=map_g[mat*n1+(k-1)].map_ver;
     map_g[mat*n1+i].map_ver=temp;
     j++;
     i++; e1++;
    }
  }
 }
}

//mergesort the matrix a and write the mapping to g_map[mat]
void mergesort(float *a,int start, int end,int mat)
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

//check whether the two matrices m1 & m2 are equal
__global__ void eq_matrix(float *m1,float *m2,mapping *gpu_map, bool *equal,int n)
{
//n1==n2
    int i=blockIdx.x*blockDim.x+threadIdx.x;
	int j=blockIdx.y*blockDim.y+threadIdx.y;

if(i<(2*n-1) && j<n) {
   if(m1[i*n+gpu_map[j].map_ver]!=m2[i*n+gpu_map[n+j].map_ver])
	   *equal=false;}
}


__global__ void adj_mat_map(float *a1, float *a2,mapping *gpu_map,bool *equal,int n)
{
//n1==n2
	int i=blockIdx.x*blockDim.x+threadIdx.x;
	int j=blockIdx.y*blockDim.y+threadIdx.y;
if(i<n && j<n) {	
  if(a1[(gpu_map[i].map_ver*n)+gpu_map[j].map_ver]!=a2[(gpu_map[n+i].map_ver*n)+gpu_map[n+j].map_ver])
	  *equal=false;}
}

int isotest(float *p1,float *p2,float *a1,float *a2)
{
mergesort(p1,0,n1-1,0);
mergesort(p2,0,n2-1,1);
float *gpu_p2;
bool *gpu_equal,equal;
equal = true;
int sizeb = sizeof(bool);
int sizem = 2*n1*sizeof(mapping);
mapping *map;
int size = (2*n1-1)*n1*sizeof(float);

//allocating memory for gpu variables
cudaMalloc((void**)&gpu_p2,size);
cudaMalloc((void**)&map,sizem);
cudaMalloc((void**)&gpu_equal,sizeb);
//copying to gpu variables
cudaMemcpy(gpu_p2,p2,size,cudaMemcpyHostToDevice);
cudaMemcpy(gpu_equal,&equal,sizeb,cudaMemcpyHostToDevice);
cudaMemcpy(map,map_g,sizem,cudaMemcpyHostToDevice);

eq_matrix<<<dim3(n1/2 , (2*n1-1)/2), dim3(2,2)>>>(gpu_p1,gpu_p2,map,gpu_equal,n1);

cudaMemcpy(&equal,gpu_equal,sizeb,cudaMemcpyDeviceToHost);
cudaFree(gpu_p2);
if(equal)
 {
	 equal=true;
	 //copying to gpu variables
	 cudaMemcpy(gpu_equal,&equal,sizeb,cudaMemcpyHostToDevice);

	 adj_mat_map<<<dim3(n1/2,n1/2),dim3(2,2)>>>(gpu_g1,gpu_g2,map,gpu_equal,n1);

	 cudaMemcpy(&equal,gpu_equal,sizeb,cudaMemcpyDeviceToHost);
	 cudaFree(gpu_equal); cudaFree(map);
  if(equal)
   return 2;
  else
   return 1;
 }
else
 return 0;
}

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
__global__ void matrix_prod(float *res,float *m1,int c1,float *m2,int r2,int c2)
{
float y,t,c;
int j=blockIdx.x*blockDim.x+threadIdx.x;
if(c1==r2 && j<c2){
 res[j]=0;
 c=0.0;
  for(int k=0;k<c1;k++){
//kahan summation to avoid precision lose
  y=(m1[k]*m2[k*c2+j])-c;
  t=res[j]+y;
  c = (t-res[j])-y;
  res[j]=t;}
}}

//calculates the probability propogation matrix for the initial state initstate
float* prob_prop_matrix(float *p, float *gpu, int n, int initstate)
{
float *row_mat,*gpu_rowmat,*row_mat_copy;
//dynamically allocating array for probability distribution matrix
p = new float[n*((2*n)-1)];
//row_mat holds the value of each state distribution vector
row_mat = new float[n];
//writes the initial state vector to the row_mat
istate_dibn_vec(row_mat,initstate,n);
int size = n*sizeof(float);
dim3 blocksize(2,1);
dim3 gridsize((n/blocksize.x)+((n/blocksize.x)%n),1);
cudaMalloc((void**)&gpu_rowmat,size);
cudaMalloc((void**)&row_mat_copy,size);

for(int i=0;i<((2*n)-1);i++)
{
//copying state distribution vector to probability propogation matrix
 for(int j=0;j<n;j++)
  p[i*n +j]=row_mat[j];

 cudaMemcpy(row_mat_copy,row_mat,size,cudaMemcpyHostToDevice);
//calculating the state distribution vector for string of next length
 matrix_prod<<<gridsize,blocksize>>>(gpu_rowmat,row_mat_copy,n1,gpu,n1,n1); //n1==n2
 cudaMemcpy(row_mat,gpu_rowmat,size,cudaMemcpyDeviceToHost);
}

//deleting the allocated memory
cudaFree(gpu_rowmat);
cudaFree(row_mat_copy);
delete [] row_mat;
return p;
}

//returns the degree of a vertix
__device__ int degree(float *m,int row,int n)
{
int deg=0;
for(int i=0;i<n;i++)
deg+=m[row*n+i];
return deg;
}

//computing the probability distribution matrices
__global__ void prob_dibn(float *m,int n)
{
int deg;
int y=blockIdx.y*blockDim.y+threadIdx.y;
if(y<n){
 deg = degree(m,y,n);
for(int i=0;i<n;i++)
	m[y*n+i]/=deg;}
}

int main()
{
int i,j,mode,pi,pj,iso=0,psize,gsize;
float *p1=NULL,*p2=NULL,*g1,*g2;
char ch;
ch=' ';
mode=0;

FILE *read1 = fopen("g1.txt","r");
//reading the adjacent matrix of Graph 1
//first checking the no: of elements in a row
while(ch!='\n')
{
ch = fgetc(read1);
 if(ch>=48 && ch<=57 && mode==0)
 {
  mode=1;
  n1++;
 }
 else if(ch<48 || ch>57)
  mode=0;
}

//dynamically allocating array
map_g = new mapping[2*n1];

g1 = new float[n1*n1];
for(i=0;i<n1;i++){
map_g[i].map_ver=i;
map_g[n1+i].map_ver=i;
}

fseek(read1,0,SEEK_SET);
for(i=0;i<n1;i++)
for(j=0;j<n1;j++){
fscanf(read1,"%f",&g1[i*n1+j]);
}

fclose(read1);
ch=' ';
mode=0;
FILE *read2 = fopen("g2.txt","r");
//reading the adjacent matrix of Graph 2
//first checking the no: of elements in a row
while(ch!='\n')
{
ch = fgetc(read2);
 if(ch>=48 && ch<=57 && mode==0)
 {
  mode=1;
  n2++;
 }
 else if(ch==' ')
  mode=0;
}

//dynamically allocating array
g2 = new float[n2*n2];

fseek(read2,0,SEEK_SET);
for(i=0;i<n2;i++)
for(j=0;j<n2;j++){
fscanf(read2,"%f",&g2[i*n2 +j]);
}

fclose(read2);

if(n1==n2) //if number of vertices of both graphs are not equal then not isomorphic
{
 dim3 dimBlock(1,1);
 dim3 dimGrid(1,n1);
 gsize = n1*n1*sizeof(float);
//computing probability distribution matrices of both graphs
 cudaMalloc((void**)&gpu_g1,gsize);
 cudaMemcpy(gpu_g1,g1,gsize,cudaMemcpyHostToDevice);
 prob_dibn<<<dimGrid,dimBlock>>>(gpu_g1,n1); //g1 is converted to the probability distribution matrix of graph 1
 cudaMemcpy(g1,gpu_g1,gsize,cudaMemcpyDeviceToHost);
 
 
 cudaMalloc((void**)&gpu_g2,gsize);
 cudaMemcpy(gpu_g2,g2,gsize,cudaMemcpyHostToDevice);
 prob_dibn<<<dimGrid,dimBlock>>>(gpu_g2,n2); //g2 is converted to the probability distribution matrix of graph 2
 cudaMemcpy(g2,gpu_g2,gsize,cudaMemcpyDeviceToHost);


 iso=0;
  psize = (2*n1-1)*n1*sizeof(float);
 for(pi=0;(pi<n1)&&(iso!=2);pi++)
 {
  p1=prob_prop_matrix(p1,gpu_g1,n1,pi);  
  cudaMalloc((void**)&gpu_p1,psize);
  cudaMemcpy(gpu_p1,p1,psize,cudaMemcpyHostToDevice);
  
  for(pj=0;(pj<n2)&&(iso!=2);pj++)
  {
   p2=prob_prop_matrix(p2,gpu_g2,n2,pj);
   iso = isotest(p1,p2,g1,g2);
   //deleting the memory for the probability propogation matrix
       delete [] p2;
  }
  //deleting the memory for probability propogation matrix
  delete [] p1;
  cudaFree(gpu_p1);
 }
}
else
 iso=0;

if(iso==2)
{
cout<<"ISOMORPHIC MAPPING :\n";
for(i=0;i<n1;i++)
cout<<map_g[i].map_ver<<"->"<<map_g[n1+i].map_ver<<"\n";
}
else
cout<<"NOT ISOMORPHIC\n";
//deleting memory allocated for arrays
    delete [] g1;
	delete [] g2;
	delete [] map_g;
	cudaFree(gpu_g1);
    cudaFree(gpu_g2);
getch();
return 0;
}
