#include "User.h"

int User::GetUserId() { return UserId; }
std::string User::GetFirstName() { return FirstName; }
std::string User::GetLastName() { return LastName; }
std::vector<Rent *> User::GetRentedBooks() { return RentedBooks; }