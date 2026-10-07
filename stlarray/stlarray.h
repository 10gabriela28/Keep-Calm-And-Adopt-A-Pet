
#pragma once
#include "dog.h"
#include <vector>

class STLArray {
private:
    std::vector<Dog> dogs;
public:
    STLArray();
    STLArray(int size, int capacity);

    auto begin() { return dogs.begin(); }
    auto end() { return dogs.end(); }
    auto begin() const { return dogs.begin(); }
    auto end() const { return dogs.end(); }

    void addDog(const Dog& d);
    void removeDog(const Dog& d);
    int getSize() const;
    Dog getAt(int pos) const;
    void updateDog(int ind, const Dog& element);
};