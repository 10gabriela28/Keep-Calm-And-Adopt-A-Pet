
#pragma once
#include "service.h"

class UI {
private:
    Service* service;
    Service* adoptionService;

    void admin_menu();
    void user_menu();

public:
    UI();
    ~UI();
    void run();
};