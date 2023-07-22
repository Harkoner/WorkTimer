
#include "taskmodel.h"

timeModel::timeModel()
{
    days = 0;
    hours = 0;
    minutes = 0;
    seconds = 0;
}

void timeModel::addSec()
{
    seconds += 1;

    if(seconds == 60)
    {
        seconds = 0;
        minutes += 1;
        if(minutes == 60)
        {
            minutes = 0;
            hours += 1;
            if(hours == 24)
            {
                hours = 0;
                days += 1;
            }
        }
    }
}

taskModel::taskModel()
{
    title = "title";
    expired = false;
}
