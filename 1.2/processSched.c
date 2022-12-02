#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/wait.h>
#include <sched.h>
#include <time.h>
#include <string.h>
#define OTHER 0
#define FIFO 1
#define RR 2
int pr_rr = 1, pr_other = 0 , pr_fifo = 1;
int find(pid_t pid, pid_t *pids)
{
        for (size_t i = 0; i < 3; i++)
        {
                if (pids[i] == pid)
                {
                        return i;
                }
        }
        return -1;
}
int main()
{
        pid_t pids[3];
        struct timespec start[3] = {0};
        struct timespec fin[3] = {0};
        struct timespec diffs[3] = {0};
        struct timespec finish;
        pid_t parent = getpid();
        for (int i = 0; i < 3; i++)
        {
                clock_gettime(CLOCK_REALTIME, &(start[i]));
                pid_t pid = fork();
                if (pid == 0)
                {

                        struct sched_param param;
                         char s[100] = "/root/osa2/1.2/compile";
                        // strcat(s," ");
                        if (i == OTHER)
                        {
                                param.sched_priority = 0;
                                strcat(s,"0");
                        }
                        else if (i == FIFO)
                        {
                                strcat(s,"1");
                                param.sched_priority = pr_fifo;
                        }
                        else if (i == RR)
                        {
                                strcat(s,"2");
                                param.sched_priority = pr_rr;
                        }

                        int rc = sched_setscheduler(getpid(), i, &param);
                        int pol = sched_getscheduler(getpid());
                        printf("%d %d\n", i, pol);
                        if (rc != 0)
                        {
                                printf("%s", strerror(errno));
                        }

                        fflush(stdout);

                        strcat(s,".sh");
                        execl("/bin/bash", "bash", s, NULL);
                }
                else
                {
                        pids[i] = pid;
                }
        }

        // for (size_t i = 0; i < 3; i++)
        // {
        //         printf("{%d}\n", pids[i]);
        // }

        for (int i = 0; i < 3; i++)
        {
                pid_t pid = wait(NULL);
                // printf("%d\n", pid);
                int res = find(pid, pids);
                if (res < 0)
                {
                        printf("Error\n");
                }
                else
                {
                        clock_gettime(CLOCK_REALTIME, &(fin[res]));
                }
        }

        for (size_t i = 0; i < 3; i++)
        {
                diffs[i].tv_sec = fin[i].tv_sec - start[i].tv_sec;
                diffs[i].tv_nsec = fin[i].tv_nsec - start[i].tv_nsec;
                if (diffs[i].tv_nsec < 0)
                {
                        diffs[i].tv_sec--;
                        diffs[i].tv_nsec += 1000000000;
                }

                printf("%d   %d.%lld\n", i, diffs[i].tv_sec, diffs[i].tv_nsec);
        }
        FILE *fptr = fopen("./results", "a");
        if (fptr == NULL)
        {
            printf("Error!");
            exit(1);
        }        
        fprintf(fptr,"%d,%d,%d.%ld,%d.%ld,%d.%ld\n",pr_fifo,pr_rr,(int)diffs[1].tv_sec, diffs[1].tv_nsec, (int)diffs[2].tv_sec, diffs[2].tv_nsec, (int)diffs[0].tv_sec, diffs[0].tv_nsec);
}