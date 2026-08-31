#include "Vendor.h"
#include <iostream>

Vendor::Vendor(std::string name, int capacity) : EventUnit(std::move(name), capacity) {}

void Vendor::open() {
    isOpen_ = true;
    serving_ = true;
    std::cout << "[Vendor] " << name_ << " is open and serving.\n";
}

void Vendor::close() {
    isOpen_ = false;
    serving_ = false;
    std::cout << "[Vendor] " << name_ << " has closed.\n";
}

void Vendor::reportStatus() const {
    std::cout << "Vendor '" << name_ << "': "
              << (!isOpen_ ? "closed" : (serving_ ? "open, serving" : "open, service suspended"))
              << ", capacity " << capacity_ << "\n";
}

void Vendor::update(const Notice& notice) {
    switch (notice.type) {
        case NoticeType::EVACUATE:
            case NoticeType::CAPACITY_ALERT:
                serving_ = false;
                std::cout << "[Vendor] " << name_ << " suspends service (" << notice.description << ")\n";
                break;
        case NoticeType::RESUME:
            serving_ = true;
            std::cout << "[Vendor] " << name_ << " resumes service.\n";
            break;
        default:
            break; // Vendor has no reaction to other notice types.
    }
}
