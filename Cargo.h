#ifndef CARGO_H
#define CARGO_H

#include <string>
#include <vector>
using namespace std;

class Cargo {
private:
    string id;
    string destination;
    string timeToReach;

public:
    Cargo(string id, string destination, string timeToReach);
    void display() const;

    // Static method to load cargos from file
    static vector<Cargo> loadFromFile(const string& filename);
};

#endif
