// Copyright (c) 2018, Vishal_S
// All rights reserved. Please read the "license.txt" for license terms.
//
// Project Title: OpenMP
//
// Developer: Vishal S
//
// Contact Info: vishalsubbu97@gmail.com
//
#include <stdio.h>
#include <omp.h>

int main()
{
    long i;
    #pragma omp parallel
    {
        printf("Printing 1st statement from : %d\n",omp_get_thread_num());
        for(i=0;i<10000;i++);
        printf("Printing 2nd statement from : %d\n",omp_get_thread_num());
    }
}
