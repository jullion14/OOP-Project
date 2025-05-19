#include "Cargo.h"
#include <vector>
using namespace std;

int main() {
    vector<Cargo> cargos = Cargo::loadFromFile("Cargo.txt");

    for (const auto& cargo : cargos) {
        cargo.display();
    }

    return 0;
}
