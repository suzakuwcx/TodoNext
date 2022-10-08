#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "task.h"

class Scheduler
{
public:
// submit a task
    virtual void submit(Task task) = 0;
// get next task
    virtual Task get() = 0;
};

#endif