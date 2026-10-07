
#pragma once
#include <string>
#include <iostream>

class Dog {
private:
    std::string breed;
    std::string name;
    int age;
    std::string photograph;
public:
    friend std::ostream& operator<<(std::ostream& os, const Dog& d);
    friend std::istream& operator>>(std::istream& is, Dog& d);

    Dog();
    Dog(const std::string& breed, const std::string& name, int age, const std::string& photograph);

    std::string getBreed() const;
    std::string getName() const;
    int getAge() const;
    std::string getPhotograph() const;

    void setBreed(const std::string& breed);
    void setName(const std::string& name);
    void setAge(int age);
    void setPhotograph(const std::string& photograph);
};
