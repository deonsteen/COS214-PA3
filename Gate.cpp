#include "Gate.h"
#include <iostream>

Gate::Gate(std::string name, int capacity) : EventUnit(std::move(name), capacity) {}

void Gate::open() {
    isOpen_ = true;
    admitting_ = true;
    std::cout << "[Gate] " << name_ << " is open and admitting attendees.\n";
}

void Gate::close() {
    isOpen_ = false;
    admitting_ = false;
    std::cout << "[Gate] " << name_ << " is closed.\n";
}

void Gate::reportStatus() const {
    std::cout << "Gate '" << name_ << "': "
                << (!isOpen_ ? "closed" : (admitting_ ? "open, admitting" : "open, admission stopped"))
                << ", capacity " << capacity_ << "\n";
}

void Gate::update(const Notice& notice) {
    switch (notice.type) {
        case NoticeType::EVACUATE:
            case NoticeType::CAPACITY_ALERT:
                admitting_ = false;
                std::cout << "[Gate] " << name_ << " stops admitting attendees (" << notice.description << ")\n";
                break;
        case NoticeType::RESUME:
            admitting_ = true;
            std::cout << "[Gate] " << name_ << " resumes admitting attendees.\n";
            break;
        default:
            break; // Gate has no reaction to other notice types.
    }
}
