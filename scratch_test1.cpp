// scratch_test.cpp — delete or move into proper tests later
#include "Subject.h"
#include <iostream>

class LoggingObserver : public Observer {
public:
    LoggingObserver(std::string name) : name_(std::move(name)) {}
    void update(const Notice& n) override {
        std::cout << name_ << " received notice: " << n.description << "\n";
    }
private:
    std::string name_;
};

int main() {
    Subject s;
    LoggingObserver a("Medical"), b("Vendor");
    s.attach(&a);
    s.attach(&b);
    s.attach(&a); // duplicate -> should not double-fire
    s.notify(Notice(NoticeType::WEATHER_ALERT, "Storm incoming", 80));
    s.detach(&a);
    s.notify(Notice(NoticeType::RESUME, "All clear"));
    return 0;
}
