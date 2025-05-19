#include "FileManager.h"
#include "Scheduler.h"
#include <iostream>
#include <string>
using namespace std;


int main() 
{
    Scheduler scheduler;
    vector<Cargo> cargos = FileManager::loadCargoData("Cargo.txt");
    vector<Freight> freights = FileManager::loadFreightData("Freight.txt");

    int choice;

    do {
        cout 
        << "\n========== MAIN MENU ==========\n" << endl
	    << "1. View Cargo" << endl
	    << "2. View Schedule" << endl
        << "3. Add Cargo" << endl
        << "4. Edit Cargo" << endl
        << "5. Delete Cargo" << endl
        << "6. Add Freight" << endl
        << "7. Edit Freight" << endl
        << "8. Delete Freight" << endl 
        << "9. Generate & View Schedule" << endl
        << "10. Save Schedule to File" << endl
        << "11. Exit" << endl
        << "\nSelect an option: ";
        cin >> choice;

        // Clear bad input if any
        if (cin.fail()) 
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number." << endl;
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
        {
			scheduler.saveScheduleToFile();
            break;
        }

        case 11:
            char saveChoice;
            cout << "Would you like to save changes before exiting? (Y/N): ";
            cin >> saveChoice;

            while (saveChoice != 'Y' && saveChoice != 'y' && saveChoice != 'N' && saveChoice != 'n')
            {
                cout << "Please enter Y or N: ";
                cin >> saveChoice;
            }

            if (saveChoice == 'Y' || saveChoice == 'y')
            {
                FileManager::saveCargoData("Cargo.txt", cargos);
                FileManager::saveFreightData("Freight.txt", freights);
                cout << "Data saved successfully. Exiting..." << endl;
            }
            else
            {
                cout << "Exiting without saving changes." << endl;
            }

            break;

        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 11);

    return 0;
}


