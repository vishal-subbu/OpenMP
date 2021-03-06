// Copyright (c) 2018, Vishal_S
// All rights reserved. Please read the "license.txt" for license terms.
//
// Project Title: OpenMP
//
// Developer: Vishal S
//
// Contact Info: vishalsubbu97@gmail.com
//
/* Print hello world from multiplle threads */

/* Include OpenMPheader file */

#include <omp.h>
#include <stdio.h>


/* Main function */

int main(int *argc, char *argv[] )
{
    int numt;
     /*Specify the block to be executed in parallel */
#pragma omp parallel
    {
        /*Get the number of threads*/
        numt = omp_get_num_threads();
        /* Get thread id */
        int tid = omp_get_thread_num();
        if(tid ==0)
            numt = omp_get_num_threads();
        
       #pragma omp barrier
        printf("Hello world from %d of %d\n",tid,numt);
    }
    return 0;
}

