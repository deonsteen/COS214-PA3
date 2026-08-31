// Smoke test for the Composite/Observer skeleton — not the final main.cpp
// (Person C owns Task 8's main.cpp). Builds a tree 3 levels deep below
// root, wires up Observer registrations separately from ownership,
// cascades a notice through 4 runtime levels, demonstrates transferring
// a unit between zones, then lets root go out of scope to show clean
// destruction of the whole owned subtree.
#include <iostream>
#include <memory>
#include "../EventGroup.h"
#include "../Stage.h"
#include "../Gate.h"
#include "../Vendor.h"
#include "../MedicalTeam.h"
#include "../ShuttleStop.h"
#include "../InformationDesk.h"
#include "../Subject.h"

int main() {
    // --- Build the tree ---
    // City Lights Festival (root)
    //   +-- Main Stage Zone
    //   |     +-- Main Stage
    //   |     +-- Front Gate
    //   |     +-- Food Court            <- sub-zone: 3rd level below root
    //   |           +-- Taco Vendor
    //   |           +-- Coffee Vendor
    //   +-- River Zone
    //         +-- Shuttle Stop
    //         +-- Medical Team
    //         +-- Information Desk      <- never attached as an observer

    auto root = std::unique_ptr<EventGroup>(new EventGroup("City Lights Festival"));

    auto mainStageZone = std::unique_ptr<EventGroup>(new EventGroup("Main Stage Zone"));
    auto stage = std::unique_ptr<Stage>(new Stage("Main Stage", 5000));
    auto gate = std::unique_ptr<Gate>(new Gate("Front Gate", 2000));
    Stage* stagePtr = stage.get();
    Gate* gatePtr = gate.get();
    mainStageZone->addChild(std::move(stage));
    mainStageZone->addChild(std::move(gate));

    auto foodCourt = std::unique_ptr<EventGroup>(new EventGroup("Food Court"));
    auto tacoVendor = std::unique_ptr<Vendor>(new Vendor("Taco Vendor", 50));
    auto coffeeVendor = std::unique_ptr<Vendor>(new Vendor("Coffee Vendor", 30));
    Vendor* tacoVendorPtr = tacoVendor.get();
    Vendor* coffeeVendorPtr = coffeeVendor.get();
    foodCourt->addChild(std::move(tacoVendor));
    foodCourt->addChild(std::move(coffeeVendor));

    EventGroup* foodCourtPtr = foodCourt.get();
    mainStageZone->addChild(std::move(foodCourt));

    auto riverZone = std::unique_ptr<EventGroup>(new EventGroup("River Zone"));
    auto shuttle = std::unique_ptr<ShuttleStop>(new ShuttleStop("Shuttle Stop", 100));
    auto medical = std::unique_ptr<MedicalTeam>(new MedicalTeam("Medical Team", 20));
    auto infoDesk = std::unique_ptr<InformationDesk>(new InformationDesk("River Info Desk", 10));
    ShuttleStop* shuttlePtr = shuttle.get();
    MedicalTeam* medicalPtr = medical.get();
    riverZone->addChild(std::move(shuttle));
    riverZone->addChild(std::move(medical));
    riverZone->addChild(std::move(infoDesk));

    EventGroup* mainStageZonePtr = mainStageZone.get();
    EventGroup* riverZonePtr = riverZone.get();
    root->addChild(std::move(mainStageZone));
    root->addChild(std::move(riverZone));

    std::cout << "--- Initial status (3 levels below root: zone -> sub-zone -> leaf) ---\n";
    root->reportStatus();
    std::cout << "Total capacity: " << root->getCapacity() << "\n\n";

    root->open();

    // --- Observer registration: completely separate from ownership ---
    // control stands in for EventControl in this standalone test.
    Subject control;
    control.attach(mainStageZonePtr);
    control.attach(riverZonePtr);
    mainStageZonePtr->attach(stagePtr);
    mainStageZonePtr->attach(gatePtr);
    mainStageZonePtr->attach(foodCourtPtr);   // relay one level deeper
    foodCourtPtr->attach(tacoVendorPtr);
    foodCourtPtr->attach(coffeeVendorPtr);
    riverZonePtr->attach(shuttlePtr);
    riverZonePtr->attach(medicalPtr);
    // Note: infoDesk is deliberately never attach()ed — it doesn't
    // implement Observer, so it structurally can't be.

    std::cout << "\n--- Weather alert cascades through 4 runtime levels ---\n";
    std::cout << "(control -> Main Stage Zone -> Food Court -> Coffee/Taco Vendor)\n";
    control.notify(Notice(NoticeType::WEATHER_ALERT, "Storm approaching", 80));

    // --- Runtime reorganisation: transfer Coffee Vendor between zones ---
    std::cout << "\n--- Transferring Coffee Vendor: Food Court -> River Zone ---\n";
    std::unique_ptr<EventComponent> released = foodCourtPtr->removeChild(coffeeVendorPtr);
    foodCourtPtr->detach(coffeeVendorPtr);      // leaving Food Court's notification scope
    riverZonePtr->addChild(std::move(released)); // now owned by River Zone
    riverZonePtr->attach(coffeeVendorPtr);        // joins River Zone's notification scope

    std::cout << "\n--- Status after alert + transfer ---\n";
    root->reportStatus();
    std::cout << "Total capacity unchanged by transfer: " << root->getCapacity() << "\n";

    std::cout << "\n--- Resuming ---\n";
    control.notify(Notice(NoticeType::RESUME, "All clear"));

    std::cout << "\n--- root goes out of scope now: destroys the whole owned subtree exactly once ---\n";
    // No explicit deletes anywhere. Each EventGroup's children_ vector of
    // unique_ptr<EventComponent> destroys its own children automatically,
    // recursively, when the EventGroup itself is destroyed.
    return 0;
}
