#include "EventUnit.h"

EventUnit::EventUnit(std::string name, int capacity)
    : EventComponent(name), capacity_(capacity) {}

int EventUnit::getCapacity() const
{
    return capacity_;
}
