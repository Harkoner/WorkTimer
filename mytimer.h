
#ifndef MYTIMER_H
#define MYTIMER_H

#include <QTimer>
#include "qobject.h"
#include "taskmodel.h"

class myTimer : public QObject
{
    Q_OBJECT
public:
    myTimer();
    void start();
    void stop();
    timeModel *xtaskTime = nullptr;
    timeModel *xglobalTime = nullptr;

    void setConnection(timeModel *taskTime, timeModel *globalTime);
signals:
    void timeChanged();

private slots:
    void timeExpired();
private:
    QTimer timer;
};

#endif // MYTIMER_H
