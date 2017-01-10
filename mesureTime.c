// compile with -lrt
// gcc -std=c99 mesureTime.c -o testtime -lrt
//
#define _POSIX_C_SOURCE 200112L
#include <stdio.h>  
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>

int main() {
    struct timespec tv_start, tv_end;
    struct timeval tv_tmp;
    int count = 1 * 1000 * 1000 * 50;
    clockid_t clockid;
    int rv = clock_getcpuclockid(0, &clockid);

    if (rv) 
    {
        perror("clock_getcpuclockid");
        return 1;
    }

    clock_gettime(clockid, &tv_start);
    for (int i = 0; i < count; i++)
        gettimeofday(&tv_tmp, NULL);
    clock_gettime(clockid, &tv_end);

    long long diff = (long long)(tv_end.tv_sec - tv_start.tv_sec)*(1*1000*1000*1000);
    diff += (tv_end.tv_nsec - tv_start.tv_nsec);

    printf("gettimeofday(): %d cycles in %lld ns = %f ns/cycle\n", count, diff, (double)diff / (double)count);

    clock_gettime(clockid, &tv_start);
    for (int i = 0; i < count; i++)
        time(NULL);
    clock_gettime(clockid, &tv_end);

    diff = (long long)(tv_end.tv_sec - tv_start.tv_sec)*(1*1000*1000*1000);
    diff += (tv_end.tv_nsec - tv_start.tv_nsec);

    printf("time()        : %d cycles in %lld ns = %f ns/cycle\n", count, diff, (double)diff / (double)count);

    return 0;
}
