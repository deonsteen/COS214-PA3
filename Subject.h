#ifndef SUBJECT_H
#define SUBJECT_H

#include <vector>
#include "Observer.h"
#include "Notice.h"

/**
 * @brief GoF Subject role. Maintains a non-owning registry of Observers
 * and notifies them of Notices.
 *
 * Ownership policy: Subject does NOT own its observers — pointers stored
 * here are non-owning. Registered observers must remain alive while
 * attached and should detach() themselves before their own destruction
 * to avoid dangling pointers.
 *
 * attach() is idempotent: attaching an already-registered pointer is a
 * silent no-op. detach() on a pointer that isn't registered is also a
 * safe no-op. notify() iterates over a snapshot of the observer list,
 * so an observer that attaches or detaches itself (or another observer)
 * from within its own update() call cannot invalidate the iteration.
 */
class Subject {
public:
    virtual ~Subject() = default;

    /**
     * @brief Registers an observer for future notifications.
     * @param observer Observer to register. Ignored if nullptr or
     *        already registered.
     */
    virtual void attach(Observer* observer);

    /**
     * @brief Deregisters an observer.
     * @param observer Observer to remove. Safe no-op if not registered.
     */
    virtual void detach(Observer* observer);

    /**
     * @brief Notifies all currently registered observers, in
     * registration order, of the given notice.
     * @param notice The notice to broadcast.
     */
    virtual void notify(const Notice& notice);

protected:
    std::vector<Observer*> observers_; ///< Non-owning pointers.
};

#endif
