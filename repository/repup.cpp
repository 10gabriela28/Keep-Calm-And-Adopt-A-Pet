
#include "repup.h"
#include <fstream>

Repository::Repository(std::string filename) : filename(filename) {
    this->clearAll();
    this->loadFromFile();
}

void Repository::resetFile() {
    std::ofstream myFile(this->filename);
    myFile.close();
}

void Repository::clearAll() {
    this->dogs = STLArray();
}

void Repository::saveToFile() {
    std::ofstream f(this->filename);
    for (const auto& d : this->dogs) {
        f << d;
    }
    f.close();
}

void Repository::loadFromFile() {
    std::ifstream f(this->filename);
    if (!f.is_open()) return;

    this->clearAll();

    Dog d;
    while (f >> d) {
        this->dogs.addDog(d);
    }
    f.close();
}

bool Repository::addDog(Dog d) {
    this->dogs.addDog(d);
    this->saveToFile();
    return true;
}

bool Repository::removeDog(Dog d) {
    this->dogs.removeDog(d);
    this->saveToFile();
    return true;
}

Dog Repository::getDog(int index) const {
    return this->dogs.getAt(index);
}

const STLArray& Repository::getDogs() const {
    return this->dogs;
}

STLArray& Repository::getDogs() {
    return this->dogs;
}