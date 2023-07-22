
#ifndef MYJSON_H
#define MYJSON_H




#include "taskmodel.h"
#include <QList>


class myJson
{
public:
    myJson();
    void save();
    void read();
    QList<taskModel> tasks;
    timeModel global;
    taskModel *getTaskByTitle(QString title);
};

#endif // MYJSON_H
