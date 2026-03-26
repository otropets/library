#pragma once
#include "User.h"

class BookCopy;

class Student : public User {
private:
  int StudentId;

public:
  Student(int UserId, std::string FirstName, std::string LastName,
          int StudentId)
      : User(UserId, FirstName, LastName, STUDENT), StudentId(StudentId) {};
  int GetMaxBooksAmount() override;
  int GetStudentId();
};