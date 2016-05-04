#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/time.h>
#include "get_fun.h"
#include "decls.h"
#include "util.h"

int T1t1,T1t2,T1t3,T2t1,T2t2,T2t3;

void init(int c)
{
   T1t1=32;T1t2=32;T1t3=32;
   T2t1=c;T2t2=c;T2t3=c;
}

void trisolv_ref(long N)
{
    long i,j,k;


    for (i=0;i<=N-1;i++) {
        for (j=0;j<=N-1;j++) {
            for (k=0;k<=j-1;k++) {
                B1[j][i]=B1[j][i]-L1[j][k]*B1[k][i];  //S1 ;

            }
            B1[j][i]=B1[j][i]/L1[j][j]; // S2 ;
        } // for j
    } // for i

}

void trisolv(long N) 
{
    long i,j,k;
#pragma zyl
#pragma scop
    for (i=0;i<=N-1;i++) {
        for (j=0;j<=N-1;j++) {
            for (k=0;k<=j-1;k++) {
                B[j][i]=B[j][i]-L[j][k]*B[k][i];  //S1 ;

            }
            B[j][i]=B[j][i]/L[j][j]; // S2 ;
        } // for j
    } // for i
#pragma endscop
#pragma endzyl
}


int main()
{
    long N=NMAX;
    int i,j;
    double t_start, t_end;
//    trisolv_ref(N);
    IF_TIME(t_start = rtclock());
    trisolv(N);
    IF_TIME(t_end = rtclock());
    IF_TIME(fprintf(stderr, "%0.6lfs\n", t_end - t_start));
    
    float diff;
  int diff_flag = 0;
  for(i=0;i<N;i++)
          for(j=0;j<N;j++) {
                  diff = fabs(B1[i][j] - B[i][j] );
                  if(diff > 0.1) {
//                          printf("Position %d (%f) and Position %d (%f) differ by %f\n",i*N+j,c_ref[i][j],i*N+j,c[i][j],diff);
                          diff_flag = 1;
                  }
          }


  if(diff_flag)
          printf("Output differs\n");
  else
          printf("Output is identical\n");

    if (fopen(".test", "r")) {
        for (i = 0; i < N; i++) {
            for (j = 0; j < N; j++) {
                fprintf(stdout, "%lf ", B[i][j]);
            }
            fprintf(stdout, "\n");
        }
    }
    return 0;
}
