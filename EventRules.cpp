#include "EventRules.h"
#include <memory>

namespace EventRules {

bool transferUnit(
    EventGroup& from,
    EventGroup& to,
    EventComponent* unit,
    bool transferObserverRegistration)
{
    // ASSUMED API: removeChild returns std::unique_ptr<EventComponent>,
    // nullptr/empty if `unit` was not a direct child of `from`.
    // CONFIRM against real EventGroup.h before relying on this.
    std::unique_ptr<EventComponent> released = from.removeChild(unit);

    if (!released) {
        return false;
    }

    if (transferObserverRegistration) {
        Observer* asObserver = dynamic_cast<Observer*>(released.get());
        if (asObserver != nullptr) {
            // Ownership and observation are separate operations by design;
            // being an Observer type does not imply it was observing `from`,
            // so detach/attach here are best-effort and rely on Subject's
            // own idempotent/no-op guarantees for calls that don't apply.
            from.detach(asObserver);
            to.attach(asObserver);
        }
    }

    to.addChild(std::move(released));
    return true;
}

bool meetsCapacityThreshold(const EventGroup& zone, int threshold)
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