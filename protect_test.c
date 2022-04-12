// Test that mprotect and munprotect works

#include "types.h"
#include "stat.h"
#include "user.h"
#include "mmu.h"

// test mprotect works
void
mprotecttest(void){
    char *strt = sbrk(0);
    sbrk(PGSIZE);
    *strt=100;
    mprotect(strt, 1) ;
    int c = fork();
    if(c == 0){
	    printf(1, "protect value = %d\n",*strt); 
        exit();
    }
    else if(c > 0){
        wait();
        printf(1, "\ntrapping...\n"); 
        *strt=3; 
        printf(1, "\nshould not print\n");
        exit(); 
    }
}

// test munprotext works
void
munprotecttest(void){
    char *strt = sbrk(0);
    sbrk(PGSIZE);
    *strt=100;
    mprotect(strt, 1);
    int c = fork();
    if(c == 0){
	    printf(1, "protect value = %d\n",*strt); 
        munprotect(strt, 1) ;  
        *strt=50;
        printf(1, "after unprotect = %d\n",*strt); 
        exit();
    }
}

int
main(void)
{
    munprotecttest();
    wait();
    mprotecttest();
    exit();
}