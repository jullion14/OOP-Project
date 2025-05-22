#ifndef FREIGHT_H
#define FREIGHT_H

#include <string>
#include <vector>
using namespace std;

class Freight
{
private:
    string id;
    string refuelStop;
    string refuelTime;

public:
    Freight(string id, string refuelStop, string refuelTime);
    void display() const;
    static vector<Freight> loadFromFile(const string& filename);
    string getId() const;
    string getRefuelStop() const;
    string getRefuelTime() const;

    // Time validation helper
    static bool isValidTime(const string& time);
};

#endif
