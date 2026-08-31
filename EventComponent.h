#ifndef EVENTCOMPONENT_H
#define EVENTCOMPONENT_H

#include <string>

/**
 * @brief Common Component interface for the EventFlow Composite tree.
 *
 * Shared abstraction implemented by both EventUnit (Leaf) and EventGroup
 * (Composite) so that client code can open, close, report status on, and
 * query the capacity of a single unit or an entire nested sub-tree
 * uniformly, without knowing whether it holds a Leaf or a whole
 * Composite.
 */
class EventComponent
{
public:
    /**
     * @brief Constructs a named component, of the composite or leaf variety.
     * @param name Human-readable identifier used in status output.
     */
    explicit EventComponent(std::string name);

    virtual ~EventComponent() = default;

    /// @brief Opens this component (and, for a Composite, its children).
    virtual void open() = 0;

    /// @brief Closes this component (and, for a Composite, its children).
    virtual void close() = 0;

    /// @brief Prints/logs this component's current status.
    virtual void reportStatus() const = 0;

    /**
     * @brief Returns this component's capacity.
     * @return For a Leaf, its own fixed capacity; for a Composite, the
     *         recursive sum of its children's capacities.
     */
    virtual int getCapacity() const = 0;

    /// @brief Returns this component's name.
    const std::string &getName() const;

protected:
    std::string name_;
};

#endif
