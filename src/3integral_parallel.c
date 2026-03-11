//   ./3integral_parallel <number_of_intervals> <number_of_threads>

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#include <sys/time.h>

#define TIMER_CLEAR     (tv1.tv_sec = tv1.tv_usec = tv2.tv_sec = tv2.tv_usec = 0)
#define TIMER_START     gettimeofday(&tv1, (struct timezone*)0)
#define TIMER_ELAPSED   (double) (tv2.tv_usec-tv1.tv_usec)/1000000.0+(tv2.tv_sec-tv1.tv_sec)
#define TIMER_STOP      gettimeofday(&tv2, (struct timezone*)0)
struct timeval tv1, tv2;


long double global_sum = 0.0L;
pthread_mutex_t mutex;


struct thread_data {
    long start;
    long end;
    long double a;
    long double width;
};


// Function to compute the partial sum or local_sum by each thread for given chunks/range of rectangles
void* compute(void* arg)
{
    struct thread_data* data = (struct thread_data*)arg;

    long double local_sum = 0.0L;

    for (long i = (data->start);   i < (data->end);   i++)
    {
        long double x = data->a + (i + 0.5L) * data->width;
        local_sum = local_sum + 4.0L * sqrtl(1.0L - x * x);
        //this is the sum of all the heights by each thread in the variable local_sum,
        //each thread calculates the sum of heights for its assigned chunk of rectangles, 
        //i.e. from data->start to data->end, and accumulates the heights in local_sum.
    }

    pthread_mutex_lock(&mutex);
    global_sum = global_sum + local_sum;  //finally, all local heights are added to  global_sum
    pthread_mutex_unlock(&mutex);
    pthread_exit(NULL);
}



int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        printf("Usage: %s <number_of_intervals> <number_of_threads>\n", argv[0]);
        return 1;
    }

    long N = atol(argv[1]); //total number of rectanges, or the number of sunbintervals for the integral approximation
    int num_threads = atoi(argv[2]);  //total number of threads to use for parallel computation
    long double a = 0.0L;  //long double is used 
    long double b = 1.0L;
    long double width = (b - a) / (long double)N; //N is casted to the long double, was initially double

    pthread_t threads[num_threads];  //initialized an array of thread identifiers to hold the thread IDs for each created thread
    struct thread_data data[num_threads];  //initialized an array of thread_data structures, see the above structure
            //to hold the data for each thread, like data[0] structure would hold start, end, a, and width for thread 0, and so on....

    pthread_mutex_init(&mutex, NULL); //mutex is initialized 

    long chunk = N / num_threads; //chunks are the numbers of rectangles or subintervals that each thread will process, 
               //this is calculated by = total number of rectangles (N) / total number of threads (num_threads)
               //so that each threads get an equal number of shares

    TIMER_CLEAR;
    TIMER_START;

    for (int t = 0; t < num_threads; t++)
    {
        data[t].start = t * chunk;
        data[t].end = (t == num_threads - 1) ? N : (t + 1) * chunk;
        data[t].a = a;
        data[t].width = width;
        //structure data[0] will have             start = 0,                       end = chunk,     a = 0.0,     width = (b - a) / N
        //structure data[1] will have             start = chunk,                   end = 2*chunk,   a = 0.0,     width = (b - a) / N
        //structure data[2] will have             start = 2*chunk,                 end = 3*chunk,   a = 0.0,     width = (b - a) / N
        //....
        //structure data[num_threads-1] will have start = (num_threads-1)*chunk,   end = N,         a = 0.0,     width = (b - a) / N

        pthread_create(&threads[t], NULL, compute, &data[t]);
        //thread[0] will execute compute function with parameter data[0], 
        //thread[1] will execute compute function with parameter data[1], and so on...
    }

    for (int t = 0; t < num_threads; t++)
    {
        pthread_join(threads[t], NULL);
    }

    long double pi = global_sum * width;  //final area is caluculated here
    //A = width * sum, where sum is the toal sum of heights calculated by all threads and stored in global_sum
    
    TIMER_STOP;

    printf("Parallel Method\n");
    printf("Intervals = %ld\n", N);
    printf("Threads = %d\n", num_threads);
    printf("Computed PI ≈ %.18Lf\n", pi);
    printf("Time elapsed = %f seconds\n", TIMER_ELAPSED);

    pthread_mutex_destroy(&mutex);  //mutex is destroyed after all mutex operations are done.

    return 0;
}
