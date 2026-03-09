#include <stdio.h>
#include <stdlib.h>
#include<math.h>
// list of user defined functions

//int **alloc2DArr(int,int);
//void read2DArr(int **,int,int);
//void disp2DArr(int **,int,int);

//int **add2DArr(int **,int **,int,int);
//int **mult2DArr(int **,int,int,int **,int,int);

//int  **minor(int  **,int,int);
//int matrixDet(int **,int);
//void fillRandom(int **mat, int n);

//--------------------------------------------------------
int **alloc2DArr(int r,int c)
{
    int **p,i; // will hold the base addr of the (int *) array of size r

    //printf("\n Dyn allocating space for a 2D array of size %d rows & %d cols",r,c);
    p=(int**)malloc(sizeof(int*)*r);  // Step A

    // allocating space for each individual rows of size each 'c' elements
    for(i=0;i<r;i++)
    {
        p[i]=(int*)malloc(sizeof(int)*c);  // Step B: dy alloc space for i-th row and assign its base addr to p[i]
    }

   return p;
}
//////////////////////////////////////////////////
void read2DArr(int **p,int r,int c)  // 1st arg callByaddr, 2nd & 3rd arg callByvalue 
{    
     int i,j;
     
     for(i=0;i<r;i++)
     {  // reading all elements for ith row

         for(j=0;j<c;j++)
         {    // reading the ith row jth col element of the array 
              printf("\n Enter the [%d][%d]th value: ",i,j);
              scanf("%d",&p[i][j]); //  &p[i][j] eq (*(p+i)+j)
         }
     }
     return;
}  
/////////////////////////////////////////////////////////////
int **add2DArr(int **b1,int **b2,int r,int c)
{
    int **s,i,j;

    s=alloc2DArr(3,2);

    // adding matrices
    printf("\n Matrix addition: ");
    for(i=0;i<r;i++)
        for(j=0;j<c;j++)
        {
            s[i][j]=b1[i][j]+b2[i][j];
        }
    return s;
}
/////////////////////////////////////////////////////

void disp2DArr(int **p,int r,int c)  // 1st arg callByaddr, 2nd & 3rd arg callByvalue 
{
   int i,j;

   //printf("\n Displaying the 2D array:::::\n");
   for(i=0;i<r;i++)
     {  // displaying all elements for ith row

         for(j=0;j<c;j++)
         {    // displaying the ith row jth col element of the array 
              //printf("\n Enter the [%d][%d]th value: %d",i,j,p[i][j]);
              printf(" %d  ",p[i][j]); // p[i][j] eq *(*(p+i)+j)
         }
         printf("\n");
     }

}
//////////////////////////////////////////////////////////


void mult2DArr(int **A, int **B, int n, int start, int rows)
{
    for(int i = start; i < start + rows; i++)
    {
        for(int j = 0; j < n; j++)
        {
            int sum = 0;
            for(int k = 0; k < n; k++)
                sum += A[i][k] * B[k][j];
        }
    }
}

////////////////////////////////////////////////////////
//////////////////////////////////////////////////////
// function to extract the minor of m[0][index]
int  **minor(int  **m, int index, int s)  
{
    int **c = alloc2DArr((s-1),(s-1)); //space allocation for minor matrix

    int  ci=0,cj=0;  //  indices for the minor matrix c
    int  i,j;      // indices for orginal martix m

    // copying suitable elements from m to c excluding 0th row & (index) cloumn
    for(i=1;i<s;i++) // consider from row 1
    {
        cj=0;
        for(j=0;j<s;j++)
        {
            if(j!=index) // exclude index col
                {
                    c[ci][cj]=m[i][j];
                    cj++;
                }
        }
        ci++;
    }
    //printf("\n Minor");
    //disp2DArr(c,(s-1),(s-1));

    return c;

}
////////////////////////////////////////////////////
int matrixDet(int **m, int n)
{
    if(n==1)
        return m[0][0];
    else if(n==2)
        return((m[0][0]*m[1][1])-(m[0][1]*m[1][0]));
    else
    {
        int res=0, i=0;  // Let's always consider row 0

        for(int j=0;j<n;j++)
        {
            int **minorMat=minor(m,j,n);  // function to extract the minor of m[0][j] of mat dim n x n

            int cofactor= pow(-1,(0+j)) * matrixDet(minorMat,(n-1)); // calc cofactor of minor
            res += ( m[0][j] * cofactor);

            //printf("\n [0][%d]  %d cofactor= %d partialSum= %d ",j,m[i][j],cofactor,res);
            //deallocMatrix(minorMat,n-1,n-1);  
        }
        return res;
    }
}
////////////////////////////////////////////////////////////



void fillRandom(int **mat, int n)
{
	for(int i=0; i<n; i++) 
	{
		for(int j=0; j<n;j++)
		{
			mat[i][j]=random()%10;
		}
	}
}
