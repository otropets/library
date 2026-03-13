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

protected:
  LibraryService &libraryService;

public:
  User(int UserId, std::string FirstName, std::string LastName,
       LibraryService &libraryService, std::vector<Rent *> RentedBooks = {})
      : UserId(UserId), FirstName(FirstName), LastName(LastName),
        libraryService(libraryService), RentedBooks(RentedBooks) {};
  int GetUserId();
  virtual int GetMaxBooksAmount() = 0;
  std::string GetFirstName();
  std::string GetLastName();
  std::vector<Rent *> GetRentedBooks();
  virtual ~User() = default;
};

// функції, які будуть мати спільну логіку для всіх наслідуючих файлів
// імплементується тут ті, які відрізняються імплементацією стають virtual = 0;
// якщо не обовязково імплементовувати то virtual

// мусить бути віртуальний деструктор, це викликатиме в наслідуючих класах їх
// власні деструктори а не ~User