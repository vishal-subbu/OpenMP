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
     /*Specify the block to be executed in parallel */
#pragma omp parallel
    {
        /* print hello world from each thread */
        printf("Hello World \n");
    }
    return 0;
}

