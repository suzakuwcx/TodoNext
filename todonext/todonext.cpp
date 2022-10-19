#include "todonext.h"
#include <QObject>
#include <QString>
#include <vector>
#include <QDebug>

// change int number to ascll char, example 0 --> '0'
#define ITOC(x) (x + 49);

TodoNext::TodoNext(QObject *parent) : QObject(parent)
{
    root_task.load();
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
    Task* temp_task = this->parseTreePath(tree_path);
    this->tree_path = tree_path;
    current_task = temp_task;
}

QString TodoNext::getTaskName()
{
    return current_task->getName();
}

QStringList TodoNext::getSubTaskTreePath()
{
    QStringList list;
    for (int i = 0;i < (current_task->getChildren()).size(); ++i) {
        list << tree_path + ITOC(i);
    }
    return list;
}

QString TodoNext::getTaskName(QString tree_path)
{
    Task* temp_task = this->parseTreePath(tree_path);
    if (temp_task == nullptr)
        return "";
    return temp_task->getName();
}

QStringList TodoNext::getSubTaskTreePath(QString tree_path)
{
    Task* temp_task = this->parseTreePath(tree_path);
    QStringList list;
    if (temp_task != nullptr) {
        for (int i = 0; i < (temp_task->getChildren()).size(); ++i) {
            list << tree_path + ITOC(i);
        }
    }
    return list;
}

Task* TodoNext::parseTreePath(QString tree_path)
{
    Task* temp_task = &root_task;
    for (QChar c : tree_path){
        int i = c.digitValue();
        if (i == -1) 
            return nullptr;
        temp_task = temp_task->getChildByIndex(i);

        if (temp_task == nullptr)
            return nullptr;
    }
    return temp_task;
}