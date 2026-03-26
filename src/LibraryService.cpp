#include "LibraryService.h"
#include "Book.h"
#include "BookCopy.h"
#include "Librarian.h"
#include "Rent.h"
#include "Student.h"
#include "Teacher.h"
#include "User.h"
#include "algorithm"

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

bool LibraryService::CreateBook(int bookId, std::string title,
                                std::string author, Language lang) {
  Book *book = new Book(bookId, title, author, lang);
  BookList.push_back(book);
  return true;
}
bool LibraryService::DeleteBook(Book *book) {
  BookList.erase(std::remove(BookList.begin(), BookList.end(), book),
                 BookList.end());
  delete book;
  return true;
}
bool LibraryService::AddBookCopy(int BookCopyId, Book &book) {
  BookCopy *bc = new BookCopy(BookCopyId, book);
  BookCopyList.push_back(bc);
  return true;
}
bool LibraryService::DeleteBookCopy(BookCopy *bookCopy) {
  BookCopyList.erase(
      std::remove(BookCopyList.begin(), BookCopyList.end(), bookCopy),
      BookCopyList.end());
  delete bookCopy;
  return true;
}
bool LibraryService::IsUserBlocked(User &user) { return user.GetBalance() < 0; }

bool LibraryService::BorrowBookCopy(User &user, BookCopy &bookCopy) {
  if (user.GetBalance() < 0) {
    return false;
  }
  if (user.GetRentedBooks().size() >= user.GetMaxBooksAmount()) {
    return false;
  }
  if (!bookCopy.GetAvailability()) {
    return false;
  }
  std::time_t start = std::time(nullptr);
  std::time_t end = start + (14 * 24 * 60 * 60);
  Rent *rent = new Rent(user, bookCopy, start, end);
  RentList.push_back(rent);
  user.AddRent(rent);
  bookCopy.SetAvailability(false);
  return true;
}

bool LibraryService::ReturnBookCopy(Rent *rent) {
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
  return true;
}

bool LibraryService::CreateStudent(int UserId, std::string FirstName,
                                   std::string LastName, int StudentId) {
  User *new_user = new Student(UserId, FirstName, LastName, StudentId);
  UserList.push_back(new_user);
  return true;
}
bool LibraryService::CreateTeacher(int UserId, std::string FirstName,
                                   std::string LastName, int TeacherId) {
  User *new_user = new Teacher(UserId, FirstName, LastName, TeacherId);
  UserList.push_back(new_user);
  return true;
}
bool LibraryService::CreateLibrarian(int UserId, std::string FirstName,
                                     std::string LastName, int LibrarianId) {
  User *new_user = new Librarian(UserId, FirstName, LastName, LibrarianId);
  UserList.push_back(new_user);
  return true;
}
bool LibraryService::DeleteUser(User *user) {
  UserList.erase(std::remove(UserList.begin(), UserList.end(), user),
                 UserList.end());
  delete user;
  return true;
};

bool LibraryService::PayPenalty(User &user) {
  user.AddToBalance(-user.GetBalance());
  return true;
}
LibraryService::~LibraryService() {
  for (auto book : BookList)
    delete book;
  for (auto copy : BookCopyList)
    delete copy;
  for (auto rent : RentList)
    delete rent;
  for (auto user : UserList)
    delete user;
}