#include "Cargo.h"
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

Cargo::Cargo(string id, string destination, string timeToReach)
    : id(id), destination(destination), timeToReach(timeToReach) {
}

void Cargo::display() const {
    cout << "Cargo ID: " << id
        << ", Destination: " << destination
        << ", Time to Reach: " << timeToReach << endl;
}

vector<Cargo> Cargo::loadFromFile(const string& filename) {
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
