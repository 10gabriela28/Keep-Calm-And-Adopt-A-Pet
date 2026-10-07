
#pragma once
#include "dog.h"
#include "../stlarray/stlarray.h"
#include <string>

class Repository {
protected:
    STLArray dogs;
    std::string filename;
public:
    Repository(std::string filename = "");
    virtual ~Repository() {}
    virtual void saveToFile(); // noteworthy. using inheritance here.
    void loadFromFile();
    void resetFile();
    void clearAll();
    bool addDog(Dog d);
    bool removeDog(Dog d);
    Dog getDog(int index) const;
    const STLArray& getDogs() const;
    STLArray& getDogs();
};