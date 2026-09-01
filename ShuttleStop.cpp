#include "ShuttleStop.h"
#include <iostream>

ShuttleStop::ShuttleStop(std::string name, int capacity) : EventUnit(std::move(name), capacity) {}

void ShuttleStop::open() {
    isOpen_ = true;
    std::cout << "[ShuttleStop] " << name_ << " is running (" << currentRoute_ << ").\n";
}

void ShuttleStop::close() {
    isOpen_ = false;
    std::cout << "[ShuttleStop] " << name_ << " has stopped running.\n";
}

void ShuttleStop::reportStatus() const {
    std::cout << "ShuttleStop '" << name_ << "': "
                << (!isOpen_ ? "stopped" : ("running on " + currentRoute_))
                << ", capacity " << capacity_ << "\n";
}

 void ShuttleStop::update(const Notice& notice) {   //changed update to accomidate 5 event rules
    switch (notice.type) {
        case NoticeType::WEATHER_ALERT:
            currentRoute_ = "Indoor Shelter Route";
            std::cout << "[ShuttleStop] " << name_
                      << " changes route to " << currentRoute_
                      << " (" << notice.description << ")\n";
            break;

        case NoticeType::EVACUATE:
            currentRoute_ = "Emergency Evacuation Route";
            std::cout << "[ShuttleStop] " << name_
                      << " switches to " << currentRoute_
                      << " (" << notice.description << ")\n";
            break;

        case NoticeType::RESUME:
            currentRoute_ = "Standard Route";
            std::cout << "[ShuttleStop] " << name_
                      << " reverts to " << currentRoute_ << ".\n";
            break;

        default:
            break;
    }
}

