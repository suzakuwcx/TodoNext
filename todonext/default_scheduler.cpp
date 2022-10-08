#include "default_scheduler.h"
#include "task.h"

void DefaultScheduler::submit(Task task)
{
    
}

Task DefaultScheduler::get()
{
    Task task ={
        .father = nullptr,
    };
    return task;
}