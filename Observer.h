#ifndef OBSERVER_H
#define OBSERVER_H
#include "Notice.h"


/**
 * @brief GoF Observer role. Receives push notifications from a Subject.
 *
 * Any class that needs to react to event notices implements this
 * interface and registers itself with a Subject via attach().
 */

class Observer {
public:
    virtual ~Observer() = default;

    /**
     * @brief Called by a Subject when a Notice is issued.
     *
     * Under this design's push model, the Notice carries all state
     * the observer needs; observers should not need to call back
     * into the Subject to fetch further information.
     *
     * @param notice The notice payload being broadcast.
     */
    virtual void update(const Notice& notice) = 0;
};







#endif