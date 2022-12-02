#include <stdio.h>
#include <sys/syscall.h>
#include <linux/kernel.h>
#include <unistd.h>
#include<stdlib.h>
#include <errno.h>

#define KER_SYS_CALL 451

int main()
{
    long sys_call_status;
    float src[5][5] = { {1.5,2.5,3.5,10.5,11.5},{4.5,5.5,6.5,12.5,13.5},{7.5,8.5,9.5,14.5,15.5},{4.5,5.5,6.5,12.5,13.5},{7.5,8.5,9.5,14.5,15.5} };
    float dst[5][5] = {0};
    sys_call_status = syscall(KER_SYS_CALL,src,dst,5,5);

    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            printf("%0.5f ",dst[i][j]);
        }
        printf("\n");
        
    }
    

    if (!sys_call_status)
    {
        printf("Successfully invoked system call 451\n");
    }

    return 0;
}