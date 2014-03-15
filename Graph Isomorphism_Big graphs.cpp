// Copyright (c) 2014 Godly T.Alias
//
// This is a free software; you can redistribute it and/or modify it
// under the terms of the GNU Lesser General Public License
// as published by the Free Software Foundation,
// either version 3 of the License, or (at your option) any later version.

#include<iostream>
#include<conio.h>
#include<fstream>
using namespace std;

int n1=0,n2=0;

struct mapping
{
int map_ver;
};

mapping **map_g;

//check whether the two matrices m1 & m2 are equal
bool eq_matrix(int p1,int p2)
{/*
//n1==n2
for(int i=0;i<((2*n1)-1);i++)
 for(int j=0;j<n1;j++)
  {
   if(m1[i][map_g[0][j].map_ver]!=m2[i][map_g[1][j].map_ver]){
    return false;}
  } */
return true;
}

//merge the partitions made by the mergesort
void merge(int init_node,int s1,int e1,int s2,int e2,int graph_id)
{
FILE *read;
int i,j,l,m,temp;
double temp_num,a,b;
char filename[40];
sprintf(filename,"files/prob_prop_%d_%d",graph_id,init_node);
 if(s1<e2 && (e1+1)==s2)
 {
  i=s1;
  j=s2;
  
  while(i<=e1 && j<=e2)
  {
   read = fopen(filename,"r");
   l=0; a=b=0.0; temp_num=2.0;
   while(a==b && l<2*(n1-1))
   {
    m=0;
    while(m<n1)
    {
     fscanf(read,"%f",&temp_num);   
    if(m==map_g[graph_id][i].map_ver)
     a=temp_num;
    if(m==map_g[graph_id][j].map_ver)
     b=temp_num; 
      m++;
    }
      l++;                           
   }   
  fclose(read);
   if(a<b)
   i++;
   else if(a>=b)
    {
     temp = map_g[graph_id][j].map_ver;
     for(int k=j;k>i;k--)
     map_g[graph_id][k].map_ver=map_g[graph_id][k-1].map_ver;
     map_g[graph_id][i].map_ver=temp;
     j++;
     i++; e1++;
    }
  }
 }
}

//mergesort the matrix a and write the mapping to g_map[mat]
void mergesort(int init_node,int start, int end,int graph_id)
{
if(start<(end-1))
 {
 mergesort(init_node,start,(start+end)/2,graph_id);
 mergesort(init_node,((start+end)/2)+1,end,graph_id);
 merge(init_node,start,(start+end)/2,((start+end)/2)+1,end,graph_id);
 }
else
 merge(init_node,start,start,end,end,graph_id);
}

bool adj_mat_map(double **a1, double **a2)
{
//n1==n2
for(int i=0;i<n1;i++)
 for(int j=0;j<n1;j++)
  if(a1[map_g[0][i].map_ver][map_g[0][j].map_ver]!=a2[map_g[1][i].map_ver][map_g[1][j].map_ver])
   return false;
return true;
}

int isotest(int p1_init_node,int p2_init_node,double **a1,double **a2)
{
mergesort(p1_init_node,0,n1-1,0);
mergesort(p2_init_node,0,n2-1,1);
if(eq_matrix(p1_init_node,p2_init_node))
 {
  if(adj_mat_map(a1,a2))
   return 2;
  else
   return 1;
 }
else
 return 0;
}

double *row_mat,*row_mat_copy;
//returns the initial state distribution vector
void istate_dibn_vec(double* init_state, int i,int n)
{
for(int j=0;j<n;j++)
 if(j==i)
  init_state[j]=1.0;
 else
  init_state[j]=0.0;
}

//computes the product of matrices m1 & m2 and write the result in res matrix
void matrix_prod(double *res,double *m1,int c1,double **m2,int r2,int c2)
{
double y,t,c;
if(c1==r2){
 for(int j=0;j<c2;j++){
 res[j]=0;
 c=0.0;
  for(int k=0;k<c1;k++){
//kahan summation to avoid precision lose
  y=(m1[k]*m2[k][j])-c;
  t=res[j]+y;
  c = (t-res[j])-y;
  res[j]=t;}
 }
}}

