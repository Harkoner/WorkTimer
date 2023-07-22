
#include "myjson.h"

#include <QJsonObject>
#include <QJsonArray>
#include <QFile>
#include <QJsonDocument>
#include <QList>

/*
https://doc.qt.io/qt-6/json.html

*/

myJson::myJson()
{
    global.hours = 0;
    global.minutes = 0;
    global.seconds = 0;
}

void myJson::save()
{
    QJsonObject json;
    QJsonArray taskArray;
    QJsonObject xglobal;
    for(const taskModel &task : tasks)
    {
        QJsonObject topic;
        topic["title"] = task.title;
        topic["expired"] = task.expired;
        topic["hours"] = task.time.hours;
        topic["minutes"] = task.time.minutes;
        topic["seconds"] = task.time.seconds;
        taskArray.append(topic);
    }
    json["task"] = taskArray;

    xglobal["hours"] = global.hours;
    xglobal["minutes"] = global.minutes;
    xglobal["seconds"] = global.seconds;
    xglobal["days"] = global.days;
    json["global"] = xglobal;

    QFile saveFile(QStringLiteral("property\\form.json"));

    if (!saveFile.open(QIODevice::WriteOnly)) {
        qWarning("Couldn't open save file.");
    }
    saveFile.write(QJsonDocument(json).toJson());
}

void myJson::read()
{
    QFile loadFile(QStringLiteral("property\\form.json"));

    if (!loadFile.open(QIODevice::ReadOnly)) {
        qWarning("Couldn't open save file.");
    }

    QByteArray saveData = loadFile.readAll();

    QJsonDocument loadDoc(QJsonDocument::fromJson(saveData));

    for(const QJsonValue &task : loadDoc.object()["task"].toArray())
    {
        taskModel xtask;
        xtask.title = task["title"].toString();
        xtask.expired = task["expired"].toBool();
        xtask.time.hours = task["hours"].toInt();
        xtask.time.minutes = task["minutes"].toInt();
        xtask.time.seconds = task["seconds"].toInt();
        tasks.append(xtask);
    }

    QJsonValue info = loadDoc.object()["global"];
    global.days = info["days"].toInt();
    global.hours = info["hours"].toInt();
    global.minutes = info["minutes"].toInt();
    global.seconds = info["seconds"].toInt();
}

taskModel * myJson::getTaskByTitle(QString title)
{
    for(taskModel &task : tasks)
    {
        if(task.title == title)
        {
            return &task;
        }
    }
    return nullptr;
}


