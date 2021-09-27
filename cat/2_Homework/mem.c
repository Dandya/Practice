#include <stdio.h>
#include <mcheck.h>
#include <malloc.h>
#include <stdlib.h>

#ifndef MEM_H
#define MEM_H

static char* cmdline;

void* new(size_t size)
{
    return malloc(size);
}

/**
 * concatenatoinStr
 * * Function concatenations two strings
 */
static char* concatenationStr(char* strFirst, char* strSecond, int length1, int length2)
{
    char *newStr = realloc(strFirst,length1 + length2);
    if(strSecond == NULL)
    {
        return newStr;
    }
    for(int index = 0; index <= length2; index++)
    {
        newStr[index+length1] = strSecond[index];
    }
    return newStr;
}

static void __attribute__((constructor)) constructor(void)
{
    if(system("touch ./mem.log"))
    {
        fprintf(stderr, "Невозможно создать фаил mem.log\n");
    }
    if(setenv("MALLOC_TRACE", "mem.log", 1))
    {
        fprintf(stderr, "Невозможно создать переменную окружения MALLOC_TRACE!\n");
    }
    mtrace();
    FILE* proc = fopen("/proc/self/cmdline", "r");        
    if(proc == NULL)
    {
        printf("proc");
    }
    cmdline = (char*)malloc(257);
    fgets(cmdline, 257, proc);
    fclose(proc);
    printf("%s\n", cmdline);
}

static void __attribute__((destructor)) freeMem(void)
{
    /*int indexEndNameProgramm = 0;
    while(cmdline[indexEndNameProgramm] =! ' ' && cmdline[indexEndNameProgram] != '\0')
    {
        indexEndNameProgramm++;
    }
    char* command = concatenationStr("mtrace ", cmdline, 8, indexEndNameProgramm);
    command = concatenationStr(command, "mem.log", 8+indexEndNameProgramm, 8);
    if(!system(command))
    {
        fprintf(stderr, "Невозможно создать mem.log\n");
        exit()
    }
    free(command);*/
    FILE* mem_log = fopen("./mem.log", "r");
    if(mem_log == NULL)
    {
        fprintf(stderr, "Невозможно открыть mem_log\n");
    }
}

#endif
