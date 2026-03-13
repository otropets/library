#pragma once
#include <ctime>

class User;
class BookCopy;

class Rent {
private:
  BookCopy &bookCopy;
  User &user;
  std::time_t StartDate;
  std::time_t EndDate;
  bool PenaltyPaid;

public:
  Rent(BookCopy &BookCopy, User &User, std::time_t StartDate,
       std::time_t EndDate, bool PenaltyPaid)
      : bookCopy(BookCopy), user(User), StartDate(StartDate), EndDate(EndDate),
        PenaltyPaid(PenaltyPaid) {};

  User &GetUser();
  BookCopy &GetBookCopy();
  std::time_t GetStartDate();
  std::time_t GetEndDate();
  bool GetPenaltyPaid();
  bool IsOverdue();
};
