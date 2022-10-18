#ifndef TODONEXT_H
#define TODONEXT_H

#include <QObject>
#include <QStringList>
#include "task.h"

class TodoNext : public QObject
{
    Q_OBJECT
private:
    Task root_task;
    Task* current_task;
    QString tree_path;
public:
    TodoNext(QObject *parent = nullptr);
    ~TodoNext() override;

    Q_INVOKABLE void load();
    Q_INVOKABLE void save();
    Q_INVOKABLE void submit(QString sub_task_name);
    Q_INVOKABLE QString getTaskName();
    Q_INVOKABLE QStringList getSubTaskTreePath();
    Q_INVOKABLE void setCurrentTask(QString tree_path);
};

#endif