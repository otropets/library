#pragma once
#include <string>
#include <vector>
enum UserType { STUDENT, TEACHER, LIBRARIAN };
class Rent;
class BookCopy;
class User {
private:
  int UserId;
  std::string FirstName;
  std::string LastName;
  std::vector<Rent *> RentedBooks;
  double balance;

protected:
  UserType userType;

public:
  User(int UserId, std::string FirstName, std::string LastName,
       UserType userType, std::vector<Rent *> RentedBooks = {})
      : UserId(UserId), FirstName(FirstName), LastName(LastName),
        userType(userType), RentedBooks(RentedBooks) {};
  int GetUserId();
  void AddRent(Rent *rent);
  void RemoveRent(Rent *rent);
  virtual int GetMaxBooksAmount() = 0;
  std::string GetFirstName();
  std::string GetLastName();
  std::vector<Rent *> GetRentedBooks();
  double GetBalance();
  void AddToBalance(double add);
  virtual ~User() = default;
  UserType GetUserType();
};
