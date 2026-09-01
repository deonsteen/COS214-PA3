# EventFlow - COS214 Practical 3

EventFlow is a C++11 event management system demonstrating the Composite and Observer design patterns.

The system models the City Lights Festival as a hierarchy of event areas and units. The Composite pattern manages the event structure, while the Observer pattern allows event notices to be distributed to registered event units.

## Team Members

- [Deon] - Composite / Structure
- [Logan] - Observer / Notification
- [Danel] - Behaviour / Integration

## Design Overview

### Composite Pattern

- `EventComponent` - Component
- `EventGroup` - Composite
- `EventUnit` - Leaf base class
- `Stage`, `Gate`, `Vendor`, `ShuttleStop`, `MedicalTeam`, `InformationDesk` - Concrete event units

`EventGroup` owns its children using `std::unique_ptr<EventComponent>` and supports recursive operations such as opening, closing, reporting status and calculating capacity.

### Observer Pattern

- `Observer` - Observer interface
- `Subject` - Subject abstraction
- `EventControl` - Event-level coordinator / Subject
- `EventGroup` - Both Observer and Subject

Selected event units implement `Observer` and react differently to notices such as weather alerts, capacity alerts, evacuation notices and resume notices.

Composite ownership and Observer registration are kept separate.

## Build

From the project directory run:

```bash
make