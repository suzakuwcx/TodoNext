#include "task.h"
#include <QString>
#include <QList>
#include <QSharedData>
#include <QStandardPaths>
#include <QTextStream>
#include <QDir>
#include <QDebug>

enum TokenType {
    TAP, END_TAP, VALUE, NEWLINE
};

struct Token
{
    TokenType type;
    QString str;
};

Task::Task() 
{
    const QString genericDataLocation = QStandardPaths::writableLocation(QStandardPaths::GenericDataLocation);
    const QString suffix = QStringLiteral("TodoNext");
    QDir(genericDataLocation).mkdir(suffix);
    this->task_list_path = QString(genericDataLocation + QDir::separator() + suffix + QDir::separator() + "task.txt");
    this->task_finish_path = QString(genericDataLocation + QDir::separator() + suffix + QDir::separator() + "finish.txt");

    this->task_name = QString("default");
}

Task::~Task()
{
    for (AbstractTask* t : task_children){
        delete t;
    }
}

QString Task::getTaskName()
{
    return this->task_name;
}

bool Task::setTaskName(QString n_task_name)
{
    this->task_name = n_task_name;
    return true;
}

bool Task::addTaskProperties(QString key, QString value)
{
    return false;
}

QList<QString> Task::getTaskProperties(QString key)
{
    return QList<QString>();
}

int Task::getChildrenNum()
{
    return (this->task_children).size();
}

AbstractTask* Task::addChild(AbstractTask* child)
{
    (this->task_children).push_back(child);
    return child;
}

AbstractTask* Task::getChildByIndex(int index)
{
    return (this->task_children).value(index, nullptr);
}

AbstractTask* Task::getFather()
{
    return this->father;
}

bool Task::load()
{

    if (this->father != nullptr)
        return this->father->load();

    QFile task_file(this->task_list_path);

    if(!task_file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return false;
    }

    // file stream
    QTextStream in(&task_file);
    // top task
    Task* top = this;
    int top_level = -1;
    int current_level = 0;
    QList<Token> token_lists;
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
                Task* t = new Task();
                t->task_name = token_lists[i].str;
                t->father = top;
                top = (Task* )top->addChild(t);
                top_level = current_level;
                current_level = 0;
            }
            else
            if (current_level <= top_level) {
                for (int i = 0;i <= top_level - current_level; ++i) {
                    top = (Task* )top->father;
                }
                Task* t = new Task();
                t->task_name = token_lists[i].str;
                t->father = top;
                top = (Task* )top->addChild(t);
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
            return false;
        }
    }

    return true;
    EToken:
        qWarning() << "Error on parsing token: " << error_token << " at line " << line_num << Qt::endl;
        return false;
    EGrammar:
        qWarning() << "Error on token: " << error_token << Qt::endl;
        return false;
}

bool Task::save()
{
    return true;
}