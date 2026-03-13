#pragma once
#include "Book.h"
#include "LibraryService.h"
#include "User.h"
class LibraryService;
class Librarian : public User {
private:
  int LibrarianId;

public:
  Librarian(int UserId, std::string FirstName, std::string LastName,
            int LibrarianId, LibraryService &LibraryService)
      : User(UserId, FirstName, LastName, libraryService),
        LibrarianId(LibrarianId) {};
  int GetLibrarianId();
  void CreateBook(int bookId, std::string title, std::string author,
                  Language lang);
  void AddBookCopy();
  void DeleteBook();
  int GetMaxBooksAmount() override;
};