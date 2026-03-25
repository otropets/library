#pragma once
#include <string>
#include <vector>

class Rent;
class LibraryService;
class User {
private:
  int UserId;
  std::string FirstName;
  std::string LastName;
  std::vector<Rent *> RentedBooks;
  double balance;

protected:
  LibraryService &libraryService;

public:
  User(int UserId, std::string FirstName, std::string LastName,
       LibraryService &libraryService, std::vector<Rent *> RentedBooks = {})
      : UserId(UserId), FirstName(FirstName), LastName(LastName),
        libraryService(libraryService), RentedBooks(RentedBooks) {};
  int GetUserId();
  void AddRent(Rent *rent);
  void RemoveRent(Rent *rent);
  virtual int GetMaxBooksAmount() = 0;
  std::string GetFirstName();
  std::string GetLastName();
  std::vector<Rent *> GetRentedBooks();
  virtual ~User() = default;
  double GetBalance();
  void AddToBalance(double add);
};
