
#include "htmlrepup.h"
#include <fstream>

using namespace std;

void HTMLRepo::saveToFile() {
    ofstream f(this->filename);
    f << "<!DOCTYPE html>\n<html><head><title>Adoption List</title></head><body>\n";
    f << "<table border=\"1\">\n";
    f << "<tr><td>Breed</td><td>Name</td><td>Age</td><td>Photograph</td></tr>\n";

    for (int i = 0; i < this->dogs.getSize(); i++) {
        Dog d = this->dogs.getAt(i);
        f << "<tr>\n";
        f << "<td>" << d.getBreed() << "</td>\n";
        f << "<td>" << d.getName() << "</td>\n";
        f << "<td>" << d.getAge() << "</td>\n";
        f << "<td><a href=\"" << d.getPhotograph() << "\">Link</a></td>\n";
        f << "</tr>\n";
    }

    f << "</table></body></html>";
    f.close();
}