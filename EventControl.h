#ifndef EVENTCONTROL_H
#define EVENTCONTROL_H

#include "Subject.h"
#include "EventComponent.h"
#include "Notice.h"

/**
 * @brief Concrete Subject acting as the event's central coordinator.
 *
 * EventControl is deliberately not part of the Composite ownership
 * tree — it is a client-side collaborator that holds a non-owning
 * pointer to the root of the Composite structure so it can invoke
 * tree-wide operations, while separately broadcasting Notices to
 * whichever objects have registered as Observers.
 */
class EventControl : public Subject {
public:
    /**
     * @brief Associates this control point with the root of the event tree.
     * @param root Non-owning pointer to the root EventComponent.
     */
    void setRoot(EventComponent* root);

    /**
     * @brief Broadcasts a notice to all registered observers and
     * records it as the current notice.
     * @param notice The notice to issue.
     */
    void issueNotice(const Notice& notice);

    /**
     * @brief Returns the total capacity across the whole event tree,
     * delegated to the root component.
     * @return Total capacity, or 0 if no root is set.
     */
    int getTotalCapacity() const;

    /**
     * @brief Prints a full status report for the whole event tree,
     * delegated to the root component.
     */
    void reportEventStatus() const;

    /**
     * @brief Returns the most recently issued notice.
     * @return The last Notice passed to issueNotice(), or a default
     *         placeholder if none has been issued yet.
     */
    const Notice& getCurrentNotice() const;

private:
    EventComponent* root_ = nullptr; ///< Non-owning pointer to the tree root.
    Notice currentNotice_{NoticeType::CUSTOM, "No notice issued yet"};
};

#endif 