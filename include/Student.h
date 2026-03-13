#pragma once
#include "User.h"

class Student : public User {
private:
  int StudentId;

public:
  Student(int UserId, std::string FirstName, std::string LastName,
          LibraryService &libraryService, int StudentId)
      : User(UserId, FirstName, LastName, libraryService),
        StudentId(StudentId) {};
  int GetMaxBooksAmount() override;
  int GetStudentId();
  void BorrowBook();
  void ReturnBook();
  void PayPenalty();
};