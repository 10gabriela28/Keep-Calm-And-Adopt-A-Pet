
#include "ui.h"
#include "dog.h"
#include "repup.h"
#include "csvrepup.h"
#include "htmlrepup.h"
#include "adminanduser.h"
#include "service.h"
#include <iostream>
#include <cstring>
#include "validator.h"

using namespace std;

UI::UI() {
    this->service = nullptr;
    this->adoptionService = nullptr;
}

UI::~UI() {
    delete this->service;
    delete this->adoptionService;
}

void UI::admin_menu() {
    cout << "1. Add a dog." << "\n";
    cout << "2. Update any dog." << "\n";
    cout << "3. Display all of the dogs." << "\n";
    cout << "4. Log out." << "\n";
}

void UI::user_menu() {
    cout << "1. Adopt a dog." << "\n";
    cout << "2. See all the dogs of a given breed, having an age less than a given number." << "\n";
    cout << "3. See the adoption list" << "\n";
    cout << "4. See the adoption list, from the csv/html output file." << "\n";
    cout << "5. Log out." << "\n";
}

void UI::run() {

    bool m = true;
    char choice[101];
    while (m) {
        cout << "Welcome! Before we get started, in which file would you like to read your data? (CSV/HTML): ";

        cin.getline(choice, 100);

        Repository* r = nullptr;
        Repository* adopted = nullptr;

        if (strcmp(choice, "html") == 0 || strcmp(choice, "HTML") == 0) {
            r = new HTMLRepo("dogs.html");
            adopted = new HTMLRepo("adopted_dogs.html");
            this->service = new Service(r);
            this->adoptionService = new Service(adopted);
            this->service->forceReset();
            this->adoptionService->clearOnly();
            m = false;
        }
        else if (strcmp(choice, "csv") == 0 || strcmp(choice, "CSV") == 0) {
            r = new CSVRepo("dogs.csv");
            adopted = new CSVRepo("adopted_dogs.csv");
            this->service = new Service(r);
            this->adoptionService = new Service(adopted);
            this->service->forceReset();
            this->adoptionService->clearOnly();
            m = false;
        }
        else {
            cout << "ERROR - INVALID INPUT." << "\n";
        }
    }

    bool m1 = true;

    while (m1) {
        cout << "Welcome to the <<Keep Calm And Adopt A Pet>> shelter! Are you here as a staff member or a fur-parent-to-be?" << "\n";
        char n[101];
        cin.getline(n, 100);

        if (admin_logging_in(n) == 1) {
            bool m2 = true;
            cout << "Welcome, admin!" << "\n";
            while (m2) {
                admin_menu();
                char m_select[101]; // Renamed slightly to avoid conflict with bool m
                cin.getline(m_select, 100);

                try{
                    if (strcmp(m_select, "1") == 0) {
                        cout << "What breed is it?" << "\n";
                        char br[101];
                        cin.getline(br, 100);
                        cout << "What's its name?" << "\n";
                        char na[101];
                        cin.getline(na, 100);
                        cout << "How old is it?" << "\n";
                        int ag;
                        if (!(cin >> ag)) {
                            cin.clear();
                            cin.ignore(1000, '\n');
                            throw Exception("ERROR - Age must be a number!");
                        }
                        cin.ignore(1000, '\n');

                        cout << "Please provide a photograph link." << "\n";
                        char ph[1001];
                        cin.getline(ph, 1000);

                        service->addDogS(Dog(br, na, ag, ph));
                        cout << "Dog added successfully!\n";
                    }
                    else if (strcmp(m_select, "2") == 0) {
                        cout << "Which dog do you want to update? (Insert the index of the pup here.)" << "\n";
                        int ind;
                        if (!(cin >> ind)) {
                            cin.clear();
                            cin.ignore(1000, '\n');
                            throw Exception("ERROR - The index must be an integer!");
                        }

                        cin.ignore(1000, '\n');
                        if (ind >= service->getSize() || ind < 0) {
                            throw Exception("ERROR - The index can't be out of bounds!");
                        } else {
                            cout << "What do you want to update? (breed/name/age/photograph)" << "\n";
                            char answer[101];
                            cin.getline(answer, 100);

                            if (strcmp(answer, "breed") == 0) {
                                cout << "New breed: ";
                                char val[101]; cin.getline(val, 100);
                                service->updateBreed(val, ind);
                            }
                            else if (strcmp(answer, "name") == 0) {
                                cout << "New name: ";
                                char val[101]; cin.getline(val, 100);
                                service->updateName(val, ind);
                            }
                            else if (strcmp(answer, "age") == 0) {
                                cout << "New age: ";
                                int val; cin >> val; cin.ignore(1000, '\n');
                                service->updateAge(val, ind);
                            }
                            else if (strcmp(answer, "photograph") == 0) {
                                cout << "New link: ";
                                char val[1001]; cin.getline(val, 1000);
                                service->updatePhoto(val, ind);
                            }
                            else {
                                throw Exception("ERROR - Invalid input!");
                            }
                        }
                    }
                    else if (strcmp(m_select, "3") == 0) {
                        cout << "NOT ADOPTED: " << "\n";
                        service->displayAllS();
                        cout << "ADOPTED: " << "\n";
                        adoptionService->displayAllS();
                    }
                    else if (strcmp(m_select, "4") == 0) {
                        m2 = false;
                    }
                } catch (const Exception& e) {
                    cout << e.what() << endl;
                }
            }
        }
        else if (user_logging_in(n) == 1) {
            bool m3 = true;
            while (m3) {
                user_menu();
                char m_select[101];
                cin.getline(m_select, 100);

                if (strcmp(m_select, "1") == 0) {
                    int i = 0;
                    while (true) {
                        if (service->getSize() == 0) {
                            cout << "No more dogs left in the shelter!\n";
                            break;
                        }
                        Dog d = service->getDogS(i);
                        cout << "Current: " << d.getName() << " | " << d.getBreed() << " | " << d.getAge() << " years\n";
                        char ans[21];
                        cin.getline(ans, 20);

                        if (adopt(ans) == 1) {
                            adoptionService->addDogS(d);
                            service->deleteDogS(d);
                            cout << "Welcome to your new home, " << d.getName() << "!<3 \n";
                            if (service->getSize() == 0) break;
                            i = i % service->getSize();
                        } else if (strcmp(ans, "back") == 0) {
                            break;
                        } else {
                            i = (i + 1) % service->getSize();
                        }
                    }
                }
                else if (strcmp(m_select, "2") == 0) {
                    cout << "Age limit: ";
                    int x; cin >> x; cin.ignore();
                    cout << "Breed: ";
                    char br[101]; cin.getline(br, 100);
                    service->displayBreedAndAge(br, x);
                }
                else if (strcmp(m_select, "3") == 0) {
                    adoptionService->displayAllS();
                }
                else if (strcmp(m_select, "4") == 0) {
                    cout << "Opening file...";
                    if (strcmp(choice, "html")==0 || strcmp(choice, "HTML")==0) {
                        system("start adopted_dogs.html");
                    }
                    else if (strcmp(choice, "csv")==0 || strcmp(choice, "CSV")==0) {
                        system("start adopted_dogs.csv");
                    }
                }
                else if (strcmp(m_select, "5") == 0) {
                    m3 = false;
                }
            }
        }
        else if (quitting(n) == 1) {
            cout << "Would you like to see the UML diagram? (Y/N)" << "\n";
            char yesno[11];
            cin.getline(yesno, 11);
            if (strcmp(yesno, "y") == 0 || strcmp(yesno, "Y") == 0) {
                system("start UMLDiagram.png");
            }
            cout << "Goodbye!";
            m1 = false;
        }
    }
}