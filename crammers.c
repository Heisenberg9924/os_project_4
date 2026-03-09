#include<stdio.h>
#include"myheader.h"
#include<time.h>
#include<unistd.h>
#include<sys/types.h>
#include<pthread.h>
#include<stdlib.h>


int**A,**B;
int n,det;
float *sol;

void fillrandom(int**mat,int r,int c)
{	 
	FILE *fp = fopen("equation.txt","a");
	if(fp==NULL)
	{
		printf("error in opening");
		exit(0);
	}
	fprintf(fp,"\n");
	for(int i=0;i<r;i++)
	{
		for(int j=0;j<c;j++)
		{
			mat[i][j]=random()%10;
			fprintf(fp,"%d  ",mat[i][j]);
		}
		fprintf(fp,"\n");
	}
	fflush(fp);
	fclose(fp);
	
}


void modify(int** dest,int** src,int col,int n)
{
	for(int i=0;i<n;i++)
	{
		dest[i][0]=src[i][col];
	}
}

void modifyA(int** dest,int** src,int col,int n)
{
	for(int i=0;i<n;i++)
	{
		dest[i][col]=src[i][0];
	}
}

void* solve(void*arg)
{
	int i=*((int*)arg);
	int **temp=alloc2DArr(n,1);
	int** tempA=alloc2DArr(n,n);
	for(int k=0;k<n;k++)
	{
		for(int j=0;j<n;j++)
		{
			tempA[k][j]=A[k][j];
		}
	}
	modify(temp,tempA,i,n);
	modifyA(tempA,B,i,n);
	int vardet=matrixDet(tempA,n);
	modifyA(tempA,temp,i,n);
	float ans=(float)vardet/det;
	if(n<10)printf("%f   ",ans);
	sol[i]=ans;		
	pthread_exit(0);	
	
}



int main()
{
	srand(time(NULL));
	FILE *ftime=fopen("time_case1.txt","w");
	int arr[5]={2,4,6,8,10};
	
	for(int m=0;m<5;m++){
	struct timespec start,end;
	clock_gettime(CLOCK_MONOTONIC,&start);
	n=arr[m];
	A=alloc2DArr(n,n);
	B=alloc2DArr(n,1);
	sol=(float*)malloc(n*sizeof(float));
	fillrandom(A,n,n);
	fillrandom(B,n,1);
	//read2DArr(A,n,n);
	//disp2DArr(A,n,n);
	//read2DArr(B,n,1);
	//disp2DArr(B,n,1);
	
	
	
	det=matrixDet(A,n);
	if(det==0)
	{
		printf("no unique solution\n");
		exit(0);
	}
	
	pthread_t tid[n];
	int index[n];

	for(int i=0;i<n;i++)
	{
		index[i]=i;
		pthread_create(&tid[i],NULL,solve,&index[i]);
	}
	
	for(int i=0;i<n;i++)
	pthread_join(tid[i],NULL);
	
	FILE *fp=fopen("solution.txt","a");
	for(int i=0;i<n;i++)
	{
		fprintf(fp,"%f  ",sol[i]);
	}
	fprintf(fp,"\n");
	fflush(fp);
	fclose(fp);
	clock_gettime(CLOCK_MONOTONIC,&end);
	double timetaken=(end.tv_sec-start.tv_sec)+(end.tv_nsec-start.tv_nsec)/1e9;
    	//printf("Time taken = %f seconds\n", timetaken);
    	fprintf(ftime,"%d %f",arr[m],timetaken);
	}
	return 0;
	
}

