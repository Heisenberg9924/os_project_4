#include<stdio.h>
#include"myheader.h"
#include<time.h>
#include<unistd.h>
#include<sys/types.h>
#include<pthread.h>
#include<stdlib.h>

int **A, **B;
int n, det;
float *sol;
int num_threads;

void fillrandom(int**mat,int r,int c)
{	 
	FILE *fp = fopen("equation2.txt","a");
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

	fclose(fp);
}

void modify(int** dest,int** src,int col,int n)
{
	for(int i=0;i<n;i++)
		dest[i][0]=src[i][col];
}

void modifyA(int** dest,int** src,int col,int n)
{
	for(int i=0;i<n;i++)
		dest[i][col]=src[i][0];
}

void* solve(void* arg)
{
	int tid = *((int*)arg);

	int start = tid * (n / num_threads);
	int end = (tid == num_threads-1) ? n : start + (n / num_threads);

	for(int i=start;i<end;i++)
	{
		int **temp = alloc2DArr(n,1);
		int **tempA = alloc2DArr(n,n);

		for(int k=0;k<n;k++)
		{
			for(int j=0;j<n;j++)
			{
				tempA[k][j] = A[k][j];
			}
		}
		
		modify(temp,tempA,i,n);
		modifyA(tempA,B,i,n);

		int vardet = matrixDet(tempA,n);

		modifyA(tempA,temp,i,n);

		float ans = (float)vardet / det;

		if(n<10) printf("%f   ",ans);

		sol[i] = ans;
	}

	pthread_exit(NULL);
}

int main()
{
	srand(time(NULL));

	FILE *ftime=fopen("time_case2.txt","w");

	int arr[5]={200,400,600,800,1000};

	num_threads = sysconf(_SC_NPROCESSORS_ONLN);

	for(int m=0;m<4;m++)
	{
		struct timespec start,end;

		clock_gettime(CLOCK_MONOTONIC,&start);

		n = arr[m];

		A = alloc2DArr(n,n);
		B = alloc2DArr(n,1);
		sol = (float*)malloc(n*sizeof(float));

		fillrandom(A,n,n);
		fillrandom(B,n,1);

		det = matrixDet(A,n);

		if(det==0)
		{
			printf("no unique solution\n");
			exit(0);
		}

		pthread_t tid[num_threads];
		int index[num_threads];

		for(int i=0;i<num_threads;i++)
		{
			index[i]=i;
			pthread_create(&tid[i],NULL,solve,&index[i]);
		}

		for(int i=0;i<num_threads;i++)
			pthread_join(tid[i],NULL);

		FILE *fp=fopen("solution2.txt","a");

		for(int i=0;i<n;i++)
			fprintf(fp,"%f  ",sol[i]);

		fprintf(fp,"\n");

		fclose(fp);

		clock_gettime(CLOCK_MONOTONIC,&end);

		double timetaken=(end.tv_sec-start.tv_sec)+(end.tv_nsec-start.tv_nsec)/1e9;

		fprintf(ftime,"%d %f\n",arr[m],timetaken);
	}

	fclose(ftime);

	return 0;
}
