#pragma once
#include <ctime>

class User;
class BookCopy;

class Rent {
private:
  int rentId;
  BookCopy &bookCopy;
  User &user;
  std::time_t StartDate;
  std::time_t EndDate;

public:
  Rent(User &User, int rentid, BookCopy &BookCopy, std::time_t StartDate,
       std::time_t EndDate)
      : bookCopy(BookCopy), rentId(rentid), user(User), StartDate(StartDate),
        EndDate(EndDate) {};

  User &GetUser();
  int GetRentId();
  BookCopy &GetBookCopy();
  std::time_t GetStartDate();
  std::time_t GetEndDate();
  bool IsOverdue();
};
