#include<iostream>
using namespace std;
#include<mpi.h>

#define MASTER_TO_SLAVE_TAG 1 
#define SLAVE_TO_MASTER_TAG 10


int r,rank,size,i,j,k;
double mat_a[100][100]; 
double mat_b[100][100]; 
double mat_result[100][100];
double temp[100][100];
int low_bound,upper_bound,portion; 
MPI_Status status;
MPI_Request request; 
int main(int argc, char *argv[])
{
MPI_Init(&argc, &argv); 
MPI_Comm_rank(MPI_COMM_WORLD, &rank); 
MPI_Comm_size(MPI_COMM_WORLD, &size); 
/* master*/
if (rank == 0) {
cout<<"Enter the no: of rows/columns\n";
cin>>r;
for(i=0;i<r;i++)
for(j=0;j<r;j++)
mat_result[i][j]=0;
cout<<"Enter elements of matrix-1\n";
for (i = 0; i < r; i++) {
for (j = 0; j < r; j++) {
cin>>mat_a[i][j];
}
}
cout<<"Enter elements of matrix-2\n";
for (i = 0; i <r; i++) {
for (j = 0; j <r; j++) {
cin>>mat_b[i][j];
}
}
for (i = 1; i < size; i++) {
portion = (r/ (size - 1)); 
low_bound = (i - 1) * portion;
if (((i + 1) == size) && ((r % (size - 1)) != 0)) {
upper_bound = r; 
} else {
upper_bound = low_bound + portion;
}
MPI_Isend(&low_bound, 1, MPI_INT, i, MASTER_TO_SLAVE_TAG, MPI_COMM_WORLD, &request);
MPI_Isend(&upper_bound, 1, MPI_INT, i, MASTER_TO_SLAVE_TAG + 1, MPI_COMM_WORLD, &request);
MPI_Isend(&r, 1, MPI_INT, i, MASTER_TO_SLAVE_TAG + 2, MPI_COMM_WORLD, &request);
MPI_Bcast(&mat_a,100*r,MPI_DOUBLE,0,MPI_COMM_WORLD);
MPI_Bcast(&mat_b,100*r,MPI_DOUBLE,0,MPI_COMM_WORLD);
}
}
/*slaves*/
if (rank > 0) {

MPI_Recv(&low_bound, 1, MPI_INT, 0, MASTER_TO_SLAVE_TAG, MPI_COMM_WORLD, &status);
MPI_Recv(&upper_bound, 1, MPI_INT, 0, MASTER_TO_SLAVE_TAG + 1, MPI_COMM_WORLD, &status);
MPI_Recv(&r, 1, MPI_INT, 0, MASTER_TO_SLAVE_TAG + 2, MPI_COMM_WORLD, &status);

MPI_Bcast(&mat_a,100*r,MPI_DOUBLE,0,MPI_COMM_WORLD);
MPI_Bcast(&mat_b,100*r,MPI_DOUBLE,0,MPI_COMM_WORLD);
for (i = low_bound; i < upper_bound; i++) {
for (j = 0; j < r; j++) {
for (k = 0; k < r; k++) {
temp[i][j] += (mat_a[i][k] * mat_b[k][j]); }
}
}
MPI_Isend(&low_bound,1,MPI_INT,0,SLAVE_TO_MASTER_TAG+rank*3+1,MPI_COMM_WORLD,&request);
MPI_Isend(&upper_bound,1,MPI_INT,0,SLAVE_TO_MASTER_TAG+rank*3,MPI_COMM_WORLD,&request);
MPI_Isend(&temp,100*r,MPI_DOUBLE,0,SLAVE_TO_MASTER_TAG+rank*3+2,MPI_COMM_WORLD,&request);
}
/* master gathers work from slaves*/
if (rank == 0) {
for (i = 1; i < size; i++) {
MPI_Recv(&low_bound,1,MPI_INT,i,SLAVE_TO_MASTER_TAG+i*3+1,MPI_COMM_WORLD,&status);
MPI_Recv(&upper_bound,1,MPI_INT,i,SLAVE_TO_MASTER_TAG+i*3,MPI_COMM_WORLD,&status);
MPI_Recv(&temp,100*r,MPI_DOUBLE,i,SLAVE_TO_MASTER_TAG+i*3+2,MPI_COMM_WORLD,&status);

j=low_bound;

while(j<upper_bound)
{
k=0;
while(k<r){
mat_result[j][k]=temp[j][k];
k++;
}
j++;
}
}
cout<<"\nRESULT:\n";
for (i = 0; i < r; i++) {
cout<<"\n";
for (j = 0; j < r; j++)
cout<<mat_result[i][j]<<"\t";
}
cout<<"\n\n";
}
MPI_Finalize(); 
return 0;
}
