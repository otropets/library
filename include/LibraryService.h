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
  std::vector<BookCopy *> FindBookCopyByTitle(std::string);
  bool CheckBookAvailabilityByTitle(std::string);
  bool CheckBookAvailabilityById(int);
  bool CheckUserPenaltyStatus(User &);
  void CalculatePenalty(User &);
  void CreateRent(User &, BookCopy &);
  void EndRent(User &, BookCopy &);
  void AddBook(Book *);
  void AddBookCopy(BookCopy *);
};
