
#include "mytimer.h"

myTimer::myTimer()
    :timer(new QTimer)
{
    connect(&timer, &QTimer::timeout, this, &myTimer::timeExpired);
    connect(&timer, &QTimer::timeout, this, &myTimer::timeChanged);
}

void myTimer::setConnection(timeModel * taskTime, timeModel * globalTime)
{
    xtaskTime = taskTime;
    xglobalTime = globalTime;
}

void myTimer::timeExpired()
{
    xtaskTime->addSec();
    xglobalTime->addSec();
}

void myTimer::start()
{
    timer.start(1000);
}

void myTimer::stop()
{
    timer.stop();
}


