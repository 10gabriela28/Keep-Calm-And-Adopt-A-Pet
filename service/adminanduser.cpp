
#include "dog.h"
#include "repup.h"
#include "adminanduser.h"
#include <iostream>
#include <cstring>
#include <cstdlib>

using namespace std;



int admin_logging_in(char n[]) {
    if (strcmp(n, "admin")==0 || strcmp(n, "Admin")==0 || strcmp(n, "ADMIN")==0 ||
        strcmp(n, "administrator")==0 || strcmp(n, "Administrator")==0 || strcmp(n, "ADMINISTRATOR")==0) {
        return 1;
        }
    return 0;
}


int user_logging_in(char n[]) {
    if (strcmp(n, "user")==0 || strcmp(n, "User")==0 || strcmp(n, "USER")==0) {
        return 1;
    }
    return 0;
}


int adopt(char n[]) {
    if (strcmp(n, "adopt")==0 || strcmp(n, "Adopt")==0 || strcmp(n, "ADOPT")==0) {
        return 1;
    }
    return 0;
}


int dontadopt(char n[]) {
    if (strcmp(n, "don't adopt")==0 || strcmp(n, "Don't adopt")==0 || strcmp(n, "DON'T ADOPT")==0) {
        return 1;
    }
    return 0;
}


int quitting(char n[]) {
    if (strcmp(n, "quit")==0 || strcmp(n, "Quit")==0 || strcmp(n, "QUIT")==0) {
        return 1;
    }
    return 0;
}


int display(char n[]) {
    if (strcmp(n, "display")==0 || strcmp(n, "Display")==0 || strcmp(n, "DISPLAY")==0) {
        return 1;
    }
    return 0;
}


int getListLength(char n[]) {
    if (strcmp(n, "get list length")==0 || strcmp(n, "Get list length")==0 || strcmp(n, "GET LIST LENGTH")==0) {
        return 1;
    }
    return 0;
}

