
#include "dog.h"
#include <iostream>
#include <string>

using namespace std;

std::ostream& operator<<(std::ostream& os, const Dog& d) {
    os << d.breed << "," << d.name << "," << d.age << "," << d.photograph << "\n";
    return os;
}

std::istream& operator>>(std::istream& is, Dog& d) {
    string breed, name, ageStr, photo;
    if (getline(is, breed, ',')) {
        getline(is, name, ',');
        getline(is, ageStr, ',');
        getline(is, photo);
        if (!breed.empty()) {
            d.breed = breed;
            d.name = name;
            try {
                d.age = stoi(ageStr);
            } catch(...) {
                d.age = 0;
            }
            d.photograph = photo;
        }
    }
    return is;
}

Dog::Dog() {
    this->breed = "";
    this->name = "";
    this->age = 0;
    this->photograph = "";
}

Dog::Dog(const string& breed, const string& name, int age, const string& photograph) {
    this->breed = breed;
    this->name = name;
    this->age = age;
    this->photograph = photograph;
}

string Dog::getBreed() const {
    return breed;
}
string Dog::getName() const {
    return name;
}
int Dog::getAge() const {
    return age;
}
string Dog::getPhotograph() const {
    return photograph;
}

void Dog::setBreed(const string& breed) {
    this->breed = breed;
}
void Dog::setName(const string& name) {
    this->name = name;
}
void Dog::setAge(int age) {
    this->age = age;
}
void Dog::setPhotograph(const string& photograph) {
    this->photograph = photograph;
}


// TO-DO LIST:
//1. Display the dogs, one by one. my idea would be to be able to
//switch back and forth in case i wanna go back to seeing one of the previous pups.
//2&3. Choose to adopt the dog. If it's adopted, it'll be added in a list of the adopted fur babies.
//my idea would be a classic approach. The user input would have to input "adopt/Adopt/ADOPT"
//to adopt the puppy and "don't adopt/Don't adopt/DON'T ADOPT". There will be a "double-check"
//implemented ("Are you sure?"). Maybe I'll add more. :)
//4. Display all dogs of a certain breed, that are less than X years old. No breed provided = displaying all dogs.
//5. See the list of all adopted pups.

//PHOTOS OF DOGS:
//1. Maltese Poodle - NAME: Pooma
//https://dogacademy.org/blog/wp-content/uploads/2022/08/Maltese-poodle-sitting-still-with-white-background.jpg

//2. Dachshund - NAME: Larry
//https://th.bing.com/th/id/R.a6e302c3603aaf1eab3137573921d371?rik=aPXoWY%2bDDGJZLQ&riu=http%3a%2f%2fdikerdachs.com%2fportal%2fwp-content%2fuploads%2f2014%2f04%2fW_Jonna_039.jpg&ehk=58bUplde%2bUKSOWJlYSKxchBzU4GevEJfE1XuiXYjKkQ%3d&risl=&pid=ImgRaw&r=0

//3. Mallinois - NAME: Daring
//https://dogtime.com/wp-content/uploads/sites/12/2024/04/IMG_1941.jpeg?resize=1200,630

//4. Armstaff - NAME: Lucky
//https://cdn.pixabay.com/photo/2019/09/20/20/09/dog-4492516_1280.jpg

//5. Bucovina Shepherd Dog - NAME: Bellus
//https://www.petpaw.com.au/wp-content/uploads/2012/11/Bucovina-Shepherd-Dog1.jpg

//6. Husky - NAME: Aurora (Borealis)
//https://www.publicdomainpictures.net/pictures/490000/velka/siberian-husky-hund-hund-1676119906doa.jpg

//7. Pug - NAME: Teddy
//https://images.petpress.net/wp-content/uploads/2020/02/16.jpg?strip=all&lossy=1&w=662&ssl=1

//8. Dwarf Schnauzer - NAME: Freddy
//https://th.bing.com/th/id/R.6447f525c1b2aa95f2fed2e5fd3d491e?rik=z1Bx6QnBIkeDsw&riu=http%3a%2f%2fanimalsbreeds.com%2fwp-content%2fuploads%2f2014%2f07%2fMiniature-Schnauzer.jpg&ehk=6SYfUEzYpuxJVHuYZKNqL8fqGjYyw0ZMORGnnvjX2uI%3d&risl=&pid=ImgRaw&r=0

//9. Golden Retriever - NAME: Nugget
//https://iheartgoldens.com/wp-content/uploads/2023/08/everything-you-need-to-know-about-golden-retriever-rescue-in-massachusetts-adoption-success-stories-and-how-to-get-involved.webp

//10. No particular breed - NAME: Alphie
//https://th.bing.com/th/id/R.91e4154ef67f59f770201e116ab81232?rik=TFO4tnntnNc9rA&pid=ImgRaw&r=0