#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include "Cargo.h"
#include "Freight.h"
#include <vector>
#include <string>

class FileManager {
public:
    static std::vector<Cargo> loadCargoData(const std::string& filename);
    static std::vector<Freight> loadFreightData(const std::string& filename);
    static void display(const std::vector<Cargo>& cargos, const std::vector<Freight>& freights);

    //cargo editing functions
    static void addCargo(std::vector<Cargo>& cargos);
    static void editCargo(std::vector<Cargo>& cargos);
    static void deleteCargo(std::vector<Cargo>& cargos);

    //freight editing functions
    static void addFreight(std::vector<Freight>& freights);
    static void editFreight(std::vector<Freight>& freights);
    static void deleteFreight(std::vector<Freight>& freights);

    static void saveCargoData(const std::string& filename, const std::vector<Cargo>& cargos);
    static void saveFreightData(const std::string& filename, const std::vector<Freight>& freights);
};

#endif
