#include "FileManager.h"
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <fstream>
using namespace std;

vector<Cargo> FileManager::loadCargoData(const string& filename) 
{
    return Cargo::loadFromFile(filename);
}

vector<Freight> FileManager::loadFreightData(const string& filename) 
{
    return Freight::loadFromFile(filename);
}

//function to display freight and cargo information
//-------------------------------------------------------------------------------------------------//
void FileManager::display(const vector<Cargo>& cargos, const vector<Freight>& freights)
{
    cout << left << setw(10) << "Cargo ID" << setw(20) << "Destination" << setw(10) << "Time"
        << string(4, ' ')
        << setw(15) << "Freight ID" << setw(20) << "Refuel Stop" << setw(10) << "Refuel Time"
        << endl
        << string(34, '-') << string(10, ' ') << string(46, '-')
        << endl;

    size_t maxRows = max(cargos.size(), freights.size());
    for (size_t i = 0; i < maxRows; ++i) {
        if (i < cargos.size())
            cargos[i].display();
        else
            cout << setw(40) << " ";

        cout << string(4, ' ');

        if (i < freights.size())
            freights[i].display();

        cout << endl;
    }
}
//-------------------------------------------------------------------------------------------------//

void FileManager::addCargo(std::vector<Cargo>& cargos)
{
    string id, destination, time;
    cout << "Enter new Cargo ID: ";
    cin >> id;
    cout << "Enter Destination: ";
    cin.ignore(); getline(cin, destination);
    cout << "Enter Time to Reach: ";
    cin >> time;

    cargos.emplace_back(id, destination, time);
    cout << "Cargo added successfully.\n";
}

void FileManager::editCargo(vector<Cargo>& cargos)
{
    string id;
    cout << "Enter Cargo ID to edit: ";
    cin >> id;

    for (auto& cargo : cargos)
    {
        if (cargo.getId() == id)
        {
            string newDest, newTime;
            cout << "Enter new Destination: ";
            cin.ignore(); getline(cin, newDest);
            cout << "Enter new Time: ";
            cin >> newTime;
            cargo = Cargo(id, newDest, newTime);
            cout << "Cargo updated.\n";
            return;
        }
    }
    cout << "Cargo not found.\n";
}

void FileManager::deleteCargo(vector<Cargo>& cargos)
{
    string id;
    cout << "Enter Cargo ID to delete: ";
    cin >> id;

    for (auto it = cargos.begin(); it != cargos.end(); ++it)
    {
        if (it->getId() == id)
        {
            cargos.erase(it);
            cout << "Cargo deleted.\n";
            return;
        }
    }
    cout << "Cargo not found.\n";
}

void FileManager::addFreight(vector<Freight>& freights)
{
    string id, stop, time;
    cout << "Enter new Freight ID: ";
    cin >> id;
    cout << "Enter Refuel Stop: ";
    cin.ignore(); getline(cin, stop);
    cout << "Enter Refuel Time: ";
    cin >> time;

    freights.emplace_back(id, stop, time);
    cout << "Freight added successfully.\n";
}

void FileManager::editFreight(vector<Freight>& freights)
{
    string id;
    cout << "Enter Freight ID to edit: ";
    cin >> id;

    for (auto& freight : freights)
    {
        if (freight.getId() == id)
        {
            string newStop, newTime;
            cout << "Enter new Refuel Stop: ";
            cin.ignore(); getline(cin, newStop);
            cout << "Enter new Refuel Time: ";
            cin >> newTime;
            freight = Freight(id, newStop, newTime);
            cout << "Freight updated.\n";
            return;
        }
    }
    cout << "Freight not found.\n";
}

void FileManager::deleteFreight(vector<Freight>& freights)
{
    string id;
    cout << "Enter Freight ID to delete: ";
    cin >> id;

    for (auto it = freights.begin(); it != freights.end(); ++it)
    {
        if (it->getId() == id) {
            freights.erase(it);
            cout << "Freight deleted.\n";
            return;
        }
    }
    cout << "Freight not found.\n";
}

void FileManager::saveCargoData(const std::string& filename, const vector<Cargo>& cargos) {
    ofstream outFile(filename);
    for (const auto& cargo : cargos) {
        outFile << cargo.getId() << ","
            << cargo.getDestination() << ","
            << cargo.getTimeToReach() << endl;
    }
    outFile.close();
}

void FileManager::saveFreightData(const std::string& filename, const vector<Freight>& freights) {
    ofstream outFile(filename);
    for (const auto& freight : freights) {
        outFile << freight.getId() << ","
            << freight.getRefuelStop() << ","
            << freight.getRefuelTime() << endl;
    }
    outFile.close();
}


