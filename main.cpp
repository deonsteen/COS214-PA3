#include <iostream>
#include <memory>

#include "EventControl.h"
#include "EventGroup.h"
#include "EventRules.h"

#include "Stage.h"
#include "Gate.h"
#include "Vendor.h"
#include "MedicalTeam.h"
#include "ShuttleStop.h"
#include "InformationDesk.h"

int main()
{
   
    // Composite ownership and Observer registration are deliberately
    // separate. addChild() controls ownership only.

    std::unique_ptr<EventGroup> root(
        new EventGroup("City Lights Festival")
    );

    //Main Stage Zone

    std::unique_ptr<EventGroup> mainStageZone(
        new EventGroup("Main Stage Zone")
    );

    std::unique_ptr<Stage> stage(
        new Stage("Main Stage", 5000)
    );

    std::unique_ptr<Gate> gate(
        new Gate("Front Gate", 2000)
    );

    //keep non-owning pointers before moving ownership
    Stage* stagePtr = stage.get();
    Gate* gatePtr = gate.get();

    mainStageZone->addChild(std::move(stage));
    mainStageZone->addChild(std::move(gate));

    //Food Court

    std::unique_ptr<EventGroup> foodCourt(
        new EventGroup("Food Court")
    );

    std::unique_ptr<Vendor> tacoVendor(
        new Vendor("Taco Vendor", 50)
    );

    std::unique_ptr<Vendor> coffeeVendor(
        new Vendor("Coffee Vendor", 30)
    );

    Vendor* tacoVendorPtr = tacoVendor.get();
    Vendor* coffeeVendorPtr = coffeeVendor.get();

    foodCourt->addChild(std::move(tacoVendor));
    foodCourt->addChild(std::move(coffeeVendor));

    EventGroup* foodCourtPtr = foodCourt.get();

    mainStageZone->addChild(std::move(foodCourt));

    //River Zone 

    std::unique_ptr<EventGroup> riverZone(
        new EventGroup("River Zone")
    );

    std::unique_ptr<ShuttleStop> shuttle(
        new ShuttleStop("Shuttle Stop", 100)
    );

    std::unique_ptr<MedicalTeam> medical(
        new MedicalTeam("Medical Team", 20)
    );

    std::unique_ptr<InformationDesk> infoDesk(
        new InformationDesk("River Info Desk", 10)
    );

    ShuttleStop* shuttlePtr = shuttle.get();
    MedicalTeam* medicalPtr = medical.get();

    riverZone->addChild(std::move(shuttle));
    riverZone->addChild(std::move(medical));
    riverZone->addChild(std::move(infoDesk));

    //keep pointers to the groups before ownership moves to root
    EventGroup* mainStageZonePtr = mainStageZone.get();
    EventGroup* riverZonePtr = riverZone.get();

    root->addChild(std::move(mainStageZone));
    root->addChild(std::move(riverZone));

    //create the real eventcontrol
 
    EventControl control;

    //EventControl does not own the tree, it stores a non-owning pointer to the root
    control.setRoot(root.get());

    //establish observer registrations
    //(registration is deliberately separate from Composite ownership)

    control.attach(mainStageZonePtr);
    control.attach(riverZonePtr);

    //main stage zone observers
    mainStageZonePtr->attach(stagePtr);
    mainStageZonePtr->attach(gatePtr);
    mainStageZonePtr->attach(foodCourtPtr);

    //food court observers
    foodCourtPtr->attach(tacoVendorPtr);
    foodCourtPtr->attach(coffeeVendorPtr);

    //river zone observers
    riverZonePtr->attach(shuttlePtr);
    riverZonePtr->attach(medicalPtr);

    //informationDesk deliberately does not implement Observer and is structurally owned without being registered

    //composite query / initial status

    std::cout << "-Initial Event Status\n";

    control.reportEventStatus();

    std::cout << "\nTotal event capacity: "
              << control.getTotalCapacity()
              << "\n\n";

    //recursively opens the complete Composite tree
    std::cout << "Opening Event\n";

    root->open();

    // Notice 1: wheather alert
    // original EventRules feature: derive the appropriate Notice from measured wind speed

    std::cout << "\nWheather Monitoring\n";

    const int moderateWindSpeed = 75;
    const int evacuationThreshold = 90;

    Notice weatherNotice =
        EventRules::deriveWeatherNotice(
            moderateWindSpeed,
            evacuationThreshold
        );

    std::cout << "Measured wind speed: "
              << moderateWindSpeed
              << " km/h\n";

    control.issueNotice(weatherNotice);

   // Condition-Based Capacity Decision

    // This supplies the condition needed for Task 4.3 / SD3

    // getCapacity() represents rated aggregate capacity, not current live occupancy

    std::cout << "\n-Capacity Rule Check\n";

    const int capacityThreshold = 7000;

    int mainZoneCapacity = mainStageZonePtr->getCapacity();

    std::cout << "Main Stage Zone aggregate capacity: "
              << mainZoneCapacity
              << "\n";

    std::cout << "Configured threshold: "
              << capacityThreshold
              << "\n";

    if (EventRules::isOverCapacityThreshold(
            *mainStageZonePtr,
            capacityThreshold))
    {
        std::cout
            << "Condition [capacity >= threshold] is TRUE.\n";

        Notice capacityNotice(
            NoticeType::CAPACITY_ALERT,
            "Configured zone capacity threshold reached",
            mainZoneCapacity
        );

        
        control.issueNotice(capacityNotice);
    }
    else
    {
        std::cout
            << "Condition [else]: capacity threshold not reached.\n";
    }
    
    // runtime reorganisation


    // the final argument true means its Observer registration moves with it as part of this particular runtime operation
    //
    // Composite ownership and Observer registration remain separate
    // internally: removeChild/addChild and detach/attach are distinct.

    std::cout << "\nRuntime Reorganisation\n";
    std::cout
        << "Moving Coffee Vendor from Food Court to River Zone...\n";

    bool transferred =
        EventRules::transferUnit(
            *foodCourtPtr,
            *riverZonePtr,
            coffeeVendorPtr,
            true
        );

    if (transferred)
    {
        std::cout
            << "Coffee Vendor transferred successfully.\n";
    }
    else
    {
        std::cout
            << "Coffee Vendor transfer failed.\n";
    }

    std::cout << "\n-Status After Transfer\n";

    control.reportEventStatus();

    std::cout
        << "\nTotal event capacity after transfer: "
        << control.getTotalCapacity()
        << "\n";

    //Notice 3: Critical Weather / Evacuation


    // the same EventRules operation now produces evacuate  because wind exceeds the configured threshold

    std::cout << "\nCritical Weather Escalation\n";

    const int criticalWindSpeed = 105;

    Notice evacuationNotice =
        EventRules::deriveWeatherNotice(
            criticalWindSpeed,
            evacuationThreshold
        );

    std::cout
        << "Measured wind speed: "
        << criticalWindSpeed
        << " km/h\n";

    
    control.issueNotice(evacuationNotice);

    // EventControl never checks any concrete type.
    
    //show current subject state

    std::cout << "\nCurrent Control Notice\n";

    const Notice& currentNotice =
        control.getCurrentNotice();

    std::cout
        << "Current notice description: "
        << currentNotice.description
        << "\n";

    std::cout
        << "Current notice severity: "
        << currentNotice.severity
        << "\n";

    // Notice 4: Recovery / Resume

    std::cout << "\nEvent Recovery\n";

    Notice resumeNotice(
        NoticeType::RESUME,
        "Conditions declared safe, resume normal operations"
    );

    // NOTICE 4
    control.issueNotice(resumeNotice);

    
    //Final event status

    std::cout << "\nFinal Operational Status\n";

    control.reportEventStatus();

    //Clean Shutdown
    
    std::cout << "\n-Closing Event\n";

    root->close();

    std::cout << "\nFinal Closed Status\n";

    control.reportEventStatus();

    std::cout
        << "\nEventFlow simulation complete.\n"
        << "The root Composite will now leave scope.\n"
        << "Its unique_ptr-owned subtree is destroyed recursively "
        << "exactly once.\n";

    return 0;
}