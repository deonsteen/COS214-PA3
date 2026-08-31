#include "EventComponent.h"
using namespace std;

EventComponent::EventComponent(string name) : name_(name) {}

const string& EventComponent::getName() const {
    return name_;
}
