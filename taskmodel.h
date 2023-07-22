
#ifndef TASKMODEL_H
#define TASKMODEL_H


#include "qobject.h"
#include <QString>

class timeModel
{

public :
    timeModel();

    int days;
    int hours;
    int minutes;
    int seconds;
    void addSec();
};

class taskModel
{
public:
    taskModel();
//    taskModel(const taskModel&);
    QString title;
    bool expired;
    timeModel time;
//    int hours;
//    int minutes;
//    int seconds;
};

class globalModel
{
public:
    globalModel();
    timeModel time;
//    int days;
//    int hours;
//    int minutes;
//    int seconds;
};

#endif // TASKMODEL_H
