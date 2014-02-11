//Basic Concept: Adjacency Matrices of Isomorphic Graphs can be made identical
//by swapping the vertices (rows & columns)

#include<iostream>
using namespace std;

//returns the sum of the specified row(3rd parameter) of the matrix
int row_sum(int matrix[100][100],int n,int row)
{
int i,sum=0;
for(i=0;i<n;i++)
sum+=matrix[row][i];
return sum;
}

//returns the sum of the specified column(3rd parameter) of the matrix
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

//calculating the row sum & col sum of 1st matrix and storing it in the nth column & nth row of the matrix-1
for(i=0;i<n1;i++)
{
a[n1][i]=row_sum(a,n1,i);
a[i][n1]=col_sum(a,n1,i);
}

//calculating the row sum & col sum of 2nd matrix and storing it in the nth column & nth row of the matrix-2
for(i=0;i<n2;i++)
{
b[n2][i]=row_sum(b,n2,i);
b[i][n2]=col_sum(b,n2,i);
}

//finding isomorphism
//checking whether the no: of vertices are same for both graphs
if(n1==n2)
{
//ADJACENCY MATRIX OF ISOMORPHIC GRAPHS CAN BE MADE IDENTICAL
//CHECKING WHETHER AJACENCY MATRIXES CAN BE MADE IDENTICAL COMPARING THE ROW-SUM & COL-SUM
	isomorphism=true;
	i=0;
	n=n1; 
	while(i<n) //n is no: of vertices of both graph
	{
		j=i;
		while((j<n)&&(a[i][n]!=b[j][n])) //comparing the row-sum of matrix-1 & matrix-2
			j++;			//j will be incremented to a row no. where row-sum of 2nd graph will
						//be same as of first
		if((j<n)&&(j!=i))  //if a row with same row-sum as of the row-sum of the first graph is found.
		{
			tempi=b[i][n];   //swapping the row-sums
			b[i][n]=b[j][n];
			b[j][n]=tempi;
			tempc=vb[i];	//swapping the vertex names accordingly
			vb[i]=vb[j];
			vb[j]=tempc;
		}
		else if(j!=i) {isomorphism=false; break;} //if there is no row having the row-sum equal to the row-sum
							  //of the 1st graph, then there is no isomorphism
		i++;		
	}
//rows are swapped so that the row-sums of both graphs are same in all rows
	if(isomorphism)  //checking the col-sums
	{
		i=0;
		while(i<n)
		{
			j=i;
			while((j<n)&&(a[n][i]!=b[n][j])) //comparing the col-sum of matrix-1 & matrix-2
				j++;	//j will be incremented to a col no. where col-sum of 2nd graph will
					//be same as of first
			if((j<n)&&(j!=i))
			{
				tempi=b[n][i];	//swapping the col-sums
				b[n][i]=b[n][j];
				b[n][j]=tempi;
				tempc=vb[i];	//swapping the vertex names accordingly
				vb[i]=vb[j];
				vb[j]=tempc;
			}
			else if(j!=i) {isomorphism=false; break;} //if there is no row having the row-sum equal to the
			i++;					 //col-sum of the 1st graph, then there is no isomorphism
		}
	}
	if(isomorphism) //isomorphism will be having true if row-sum & col-sum of 2nd graph can be swapped to have
			//same values as the row-sum and column-sum of 1st graph
	{
		cout<<"\nGRAPH-1 & GRAPH-2 ARE ISOMORPHIC\n\n\tISOMORPHISM FUNCTION:\n";
		for(i=0;i<n1;i++)
		cout<<"f("<<va[i]<<") -> "<<vb[i]<<"\n";
	}
	else
		cout<<"\nNOT ISOMORPHIC";
}
else  //if not having same no: of vertices
cout<<"\nNOT ISOMORPHIC";

return 0;
}
