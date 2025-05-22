#ifndef USE_GUI
#pragma comment(linker, "/SUBSYSTEM:CONSOLE") // expects ordinary main()

#include "FileManager.h"
#include "Scheduler.h"
#include <iostream>
#include <string>
#include <vector>
#include <limits>   // for numeric_limits
#include <cctype>   // for tolower

using namespace std;

// askYesNo: keeps prompting until user types Y or N (case-insensitive).
// Returns 'y' or 'n'.
// It also clears any leftover newline from the previous cin >> ... call.
static char askYesNo(const string& prompt)
{
    // clear leftover newline from previous cin>>
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    while (true)
    {
        cout << prompt << " (Y/N): ";
        string line;
        if (!getline(cin, line))    // EOF -> treat as 'n'
            return 'n';

        // find first non-whitespace
        size_t pos = line.find_first_not_of(" \t\r\n");
        if (pos == string::npos)
            continue;

        char c = static_cast<char>(tolower(static_cast<unsigned char>(line[pos])));
        if (c == 'y' || c == 'n')
            return c;

        cout << "Please enter Y or N and press Enter.\n";
    }
}

int main()
{
    Scheduler scheduler;
    vector<Cargo> cargos = FileManager::loadCargoData("Cargo.txt");
    vector<Freight> freights = FileManager::loadFreightData("Freight.txt");

    int choice = 0;
    do
    {
        cout << "\n========== MAIN MENU ==========\n\n"
            << "1.  View Cargo\n"
            << "2.  View Schedule\n"
            << "3.  Add Cargo\n"
            << "4.  Edit Cargo\n"
            << "5.  Delete Cargo\n"
            << "6.  Add Freight\n"
            << "7.  Edit Freight\n"
            << "8.  Delete Freight\n"
            << "9.  Generate & View Schedule\n"
            << "10. Save Schedule to File\n"
            << "11. Exit\n\n"
            << "Select an option: ";
        cin >> choice;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number.\n";
            continue;
        }

        switch (choice)
        {
        case 1:
            FileManager::display(cargos, freights);
            break;
        case 2:
            scheduler.displayScheduleFromFile();
            break;
        case 3:
            FileManager::addCargo(cargos);
            break;
        case 4:
            FileManager::editCargo(cargos);
            break;
        case 5:
            FileManager::deleteCargo(cargos);
            break;
        case 6:
            FileManager::addFreight(freights);
            break;
        case 7:
            FileManager::editFreight(freights);
            break;
        case 8:
            FileManager::deleteFreight(freights);
            break;
        case 9:
            scheduler.generateSchedule(freights, cargos);
            scheduler.displayScheduleFromMemory();
            break;
        case 10:
            scheduler.saveScheduleToFile();
            break;
        case 11:
        {
            char saveChoice = askYesNo("Would you like to save changes before exiting?");
            if (saveChoice == 'y')
            {
                FileManager::saveCargoData("Cargo.txt", cargos);
                FileManager::saveFreightData("Freight.txt", freights);
                cout << "Data saved successfully. Exiting...\n";
            }
            else
            {
                cout << "Exiting without saving changes.\n";
            }
            break;
        }
        default:
            cout << "Invalid choice. Please try again.\n";
            break;
        }
    } while (choice != 11);

    return 0;
}

#endif
