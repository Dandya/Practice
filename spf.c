#include <time.h>
#include <stdlib.h>
#include <stdio.h>

#include "sched.h"

static struct process_info
{
    int id;
    int time_end;
    struct process_info *next;
} *first_proc, *next_proc, *prev_proc;


// Сделать структуру с описанием процесса, и односвязным списком хранить инфу
// сделать поиск самого быстрого процесса 


static int process_count;
static int needed_search;

static int search_fast_process()
{
    //int id = prev_proc->id;
    //int min_time = prev_proc->time_end;
    struct process_info *fast_proc = prev_proc;
    next_proc = first_proc;
    
    if(first_proc == NULL)
        return -1;
    
    do
    {
        if (next_proc->time_end < fast_proc->time_end)
        {
            fast_proc = next_proc;
            //id = next_proc->id;
            //min_time = next_proc->time_end;
        }
        next_proc = next_proc->next;
    } while(next_proc != NULL);
    
    if (fast_proc->id != prev_proc->id || min_time == 0)
        needed_search = 1;
    else
        needed_search = 0;
        
    prev_proc = fast_proc;
    return fast_proc->id;
}

static int delete_process(struct process_info *proc)
{
    struct process_info *tmp_proc = first_proc;
    
    while(tmp_proc->next != proc)
        tmp_proc = tmp_proc->next;
        
    tmp_proc->next = proc
    return 0;
}

int sched_init(void)
{
  
  return 0;
}

void sched_clean(void)
{
  process_count = 0;
}

int add_proc(void)
{
  return (process_count++);
}

int sched(int time, int cont)
{
  if (cont == 0 && time != 0) 
  {
    delete_process(prev_proc);
  }
  
  prev_proc->time_end = cont;
  
  
  return needed_search? search_fast_process(): prev_proc->id;
}

int sched_fin(void)
{
  return 0;
}


