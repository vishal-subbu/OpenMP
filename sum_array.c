// Copyright (c) 2018, Vishal_S
// All rights reserved. Please read the "license.txt" for license terms.
//
// Project Title: OpenMP
//
// Developer: Vishal S
//
// Contact Info: vishalsubbu97@gmail.com
//
/* Calcualte the sum of an array */

/* Include OpenMPheader file */

#include <omp.h>
#include <stdio.h>

#define ARR_SIZE 1000000000

int arr[ARR_SIZE];
/* Main function */

int main(int *argc, char *argv[] )
{
    
    int i = 0,sum = 0,tid,numt;
    
    double t1,t2;
    for (i=0;i<ARR_SIZE;i++)
    {
        arr[i] = i;
    }
    
    
    t1 =omp_get_wtime();
#pragma omp parallel default(shared) private(tid,i)
    {
        int from,to,psum=0;;
        tid = omp_get_thread_num();
        numt = omp_get_num_threads();
        from = (ARR_SIZE/numt)*tid;
        to = (ARR_SIZE/numt)*(tid+1) -1;
        
        if (tid == numt-1)
            to = ARR_SIZE -1;
        printf("Hello world from %d of %d, my range is from %d to %d\n",tid,numt,from,to);
        for (i=from;i<=to;i++)
        {
            psum +=arr[i] ;
        }
        #pragma omp critical
        sum+=psum;
    }
    t2 = omp_get_wtime();
    printf("Sum of the elemets in the array is : %d. It is calculated in %g s\n",sum, t2-t1);
  
     return 0;
}


