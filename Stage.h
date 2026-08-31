#ifndef STAGE_H
#define STAGE_H

#include "EventUnit.h"
#include "Observer.h"

/**
 * @brief Concrete Leaf: a live performance stage.
 *
 *  Observer role: a Stage cares about weather and evacuation notices and
 *  reacts by pausing its current performance, then resumes on RESUME.
 *
 *  Dual Pattern inheritance:
 *  Stage is a Leaf in the composite pattern when held by a EventComponent
 *  pointer that can work as part of a event tree 
 * 
 *  Stage is also an Observer in the observer pattern when held by a Observer
 *  such that when it participates as a observer it can be attached to a subject 
 *  and receive notices from the subject.
 */
class Stage : public EventUnit, public Observer {
public:
    /**
     * @brief Constructs a stage with a fixed capacity.
     * @param name Human-readable identifier for this stage.
     * @param capacity Maximum number of people the stage can accommodate.
     */
    Stage(std::string name, int capacity);
    ~Stage() override = default;

    void open() override;
    void close() override;
    void reportStatus() const override;

    void update(const Notice& notice) override;

private:
    bool paused_ = false;
};

#endif
