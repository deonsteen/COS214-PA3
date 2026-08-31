#include "EventRules.h"
#include "Observer.h"

bool EventRules::transferUnit(
    EventGroup& from,
    EventGroup& to,
    EventComponent* unit,
    bool transferObserverRegistration
)
{
    std::unique_ptr<EventComponent> released = from.removeChild(unit);

    if (!released)
    {
        return false;
    }

    /*
    Ownership and observation are deliberately separate.
    A component may structurally belong to an EventGroup without observing that group. 
    Observer registration is therefore moved only when the caller explicitly requests it.
     */
    if (transferObserverRegistration)
    {
        Observer* observer = dynamic_cast<Observer*>(released.get());

        if (observer != nullptr)
        {
            from.detach(observer);
            to.attach(observer);
        }
    }

    to.addChild(std::move(released));

    return true;
}

bool EventRules::meetsCapacityThreshold(
    const EventGroup& zone,
    int threshold
)
{
    return zone.getCapacity() >= threshold;
}

Notice EventRules::deriveWeatherNotice(
    int windSpeedKmh,
    int evacuateThreshold
)
{
    if (windSpeedKmh >= evacuateThreshold)
    {
        return Notice(
            NoticeType::EVACUATE,
            "Wind speed critical - evacuate outdoor areas",
            windSpeedKmh
        );
    }

    return Notice(
        NoticeType::WEATHER_ALERT,
        "Weather advisory - high winds",
        windSpeedKmh
    );
}