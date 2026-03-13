#pragma once
#include "Book.h"
class BookCopy {
private:
  int BookCopyId;
  Book &book;
  bool availability;

public:
  BookCopy(int BookCopyId, Book &book, bool availability)
      : BookCopyId(BookCopyId), book(book), availability(availability) {};
  int GetBookCopyId();
  Book *getBook();
  bool GetAvailability();
  ~BookCopy() {};
};