#include <stdio.h>
#include <mcheck.h>
#include <malloc.h>

static char* cmdline;

void* new(size_t size)
{
    return malloc(size);
}

static void __attribute__((constructor)) constructor(void)
{
    mtrace();
    FILE* proc = fopen("/proc/self/cmdline", "r");        
    if(proc == NULL)
    {
        printf("proc");
    }
    cmdline = (char*)malloc(257);
    fgets(cmdline, 257, proc);
    close(proc);
}

static void __attribute__((destructor)) freeMem(void)
{
    int indexEndNameProgramm = 0;
    while(cmdline[indexEndNameProgramm] =! ' ')
    {
        indexEndNameProgramm++;
    }
    char* command = concatinationStr("MALLOC_TRACE=mem.log ", cmdline, 22, indexEndNameProgramm); // ! check
    system(command);
    free(command);
    command = concatinationStr("mtrace ", cmdline, 8, indexEndNameProgramm);
    command = concatinationStr(command, "mem.log", 8+indexEndNameProgramm, 8);
    system(command);
    free(command);
    FILE* mem_log = fopen("./mem.log", "r");
    if(mem_log == NULL)
    {
        printf("mem_log");
    }
    while()
    
    
}

