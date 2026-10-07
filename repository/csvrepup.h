
#pragma once
#include "repup.h"

class CSVRepo : public Repository {
public:
    CSVRepo(std::string filename) : Repository(filename) { this->loadFromFile(); }
    void saveToFile() override;
};