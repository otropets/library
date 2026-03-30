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
  LibraryService();
  std::vector<BookCopy *> FindAvailableBookCopyByTitle(std::string);
  BookCopy *FindBookCopyById(int);

  //+
  bool CreateBook(User &, int, std::string, std::string, Language);
  bool DeleteBook(User &, int);

  bool AddBookCopy(User &, int, int);
  bool DeleteBookCopy(User &, int);

  bool BorrowBookCopy(User &, int BookCopyId);
  bool ReturnBookCopy(User &cur_user, int bookCopyId);

  bool CreateStudent(User &cur_user, int UserId, std::string FirstName,
                     std::string LastName, int StudentId);

  bool CreateTeacher(User &, int, std::string, std::string, int);
  bool CreateLibrarian(User &, int, std::string, std::string, int);

  bool DeleteUser(User &, User *);
  bool PayPenalty(User &);
  bool IsUserBlocked(User &);
  ~LibraryService();
  User *FindUserById(int);
};
