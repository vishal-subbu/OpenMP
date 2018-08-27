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
#include <stdlib.h>
#include <time.h>
#include <omp.h>

#define MINDIM 1536
#define MAXDIM 1536
#define NUM_VALIDATES 1000

void MatMul( int m, int n, int p, int b, double alpha, double beta, double *A, double *B, double *C ) ;

int main( int argc, char **argv )
{
    double *A, *B, *C, *Corg, alpha, beta, time1, time2, time3, time4 ;
    int m, n, p, b, bb, bbmin, bbmax ;
    int row, col, numt ;

    int i,j,k;
    alpha = (double) 1.3 ;
    beta  = (double) 0.0 ;

    A = (double *) malloc( sizeof(double) * MAXDIM * MAXDIM ) ;
    B = (double *) malloc( sizeof(double) * MAXDIM * MAXDIM ) ;
    C = (double *) malloc( sizeof(double) * MAXDIM * MAXDIM ) ;
    Corg = (double *) malloc( sizeof(double) * MAXDIM * MAXDIM ) ;
    if ( ( A == NULL ) || ( B == NULL ) || ( C == NULL ) || ( Corg == NULL ) )
    {
        printf( "Out of Memory\n" ) ;
        exit(1) ;
    }

    // m = n = p = 64 ;
    // b = 16 ;
    for( row = 0 ; row < MAXDIM ; row++ )
        for( col = 0 ; col < MAXDIM ; col++ )
             A[row*MAXDIM+col] = rand() ;

    for( row = 0 ; row < MAXDIM ; row++ )
        for( col = 0 ; col < MAXDIM ; col++ )
            B[row*MAXDIM+col] = rand() ;

    for( row = 0 ; row < MAXDIM ; row++ )
        for( col = 0 ; col < MAXDIM ; col++ )
            Corg[row*MAXDIM+col] = rand() ;

    printf( "m,n,p,numt,b,time,status\n" ) ;
    for( m = MINDIM ; m <= MAXDIM ; m *= 2 )
       for( n = m ; n <= MAXDIM ; n *= 2 )
          for( p = n ; p <= MAXDIM ; p *= 2 )
             for( numt = 4 ; numt <= 4 ; numt *= 2 )
             {
                if ( numt == 4 )
                {
                    bbmin = 16 ;
                    bbmax = 64 ;
                }
                else
                    bbmin = bbmax = 16 ;
                for( bb = bbmin ; bb <= bbmax ; bb *= 2 )
                {
                    for( row = 0 ; row < m ; row++ )
                        for( col = 0 ; col < p ; col++ )
                            C[row*p+col] = Corg[row*p+col] ;

                    b = bb ;
                    if ( b > m ) b = m ;
                    if ( b > n ) b = n ;
                    if ( b > p ) b = p ;
                    omp_set_num_threads( numt ) ;
                    time1 = omp_get_wtime() ;
                    MatMul( m, n, p, b, alpha, beta, A, B, C ) ;
                    time2 = omp_get_wtime();
                    //time2 = omp_get_wtime() ;

                    /* Validate random entries */
                    int success = 1, r ;
                    for(  r = 0 ; r < NUM_VALIDATES ; r++ )
                    {
                        double min, max, err, ans ;

                        row = ( rand() % m ) ;
                        col = ( rand() % p ) ;

                        int k ;
                        ans = Corg[row*p+col] * beta ;
                        for( k = 0 ; k < n ; k++ )
                            ans += alpha * A[row*n+k]*B[k*p+col] ;

                        if ( ans > C[row*p+col] )
                        {
                            min = C[row*p+col] ;
                            max = ans ;
                        }
                        else
                        {
                            min = ans ;
                            max = C[row*p+col] ;
                        }
                        err = (double) (max-min)/ (double) max ;

                        //printf(" min = %lf, error = %lf\n",min,err);
                        if ( ( max > (double) 0.000001 ) && ( err > (double) 0.000001 ) )
                            success = 0 ;
                    }

                    /*printf("Printing A\n");
                    for(i=0;i<m;i++)
                    {
                        for(j=0;j<n;j++)
                        {
                            printf("%lf ",A[i*n +j]);
                        }
                        printf("\n");
                    }
                    printf("\nPrinting B\n");
                    for(i=0;i<m;i++)
                    {
                        for(j=0;j<n;j++)
                        {
                            printf("%lf ",B[i*n +j]);
                        }
                        printf("\n");
                    }
                    printf("\nPrinting Corg\n");
                    for(i=0;i<m;i++)
                    {
                        for(j=0;j<n;j++)
                        {
                            printf("%lf ",Corg[i*n +j]);
                        }
                        printf("\n");
                    }
                    printf("\nPrinting C\n");
                    for(i=0;i<m;i++)
                    {
                        for(j=0;j<n;j++)
                        {
                            printf("%lf ",C[i*n +j]);
                        }
                        printf("\n");
                    }*/
                    if ( success == 0 )
                        printf( "%d,%d,%d,%d,%d,%g,Failed\n", m, n, p, numt,b,time2-time1 ) ;
                    else
                        printf( "%d,%d,%d,%d,%d,%g,Passed\n",  m, n, p, numt,b,time2-time1 ) ;
                }
             }

    return 0 ;
}
