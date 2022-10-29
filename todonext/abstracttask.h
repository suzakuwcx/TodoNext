#ifndef ABSTRACTTASK_H
#define ABSTRACTTASK_H

#include <QString>
#include <QObject>
#include <QVector>
#include <QMap>
#include <QList>

class AbstractTask : public QObject
{
    Q_OBJECT
protected:
    QString task_name;
    QMap<QString, QString> task_properties;
    QVector<AbstractTask*> task_children;
    AbstractTask* father = nullptr;
public:
    explicit AbstractTask() = default;
    virtual ~AbstractTask() = default;
public:
    Q_INVOKABLE virtual QString getTaskName() = 0;
    Q_INVOKABLE virtual bool setTaskName(QString n_task_name) = 0;

    virtual bool addTaskProperties(QString key, QString value) = 0;
    virtual QList<QString> getTaskProperties(QString key) = 0;

    Q_INVOKABLE virtual int getChildrenNum() = 0;
    virtual AbstractTask* addChild(AbstractTask* child) = 0;
    Q_INVOKABLE virtual AbstractTask* getChildByIndex(int index) = 0;
    Q_INVOKABLE virtual AbstractTask* getFather() = 0;

    virtual bool load() = 0;
    virtual bool save() = 0;
};

#endif