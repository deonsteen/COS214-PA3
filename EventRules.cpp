#include "EventRules.h"
#include <memory>

namespace EventRules {

bool transferUnit(
    EventGroup& from,
    EventGroup& to,
    EventComponent* unit,
    bool transferObserverRegistration)
{
    std::unique_ptr<EventComponent> released = from.removeChild(unit);

    if (!released) {
        return false;
    }

    if (transferObserverRegistration) {
        Observer* asObserver = dynamic_cast<Observer*>(released.get());
        if (asObserver != nullptr) {
            
            from.detach(asObserver);
            to.attach(asObserver);
        }
    }

    to.addChild(std::move(released));
    return true;
}

bool isOverCapacityThreshold(const EventGroup& zone, int threshold)
{
    return zone.getCapacity() >= threshold;
}

Notice deriveWeatherNotice(int windSpeedKmh, int evacuateThreshold)
{
    if (windSpeedKmh >= evacuateThreshold) {
        return Notice(NoticeType::EVACUATE, "High wind: evacuating outdoor areas", windSpeedKmh);
    }
    return Notice(NoticeType::WEATHER_ALERT, "Weather advisory: monitor conditions", windSpeedKmh);
}

} // namespace EventRules