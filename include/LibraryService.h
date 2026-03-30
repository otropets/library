#pragma once
#include "Book.h"
#include "BookCopy.h"
#include "Rent.h"
#include "User.h"
#include <memory>
#include <string>
#include <vector>

class LibraryService {
private:
  std::vector<std::unique_ptr<Book>> BookList;
  std::vector<std::unique_ptr<User>> UserList;
  std::vector<std::unique_ptr<BookCopy>> BookCopyList;
  std::vector<std::unique_ptr<Rent>> RentList;

public:
  LibraryService();
  std::vector<BookCopy *> FindAvailableBookCopyByTitle(std::string);
  BookCopy *FindBookCopyById(int);

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
  User *FindUserById(int);
};
