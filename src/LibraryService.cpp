#include "LibraryService.h"
#include "Book.h"
#include "BookCopy.h"
#include "Librarian.h"
#include "Rent.h"
#include "Student.h"
#include "Teacher.h"
#include "User.h"
#include <algorithm>
#include <iostream>

LibraryService::LibraryService() {
  UserList.push_back(std::make_unique<Librarian>(1, "Admin", "Librarian", 1));
}
std::vector<BookCopy *>
LibraryService::FindAvailableBookCopyByTitle(std::string BookTitle) {
  std::vector<BookCopy *> res;
  for (auto &x : BookCopyList) {
    std::string cur_book = x->getBook()->GetTitle();
    if (cur_book == BookTitle && x->GetAvailability() == true) {

      res.push_back(x.get());
    }
  }
  return res;
}

BookCopy *LibraryService::FindBookCopyById(int CheckBookId) {
  for (auto &x : BookCopyList) {
    int cur_book = x->GetBookCopyId();
    if (cur_book == CheckBookId) {
      return x.get();
    }
  }
  return nullptr;
}

bool LibraryService::CreateBook(User &cur_user, int bookId, std::string title,
                                std::string author, Language lang) {
  if (cur_user.GetUserType() != LIBRARIAN) {
    std::cout << "Permission declined" << std::endl;
    return false;
  }
  for (auto &x : BookList) {
    if (x->GetBookId() == bookId) {
      std::cout << "Book with such ID already exists!" << std::endl;
      return false;
    }
  }
  BookList.push_back(std::make_unique<Book>(bookId, title, author, lang));
  std::cout << "Book " << title << " was succesfully created" << std::endl;
  return true;
}
bool LibraryService::DeleteBook(User &cur_user, int bookId) {
  if (cur_user.GetUserType() != LIBRARIAN) {
    std::cout << "Permission declined" << std::endl;
    return false;
  }
  for (auto &rent : RentList) {
    if (rent->GetBookCopy().getBook()->GetBookId() == bookId) {
      std::cout << "Cannot delete, book has active rents" << std::endl;
      return false;
    }
  }
  for (auto it = BookList.begin(); it != BookList.end(); it++) {
    if ((*it)->GetBookId() == bookId) {
      std::cout << "Book " << (*it)->GetTitle() << " was succesfully deleted"
                << std::endl;
      BookList.erase(it);
      return true;
    }
  }

  return true;
}
bool LibraryService::AddBookCopy(User &cur_user, int BookCopyId, int bookId) {
  if (cur_user.GetUserType() != LIBRARIAN) {
    std::cout << "Permission declined" << std::endl;
    return false;
  }
  for (auto &x : BookCopyList) {
    if (x->GetBookCopyId() == BookCopyId) {
      std::cout << "Book copy with such ID already exists!" << std::endl;
      return false;
    }
  }

  for (auto it = BookList.begin(); it != BookList.end(); it++) {
    if ((*it)->GetBookId() == bookId) {
      BookCopyList.push_back(std::make_unique<BookCopy>(BookCopyId, **it));
      std::cout << "Book copy of " << (**it).GetTitle()
                << " was succesfully created" << std::endl;
      return true;
    }
  }
  return false;
}
bool LibraryService::DeleteBookCopy(User &cur_user, int bookCopyId) {
  if (cur_user.GetUserType() != LIBRARIAN) {
    std::cout << "Permission declined" << std::endl;
    return false;
  }
  for (auto &rent : RentList) {
    if (rent->GetBookCopy().GetBookCopyId() == bookCopyId) {
      std::cout << "Cannot delete, book copy has active rent" << std::endl;
      return false;
    }
  }
  for (auto it = BookCopyList.begin(); it != BookCopyList.end(); it++) {
    if ((*it)->GetBookCopyId() == bookCopyId) {
      std::cout << "Book copy of " << (**it).getBook()->GetTitle()
                << " was succesfully deleted" << std::endl;
      BookCopyList.erase(it);
      return true;
    }
  }
  return false;
}
bool LibraryService::IsUserBlocked(User &user) {
  if (user.GetBalance() < 0) {
    std::cout << "User is BLOCKED from borrowing books. Low funds" << std::endl;
  } else {
    std::cout << "User is NOT blocked from borrowing books" << std::endl;
  }
  return user.GetBalance() < 0;
}

