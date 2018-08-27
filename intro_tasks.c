// Copyright (c) 2018, Vishal_S
// All rights reserved. Please read the "license.txt" for license terms.
//
// Project Title: OpenMP
//
// Developer: Vishal S
//
// Contact Info: vishalsubbu97@gmail.com
//
/* Program explainig the usage of taks*/

/* Include OpenMPheader file */

#include <omp.h>
#include <stdio.h>

#define ARR_SIZE 600
#define step_size 100
double a[ARR_SIZE];
/* Main function */

int main(int *argc, char *argv[] )
{
    
    int i = 0;
    double sum,t1,t2;
    for (i=0;i<ARR_SIZE;i++)
    {
        a[i] = i;
    }
    
    
    t1 =omp_get_wtime();
    #pragma omp parallel
    {
        #pragma omp for
         for (i=0;i<ARR_SIZE;i+=step_size)
            {
                int j,start=i,end = i+step_size -1;
                printf("Computing Sum(%d,%d) from %d of %d\n",start,end,omp_get_thread_num(),omp_get_num_threads());
             #pragma omp task
                {
                    int psum = 0;
                    printf("Task computing Sum(%d,%d) from %d of %d\n",start,end,omp_get_thread_num(),omp_get_num_threads());
                    for(j=start;j<=end;j++)
                        psum += a[j];
             #pragma  omp critical
                    sum += psum;
                }
            }
    }
    t2 = omp_get_wtime();
    printf("Sum of the elements in the array is : %g. It is calculated in %g s\n",sum, t2-t1);
    
    return 0;
}
