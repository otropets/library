#include "LibraryService.h"
#include "Book.h"
#include "BookCopy.h"
#include "Rent.h"
#include "User.h"

std::vector<BookCopy *>
LibraryService::FindAvailableBookCopyByTitle(std::string BookTitle) {
  std::vector<BookCopy *> res;
  for (auto &x : BookCopyList) {
    std::string cur_book = x->getBook()->GetTitle();
    if (cur_book == BookTitle && x->GetAvailability() == true) {
      res.push_back(x);
    }
  }
  return res;
}
BookCopy *LibraryService::FindBookCopyById(int CheckBookId) {
  for (auto &x : BookCopyList) {
    int cur_book = x->GetBookCopyId();
    if (cur_book == CheckBookId) {
      return x;
    }
  }
  return nullptr;
}
bool LibraryService::IsUserBlocked(User &user) { return user.GetBalance() < 0; }
void LibraryService::CreateRent(User &user, BookCopy &bookCopy) {
  std::time_t start = std::time(nullptr);
  std::time_t end = start + (14 * 24 * 60 * 60);
  Rent *rent = new Rent(user, bookCopy, start, end, false);
  RentList.push_back(rent);
  user.AddRent(rent);
  bookCopy.SetAvailability(false);
}
void LibraryService::EndRent(Rent *rent) {
  if (rent->IsOverdue()) {
    time_t now = std::time(nullptr);
    time_t end = rent->GetEndDate();
    int days = (now - end) / (24 * 60 * 60);
    rent->GetUser().AddToBalance(-(days));
  }
  rent->GetUser().RemoveRent(rent);
  RentList.erase(std::remove(RentList.begin(), RentList.end(), rent),
                 RentList.end());
  rent->GetBookCopy().SetAvailability(true);
  delete rent;
};
void LibraryService::AddBook(Book *book) { BookList.push_back(book); };
void LibraryService::AddBookCopy(BookCopy *bookCopy) {
  BookCopyList.push_back(bookCopy);
};
