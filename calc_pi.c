// Copyright (c) 2018, Vishal_S
// All rights reserved. Please read the "license.txt" for license terms.
//
// Project Title: OpenMP
//
// Developer: Vishal S
//
// Contact Info: vishalsubbu97@gmail.com
//
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<omp.h>

#define num_steps 5000000

void main ()
{
    double step;
    int i,max;  
    double pi = 0.0;
    double x,pi_sum =0.0;;
    step = 1.0/(double) num_steps;
    
    //max = omp_get_max_threads();
    
#pragma omp parallel num_threads(4) reduction(+:pi) shared(x)
    {
        
        #pragma omp for
        for (i=0;i< num_steps; i++)
        {
            x   = (i+0.5)*step;
            pi += 4.0/(1.0+x*x);
        }
    }
    pi = pi*step;
    
    printf("The value of pi = %le\n",pi);
}
