#ifndef INFORMATIONDESK_H
#define INFORMATIONDESK_H

#include "EventUnit.h"

/**
 * @brief Concrete Leaf: a static information desk.
 *
 *  Single Pattern participation:
 *  InformationDesk is a Leaf in the composite pattern when held by a
 *  EventComponent pointer that can work as part of a event tree, but it
 *  deliberately does NOT implement Observer: it has no meaningful
 *  reaction to event notices, so forcing it to implement update() would
 *  be uniformity for its own sake rather than a genuine collaboration
 *  (see design question: "do all Leaves implement Observer?"). It is
 *  never attach()ed to a Subject and never receives a notice.
 */
class InformationDesk : public EventUnit {
public:
    /**
     * @brief Constructs an information desk with a fixed capacity.
     * @param name Human-readable identifier for this information desk.
     * @param capacity Maximum number of people the desk can serve at once.
     */
    InformationDesk(std::string name, int capacity);
    ~InformationDesk() override = default;

    void open() override;
    void close() override;
    void reportStatus() const override;
};

#endif
