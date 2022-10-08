#ifndef TASK_H
#define TASK_H

#include <string>
#include <vector>

struct Task
{
    std::string task_name;
    // time_t submit_time;
    std::vector<Task*> children;
    Task* father;
};

#endif