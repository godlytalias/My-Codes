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

int n1,n2,s,e;

struct mapping
{
int map_ver;
float state;
int classid; };

mapping **map_g;
float **g1,**g2;
int node,w_node;
int tmp_count;


//merge the partitions made by the mergesort
void merge(float *g,int s1,int e1,int s2,int e2,int graph_id)
{
FILE *read;
int i,j,temp;
float a,b;
 if(s1<e2 && (e1+1)==s2)
 {
  i=s1;
  j=s2;
  while(i<=e1 && j<=e2)
  {
   a=g[map_g[graph_id][i].map_ver];
   b=g[map_g[graph_id][j].map_ver];
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
    FILE *read1 = fopen(filename,"r");
    sprintf(filename,"../graphiso/map_1_%d",p2_init_node);
    FILE *read2 = fopen(filename,"r");
while(!feof(read1)){
for(int i=0;i<node;i++)
 fscanf(read1,"%d",&map_g[0][i].map_ver);

while(!feof(read2)){
for(int j=0;j<node;j++)
 fscanf(read2,"%d",&map_g[1][j].map_ver);

  if(adj_mat_map(a1,a2))
 { fclose(read1);
   fclose(read2);
   return 2; } }
      
 fseek(read2,0,SEEK_SET);
    }
fclose(read1);
fclose(read2);
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

//swaps the given parameters
void swap(mapping *a,mapping *b)
{
 mapping temp;
 temp=*a;
 *a=*b;
 *b=temp;     
}

//output all the possible mappings when 2 column vectors of 
//probability propogation matrix becomes equal
void permute(int start,int end,FILE *file,int graph_id,bool flag)
{
 int t_start=0,t_end=0;
 if(start==end && flag)
 {
 for(int i=0;i<node;i++)
  fprintf(file,"%d ",map_g[graph_id][i].map_ver);
 fprintf(file,"\n");
 }
 else
 {
 for(int i=0;i<=(end-start);i++)
  {
   swap(&map_g[graph_id][start],&map_g[graph_id][start+i]);
   if(start==s || (i>0 && end<=e))
   {
   for(int j=end+1;j<(node-1);j++)
    if(map_g[graph_id][j].classid==map_g[graph_id][j+1].classid)
     { t_start=j; break; }
   if(t_start>0)
   for(int j=t_start+1;j<node-1;j++)
    if(map_g[graph_id][j].classid!=map_g[graph_id][j+1].classid)
     { t_end = j; break; }
   if(t_start!=t_end){
     permute(t_start,t_end,file,graph_id,true);
     flag=false;}}
   permute(start+1,end,file,graph_id,flag);
   flag=true;
   swap(&map_g[graph_id][start+i],&map_g[graph_id][start]);
   }
 }
}

//calculates the probability propogation matrix for the initial state initstate
void prob_prop_matrix(int graph_id, float **g, int n, int initstate)
{
char file_name[40];
bool flag=true;
int j,temp,classptr;
float temps;
sprintf(file_name,"../graphiso/map_%d_%d",graph_id,initstate);
FILE *write = fopen(file_name,"w");
//row_mat holds the value of each state distribution vector
row_mat = new float[n];
row_mat_copy = new float[n];
//writes the initial state vector to the row_mat
istate_dibn_vec(row_mat,initstate,n);
classptr=1;
for(int i=0;flag && i<((2*n)-1);i++)
{
        j=1;
        //this loop gives different class id to vertices with same class id but different state
        while(j<n && map_g[graph_id][j].classid==map_g[graph_id][j-1].classid)
        {
        if(map_g[graph_id][j].state!=map_g[graph_id][j-1].state)
          {
            temp=map_g[graph_id][j].classid;
          while(j<n && map_g[graph_id][j].classid==temp){
            temps=map_g[graph_id][j].state;
             while(j<n && map_g[graph_id][j].state==temps && map_g[graph_id][j].classid==temp){
              map_g[graph_id][j].classid=classptr;
              j++;
              }
              classptr++;
              }  
             }  
         else j++;  
                  }
                  
        s=0;
        j=0;
        flag=false;
        while(j<n)
        {
        e=s+1;
        j++;
        while(j<n && map_g[graph_id][e].classid==map_g[graph_id][s].classid)
        {
          j++; e++;               
         }
        if(s<e-1){
        mergesort(row_mat,s,e-1,graph_id);
        flag=true;}
        s=e;
        }
       
//writing state distribution vector to probability propogation matrix
for(j=0;j<n;j++){
 row_mat_copy[j]=row_mat[j];
 map_g[graph_id][j].state=row_mat[map_g[graph_id][j].map_ver];
 }
 
//calculating the state distribution vector for string of next length
matrix_prod(row_mat,row_mat_copy,n,g,n,n);
}

for(int i=0;i<node;i++)
printf("%d ",map_g[graph_id][i].classid);
printf("\n");

delete [] row_mat;
delete [] row_mat_copy;
s=0;
while(s<n-1){
 if(map_g[graph_id][s].classid==map_g[graph_id][s+1].classid)
  break;
 s++; }
e=s+1;
while(e<n-1){
 if(map_g[graph_id][e].classid!=map_g[graph_id][e+1].classid)
  break;
 e++; }
permute(s,e,write,graph_id,true);
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
        map_g[0][i].state=-1.0;
        map_g[0][i].classid=0;
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
        map_g[1][i].state=-1.0;
        map_g[1][i].classid=0;
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
