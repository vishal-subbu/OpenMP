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

#define ARR_SIZE 1000000000

double a[ARR_SIZE];
double b[ARR_SIZE];
/* Main function */

int main(int *argc, char *argv[] )
{
    
    int i = 0,tid,numt;
    double dot =0;
    double t1,t2;
    for (i=0;i<ARR_SIZE;i++)
    {
        a[i] = i;
        b[i] = i;
    }
    
    
    t1 =omp_get_wtime();
    #pragma omp parallel for schedule(dynamic,1000) reduction(+:dot)
    for (i=0;i<ARR_SIZE;i++)
    {
        dot +=a[i]*b[i] ;
    }
    
    
    t2 = omp_get_wtime();
    printf("Dot product of the 2 arrays is : %g. It is calculated in %g s\n",dot, t2-t1);
  
     return 0;
}


