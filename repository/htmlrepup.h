
#pragma once
#include "repup.h"

class HTMLRepo : public Repository {
public:
    HTMLRepo(std::string filename) : Repository(filename) { this->loadFromFile(); }
    void saveToFile() override;
};