//calculates the probability propogation matrix for the initial state initstate
void prob_prop_matrix(int graph_id, double **g, int n, int initstate)
{
char file_name[40];
sprintf(file_name,"files/prob_prop_%d_%d",graph_id,initstate);
FILE *read = fopen(file_name,"w");
//row_mat holds the value of each state distribution vector
row_mat = new double[n];
row_mat_copy = new double[n];
//writes the initial state vector to the row_mat
istate_dibn_vec(row_mat,initstate,n);

for(int i=0;i<((2*n)-1);i++)
{
//writing state distribution vector to probability propogation matrix
for(int j=0;j<n;j++){
fprintf(read,"%.16lf ",row_mat[j]);
row_mat_copy[j]=row_mat[j];}
fprintf(read,"\n");
//calculating the state distribution vector for string of next length
matrix_prod(row_mat,row_mat_copy,n,g,n,n);
}

delete [] row_mat;
delete [] row_mat_copy;
fclose(read);
}

//returns the degree of a vertix
int degree(double **m,int row,int n)
{
int deg=0;
for(int i=0;i<n;i++)
deg+=(int)m[row][i];
return deg;
}

//computing the probability distribution matrices
void prob_dibn(double **m,int n)
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
int i,j,mode,deg=0,pi,pj,iso=0;
double **g1,**g2,**p1=NULL,**p2=NULL;
char ch,filename[40];
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
map_g = new mapping*[2];
map_g[0]=new mapping[n1];

g1 = new double*[n1];
for(i=0;i<n1;i++){
g1[i]=new double[n1];
map_g[0][i].map_ver=i;
}

fseek(read1,0,SEEK_SET);
for(i=0;i<n1;i++)
for(j=0;j<n1;j++){
fscanf(read1,"%lf",&g1[i][j]);
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
map_g[1]=new mapping[n2];

g2 = new double*[n2];

for(i=0;i<n2;i++){
g2[i]=new double[n2];
map_g[1][i].map_ver = i;
}

fseek(read2,0,SEEK_SET);
for(i=0;i<n2;i++)
for(j=0;j<n2;j++){
fscanf(read2,"%lf",&g2[i][j]);
}

fclose(read2);
//computing probability distribution matrices of both graphs
prob_dibn(g1,n1); //g1 is converted to the probability distribution matrix of graph 1
prob_dibn(g2,n2); //g2 is converted to the probability distribution matrix of graph 2

if(n1==n2) //if number of vertices of both graphs are not equal then not isomorphic
{
 //dynamically allocating array for probability distribution matrix
 for(pi=0;(pi<n1)&&(iso!=2);pi++)
 {
  sprintf(filename,"files/prob_prop_%d_%d",0,pi);  
  read1=fopen(filename,"r");
  if(!read1)
   prob_prop_matrix(0,g1,n1,pi);
  fclose(read1);
  for(pj=0;(pj<n2)&&(iso!=2);pj++)
  {
   sprintf(filename,"files/prob_prop_%d_%d",1,pj);
   read2=fopen(filename,"r");
   if(!read2)
    prob_prop_matrix(1,g2,n2,pj);
   fclose(read2);
   iso = isotest(pi,pj,g1,g2);
  }
 }
}
else
 iso=0;


if(iso==2)
{
cout<<"ISOMORPHIC MAPPING\n";
for(i=0;i<n1;i++)
cout<<map_g[0][i].map_ver<<"->"<<map_g[1][i].map_ver<<"\n";
}
else
cout<<"NOT ISOMORPHIC\n";

//deleting memory allocated for arrays
for(i = 0; i < n1; i++) {
    delete [] g1[i];
}
delete [] g1;
for(i = 0; i < n2; i++) {
    delete [] g2[i];
}
delete [] g2;
for(i=0;i<=1;i++)  {
    delete [] map_g[i];
}
delete [] map_g;
getch();
return 0;
}
