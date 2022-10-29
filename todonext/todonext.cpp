#include "todonext.h"
#include "task.h"
#include <QString>
#include <QDebug>

TodoNext::TodoNext()
{

}

TodoNext::~TodoNext()
{

}

AbstractTask* TodoNext::getDefaultTask()
{
    AbstractTask* task = new Task();
    task->load();
    return task;
}

AbstractTask* TodoNext::getCurrentTask(QString path)
{
    AbstractTask* task = new Task();
    task->load();
    for (QChar c : path){
        int i = c.digitValue();
        if (i == -1) 
            return nullptr;
        task = task->getChildByIndex(i);
        if (task == nullptr)
            return nullptr;
    }
    return task;
}