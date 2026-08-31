#include "Stage.h"
#include <iostream>
using namespace std;


//calls EventUnit as it can only call its direct base 
Stage::Stage(string name, int capacity) : EventUnit(move(name), capacity) {}

void Stage::open() {
    isOpen_ = true;
    paused_ = false;
    cout << "[Stage] " << name_ << " is open for performances.\n";
}

void Stage::close() {
    isOpen_ = false;
    cout << "[Stage] " << name_ << " has closed for the day.\n";
}

void Stage::reportStatus() const {
    cout << "Stage '" << name_ << "': "
                << (!isOpen_ ? "closed" : (paused_ ? "open, PAUSED" : "open, performing"))
                << ", capacity " << capacity_ << "\n";
}

void Stage::update(const Notice& notice) {
    switch (notice.type) {
        case NoticeType::WEATHER_ALERT:
            case NoticeType::EVACUATE:
                paused_ = true;
                cout << "[Stage] " << name_ << " pauses performance (" << notice.description << ")\n";
                break;
        case NoticeType::RESUME:
            paused_ = false;
            cout << "[Stage] " << name_ << " resumes performance.\n";
            break;
        default:
            break; // Stage has no reaction to other notice types.
    }
}
