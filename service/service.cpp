
#include <iostream>
#include <algorithm>
#include "service.h"
#include "validator.h"

using namespace std;

Service::Service(Repository* repo) {
    this->repo = repo;
}

void Service::forceReset() {
    this->repo->loadFromFile();
    if (this->repo->getDogs().getSize() > 0) {
        return;
    }

    this->addDogS(Dog("Maltese Poodle", "Pooma", 2, "https://dogacademy.org/blog/wp-content/uploads/2022/08/Maltese-poodle-sitting-still-with-white-background.jpg"));
    this->addDogS(Dog("Dachshund", "Larry", 4, "https://th.bing.com/th/id/R.a6e302c3603aaf1eab3137573921d371?rik=aPXoWY%2bDDGJZLQ&riu=http%3a%2f%2fdikerdachs.com%2fportal%2fwp-content%2fuploads%2f2014%2f04%2fW_Jonna_039.jpg&ehk=58bUplde%2bUKSOWJlYSKxchBzU4GevEJfE1XuiXYjKkQ%3d&risl=&pid=ImgRaw&r=0"));
    this->addDogS(Dog("Mallinois", "Daring", 3, "https://dogtime.com/wp-content/uploads/sites/12/2024/04/IMG_1941.jpeg?resize=1200,630"));
    this->addDogS(Dog("Armstaff", "Lucky", 5, "https://cdn.pixabay.com/photo/2019/09/20/20/09/dog-4492516_1280.jpg"));
    this->addDogS(Dog("Bucovina Shepherd", "Bellus", 6, "https://www.petpaw.com.au/wp-content/uploads/2012/11/Bucovina-Shepherd-Dog1.jpg"));
    this->addDogS(Dog("Husky", "Aurora", 2, "https://www.publicdomainpictures.net/pictures/490000/velka/siberian-husky-hund-hund-1676119906doa.jpg"));
    this->addDogS(Dog("Pug", "Teddy", 1, "https://images.petpress.net/wp-content/uploads/2020/02/16.jpg?strip=all&lossy=1&w=662&ssl=1"));
    this->addDogS(Dog("Dwarf Schnauzer", "Freddy", 4, "https://th.bing.com/th/id/R.6447f525c1b2aa95f2fed2e5fd3d491e?rik=z1Bx6QnBIkeDsw&riu=http%3a%2f%2fanimalsbreeds.com%2fwp-content%2fuploads%2f2014%2f07%2fMiniature-Schnauzer.jpg&ehk=6SYfUEzYpuxJVHuYZKNqL8fqGjYyw0ZMORGnnvjX2uI%3d&risl=&pid=ImgRaw&r=0"));
    this->addDogS(Dog("Golden Retriever", "Nugget", 2, "https://iheartgoldens.com/wp-content/uploads/2023/08/everything-you-need-to-know-about-golden-retriever-rescue-in-massachusetts-adoption-success-stories-and-how-to-get-involved.webp"));
    this->addDogS(Dog("Mixed Breed", "Alphie", 3, "https://th.bing.com/th/id/R.91e4154ef67f59f770201e116ab81232?rik=TFO4tnntnNc9rA&pid=ImgRaw&r=0"));
}

void Service::clearOnly() {
    this->repo->resetFile();
    this->repo->clearAll();
}

int Service::addDogS(const Dog& d) {
    DogValidator::validate(d);

    for (const auto& d1 : this->repo->getDogs()) {
        if (d1.getName() == d.getName() && d1.getBreed() == d.getBreed()) {
            throw Exception("ERROR - This dog already exists in the shelter!");
        }
    }
    this->repo->addDog(d);
    return true;
}

int Service::deleteDogS(const Dog& d) {
    this->repo->removeDog(d);
    return true;
}

void Service::displayAllS() {
    int count = 1;
    for (const auto& d : this->repo->getDogs()) {
        cout << "DOG NO. " << count++ << ": " << d.getName() << " | "
             << d.getBreed() << " | " << d.getAge() << " years | "
             << d.getPhotograph() << endl;
    }
}

int Service::displayBreedAndAge(const std::string &br, int x) {
    if (br.empty()) {
        displayAllS();
        return -1;
    }

    std::vector<Dog> filtered;
    auto& allDogs = this->repo->getDogs();

    std::copy_if(allDogs.begin(), allDogs.end(), back_inserter(filtered),
        [&br, x](const Dog& d) {
            return d.getBreed() == br && d.getAge() < x;
        });

    int count = 1;
    for (const auto& d : filtered) {
        cout << "DOG NO. " << count++ << ": " << d.getName() << " | " << d.getBreed() << endl;
    }
    if (count == 1) {
        cout << "There isn't any dog meeting this criteria registered in the database!"<<"\n";
    }
    return 1;
}

int Service::updateBreed(const std::string &br, int ind) {
    if (ind < 0 || ind >= this->repo->getDogs().getSize()) {
       throw Exception("ERROR - The index cannot be out of bounds!");
    }
    Dog d = this->repo->getDogs().getAt(ind);
    d.setBreed(br);
    this->repo->getDogs().updateDog(ind, d);
    this->repo->saveToFile(); // Calls the specific CSV or HTML save automatically
    return true;
}

int Service::updateName(const std::string& na, int ind) {
    if (ind < 0 || ind >= this->repo->getDogs().getSize()) {
        throw Exception("ERROR - The index cannot be out of bounds!");
    }
    Dog d = this->repo->getDogs().getAt(ind);
    d.setName(na);
    this->repo->getDogs().updateDog(ind, d);
    this->repo->saveToFile();
    return true;
}

int Service::updateAge(int age, int ind) {
    if (ind < 0 || ind >= this->repo->getDogs().getSize()) {
        throw Exception("ERROR - The index cannot be out of bounds!");
    }
    Dog d = this->repo->getDogs().getAt(ind);
    d.setAge(age);
    this->repo->getDogs().updateDog(ind, d);
    this->repo->saveToFile();
    return true;
}

int Service::updatePhoto(const std::string& ph, int ind) {
    if (ind < 0 || ind >= this->repo->getDogs().getSize()) {
        throw Exception("ERROR - The index cannot be out of bounds!");
    }
    Dog d = this->repo->getDogs().getAt(ind);
    d.setPhotograph(ph);
    this->repo->getDogs().updateDog(ind, d);
    this->repo->saveToFile();
    return true;
}

int Service::getSize() const {
    return this->repo->getDogs().getSize();
}
STLArray Service::getAll() const {
    return this->repo->getDogs();
}

Dog Service::getDogS(int index) const {
    return this->repo->getDog(index);
}