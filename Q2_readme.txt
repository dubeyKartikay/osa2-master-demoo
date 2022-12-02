In Q2
    SYSCALL_DEFINE4 was used to define a syscall that takes 4 parameters
    source address, destination address, number of rows, and number of columns
    a buffer matrix of 5 rows and 5 colums was declared and then used to copy 
    src data in buffer, and then it was used to copy its data into destination

    copying a 2d array is a simple task as the array is stored contiguously in memory,
    and has the size of rows*columns

    the syscall_64.tbl file was updated to include our syscall
    as well as the main makefile to compile and link our custom syscall
    
Code for syscall

#include <linux/kernel.h>
#include <linux/syscalls.h>

/*
 * Definition for onedcopy system call 
 */
SYSCALL_DEFINE4(kernel_2d_memcpy, float*, src, float*, dest, int, rows,int,cols)
{
    /* Allocate a buffer of size len to hold the elements of array */
    float buffer[5][5]; 
    
    /* Copy from user copies the data from src to buffer of size len */
    if (__copy_from_user(buffer, src, sizeof(float)*(rows)*(cols)))
       return -EFAULT;

   /* Copy to user copies the data from buffer to dest of size len */
    if (__copy_to_user(dest, buffer, sizeof(float)*(rows)*(cols)))
       return -EFAULT;

    return 0;
}