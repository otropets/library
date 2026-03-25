#pragma once
#include <string>
#include <vector>
class Book;
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
  bool IsUserBlocked(User &);
  void CreateRent(User &, BookCopy &);
  void EndRent(Rent *rent);
  void AddBook(Book *book);
  void AddBookCopy(BookCopy *bookCopy);
};
