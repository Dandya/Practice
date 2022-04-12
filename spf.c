#include <time.h>
#include <stdlib.h>
#include <stdio.h>

#include "sched.h"

static struct process_info
{
    int id;
    int time_end;
    struct process_info *next;
} *first_proc, *next_proc;


// Сделать структуру с описанием процесса, и односвязным списком хранить инфу
// сделать поиск самого быстрого процесса 


static int process_count;
static int prev_id = 0;


static int search_fast_process()
{
    int id = 0;
    int min_time = first_proc->time_end;
    next_proc = first_proc->next;
    
    if( next_proc == NULL )
    {
        return 0;
    }
    
    do
    {
        if (next_proc->time_end < min_time)
        {
            id = next_proc->id;
            min_time = next_proc->time_end;
        }
        next_proc = next_proc->next;
    } while(next_proc != NULL);
    
    return id;
}

static int delete_process()

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
  if (cont == 0 && time != 0) {
    delete_process(prev_id);
  }
  
  int 

  return process_count;
}

int sched_fin(void)
{
  return 0;
}


