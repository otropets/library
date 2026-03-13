#pragma once
#include "User.h"

class Teacher : public User {
private:
  int TeacherId;

public:
  Teacher(int UserId, std::string FirstName, std::string LastName,
          LibraryService &libraryService, int TeacherId)
      : User(UserId, FirstName, LastName, libraryService),
        TeacherId(TeacherId) {};

  int GetMaxBooksAmount() override;
  int GetTeacherId();
  void BorrowBook();
  void ReturnBook();
  void PayPenalty();
};