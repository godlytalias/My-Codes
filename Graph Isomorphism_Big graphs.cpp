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

int n1,n2;

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

struct mapping
{
int map_ver;
int state; //0-fixed 1-neutral 2-not fixed
};

mapping **map_g;
float **g1,**g2;
int node,w_node;
int tmp_count;

//merge the partitions made by the mergesort
void merge(float *g,int s1,int e1,int s2,int e2,int graph_id)
{
FILE *read;
int i,j,m,temp;
float a,b;
 if(s1<e2 && (e1+1)==s2)
 {
  i=s1;
  j=s2;
  while(i<=e1 && j<=e2)
  {
   m=0;
   a=g[map_g[graph_id][i].map_ver];
   b=g[map_g[graph_id][j].map_ver];
     if(a==b)
           {
           map_g[graph_id][i].state=2;
           map_g[graph_id][j].state=2;
           }
   
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

//mergesort the matrix a and write the mapping to map_g[mat]
void mergesort(float *g,int start, int end,int graph_id)
{
if(start<(end-1))
 {
 mergesort(g,start,(start+end)/2,graph_id);
 mergesort(g,((start+end)/2)+1,end,graph_id);
 merge(g,start,(start+end)/2,((start+end)/2)+1,end,graph_id);
 }
else
 merge(g,start,start,end,end,graph_id);
 
}

bool adj_mat_map(float **a1, float **a2)
{
for(int i=0;i<node;i++)
 for(int j=0;j<node;j++)
  if(a1[map_g[0][i].map_ver][map_g[0][j].map_ver]!=a2[map_g[1][i].map_ver][map_g[1][j].map_ver])
   return false;
return true;
}


int isotest(int p1_init_node,int p2_init_node,float **a1,float **a2)
{
    char filename[40];
    sprintf(filename,"../graphiso/map_0_%d",p1_init_node);
FILE *read = fopen(filename,"r");
for(int i=0;i<node;i++)
 fscanf(read,"%d",&map_g[0][i].map_ver);
fclose(read);

sprintf(filename,"../graphiso/map_1_%d",p2_init_node);
read = fopen(filename,"r");
for(int i=0;i<node;i++)
 fscanf(read,"%d",&map_g[1][i].map_ver);
fclose(read);

//if(eq_matrix(p1_init_node,p2_init_node))
// {
  if(adj_mat_map(a1,a2))
   return 2;
//  else
//   return 1;
// }
else
 return 0;
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
void matrix_prod(float *res,float *m1,int c1,float **m2,int r2,int c2)
{
float y,t,c;
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
void prob_prop_matrix(int graph_id, float **g, int n, int initstate)
{
char file_name[40];
bool flag=true;
int start,end,j;
sprintf(file_name,"../graphiso/map_%d_%d",graph_id,initstate);
FILE *write = fopen(file_name,"w");
//row_mat holds the value of each state distribution vector
row_mat = new float[n];
row_mat_copy = new float[n];
//writes the initial state vector to the row_mat
istate_dibn_vec(row_mat,initstate,n);

for(int i=0;flag && i<((2*n)-1);i++)
{
        start=0;
        end=1;
        j=0;
        while(j<n)
        {
        while(map_g[graph_id][start].state==0){ start++; j++; }
        while(map_g[graph_id][end].state!=0 && end<n) {end++; j++;}
        mergesort(row_mat,start,end-1,graph_id);
        start=end+1;
        end=start;
        }
        
flag=false;
//writing state distribution vector to probability propogation matrix
for(int j=0;j<n;j++){
 row_mat_copy[j]=row_mat[j];
 if(map_g[graph_id][j].state==1)
  map_g[graph_id][j].state=0;
 if(map_g[graph_id][j].state!=0)
  flag=true;
 }
//calculating the state distribution vector for string of next length
matrix_prod(row_mat,row_mat_copy,n,g,n,n);
}

delete [] row_mat;
delete [] row_mat_copy;
for(int i=0;i<n;i++)
fprintf(write,"%d ",map_g[graph_id][i].map_ver);
fclose(write);
}

//returns the degree of a vertix
int degree(float **m,int row,int n)
{
int deg=0;
for(int i=0;i<n;i++)
deg+=(int)m[row][i];
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

void get_graphs()
{
     int mode=0;
     char ch=' ';
     FILE *f = fopen("g1.txt","r");
      n1=0;n2=0;
         //checking the no: of nodes in the graph 1
		 while(ch!='\n')
         {
         ch = fgetc(f);
          if(ch>=48 && ch<=57 && mode==0)
           {
             mode=1;
               n1++;
            }
             else if(ch<48 || ch>57)
              mode=0;
          }
          
          //initializing graph 1 and inputing values
         g1 = new float*[n1];
         for(int i=0;i<n1;i++)
         g1[i]=new float[n1];
         fseek(f,0,SEEK_SET);
         for(int i=0;i<n1;i++)
         for(int j=0;j<n1;j++)
         fscanf(f,"%f",&g1[i][j]);
         
         fclose(f);
         
         ch=' ';
mode=0;
f = fopen("g2.txt","r");
//reading the adjacent matrix of Graph 2
//first checking the no: of elements in a row
while(ch!='\n')
{
ch = fgetc(f);
 if(ch>=48 && ch<=57 && mode==0)
 {
  mode=1;
  n2++;
 }
 else if(ch==' ')
  mode=0;
}
         g2 = new float*[n2];
         for(int i=0;i<n2;i++)
         g2[i]=new float[n2];
         fseek(f,0,SEEK_SET);
         for(int i=0;i<n2;i++)
         for(int j=0;j<n2;j++)
         fscanf(f,"%f",&g2[i][j]);
         
         fclose(f); 
         
         //computing probability distribution matrices of both graphs
prob_dibn(g1,n1); //g1 is converted to the probability distribution matrix of graph 1
prob_dibn(g2,n2); //g2 is converted to the probability distribution matrix of graph 2          
     }

int main()
{
int i,j,mode,deg=0,pi,pj,iso=0;
char ch,filename[40];
ch=' ';
get_graphs();

map_g = new mapping*[2];
for(int i=0;i<2;i++)
map_g[i]=new mapping[n1];



FILE *read1,*read2;

if(n1==n2) //if number of vertices of both graphs are not equal then not isomorphic
{
           node=n1;
 //dynamically allocating array for probability distribution matrix
 for(pi=0;(pi<n1)&&(iso!=2);pi++)
 {
        for(int i=0;i<n1;i++)
{
        map_g[0][i].map_ver=i;
        map_g[0][i].state=1;
        }
  sprintf(filename,"../graphiso/map_%d_%d",0,pi);  
  read1=fopen(filename,"r");
  if(!read1)
   prob_prop_matrix(0,g1,n1,pi);
   else
  fclose(read1);
  for(pj=0;(pj<n2)&&(iso!=2);pj++)
  {
   for(int i=0;i<n1;i++)
        {
        map_g[1][i].map_ver=i;
        map_g[1][i].state=1;
        }
   sprintf(filename,"../graphiso/map_%d_%d",1,pj);
   read2=fopen(filename,"r");
   if(!read2)
    prob_prop_matrix(1,g2,n2,pj);
    else
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