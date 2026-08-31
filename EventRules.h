#ifndef EVENTRULES_H
#define EVENTRULES_H

#include "EventComponent.h"
#include "EventGroup.h"   // ASSUMED filename — confirm once Person A's branch is inspected
#include "Observer.h"
#include "Notice.h"

/**
 * @brief Free functions implementing Task 4 event rules and dynamic
 * behaviour: runtime reorganisation, capacity-threshold decisions and
 * weather-derived notices.
 *
 * These functions deliberately do not belong to EventComponent or
 * EventGroup: they are policy/orchestration, not structural state, so
 * they are kept as a separate collaborator rather than growing either
 * class into a god object (Task 4.4 rationale).
 */
namespace EventRules {

/**
 * @brief Transfers a child unit from one EventGroup to another at runtime.
 *
 * Ownership transfer (Composite) and Observer registration are treated
 * as two separate operations by design (see team decision: owning a
 * child does not automatically register it as an observer). This keeps
 * "who owns me" and "who do I listen to" independently controllable.
 *
 * @param from Source group currently owning the unit.
 * @param to Destination group that will take ownership.
 * @param unit Raw pointer identifying which child to move (not owned by
 *             this function; used only to find the corresponding
 *             std::unique_ptr held by `from`).
 * @param transferObserverRegistration If true and `unit` is also an
 *        Observer, detaches it from `from` and attaches it to `to`
 *        (only meaningful if `from`/`to` are themselves Subjects).
 * @return true if the unit was found in `from` and moved; false if not found.
 */
bool transferUnit(
    EventGroup& from,
    EventGroup& to,
    EventComponent* unit,
    bool transferObserverRegistration
);

/**
 * @brief Checks whether a zone's aggregate rated capacity meets a threshold.
 *
 * This compares rated aggregate capacity (the recursive sum of child
 * capacities), NOT live occupancy — EventFlow does not currently track
 * real-time occupancy, only fixed configured capacity per unit.
 *
 * @param zone The composite whose capacity is queried.
 * @param threshold The capacity threshold to compare against.
 * @return true if zone.getCapacity() >= threshold.
 */
bool meetsCapacityThreshold(
    const EventGroup& zone,
    int threshold
);

/**
 * @brief Derives an appropriate Notice from a measured wind speed.
 *
 * Encodes the alt-fragment condition used in SD3: an EVACUATE notice is
 * issued once wind speed reaches the evacuation threshold; otherwise a
 * milder WEATHER_ALERT is issued.
 *
 * @param windSpeedKmh Current measured wind speed in km/h.
 * @param evacuateThreshold Wind speed at/above which EVACUATE is issued.
 * @return A Notice of type EVACUATE or WEATHER_ALERT with severity set
 *         to windSpeedKmh.
 */
Notice deriveWeatherNotice(
    int windSpeedKmh,
    int evacuateThreshold = 90
);

} // namespace EventRules

#endif