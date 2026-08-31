#ifndef VENDOR_H
#define VENDOR_H

#include "EventUnit.h"
#include "Observer.h"

/**
 * @brief Concrete Leaf: a food/merchandise vendor.
 *
 *  Observer role: a Vendor suspends service during safety or capacity
 *  notices, and resumes on RESUME.
 *
 *  Dual Pattern inheritance:
 *  Vendor is a Leaf in the composite pattern when held by a EventComponent
 *  pointer that can work as part of a event tree
 *
 *  Vendor is also an Observer in the observer pattern when held by a Observer
 *  such that when it participates as a observer it can be attached to a subject
 *  and receive notices from the subject.
 */
class Vendor : public EventUnit, public Observer {
public:
    /**
     * @brief Constructs a vendor with a fixed capacity.
     * @param name Human-readable identifier for this vendor.
     * @param capacity Maximum number of people the vendor can serve at once.
     */
    Vendor(std::string name, int capacity);
    ~Vendor() override = default;

    void open() override;
    void close() override;
    void reportStatus() const override;

    void update(const Notice& notice) override;

private:
    bool serving_ = false;
};

#endif
