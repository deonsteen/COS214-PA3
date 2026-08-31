#include "EventGroup.h"
#include <algorithm>
#include <iostream>

using namespace std;

EventGroup::EventGroup(string name) : EventComponent(move(name)) {}

void EventGroup::addChild(unique_ptr<EventComponent> child) {
    if (child) {
        children_.push_back(move(child));
    }
}

unique_ptr<EventComponent> EventGroup::removeChild(EventComponent* child) {
    auto it = find_if(children_.begin(), children_.end(),
        [child](const unique_ptr<EventComponent>& owned) {
            return owned.get() == child;
        });

    if (it == children_.end()) {
        return nullptr;
    }

    std::unique_ptr<EventComponent> released = std::move(*it);
    children_.erase(it);
    return released;
}

void EventGroup::open() {
    std::cout << "[EventGroup] " << name_ << " opening.\n";
    for (auto& child : children_) {
        child->open();
    }
}

void EventGroup::close() {
    std::cout << "[EventGroup] " << name_ << " closing.\n";
    for (auto& child : children_) {
        child->close();
    }
}

void EventGroup::reportStatus() const {
    std::cout << "== " << name_ << " ==\n";
    for (const auto& child : children_) {
        child->reportStatus();
    }
}

int EventGroup::getCapacity() const {
    int total = 0;
    for (const auto& child : children_) {
        total += child->getCapacity();
    }
    return total;
}

void EventGroup::update(const Notice& notice) {
    std::cout << "[EventGroup] " << name_ << " relays notice: " << notice.description << "\n";
    notify(notice);
}
