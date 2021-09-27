#include <stdio.h>
#include <mcheck.h>
#include <malloc.h>
#include <stdlib.h>

#ifndef MEM_H
#define MEM_H

void* new(size_t size)
{
    return malloc(size);
}

static int goToNewLine(FILE* stream)
{
    while(fgetc(stream) != '\n')
    {
        continue;
    }
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
}

static void __attribute__((destructor)) freeMem(void)
{
    if(!system("mtrace mem.log > mem.result.log"))
    {
        fprintf(stderr, "Невозможно использовать программу mtrace или записать её вывод в mem.result.log\n");
    }
    FILE* mem_result_log = fopen("./mem.result.log", "r");
    if(mem_result_log == NULL)
    {
        fprintf(stderr, "Невозможно открыть mem_result_log\n");
    }
    void* ptr; 
    char* ptrHex = (char*)malloc(19);
    int index = 0;
    while(!feof(mem_result_log))
    {
        if(fgets(ptrHex, 19, mem_result_log) == NULL)
        {
            break;
        }
        printf("%s\n", ptrHex);
        if(ptrHex[1] == 'x')
        {
            ptr = (void*)strtoll(ptrHex, NULL, 16);
            free(ptr);
            index++;
            printf("%d - %lld\n", index, ptr);
        }
        goToNewLine(mem_result_log);
    }
    free(ptrHex);
    fclose(mem_result_log);
    if(system("rm mem.result.log"))
    {
        fprintf(stderr, "Невозможно удалить mem.result.log\n");
    }
    if(system("rm mem.log"))
    {
        fprintf(stderr, "Невозможно удалить mem.log\n");
    }
}

#endif
