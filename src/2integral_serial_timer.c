
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/time.h>

#define TIMER_CLEAR     (tv1.tv_sec = tv1.tv_usec = tv2.tv_sec = tv2.tv_usec = 0)
#define TIMER_START     gettimeofday(&tv1, (struct timezone*)0)
#define TIMER_ELAPSED   (double) (tv2.tv_usec-tv1.tv_usec)/1000000.0+(tv2.tv_sec-tv1.tv_sec)
#define TIMER_STOP      gettimeofday(&tv2, (struct timezone*)0)
struct timeval tv1, tv2;

int main(int argc, char *argv[])
{
    //Ensure the user provides the number of intervals
    if (argc < 2)
    {
        printf("Usage: %s <number_of_intervals>\n", argv[0]);
        return 1;
    }

    long N = atol(argv[1]);  //Number of rectangles (subintervals)

    long double a = 0.0;  //Lower limit of integration
    long double b = 1.0;  //Upper limit of integration

    //Width of each rectangle:
    //Δx = (b − a) / N
    long double width = (b - a) / (long double)N;  //N is long, so casted to long double to ensure precision in the division

    // sum will accumulate all function evaluations
    long double sum = 0.0;

    TIMER_CLEAR;
    TIMER_START;

    for (long i = 0; i < N; i++)
    {
        //Midpoint of the i-th rectangle:
        //xᵢ = a + (i + 0.5)Δx
        long double x = a + (i + 0.5) * width;

        //This represents the height of the rectangle
        sum = sum + 4.0L * sqrtl(1.0L - x * x);  //Summation of all the heights of rectangels
    }

    //Multiply accumulated heights by rectangle width:
    //π ≈ [Σ f(xᵢ) ] * Δx
    long double pi = sum * width;  //here the sum is [Σ f(xᵢ) ] and width is Δx

    TIMER_STOP;

    printf("Serial Method\n");
    printf("Intervals = %ld\n", N);
    printf("Computed PI ≈ %.18Lf\n", pi);
    printf("Time elapsed = %f seconds\n", TIMER_ELAPSED);

    return 0;
}