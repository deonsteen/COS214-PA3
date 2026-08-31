#include "MedicalTeam.h"
#include <iostream>

MedicalTeam::MedicalTeam(std::string name, int capacity) : EventUnit(std::move(name), capacity) {}

void MedicalTeam::open() {
    isOpen_ = true;
    std::cout << "[MedicalTeam] " << name_ << " is on duty.\n";
}

void MedicalTeam::close() {
    isOpen_ = false;
    std::cout << "[MedicalTeam] " << name_ << " has stood down.\n";
}

void MedicalTeam::reportStatus() const {
    std::cout << "MedicalTeam '" << name_ << "': "
              << (!isOpen_ ? "off duty" : (onHighAlert_ ? "on duty, HIGH ALERT" : "on duty"))
              << ", capacity " << capacity_ << "\n";
}

void MedicalTeam::update(const Notice& notice) {
    switch (notice.type) {
        case NoticeType::EVACUATE:
            onHighAlert_ = true;
            std::cout << "[MedicalTeam] " << name_ << " raises readiness but remains operational (" << notice.description << ")\n";
            break;
        case NoticeType::RESUME:
            onHighAlert_ = false;
            std::cout << "[MedicalTeam] " << name_ << " stands down from high alert, remains operational.\n";
            break;
        default:
            std::cout << "[MedicalTeam] " << name_ << " remains operational through: " << notice.description << "\n";
            break;
    }
}
