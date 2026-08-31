#ifndef GATE_H
#define GATE_H

#include "EventUnit.h"
#include "Observer.h"

/**
 * @brief Concrete Leaf: an attendee entry/exit gate.
 *
 *  Observer role: a Gate reacts to safety notices by stopping admission
 *  of new attendees, then resumes admitting on RESUME.
 *
 *  Dual Pattern inheritance:
 *  Gate is a Leaf in the composite pattern when held by a EventComponent
 *  pointer that can work as part of a event tree
 *
 *  Gate is also an Observer in the observer pattern when held by a Observer
 *  such that when it participates as a observer it can be attached to a subject
 *  and receive notices from the subject.
 */
class Gate : public EventUnit, public Observer {
public:
    /**
     * @brief Constructs a gate with a fixed capacity.
     * @param name Human-readable identifier for this gate.
     * @param capacity Maximum number of people the gate can admit.
     */
    Gate(std::string name, int capacity);
    ~Gate() override = default;

    void open() override;
    void close() override;
    void reportStatus() const override;

    void update(const Notice& notice) override;

private:
    bool admitting_ = false;
};

#endif
