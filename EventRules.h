#ifndef EVENT_RULES_H
#define EVENT_RULES_H

#include "EventGroup.h"
#include "Notice.h"

/**
 * @brief Provides Task 4 event rules and dynamic behaviour.
 *
 * EventRules contains small independent operations used by the
 * integration layer. It does not own event components and does not
 * replace polymorphic behaviour implemented by concrete event units.
 *
 * Ownership and Observer registration remain separate concerns.
 * Moving a component between EventGroups therefore does not
 * automatically change its Observer registration unless explicitly
 * requested by the caller.
 */
namespace EventRules {

    /**
     * @brief Transfers a component from one EventGroup to another.
     *
     * Composite ownership is always transferred from @p from to @p to.
     * Observer registration is transferred only when
     * @p transferObserverRegistration is true.
     *
     * This preserves the design decision that structural containment
     * and notification registration are separate relationships.
     *
     * @param from Current owning EventGroup.
     * @param to Destination EventGroup.
     * @param unit Component currently owned by @p from.
     * @param transferObserverRegistration If true, and the component
     *        implements Observer, detach it from @p from and attach it
     *        to @p to. If false, Observer registration is unchanged.
     *
     * @return true if the component was found and transferred;
     *         false if @p unit was not owned by @p from.
     */
    bool transferUnit(
        EventGroup& from,
        EventGroup& to,
        EventComponent* unit,
        bool transferObserverRegistration
    );

    /**
     * @brief Tests whether a group's aggregate capacity meets a threshold.
     *
     * EventGroup::getCapacity() represents the recursively calculated
     * rated capacity of the group. This method therefore tests rated
     * capacity and does not claim to represent live attendee occupancy.
     *
     * @param zone EventGroup whose aggregate capacity is inspected.
     * @param threshold Capacity threshold to compare against.
     *
     * @return true if the group's capacity is greater than or equal to
     *         the threshold; otherwise false.
     */
    bool meetsCapacityThreshold(
        const EventGroup& zone,
        int threshold
    );

    /**
     * @brief Derives a weather-related notice from wind speed.
     *
     * Wind below the evacuation threshold produces a WEATHER_ALERT.
     * Wind at or above the evacuation threshold produces an EVACUATE
     * notice.
     *
     * @param windSpeedKmh Current wind speed in kilometres per hour.
     * @param evacuateThreshold Wind speed at which evacuation becomes
     *        necessary. Defaults to 90 km/h.
     *
     * @return WEATHER_ALERT or EVACUATE Notice containing the wind
     *         speed as its severity value.
     */
    Notice deriveWeatherNotice(
        int windSpeedKmh,
        int evacuateThreshold = 90
    );

}

#endif