#include <stdio.h>
#include <mcheck.h>
#include <malloc.h>


void* new(size_t size)
{
    return malloc(size);
}

static void __attribute__((constructor)) constructor(void)
{
    mtrace();
}

static void __attribute__((destructor)) freeMem(void)
{
    FILE* proc = fopen("/proc/self/cmdline", "r");        
    if(proc == NULL)
    {
        printf("proc");
    }
    char* cmdline = (char*)malloc(257);
    fgets(cmdline, 257, proc);
    close(proc);
    int indexEndNameProgramm = 0;
    while()
    
    
}

