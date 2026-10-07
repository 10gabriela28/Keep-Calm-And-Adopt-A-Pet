
#pragma once
#include "repup.h"
#include "validator.h"
#include <string>
#include <vector>

class Service {
private:
    Repository* repo;
public:
    Service(Repository* repo);

    void forceReset();
    void clearOnly();
    int addDogS(const Dog& d);
    int deleteDogS(const Dog& d);
    void displayAllS();
    int displayBreedAndAge(const std::string& br, int x);
    int updateBreed(const std::string& br, int ind);
    int updateName(const std::string& na, int ind);
    int updateAge(int age, int ind);
    int updatePhoto(const std::string& ph, int ind);
    int getSize() const;
    STLArray getAll() const;
    Dog getDogS(int index) const;
};