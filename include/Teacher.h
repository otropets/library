#pragma once
#include "User.h"

class Teacher : public User {
private:
  int TeacherId;

public:
  Teacher(int UserId, std::string FirstName, std::string LastName,
          int TeacherId)
      : User(UserId, FirstName, LastName, TEACHER), TeacherId(TeacherId) {};

  int GetMaxBooksAmount() override;
  int GetTeacherId();
};