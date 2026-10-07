
#pragma once
#include "dog.h"
#include "stlarray.h"
#include "repup.h"
#include <string>

int admin_logging_in(char n[]);
int user_logging_in(char n[]);
int quitting(char n[]);
void addDog();
void deleteDog();
void displayAll();
int display(char n[]);
void admin_menu();
void user_menu();
int adopt(char n[]);
int dontadopt(char n[]);
int getListLength(char n[]);



