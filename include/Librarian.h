#pragma once
#include "Book.h"
#include "User.h"

class Librarian : public User {
private:
  int LibrarianId;

public:
  Librarian(int UserId, std::string FirstName, std::string LastName,
            int LibrarianId)
      : User(UserId, FirstName, LastName, LIBRARIAN),
        LibrarianId(LibrarianId) {};
  int GetLibrarianId();
  int GetMaxBooksAmount() override;
};