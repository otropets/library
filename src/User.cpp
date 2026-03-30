#include "User.h"

int User::GetUserId() { return UserId; }
std::string User::GetFirstName() { return FirstName; }
std::string User::GetLastName() { return LastName; }
std::vector<Rent *> User::GetRentedBooks() { return RentedBooks; }
void User::AddRent(Rent *rent) { RentedBooks.push_back(rent); }
double User::GetBalance() { return balance; }
void User::AddToBalance(double add) { balance += add; }
UserType User::GetUserType() { return userType; }
void User::RemoveRent(Rent *rent) {
  RentedBooks.erase(std::remove(RentedBooks.begin(), RentedBooks.end(), rent),
                    RentedBooks.end());
}
