CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -pedantic

TARGET = eventflow

SOURCES = \
	EventComponent.cpp \
	EventGroup.cpp \
	EventUnit.cpp \
	Gate.cpp \
	InformationDesk.cpp \
	MedicalTeam.cpp \
	ShuttleStop.cpp \
	Stage.cpp \
	Vendor.cpp \
	Subject.cpp \
	EventControl.cpp \
	EventRules.cpp \
	main.cpp

OBJECTS = $(SOURCES:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)

.PHONY: all clean