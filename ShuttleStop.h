#ifndef SHUTTLESTOP_H
#define SHUTTLESTOP_H

#include "EventUnit.h"
#include "Observer.h"
#include <string>

/**
 * @brief Concrete Leaf: a shuttle/transport stop.
 *
 *  Observer role: a ShuttleStop reroutes during a weather alert or
 *  transport-affecting notice, and reverts on RESUME.
 *
 *  Dual Pattern inheritance:
 *  ShuttleStop is a Leaf in the composite pattern when held by a EventComponent
 *  pointer that can work as part of a event tree
 *
 *  ShuttleStop is also an Observer in the observer pattern when held by a Observer
 *  such that when it participates as a observer it can be attached to a subject
 *  and receive notices from the subject.
 */
class ShuttleStop : public EventUnit, public Observer {
public:
    /**
     * @brief Constructs a shuttle stop with a fixed capacity.
     * @param name Human-readable identifier for this shuttle stop.
     * @param capacity Maximum number of people the stop can hold at once.
     */
    ShuttleStop(std::string name, int capacity);
    ~ShuttleStop() override = default;

    void open() override;
    void close() override;
    void reportStatus() const override;

    void update(const Notice& notice) override;

private:
    std::string currentRoute_ = "Standard Route";
};

#endif
