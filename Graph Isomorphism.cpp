#include<iostream>
using namespace std;

int row_sum(int matrix[100][100],int n,int row)
{
int i,sum=0;
for(i=0;i<n;i++)
sum+=matrix[row][i];
return sum;
}

int col_sum(int matrix[100][100],int n,int col)
{
int i,sum=0;
for(i=0;i<n;i++)
sum+=matrix[i][col];
return sum;
}

int main()
{
int n1,n2,a[100][100],b[100][100],i,j,tempi,n;
int va[100],vb[100],tempc;
bool isomorphism;
cout<<"Enter the no: of vertices in Graph-1\n";
cin>>n1;
cout<<"\nEnter the vertices of Graph-1\n";
for(i=0;i<n1;i++)
{
cout<<"\nVertex-"<<i<<" - ";
cin>>va[i];
}
cout<<"\nEnter the adjacency matrix of Graph-1\n";
for(i=0;i<n1;i++)
for(j=0;j<n1;j++)
cin>>a[i][j];

cout<<"Enter the no: of vertices in Graph-2\n";
cin>>n2;
cout<<"\nEnter the vertices of Graph-2\n";
for(i=0;i<n2;i++)
{
cout<<"\nVertex-"<<i<<" - ";
cin>>vb[i];
}
cout<<"\nEnter the adjacency matrix of Graph-2\n";
for(i=0;i<n2;i++)
for(j=0;j<n2;j++)
cin>>b[i][j];

for(i=0;i<n1;i++)
{
a[n1][i]=row_sum(a,n1,i);
a[i][n1]=col_sum(a,n1,i);
}

for(i=0;i<n2;i++)
{
b[n2][i]=row_sum(b,n2,i);
b[i][n2]=col_sum(b,n2,i);
}

//finding isomorphism
if(n1==n2)
{
//ADJACENCY MATRIX OF ISOMORPHIC GRAPHS CAN BE MADE IDENTICAL
//CHECKING WHETHER AJACENCY MATRIXS CAN BE MADE IDENTICAL USING THE ROW-SUM & COL-SUM
	isomorphism=true;
	i=0;
	n=n1;
	while(i<n)
	{
		j=i;
		while((j<n)&&(a[i][n]!=b[j][n]))
			j++;
		if((j<n)&&(j!=i))
		{
			tempi=b[i][n];
			b[i][n]=b[j][n];
			b[j][n]=tempi;
			tempc=vb[i];
			vb[i]=vb[j];
			vb[j]=tempc;
		}
		else if(j!=i) {isomorphism=false; break;}
		i++;
	}
	if(isomorphism)
	{
		i=0;
		while(i<n)
		{
			j=i;
			while((j<n)&&(a[n][i]!=b[n][j]))
				j++;
			if((j<n)&&(j!=i))
			{
				tempi=b[n][i];
				b[n][i]=b[n][j];
				b[n][j]=tempi;
				tempc=vb[i];
				vb[i]=vb[j];
				vb[j]=tempc;
			}
			else if(j!=i) {isomorphism=false; break;}
			i++;
		}
	}
	if(isomorphism)
	{
		cout<<"\nGRAPH-1 & GRAPH-2 ARE ISOMORPHIC\n\n\tISOMORPHISM FUNCTION:\n";
		for(i=0;i<n1;i++)
		cout<<"f("<<va[i]<<") -> "<<vb[i]<<"\n";
	}
	else
		cout<<"\nNOT ISOMORPHIC";
}
else
cout<<"\nNOT ISOMORPHIC";

return 0;
}
