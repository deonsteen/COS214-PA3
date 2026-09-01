#include "EventControl.h"
#include <iostream>

void EventControl::setRoot(EventComponent* root) {
    root_ = root;
}

void EventControl::issueNotice(const Notice& notice) {
    currentNotice_ = notice;
    std::cout << "[EventControl] Issuing notice: " << notice.description << "\n";
    notify(notice);
}

int EventControl::getTotalCapacity() const {
    if (!root_) return 0;
    return root_->getCapacity();
}

void EventControl::reportEventStatus() const {
    if (!root_) {
        std::cout << "[EventControl] No root set.\n";
        return;
    }
    root_->reportStatus();
}

const Notice& EventControl::getCurrentNotice() const {
    return currentNotice_;
}