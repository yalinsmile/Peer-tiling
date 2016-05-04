#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "get_fun.h"
#include <assert.h>

#define N 4000
#define T 500

#pragma declarations
double a[N][N];
#pragma enddeclarations

#include "util.h"
int T1t1,T1t2,T1t3,T2t1,T2t2,T2t3;

void init(int c)
{
   T1t1=32;T1t2=32;T1t3=32;
   T2t1=c;T2t2=c;T2t3=c;
}

void sgemm()
{
      int i, j, k, t;

    for (t=0; t<=T-1; t++)  {
        #pragma zyl
        #pragma scop
        for (i=1; i<=N-2; i++)  {
            for (j=1; j<=N-2; j++)  {
                a[i][j] = (a[i-1][j-1] + a[i-1][j] + a[i-1][j+1]
                        + a[i][j-1] + a[i][j] + a[i][j+1]
                        + a[i+1][j-1] + a[i+1][j] + a[i+1][j+1])/9.0;
            }
        }
        #pragma endscop
        #pragma endzyl
    }
     
}
	
int main(int argc,char *argv[])
{
    int i, j, k, t;

    double t_start, t_end;
    int nb1=atoi(argv[1]);
    init_array() ;
   // init(64,nb1);
#ifdef PERFCTR
    PERF_INIT; 
#endif

    IF_TIME(t_start = rtclock());
   sgemm();


    IF_TIME(t_end = rtclock());
    IF_TIME(fprintf(stdout, "%0.6lfs\n", t_end - t_start));

#ifdef PERFCTR
    PERF_EXIT; 
#endif

  if (fopen(".test", "r")) {
#ifdef MPI
    if (my_rank == 0) {
        print_array();
    }
#else
    print_array();
#endif
  }

    return 0;
}
