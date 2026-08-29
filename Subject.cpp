#include "Subject.h"
#include <algorithm>


void Subject::attach(Observer* observer)
{
    if (!observer)
    {
        return;
    }

    if (std::find(observers_.begin(), observers_.end(), observer) != observers_.end())
    {
        return;
    }
    observers_.push_back(observer);
}


void Subject::detach(Observer* observer)
{
    auto it = std::find(observers_.begin(), observers_.end(), observer);
    if ( it != observers_.end())
    {
        observers_.erase(it);
    }
    //not found - safe, no op, np error 
}


void Subject::notify(const Notice& notice)
{
    //Snapshot guards against mutation of observers during iteration
    std::vector<Observer*> snapshot = observers_;
    for (Observer* obs : snapshot)
    {
        if ( obs)
        {
            obs->update(notice);
        }
    }
}