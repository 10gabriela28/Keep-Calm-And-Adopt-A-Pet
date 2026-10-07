// #include <iostream>
// #include <cstdlib>
// #include <cassert>
// #include <cstring>
// #include "dog.h"
// #include "repup.h"
// #include "service.h"
// #include "dynamicarray.h"
// #include "testingallfunctionalities.h"
// #include "adminanduser.h"
//
// using namespace std;
//
// void test_dynamic_array_deep_copy() {
//     DynamicArray v1(1);
//     v1.addDog(Dog("B1", "N1", 1, "P1"));
//     v1.addDog(Dog("B2", "N2", 2, "P2"));
//     v1.addDog(Dog("B3", "N3", 3, "P3"));
//     assert(v1.getSize() == 3);
//
//     DynamicArray v2 = v1;
//     assert(v2.getSize() == 3);
//     assert(v2.getAt(2).getName() == "N3");
//
//     DynamicArray v3(10);
//     v3 = v1;
//     assert(v3.getSize() == 3);
//
//     v3 = v3;
//     assert(v3.getSize() == 3);
// }
//
// void test_dog() {
//     Dog d("Poodle", "Buddy", 3, "nophotograph");
//     assert(d.getBreed() == "Poodle");
//     assert(d.getName() == "Buddy");
//     assert(d.getAge() == 3);
//     assert(d.getPhotograph() == "nophotograph");
//
//     Dog d2;
//     assert(d2.getAge() == 0);
// }
//
// void test_repository_core() {
//     Repository testRepo;
//     Dog d("Rottweiler", "Eddie", 6, "P1");
//
//     assert(testRepo.addDog(d) == true);
//     assert(testRepo.getDogs().getSize() == 1);
//
//     testRepo.removeDog(d);
//     assert(testRepo.getDogs().getSize() == 0);
// }
//
// void test_repository_updates_exhaustive() {
//     Service testServ;
//     testServ.addDogS(Dog("Breed", "Name", 5, "Photo"));
//     char val[] = "NewVal";
//     char empty[] = "";
//
//     assert(testServ.updateBreed(val, 0) == true);
//     assert(testServ.updateName(val, 0) == true);
//     assert(testServ.updateAge(10, 0) == true);
//     assert(testServ.updatePhoto(val, 0) == true);
//
//     assert(testServ.updateBreed(empty, 0) == false);
//     assert(testServ.updateAge(-1, 0) == false);
//
//     assert(testServ.updateBreed(val, -1) == false);
//     assert(testServ.updateBreed(val, 1) == false);
//     assert(testServ.updateName(val, -1) == false);
//     assert(testServ.updateName(val, 1) == false);
//     assert(testServ.updateAge(5, -1) == false);
//     assert(testServ.updateAge(5, 1) == false);
//     assert(testServ.updatePhoto(val, -1) == false);
//     assert(testServ.updatePhoto(val, 1) == false);
// }
//
// void test_display_and_filter() {
//     Service testServ;
//     testServ.addDogS(Dog("Corgi", "Loaf", 2, "P1"));
//
//     char br[] = "Corgi";
//     char emptyBr[] = "";
//     char wrongBr[] = "Husky";
//
//     assert(testServ.displayBreedAndAge(br, 5) == true);
//     assert(testServ.displayBreedAndAge(br, 1) == true);
//     assert(testServ.displayBreedAndAge(wrongBr, 10) == true);
//     assert(testServ.displayBreedAndAge(emptyBr, 10) == false);
//
//     testServ.displayAllS();
// }
//
// void test_input_helpers_comprehensive() {
//     assert(admin_logging_in("admin") == 1);
//     assert(admin_logging_in("Admin") == 1);
//     assert(admin_logging_in("ADMIN") == 1);
//     assert(admin_logging_in("administrator") == 1);
//     assert(admin_logging_in("Administrator") == 1);
//     assert(admin_logging_in("ADMINISTRATOR") == 1);
//     assert(admin_logging_in("x") == 0);
//
//     assert(user_logging_in("user") == 1);
//     assert(user_logging_in("User") == 1);
//     assert(user_logging_in("USER") == 1);
//     assert(user_logging_in("x") == 0);
//
//     assert(adopt("adopt") == 1);
//     assert(adopt("Adopt") == 1);
//     assert(adopt("ADOPT") == 1);
//     assert(adopt("x") == 0);
//
//     assert(dontadopt("don't adopt") == 1);
//     assert(dontadopt("Don't adopt") == 1);
//     assert(dontadopt("DON'T ADOPT") == 1);
//     assert(dontadopt("x") == 0);
//
//     assert(quitting("quit") == 1);
//     assert(quitting("Quit") == 1);
//     assert(quitting("QUIT") == 1);
//     assert(quitting("x") == 0);
//
//     assert(display("display") == 1);
//     assert(display("Display") == 1);
//     assert(display("DISPLAY") == 1);
//     assert(display("x") == 0);
//
//     assert(getListLength("get list length") == 1);
//     assert(getListLength("Get list length") == 1);
//     assert(getListLength("GET LIST LENGTH") == 1);
//     assert(getListLength("x") == 0);
// }
//
// void testAllFunctionalities() {
//     test_dog();
//     test_dynamic_array_deep_copy();
//     test_repository_core();
//     test_repository_updates_exhaustive();
//     test_display_and_filter();
//     test_input_helpers_comprehensive();
// }