#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#define NEWTIMESPEC (struct timespec *)malloc(sizeof(struct timespec))
#define TWO_THIRTY_TWO 4294967296

int pr_rr = 1, pr_other = 0 , pr_fifo = 1;
void *countA(void *diff)
{
    struct timespec start, fin;
    long long int count = 1;
    struct sched_param A;
    A.sched_priority = pr_fifo;
    int stat = pthread_setschedparam(pthread_self(), SCHED_FIFO, &A);
    int policy;
    struct sched_param param;
    pthread_getschedparam(pthread_self(), &policy, &param);
    printf("fifo %d %d\n", policy, param.sched_priority);

    if (stat < 0)
    {
        printf(strerror(stat));
    }
    clock_gettime(CLOCK_REALTIME, &start);
    for (long long i = 0; i < TWO_THIRTY_TWO; i++)
    {
        count++;
    }
    clock_gettime(CLOCK_REALTIME, &fin);
    ((struct timespec *)diff)->tv_nsec = fin.tv_nsec - start.tv_nsec;
    ((struct timespec *)diff)->tv_sec = fin.tv_sec - start.tv_sec;

    if (((struct timespec *)diff)->tv_nsec < 0)
    {
        ((struct timespec *)diff)->tv_sec--;
        ((struct timespec *)diff)->tv_nsec += 1000000000;
    }
}
void *countB(void *diff)
{
    struct timespec start, fin;
    long long int count = 1;
    struct sched_param A;
    A.sched_priority = pr_rr;
    int stat = pthread_setschedparam(pthread_self(), SCHED_RR, &A);
    int policy;
    struct sched_param param;
    pthread_getschedparam(pthread_self(), &policy, &param);
    printf("rr %d %d\n", policy, param.sched_priority);

    if (stat < 0)
    {
        printf(strerror(stat));
    }

    clock_gettime(CLOCK_REALTIME, &start);
    for (long long i = 0; i < TWO_THIRTY_TWO; i++)
    {
        count++;
    }
    clock_gettime(CLOCK_REALTIME, &fin);
    ((struct timespec *)diff)->tv_nsec = fin.tv_nsec - start.tv_nsec;
    ((struct timespec *)diff)->tv_sec = fin.tv_sec - start.tv_sec;

    if (((struct timespec *)diff)->tv_nsec < 0)
    {
        ((struct timespec *)diff)->tv_sec--;
        ((struct timespec *)diff)->tv_nsec += 1000000000;
    }
}

void *countC(void *diff)
{
    struct timespec start, fin;
    long long int count = pr_other;
    struct sched_param A;
    A.sched_priority = 0;
    int stat = pthread_setschedparam(pthread_self(), SCHED_OTHER, &A);
    int policy;
    struct sched_param param;
    pthread_getschedparam(pthread_self(), &policy, &param);
    printf("Other %d %d\n", policy, param.sched_priority);

    if (stat < 0)
    {
        printf(strerror(stat));
    }

    clock_gettime(CLOCK_REALTIME, &start);
    for (long long i = 0; i < TWO_THIRTY_TWO; i++)
    {
        count++;
    }
    clock_gettime(CLOCK_REALTIME, &fin);
    ((struct timespec *)diff)->tv_nsec = fin.tv_nsec - start.tv_nsec;
    ((struct timespec *)diff)->tv_sec = fin.tv_sec - start.tv_sec;

    if (((struct timespec *)diff)->tv_nsec < 0)
    {
        ((struct timespec *)diff)->tv_sec--;
        ((struct timespec *)diff)->tv_nsec += 1000000000;
    }
}

int main()
{

    pthread_t sched_fifo, sched_other, sched_round;
    struct timespec *diffA = NEWTIMESPEC;
    struct timespec *diffB = NEWTIMESPEC;
    struct timespec *diffC = NEWTIMESPEC;

    int prs[6] = {1, 5, 10, 20, 60, 99};
    for (int i = 0; i < 6; i++)
    {
        pr_fifo = prs[i];
        // pr_rr = prs[5-i];
        pthread_create(&sched_fifo, NULL, countA, (void *)diffA);
        pthread_create(&sched_other, NULL, countB, (void *)diffB);
        pthread_create(&sched_round, NULL, countC, (void *)diffC);

        pthread_join(sched_fifo, NULL);
        pthread_join(sched_other, NULL);
        pthread_join(sched_round, NULL);
        FILE *fptr = fopen("./results", "a");
        if (fptr == NULL)
        {
            printf("Error!");
            exit(1);
        }        
        fprintf(fptr,"%d,%d,%d.%ld,%d.%ld,%d.%ld\n",pr_fifo,pr_rr,(int)diffA->tv_sec, diffA->tv_nsec, (int)diffB->tv_sec, diffB->tv_nsec, (int)diffC->tv_sec, diffC->tv_nsec);
        printf("Time FIFO  %d.%ld\n", (int)diffA->tv_sec, diffA->tv_nsec);
        printf("Time RR  %d.%ld\n", (int)diffB->tv_sec, diffB->tv_nsec);
        printf("Time OTHER  %d.%ld\n", (int)diffC->tv_sec, diffC->tv_nsec);
    }
    pr_fifo = 1;
    for (int i = 0; i < 6; i++)
    {
        // pr_fifo = prs[i];
        pr_rr = prs[i];
        pthread_create(&sched_fifo, NULL, countA, (void *)diffA);
        pthread_create(&sched_other, NULL, countB, (void *)diffB);
        pthread_create(&sched_round, NULL, countC, (void *)diffC);

        pthread_join(sched_fifo, NULL);
        pthread_join(sched_other, NULL);
        pthread_join(sched_round, NULL);
        FILE *fptr = fopen("./results", "a");
        if (fptr == NULL)
        {
            printf("Error!");
            exit(1);
        }        
        fprintf(fptr,"%d,%d,%d.%ld,%d.%ld,%d.%ld\n",pr_fifo,pr_rr,(int)diffA->tv_sec, diffA->tv_nsec, (int)diffB->tv_sec, diffB->tv_nsec, (int)diffC->tv_sec, diffC->tv_nsec);
        printf("Time FIFO  %d.%ld\n", (int)diffA->tv_sec, diffA->tv_nsec);
        printf("Time RR  %d.%ld\n", (int)diffB->tv_sec, diffB->tv_nsec);
        printf("Time OTHER  %d.%ld\n", (int)diffC->tv_sec, diffC->tv_nsec);
    }
}