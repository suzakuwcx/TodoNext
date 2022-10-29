#ifndef TODONEXT_H
#define TODONEXT_H

#include <QObject>
#include <QString>
#include "task.h"

class TodoNext : public QObject
{
    Q_OBJECT
public:
    TodoNext();
    ~TodoNext();

    Q_INVOKABLE AbstractTask* getDefaultTask();
    Q_INVOKABLE AbstractTask* getCurrentTask(QString path);
};

#endif