#include "InformationDesk.h"
#include <iostream>

InformationDesk::InformationDesk(std::string name, int capacity) : EventUnit(std::move(name), capacity) {}

void InformationDesk::open() {
    isOpen_ = true;
    std::cout << "[InformationDesk] " << name_ << " is staffed and open.\n";
}

void InformationDesk::close() {
    isOpen_ = false;
    std::cout << "[InformationDesk] " << name_ << " is unstaffed.\n";
}

void InformationDesk::reportStatus() const {
    std::cout << "InformationDesk '" << name_ << "': " << (isOpen_ ? "staffed" : "unstaffed")
                << ", capacity " << capacity_ << "\n";
}
