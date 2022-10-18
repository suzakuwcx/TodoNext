#include "todonext.h"
#include <QObject>
#include <QString>
#include <vector>
#include <QDebug>

TodoNext::TodoNext(QObject *parent) : QObject(parent)
{
    current_task = &root_task;
}

TodoNext::~TodoNext()
{

}

void TodoNext::save()
{
    root_task.save();
}

void TodoNext::load()
{
    root_task.load();
}

void TodoNext::submit(QString sub_task_name)
{
    Task sub_task(sub_task_name);
    current_task->addChildren(sub_task);
}

void TodoNext::setCurrentTask(QString tree_path)
{
    Task* temp_task = &root_task;
    for (QChar c : tree_path){
        int i = c.digitValue();
        if (i == -1) 
            return;
        temp_task = temp_task->getChildrenByIndex(i);
        if (temp_task == nullptr)
            return;
    }
    this->tree_path = tree_path;
    current_task = temp_task;
}

QString TodoNext::getTaskName()
{
    return current_task->getName();
}

QStringList TodoNext::getSubTaskTreePath()
{
    int children_size = (current_task->getChildren()).size();
    QStringList list;
    for (int i = 0;i < children_size; ++i) {
        list << tree_path + i;
    }
    return list;
}