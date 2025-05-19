#include "Scheduler.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <sstream>
using namespace std;

void Scheduler::generateSchedule(const vector<Freight>& freights, const vector<Cargo>& cargos) 
{
    matches.clear();
    unmatchedFreights.clear();
    unassignedCargos.clear();

    vector<bool> cargoAssigned(cargos.size(), false);

    for (const auto& freight : freights) 
    {
        bool matched = false;
        for (size_t i = 0; i < cargos.size(); ++i) 
        {
            if (!cargoAssigned[i] &&
                cargos[i].getDestination() == freight.getRefuelStop() &&
                cargos[i].getTimeToReach() >= freight.getRefuelTime()) {
                matches[freight.getId()] = cargos[i].getId();
                cargoAssigned[i] = true;
                matched = true;
                break;
            }
        }
        if (!matched) 
        {
            unmatchedFreights.push_back(freight);
        }
    }

    for (size_t i = 0; i < cargos.size(); ++i) 
    {
        if (!cargoAssigned[i]) 
        {
            unassignedCargos.push_back(cargos[i]);
        }
    }
}

void Scheduler::displayScheduleFromFile() const
{
    ifstream inFile("schedule.txt");
    if (!inFile) 
    {
        cerr << "Error: Could not open schedule.txt for reading.\n";
        return;
    }

    cout << "\n===== Schedule File Content (schedule.txt) =====\n\n";

    string line;
    enum Section { MATCHED, UNMATCHED, UNASSIGNED, NONE } section = NONE;

    while (getline(inFile, line)) 
    {
        if (line.empty()) {
            cout << endl;
            continue;
        }

        if (line.find("Matched Schedules:") != string::npos) 
        {
            cout << "Matched Schedules:\n";
            section = MATCHED;
            continue;
        }
        else if (line.find("Unmatched Freights:") != string::npos) 
        {
            cout << "\nUnmatched Freights:\n";
            cout << string(40, '-') << "\n";
            section = UNMATCHED;
            continue;
        }
        else if (line.find("Unassigned Cargos:") != string::npos) 
        {
            cout << "\nUnassigned Cargos:\n";
            cout << string(40, '-') << "\n";
            section = UNASSIGNED;
            continue;
        }

        if (line.find("Freight ID") != string::npos ||
            line.find("ID,Refuel Stop,Time") != string::npos ||
            line.find("ID,Destination,Time") != string::npos) 
        {
            continue; 
        }

        if (section == MATCHED && line.find(',') != string::npos && line.find("F") == 0) 
        {
            if (line == "F01,C01") 
            { 
                cout << left << setw(15) << "Freight ID" << setw(15) << "Cargo ID" << "\n";
                cout << string(30, '-') << "\n";
            }
        }

        // Parse CSV line
        stringstream ss(line);
        string part1, part2, part3;
        getline(ss, part1, ',');
        getline(ss, part2, ',');
        getline(ss, part3, ',');

        switch (section) 
        {
        case MATCHED:
            cout << left << setw(15) << part1 << setw(15) << part2 << "\n";
            break;
        case UNMATCHED:
            cout << left << setw(10) << part1 << setw(20) << part2 << setw(10) << part3 << "\n";
            break;
        case UNASSIGNED:
            cout << left << setw(10) << part1 << setw(20) << part2 << setw(10) << part3 << "\n";
            break;
        default:
            break;
        }
    }

    inFile.close();
}


void Scheduler::displayUnmatchedFreights() const 
{
    cout << "\nUnmatched Freights:\n";
    cout << left
        << setw(10) << "ID"
        << setw(20) << "Refuel Stop"
        << setw(10) << "Time" << endl;
    cout << string(40, '-') << endl;

    for (const auto& freight : unmatchedFreights) 
    {
        cout << left
            << setw(10) << freight.getId()
            << setw(20) << freight.getRefuelStop()
            << setw(10) << freight.getRefuelTime()
            << endl;
    }
}

void Scheduler::displayUnassignedCargos() const 
{
    cout << "\nUnassigned Cargos:\n";
    cout << left
        << setw(10) << "ID"
        << setw(20) << "Destination"
        << setw(10) << "Time" << endl;
    cout << string(40, '-') << endl;

    for (const auto& cargo : unassignedCargos) 
    {
        cout << left
            << setw(10) << cargo.getId()
            << setw(20) << cargo.getDestination()
            << setw(10) << cargo.getTimeToReach()
            << endl;
    }
}

void Scheduler::saveScheduleToFile() const 
{
    ofstream outFile("schedule.txt");

    if (!outFile) 
    {
        cerr << "Error: Unable to open schedule.txt for writing.\n";
        return;
    }

    outFile << "Matched Schedules:\n";

    outFile << left
        << setw(15) << "Freight ID"
        << setw(15) << "Cargo ID" << "\n"
        << string(30, '-') << "\n";

    for (const auto& pair : matches) 
    {
        outFile << setw(15) << pair.first
            << setw(15) << pair.second << "\n";
    }

    outFile << "\nUnmatched Freights:\n"
        << setw(10) << "ID"
        << setw(20) << "Refuel Stop"
        << setw(10) << "Time" << "\n"
        << string(40, '-') << "\n";

    for (const auto& freight : unmatchedFreights) 
    {
        outFile << setw(10) << freight.getId()
            << setw(20) << freight.getRefuelStop()
            << setw(10) << freight.getRefuelTime()
            << "\n";
    }

    outFile << "\nUnassigned Cargos:\n"
        << setw(10) << "ID"
        << setw(20) << "Destination"
        << setw(10) << "Time" << "\n"
        << string(40, '-') << "\n";

    for (const auto& cargo : unassignedCargos) 
    {
        outFile << setw(10) << cargo.getId()
            << setw(20) << cargo.getDestination()
            << setw(10) << cargo.getTimeToReach()
            << "\n";
    }

    outFile.close();
    cout << "Schedule saved to schedule.txt\n";
}

void Scheduler::displayScheduleFromMemory() const 
{
    cout << "\nMatched Schedules:\n";
    cout << left << setw(15) << "Freight ID" << setw(15) << "Cargo ID" << "\n";
    cout << string(30, '-') << "\n";
    for (const auto& pair : matches) 
    {
        cout << setw(15) << pair.first << setw(15) << pair.second << "\n";
    }

    cout << "\nUnmatched Freights:\n";
    cout << left << setw(10) << "ID" << setw(20) << "Refuel Stop" << setw(10) << "Time" << "\n";
    cout << string(40, '-') << "\n";
    for (const auto& freight : unmatchedFreights) 
    {
        cout << setw(10) << freight.getId()
            << setw(20) << freight.getRefuelStop()
            << setw(10) << freight.getRefuelTime() << "\n";
    }

    cout << "\nUnassigned Cargos:\n";
    cout << left << setw(10) << "ID" << setw(20) << "Destination" << setw(10) << "Time" << "\n";
    cout << string(40, '-') << "\n";
    for (const auto& cargo : unassignedCargos) 
    {
        cout << setw(10) << cargo.getId()
            << setw(20) << cargo.getDestination()
            << setw(10) << cargo.getTimeToReach() << "\n";
    }
}



