#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "Cargo.h"
#include "Freight.h"
#include <vector>
#include <map>
#include <string>
#include <iostream>

using namespace std;

class Scheduler {
private:
    std::map<string, string> matches; // FreightID -> CargoID
    std::vector<Freight> unmatchedFreights;
    std::vector<Cargo> unassignedCargos;

public:
    void generateSchedule(const vector<Freight>& freights, const vector<Cargo>& cargos);
    void displayScheduleFromFile() const;
    void displayScheduleFromMemory() const;
    void displayUnmatchedFreights() const;
    void displayUnassignedCargos() const;
    void saveScheduleToFile() const;

};

#endif
