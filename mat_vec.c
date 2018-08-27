// Copyright (c) 2018, Vishal_S
// All rights reserved. Please read the "license.txt" for license terms.
//
// Project Title: OpenMP
//
// Developer: Vishal S
//
// Contact Info: vishalsubbu97@gmail.com
//
/* Calcualte the dot product of two vectors*/

/* Include OpenMPheader file */

#include <omp.h>
#include <stdio.h>

#define ARR_SIZE 100000

double a[ARR_SIZE][ARR_SIZE];
double b[ARR_SIZE];
double c[ARR_SIZE];
/* Main function */

int main(int *argc, char *argv[] )
{
    
    int i = 0,j=0,tid,numt;
    double dot =0;
    double t1,t2;
    for (i=0;i<ARR_SIZE;i++)
    {
        b[i] = i;
        c[i]=0;
    }
    
    for (i=0;i<ARR_SIZE;i++)
    {
        for(j=0;j<ARR_SIZE;j++)
            a[i][j]=0;
    }
    printf("Initialisation done\n");
    t1 =omp_get_wtime();
    #pragma omp parallel
    {
    #pragma omp for schedule(dynamic,8)
        for(i=0;i<ARR_SIZE;i++)
        {
            for(j=0;j<ARR_SIZE;j++)
            {
                c[i] += a[i][j]*b[j];
            }
        }
    }
    t2 = omp_get_wtime();
    printf("Matrix Dot product of an array and a matrix is . It is calculated in %g s\n", t2-t1);
  
     return 0;
}


