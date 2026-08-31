#ifndef EVENTUNIT_H
#define EVENTUNIT_H

#include "EventComponent.h"

/**
 * @brief GoF Leaf role: common state shared by every concrete operational
 * unit (Stage, Gate, Vendor, MedicalTeam, ShuttleStop, ...).
 *
 * Leaves have no children, so getCapacity() has a real base-case answer
 * here (the leaf's own fixed capacity) and does not need to be
 * overridden by every concrete leaf. open(), close() and reportStatus()
 * remain abstract: concrete leaves must react to being opened, closed or
 * notified in genuinely different ways so
 * there is no sensible shared default for them.
 */
class EventUnit : public EventComponent {
public:
    /**
     * @brief Constructs a leaf with a fixed capacity.
     * @param name Human-readable identifier.
     * @param capacity Fixed capacity of this unit.
     */
    EventUnit(std::string name, int capacity);

    ~EventUnit() override = default;

    /// @brief A Leaf's capacity is just its own stored value (base case).
    int getCapacity() const override;

protected:
    int capacity_;
    bool isOpen_ = false;
};

#endif
