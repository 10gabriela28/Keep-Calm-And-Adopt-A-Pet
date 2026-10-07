
#include "stlarray.h"
#include <algorithm>

STLArray::STLArray() {}

STLArray::STLArray(int size, int capacity) {
    if (capacity > 0) dogs.reserve(capacity);
    if (size > 0) dogs.resize(size);
}

void STLArray::addDog(const Dog &d) {
    dogs.push_back(d);
}

void STLArray::removeDog(const Dog &d) {
    auto it = std::find_if(dogs.begin(), dogs.end(), [&d](const Dog& currentDog) {
        return currentDog.getName() == d.getName() && currentDog.getBreed() == d.getBreed();
    });
    if (it != dogs.end()) {
        dogs.erase(it);
    }
}

int STLArray::getSize() const {
    return dogs.size();
}

Dog STLArray::getAt(int pos) const {
    return dogs.at(pos);
}

void STLArray::updateDog(int ind, const Dog& element) {
    if (ind >= 0 && ind < dogs.size()) {
        dogs[ind] = element;
    }
}

