#ifndef DEFAULT_SCHEDULER_H
#define DEFAULT_SCHEDULER_H

#include "scheduler.h"
#include "task.h"

class DefaultScheduler : public Scheduler
{
public:
    DefaultScheduler();
    ~DefaultScheduler();

    void submit(Task task) override;
    Task get() override;
};

#endif