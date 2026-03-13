#include "LibraryService.h"
#include "Book.h"
#include "BookCopy.h"
#include "Rent.h"
#include "User.h"

std::vector<BookCopy *>
LibraryService::FindBookCopyByTitle(std::string bookTitle) {
  std::vector<BookCopy *> res;
  Book *FoundBook = nullptr;
  for (auto &x : BookList) {
    std::string cur = x->GetTitle();
    if (bookTitle == cur) {
      FoundBook = x;
      break;
    }
  }
  if (FoundBook != nullptr) {
    for (auto &x : BookCopyList) {
      if (FoundBook == x->getBook()) {
        res.push_back(x);
      }
    }
  }
  return res;
}
bool LibraryService::CheckBookAvailabilityByTitle(std::string check_title) {}
bool LibraryService::CheckBookAvailabilityById(int CheckBookId) {}
bool LibraryService::CheckUserPenaltyStatus(User &user) {}
void LibraryService::CalculatePenalty(User &user) {}
void LibraryService::CreateRent(User &user, BookCopy &bookCopy) {}
void LibraryService::EndRent(User &user, BookCopy &bookCopy) {}
void LibraryService::AddBook(Book *book) { BookList.push_back(book); };
void LibraryService::AddBookCopy(BookCopy *bookCopy) {
  BookCopyList.push_back(bookCopy);
};
