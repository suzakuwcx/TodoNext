#ifndef TODONEXT_H
#define TODONEXT_H

#include <QObject>

class TodoNext : public QObject
{
    Q_OBJECT

public:
    TodoNext(QObject *parent = nullptr);
    ~TodoNext() override;

    Q_INVOKABLE void load();
    Q_INVOKABLE void save();
};

#endif