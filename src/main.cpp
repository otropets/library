#include "Book.h"
#include "BookCopy.h"
#include "Librarian.h"
#include "LibraryService.h"
#include "Student.h"
#include "Teacher.h"
#include "User.h"
#include <iostream>
int main() {
  std::cout << "hello cmake" << std::endl;
  LibraryService library;
  User *admin = library.FindUserById(1);
  library.CreateBook(*admin, 10, "Dune", "Frank Herbert", ENG);
  library.AddBookCopy(*admin, 1005, 10);
  library.CreateStudent(*admin, 11, "Alixanro", "Tropets", 245129);
  User *student = library.FindUserById(11);
  library.IsUserBlocked(*student);
  library.CreateTeacher(*student, 444, "D", "S", 400);
  User *teacher = library.FindUserById(444);
  library.DeleteUser(*admin, teacher);
  library.BorrowBookCopy(*student, 1005);
  library.ReturnBookCopy(*student, 1005);
  library.DeleteBookCopy(*admin, 1005);
  library.DeleteBook(*admin, 10);
}
