#include "task.h"
#include <iostream>
#include <vector>
#include <QStandardPaths>
#include <QDir>
#include <QTextStream>
#include <QChar>
#include <QDebug>

Task::Task() : task_name("default"), father(nullptr)
{
    create_task_file();
}

Task::Task(const Task& task): task_name(task.task_name), father(task.father), children(task.children)
{
    create_task_file();
}

Task::Task(const QString &task_name)
{
    this->father = nullptr;
    this->task_name = task_name;
    create_task_file();
}

void Task::create_task_file()
{
    const QString genericDataLocation = QStandardPaths::writableLocation(QStandardPaths::GenericDataLocation);
    const QString suffix = QStringLiteral("TodoNext");
    QDir(genericDataLocation).mkdir(suffix);
    this->task_file = new QFile(genericDataLocation + QDir::separator() + suffix + QDir::separator() + "task.txt");
}

Task::~Task()
{
    for (int i = 0; i < children.size(); ++i) {
        delete children[i];
    }
    delete this->task_file;
}

QString Task::getName()
{
    return this->task_name;
}

Task* Task::getFather()
{
    return this->father;
}

Task* Task::addChildren(const Task &task)
{
    Task* child_task = new Task(task);
    child_task->father = this;
    children.push_back(child_task);
    return child_task;
}

std::vector<Task*> Task::getChildren()
{
    return this->children;
}

Task* Task::getChildrenByIndex(int index)
{
    if (index < 0 || index >= (this->children).size())
        return nullptr;
    return (this->children)[index];
}

void Task::load()
{
    if(!this->task_file->open(QIODevice::ReadOnly | QIODevice::Text)) {
        std::cerr << "file " + this->task_file->fileName().toStdString() + " not found" << std::endl;
        return;            
    }
    // file stream
    QTextStream in(this->task_file);
    // top task
    Task* top = this;
    int top_level = -1;
    int current_level = 0;
    std::vector<Token> token_lists;
    // error handler
    int line_num = 0;
    QChar error_token;
    // token analyze
    while (in.status() != QTextStream::ReadPastEnd)
    {
        QChar c;
        ++line_num;
        in >> c;
        if (c == "│") {
            in >> c;
            if (c != " ") {
                error_token = c;
                goto EToken;
            }
            token_lists.push_back({
                .type = TAP,
                .str = "│ ",
            });
        }
        else
        if (c == "\n") {
            error_token = c;
            goto EToken;
        }
        else
        if (c == "└") {
            in >> c;
            if (c != "─") {
                error_token = c;
                goto EToken;
            }
            token_lists.push_back({                    
                .type = END_TAP,
                .str = "└─"
            });
        }
        else
        if (c == "├") {
            in >> c;
            if (c != "─") {
                error_token = c;
                goto EToken;
            }
            token_lists.push_back({                    
                .type = END_TAP,
                .str = "├─"
            });
        }
        else
        if (c == "─") {
            error_token = c;
            goto EToken;
        }
        else
        if (c == " ") {
            in >> c;
            if(c != " ") {
                error_token = c;
                goto EToken;
            }
            token_lists.push_back({
                .type = TAP,
                .str = "  ",
            });    
        }
        else {
            QString value;
            while (
                in.status() != QTextStream::ReadPastEnd &&
                c != "\n"
            ) {
                value.push_back(c);
                in >> c;
            }
            token_lists.push_back({                    
                .type = VALUE,
                .str = value,
            });
        }
    }

    // grammar analyze
    for (int i = 0; i < token_lists.size(); ++i) {
        if (token_lists[i].type == TokenType::TAP) {
            ++current_level;
            continue;
        }
        else
        if (token_lists[i].type == TokenType::END_TAP)
        {
            ++current_level;
            continue;
        }
        else
        if (token_lists[i].type == TokenType::VALUE) {
            if (current_level - top_level == 1) {
                Task t;
                t.task_name = token_lists[i].str;
                t.father = top;
                top = top->addChildren(t);
                top_level = current_level;
                current_level = 0;
            }
            else
            if (current_level <= top_level) {
                for (int i = 0;i <= top_level - current_level; ++i) {
                    top = top->father;
                }
                Task t;
                t.task_name = token_lists[i].str;
                t.father = top;
                top = top->addChildren(t);
                top_level = current_level;
                current_level = 0;
            }
            else {
                error_token = ' ';
                goto EGrammar;
            }
        }
        else {
            qWarning() << "Invalid" << Qt::endl;
            return;
        }
    }

    return;
    EToken:
        qWarning() << "Error on parsing token: " << error_token << " at line " << line_num << Qt::endl;
        return;
    EGrammar:
        qWarning() << "Error on token: " << error_token << Qt::endl;
        return;
}

void Task::save()
{
    std::vector<bool> is_last;
    if (!(this->task_file->open(QIODevice::WriteOnly | QIODevice::Text)))
        return;
    QTextStream out(this->task_file);

    if (father != nullptr) {
        std::cerr << "This task is not root task, exit" << std::endl;
        return;
    }

    is_last.push_back(false);
    for (int i = 0; i < children.size(); ++i) {
        if ( i == (children.size() - 1))
            is_last[0] = true;
        else
            is_last[0] = false;
        (children[i])->_save(0, is_last, out);
    }
    qDebug() << "save" << Qt::endl;
    this->task_file->close();
}

void Task::_save(int level, std::vector<bool> &is_last, QTextStream &out)
{
    qDebug() << "_save" << Qt::endl;
    for (int i = 0; i < level; ++i) {
        if (i == level - 1) {
            if (is_last[level])
                out << "└─";
            else
                out << "├─";
        }
        else {
            if (is_last[i + 1])
                out << "  ";
            else
                out << "│ ";
        }
    }

    out << task_name << Qt::endl;

    if (level + 2 > is_last.size())
        is_last.push_back(false);

    for (int i = 0; i < children.size(); ++i) {
        if (i == (children.size() - 1))
            is_last[level + 1] = true;
        else
            is_last[level + 1] = false;
        (children[i])->_save(level + 1, is_last, out);
    }
}