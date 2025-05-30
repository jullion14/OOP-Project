#include "Cargo.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <cctype>
using namespace std;

Cargo::Cargo(string id, string destination, string timeToReach)
    : id(id), destination(destination), timeToReach(timeToReach) {
}

string Cargo::getId() const { return id; }
string Cargo::getDestination() const { return destination; }
string Cargo::getTimeToReach() const { return timeToReach; }

void Cargo::display() const
{
    cout << left
        << setw(10) << id
        << setw(20) << destination
        << setw(10) << timeToReach;
}

vector<Cargo> Cargo::loadFromFile(const string& filename)
{
    vector<Cargo> cargos;
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Could not open " << filename << endl;
        return cargos;
    }
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string id, destination, time;
        getline(ss, id, ',');
        getline(ss, destination, ',');
        getline(ss, time, ',');
        cargos.emplace_back(id, destination, time);
    }
    file.close();
    return cargos;
}

// --- ADDED: Time validation implementation ---
bool Cargo::isValidTime(const string& time) {
    if (time.length() != 4) return false;
    for (char c : time) {
        if (!isdigit(c)) return false;
    }
    int hour = stoi(time.substr(0, 2));
    int min = stoi(time.substr(2, 2));
    return (hour >= 0 && hour <= 23) && (min >= 0 && min <= 59);
}
