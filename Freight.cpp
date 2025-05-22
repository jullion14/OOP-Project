#include "Freight.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <cctype>
using namespace std;

Freight::Freight(string id, string refuelStop, string refuelTime)
    : id(id), refuelStop(refuelStop), refuelTime(refuelTime) {
}

string Freight::getId() const { return id; }
string Freight::getRefuelStop() const { return refuelStop; }
string Freight::getRefuelTime() const { return refuelTime; }

void Freight::display() const
{
    cout << left
        << setw(15) << id
        << setw(20) << refuelStop
        << setw(10) << refuelTime;
}

vector<Freight> Freight::loadFromFile(const string& filename)
{
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

// Time validation implementation
bool Freight::isValidTime(const string& time) {
    if (time.length() != 4) return false;
    for (char c : time) {
        if (!isdigit(c)) return false;
    }
    int hour = stoi(time.substr(0, 2));
    int min = stoi(time.substr(2, 2));
    return (hour >= 0 && hour <= 23) && (min >= 0 && min <= 59);
}
