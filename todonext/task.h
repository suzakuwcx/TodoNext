#ifndef TASK_H
#define TASK_H

#include <string>
#include <vector>
#include <QString>
#include <QFile>
#include <QTextStream>

class Task
{
public:
enum TokenType {
    TAP, END_TAP, VALUE, NEWLINE
};

struct Token
{
    TokenType type;
    QString str;
};

private:
    QString task_name;
    // time_t submit_time;
    std::vector<Task*> children;
    Task* father;
private:
    QFile* task_file;
public:
    Task();
    Task(const Task& task);
    Task(const QString &task_name);
    ~Task();
private:
    void create_task_file();
public:
    QString getName();
    Task* getFather();
    Task* addChildren(const Task &task);
    Task* getChildByIndex(int index);
    std::vector<Task*> getChildren();
    void save();
    void load();
private:
    void _save(int level, std::vector<bool> &is_last, QTextStream &out);
};

#endif