bool LibraryService::BorrowBookCopy(User &user, int BookCopyId) {
  BookCopy *bc = FindBookCopyById(BookCopyId);
  if (bc == nullptr) {
    std::cout << "No book found with such id" << std::endl;
    return false;
  }
  if (!bc->GetAvailability()) {
    std::cout << "Book is not available" << std::endl;
    return false;
  }
  if (user.GetBalance() < 0) {
    std::cout << "Low balance, unable to borrow book" << std::endl;
    return false;
  }
  if (user.GetRentedBooks().size() >= user.GetMaxBooksAmount()) {
    std::cout << "Too many books borrowed" << std::endl;
    return false;
  }

  std::time_t start = std::time(nullptr);
  std::time_t end = start + (14 * 24 * 60 * 60);
  int rentId = RentList.size() + 1;
  RentList.push_back(std::make_unique<Rent>(user, rentId, *bc, start, end));
  user.AddRent(RentList.back().get());
  bc->SetAvailability(false);
  std::cout << "Book " << bc->getBook()->GetTitle()
            << " was succesfully borrowed" << std::endl;
  return true;
}

bool LibraryService::ReturnBookCopy(User &cur_user, int bookCopykId) {
  for (auto it = RentList.begin(); it != RentList.end(); it++) {
    if (&(*it)->GetUser() == &cur_user &&
        (*it)->GetBookCopy().GetBookCopyId() == bookCopykId) {
      (*it)->GetBookCopy().SetAvailability(true);
      if ((*it)->IsOverdue()) {
        time_t now = std::time(nullptr);
        time_t end = (*it)->GetEndDate();
        int days = (now - end) / (24 * 60 * 60);
        (*it)->GetUser().AddToBalance(-(days));
      }
      (*it)->GetUser().RemoveRent((*it).get());
      RentList.erase(it);
      std::cout << "Book Copy was succesfully returned" << std::endl;
      return true;
    }
  }
  std::cout << "Book Copy was not  returned. Error" << std::endl;
  return false;
}

bool LibraryService::CreateStudent(User &cur_user, int UserId,
                                   std::string FirstName, std::string LastName,
                                   int StudentId) {
  if (cur_user.GetUserType() != LIBRARIAN) {
    std::cout << "Access denied" << std::endl;
    return false;
  }
  for (auto &x : UserList) {
    if (x->GetUserId() == UserId) {
      std::cout << "User with such ID already exists!" << std::endl;
      return false;
    }
  }
  UserList.push_back(
      std::make_unique<Student>(UserId, FirstName, LastName, StudentId));
  return true;
}
bool LibraryService::CreateTeacher(User &cur_user, int UserId,
                                   std::string FirstName, std::string LastName,
                                   int TeacherId) {
  if (cur_user.GetUserType() != LIBRARIAN) {
    std::cout << "Access denied" << std::endl;
    return false;
  }
  for (auto &x : UserList) {
    if (x->GetUserId() == UserId) {
      std::cout << "User with such ID already exists!" << std::endl;
      return false;
    }
  }
  UserList.push_back(
      std::make_unique<Teacher>(UserId, FirstName, LastName, TeacherId));
  return true;
}
bool LibraryService::CreateLibrarian(User &cur_user, int UserId,
                                     std::string FirstName,
                                     std::string LastName, int LibrarianId) {
  if (cur_user.GetUserType() != LIBRARIAN) {
    std::cout << "Access denied" << std::endl;
    return false;
  }
  for (auto &x : UserList) {
    if (x->GetUserId() == UserId) {
      std::cout << "User with such ID already exists!" << std::endl;
      return false;
    }
  }
  UserList.push_back(
      std::make_unique<Librarian>(UserId, FirstName, LastName, LibrarianId));
  return true;
}
bool LibraryService::DeleteUser(User &cur_user, User *user) {
  if (cur_user.GetUserType() != LIBRARIAN) {
    std::cout << "Access denied" << std::endl;
    return false;
  }
  if (user == nullptr) {
    std::cout << "User doesn't exist" << std::endl;
    return false;
  }
  for (auto it = UserList.begin(); it != UserList.end(); it++) {
    if (it->get() == user) {
      UserList.erase(it);
      break;
    }
  }
  std::cout << "User was succefully deleted" << std::endl;
  return true;
};

bool LibraryService::PayPenalty(User &user) {
  std::cout << "Penalty was succesfully paid" << std::endl;
  user.AddToBalance(-user.GetBalance());
  return true;
}

User *LibraryService::FindUserById(int UserId) {
  for (auto &x : UserList) {
    if (x->GetUserId() == UserId) {
      return x.get();
    }
  }
  std::cout << "User was not found" << std::endl;
  return nullptr;
}
