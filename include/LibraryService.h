#pragma once
#include "Book.h"
#include <string>
#include <vector>
class User;
class BookCopy;
class Rent;

class LibraryService {
private:
  std::vector<Book *> BookList;
  std::vector<User *> UserList;
  std::vector<BookCopy *> BookCopyList;
  std::vector<Rent *> RentList;

public:
  std::vector<BookCopy *> FindAvailableBookCopyByTitle(std::string);
  BookCopy *FindBookCopyById(int);

  bool CreateBook(int bookId, std::string title, std::string author,
                  Language lang);
  bool DeleteBook(Book *book);

  bool AddBookCopy(int BookCopyId, Book &book);
  bool DeleteBookCopy(BookCopy *bookCopy);

  bool BorrowBookCopy(User &user, BookCopy &bookCopy);
  bool ReturnBookCopy(Rent *rent);

  bool CreateStudent(int UserId, std::string FirstName, std::string LastName,
                     int StudentId);
  bool CreateTeacher(int UserId, std::string FirstName, std::string LastName,
                     int TeacherId);
  bool CreateLibrarian(int UserId, std::string FirstName, std::string LastName,
                       int LibrarianId);
  bool DeleteUser(User *user);

  bool PayPenalty(User &user);
  bool IsUserBlocked(User &);
};
