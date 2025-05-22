#ifndef CARGO_H
#define CARGO_H

#include <string>
#include <vector>
using namespace std;

class Cargo
{
private:
    string id;
    string destination;
    string timeToReach;

public:
    Cargo(string id, string destination, string timeToReach);
    static vector<Cargo> loadFromFile(const string& filename);
    void display() const;
    string getId() const;
    string getDestination() const;
    string getTimeToReach() const;

    static bool isValidTime(const string& time);
};

#endif
