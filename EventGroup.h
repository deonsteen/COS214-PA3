#ifndef EVENTGROUP_H
#define EVENTGROUP_H

#include <vector>
#include <memory>
#include "EventComponent.h"
#include "Observer.h"
#include "Subject.h"

/**
 * @brief GoF Composite role. Owns a collection of child EventComponents
 * (each either a Leaf or another EventGroup) and implements the common
 * operations recursively.
 *
 * EventGroup also inherits Observer and Subject so that an area which
 * needs to relay notices (e.g. a zone that must hear alerts from
 * EventControl and forward them to its own units) has that capability
 * available. Whether a given EventGroup instance actually participates
 * in either collaboration is decided at setup time by whoever calls (or
 * does not call) attach() on it — observation is opt-in per instance,
 * not automatic from structural nesting. This keeps "who owns whom"
 * (addChild/removeChild) completely separate from "who hears what"
 * (attach/detach): a child can be owned without being registered, and
 * in principle registered with a Subject that is not its structural
 * parent.
 */
class EventGroup : public EventComponent, public Observer, public Subject {
public:
    explicit EventGroup(std::string name);

    ~EventGroup() override = default;

    /**
     * @brief Takes ownership of a child component.
     * @param child Component to add. Ignored if nullptr.
     */
    void addChild(std::unique_ptr<EventComponent> child);

    /**
     * @brief Releases ownership of a child component without deleting it,
     * so it can be transferred to another EventGroup.
     * @param child Non-owning pointer identifying the child to remove.
     * @return The released owning pointer, or nullptr if not found.
     */
    std::unique_ptr<EventComponent> removeChild(EventComponent* child);

    void open() override;
    void close() override;
    void reportStatus() const override;

    /// @brief Recursive sum of every child's capacity (base case is in EventUnit).
    int getCapacity() const override;

    /**
     * @brief Observer role: reacts to a notice received from whatever
     * Subject this group has been attached to, then relays it to this
     * group's own observers via notify().
     * @param notice The notice being cascaded down the tree.
     */
    void update(const Notice& notice) override;

private:
    std::vector<std::unique_ptr<EventComponent>> children_; ///< Owning.
};

#endif
