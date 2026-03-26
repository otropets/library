#pragma once
#include "Book.h"
class BookCopy {
private:
  int BookCopyId;
  Book &book;
  bool availability;

public:
  BookCopy(int BookCopyId, Book &book)
      : BookCopyId(BookCopyId), book(book), availability(true) {};
  int GetBookCopyId();
  Book *getBook();
  bool GetAvailability();
  ~BookCopy() {};
  void SetAvailability(bool availability);
};