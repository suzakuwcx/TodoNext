#ifndef TODONEXT_H
#define TODONEXT_H

#include <QObject>
#include "task.h"

class TodoNext : public QObject
{
    Q_OBJECT
private:
    Task task;
public:
    TodoNext(QObject *parent = nullptr);
    ~TodoNext() override;

    Q_INVOKABLE void load();
    Q_INVOKABLE void save();
    Q_INVOKABLE void submit(QString sub_task_name);
    Q_INVOKABLE QString get();
};

#endif