#ifndef TASK_H
#define TASK_H

#include "abstracttask.h"
#include <QObject>
#include <QDir>
#include <QString>
#include <QList>

class Task : public AbstractTask
{
    Q_OBJECT
private:
    QString task_list_path;
    QString task_finish_path;

public:
    Task();
    ~Task();

    QString getTaskName();
    bool setTaskName(QString n_task_name);

    bool addTaskProperties(QString key, QString value);
    QList<QString> getTaskProperties(QString key);

    int getChildrenNum();
    AbstractTask* addChild(AbstractTask* child);
    AbstractTask* getChildByIndex(int index);
    AbstractTask* getFather();

    bool load();
    bool save();
};

#endif