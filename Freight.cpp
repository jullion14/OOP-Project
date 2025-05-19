#include "Freight.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>

using namespace std;

Freight::Freight(string id, string refuelStop, string refuelTime)
    : id(id), refuelStop(refuelStop), refuelTime(refuelTime) {
}

string Freight::getId() const 
{
    return id;
}

string Freight::getRefuelStop() const 
{
    return refuelStop;
}

string Freight::getRefuelTime() const 
{
    return refuelTime;
}


void Freight::display() const
{
    cout << left
        << setw(15) << id
        << setw(20) << refuelStop
        << setw(10) << refuelTime;
}

vector<Freight> Freight::loadFromFile(const string& filename) {
    vector<Freight> freights;
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Could not open " << filename << endl;
        return freights;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string id, refuelStop, refuelTime;
        getline(ss, id, ',');
        getline(ss, refuelStop, ',');
        getline(ss, refuelTime, ',');

        freights.emplace_back(id, refuelStop, refuelTime);
    }

    file.close();
    return freights;
}
