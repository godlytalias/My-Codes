#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <cuda.h>

__global__ void mul_matrix_on_gpu( float* a, float *b, float *c, int N )
{
	float sum=0;
	int x = blockIdx.x*blockDim.x+threadIdx.x;
	int y = blockDim.y*blockIdx.y+threadIdx.y;
	for(int i=0;i<N;i++){
	if(x<N && y<N){
	int indexa = x*N+i;
	int indexb = i*N+y;
	sum+=a[indexa]*b[indexb];}
	}
	c[x*N+y]=sum;
}

int main() 
{
	int N;
	printf("\nEnter the no: of rows/columns in the matrix : ");
scanf("%d",&N);
	float *a = new float[N*N];
	float *b = new float[N*N];
	float *c = new float[N*N];

	printf("\nEnter the 1st matrix\n");
	for ( int i = 0; i < N*N; ++i ) {
		scanf("%f",&a[i]); }

	printf("\nEnter the 2nd matrix\n");
	for ( int i = 0; i < N*N; ++i ) {
		scanf("%f",&b[i]); }

	float *ad, *bd, *cd;
	const int size = N*N*sizeof(float);

	cudaMalloc( (void**)&ad, size );
	cudaMalloc( (void**)&bd, size );
	cudaMalloc( (void**)&cd, size );


	cudaMemcpy( ad, a, size, cudaMemcpyHostToDevice );
	cudaMemcpy( bd, b, size, cudaMemcpyHostToDevice );

	int blocksize;
	if(N>2)
	for(blocksize=1;N%blocksize!=0;++blocksize);
	else blocksize=1;
	printf("\nBlock Size = %d\n",blocksize);

	dim3 dimBlock( blocksize, blocksize );
	dim3 dimGrid( N/dimBlock.x, N/dimBlock.y );

	mul_matrix_on_gpu<<<dimGrid, dimBlock>>>( ad, bd, cd, N );
        
	cudaMemcpy( c, cd, size, cudaMemcpyDeviceToHost );
	
for(int i=0;i<N;i++){
for(int j=0;j<N;j++)
printf(" %f ",a[i*N + j]);
printf("\n");}

printf("\n + \n");

for(int i=0;i<N;i++){
for(int j=0;j<N;j++)
printf(" %f ",b[i*N + j]);
printf("\n");}
	
printf("\nPRODUCT \n");

for(int i=0;i<N;i++){
for(int j=0;j<N;j++)
printf(" %f ",c[i*N + j]);
printf("\n");}

        cudaFree( ad ); cudaFree( bd ); cudaFree( cd );
	delete[] a; delete[] b; delete[] c;
	getch();
	return EXIT_SUCCESS;
}
