#ifndef MEDICALTEAM_H
#define MEDICALTEAM_H

#include "EventUnit.h"
#include "Observer.h"

/**
 * @brief Concrete Leaf: an on-site medical team.
 *
 *  Observer role: a MedicalTeam deliberately remains operational through
 *  notices that pause other units (weather, evacuation) -- it implements
 *  Observer so that this "no-op but logged" reaction is an explicit,
 *  polymorphic decision rather than an accidental omission, and so it
 *  can raise its own readiness level during an EVACUATE.
 *
 *  Dual Pattern inheritance:
 *  MedicalTeam is a Leaf in the composite pattern when held by a EventComponent
 *  pointer that can work as part of a event tree
 *
 *  MedicalTeam is also an Observer in the observer pattern when held by a Observer
 *  such that when it participates as a observer it can be attached to a subject
 *  and receive notices from the subject.
 */
class MedicalTeam : public EventUnit, public Observer {
public:
    /**
     * @brief Constructs a medical team with a fixed capacity.
     * @param name Human-readable identifier for this medical team.
     * @param capacity Maximum number of people this team can attend to at once.
     */
    MedicalTeam(std::string name, int capacity);
    ~MedicalTeam() override = default;

    void open() override;
    void close() override;
    void reportStatus() const override;

    void update(const Notice& notice) override;

private:
    bool onHighAlert_ = false;
};

#endif
