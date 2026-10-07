
#pragma once
#include "dog.h"
#include <stdexcept>
#include <string>
#include <exception>

class Exception : public std::runtime_error {
    public:
    Exception(const std::string &message) : std::runtime_error(message) {}
};

class DogValidator {
public:
    static void validate(const Dog& d) {
        std::string errors = "";
        if (d.getBreed().empty()) {
            errors += "ERROR - Breed cannot be empty!\n";
        }
        if (d.getName().empty()) {
            errors += "ERROR - Name cannot be empty!\n";
        }
        if (d.getAge() < 0) {
            errors += "ERROR - The age cannot be a negative integer!\n";
        }
        if (d.getPhotograph().empty()) {
            errors += "ERROR - You must provide a photograph of the dog!\n";
        }

        if (!errors.empty()) {
            throw Exception("VALIDATION ERRORS: \n" + errors);
        }
    }
};