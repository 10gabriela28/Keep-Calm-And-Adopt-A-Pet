
#include "csvrepup.h"
#include <fstream>

using namespace std;

void CSVRepo::saveToFile() {
    ofstream f(this->filename);
    for (const auto& d : this->dogs) {
        f << d;
    }
    f.close();
}