#include "LibraryService.h"
#include "Student.h"
#include <gtest/gtest.h>

TEST(LibraryServiceTest, CreateBook) {
  LibraryService library;
  User *admin = library.FindUserById(1);
  EXPECT_TRUE(library.CreateBook(*admin, 10, "Dune", "Frank Herbert", ENG));
}

TEST(LibraryServiceTest, CreateBookCopy) {
  LibraryService library;
  User *admin = library.FindUserById(1);
  library.CreateBook(*admin, 10, "Dune", "Frank Herbert", ENG);
  EXPECT_TRUE(library.AddBookCopy(*admin, 1, 10));
}

TEST(LibraryServiceTest, CreateStudent) {
  LibraryService library;
  User *admin = library.FindUserById(1);
  EXPECT_TRUE(library.CreateStudent(*admin, 2, "John", "Doe", 200));
}

TEST(LibraryServiceTest, CreateTeacher) {
  LibraryService library;
  User *admin = library.FindUserById(1);
  EXPECT_TRUE(library.CreateTeacher(*admin, 3, "Jane", "Smith", 300));
}

TEST(LibraryServiceTest, CreateLibrarian) {
  LibraryService library;
  User *admin = library.FindUserById(1);
  EXPECT_TRUE(library.CreateLibrarian(*admin, 4, "Bob", "Jones", 400));
}

TEST(LibraryServiceTest, DeleteExistingUser) {
  LibraryService library;
  User *admin = library.FindUserById(1);
  library.CreateStudent(*admin, 2, "John", "Doe", 200);
  User *student = library.FindUserById(2);
  EXPECT_TRUE(library.DeleteUser(*admin, student));
}

TEST(LibraryServiceTest, DeleteNonExistingUser) {
  LibraryService library;
  User *admin = library.FindUserById(1);
  EXPECT_FALSE(library.DeleteUser(*admin, nullptr));
}

TEST(LibraryServiceTest, BorrowNonExistingBook) {
  LibraryService library;
  User *admin = library.FindUserById(1);
  library.CreateStudent(*admin, 2, "John", "Doe", 200);
  User *student = library.FindUserById(2);
  EXPECT_FALSE(library.BorrowBookCopy(*student, 999));
}
TEST(LibraryServiceTest, BorrowExistingBook) {
  LibraryService library;
  User *admin = library.FindUserById(1);
  library.CreateBook(*admin, 10, "Dune", "Frank Herbert", ENG);
  library.AddBookCopy(*admin, 1, 10);
  library.CreateStudent(*admin, 2, "John", "Doe", 200);
  User *student = library.FindUserById(2);
  EXPECT_TRUE(library.BorrowBookCopy(*student, 1));
}

TEST(LibraryServiceTest, BorrowWithTeacher) {
  LibraryService library;
  User *admin = library.FindUserById(1);
  library.CreateBook(*admin, 10, "Dune", "Frank Herbert", ENG);
  library.AddBookCopy(*admin, 1, 10);
  library.CreateTeacher(*admin, 3, "Jane", "Smith", 300);
  User *teacher = library.FindUserById(3);
  EXPECT_TRUE(library.BorrowBookCopy(*teacher, 1));
}

TEST(LibraryServiceTest, BorrowWithLibrarian) {
  LibraryService library;
  User *admin = library.FindUserById(1);
  library.CreateBook(*admin, 10, "Dune", "Frank Herbert", ENG);
  library.AddBookCopy(*admin, 1, 10);
  EXPECT_FALSE(library.BorrowBookCopy(*admin, 1));
}

TEST(LibraryServiceTest, BorrowAlreadyBorrowedBook) {
  LibraryService library;
  User *admin = library.FindUserById(1);
  library.CreateBook(*admin, 10, "Dune", "Frank Herbert", ENG);
  library.AddBookCopy(*admin, 1, 10);
  library.CreateStudent(*admin, 2, "John", "Doe", 200);
  library.CreateStudent(*admin, 5, "Jane", "Doe", 201);
  User *student1 = library.FindUserById(2);
  User *student2 = library.FindUserById(5);
  library.BorrowBookCopy(*student1, 1);
  EXPECT_FALSE(library.BorrowBookCopy(*student2, 1));
}

TEST(LibraryServiceTest, BorrowTooManyBooksStudent) {
  LibraryService library;
  User *admin = library.FindUserById(1);
  library.CreateStudent(*admin, 2, "Alixanro", "Tropets", 244);
  User *student = library.FindUserById(2);
  library.CreateBook(*admin, 10, "Dune", "Frank Herbert", ENG);
  library.AddBookCopy(*admin, 501, 10);
  library.AddBookCopy(*admin, 502, 10);
  library.AddBookCopy(*admin, 503, 10);
  library.AddBookCopy(*admin, 504, 10);
  library.AddBookCopy(*admin, 505, 10);
  library.AddBookCopy(*admin, 506, 10);
  library.BorrowBookCopy(*student, 501);
  library.BorrowBookCopy(*student, 502);
  library.BorrowBookCopy(*student, 503);
  library.BorrowBookCopy(*student, 504);
  library.BorrowBookCopy(*student, 505);
  EXPECT_FALSE(library.BorrowBookCopy(*student, 506));
}

TEST(LibraryServiceTest, BorrowOverTeacherLimit) {
  LibraryService library;
  User *admin = library.FindUserById(1);
  library.CreateTeacher(*admin, 3, "Jane", "Smith", 300);
  User *teacher = library.FindUserById(3);

  for (int i = 1; i <= 11; i++) {
    library.CreateBook(*admin, i, "Book" + std::to_string(i), "Author", ENG);
    library.AddBookCopy(*admin, i, i);
  }

  for (int i = 1; i <= 10; i++) {
    library.BorrowBookCopy(*teacher, i);
  }

  EXPECT_FALSE(library.BorrowBookCopy(*teacher, 11));
}

TEST(LibaryServiceTest, ReturningNonExistingBookCopy) {
  LibraryService library;
  library.CreateStudent(*library.FindUserById(1), 2, "Alixanro", "Tropets",
                        244);
  EXPECT_FALSE(library.ReturnBookCopy(*library.FindUserById(2), 100));
}
TEST(LibraryServiceTest, ReturnBookWithWrongUser) {
  LibraryService library;
  User *admin = library.FindUserById(1);
  library.CreateBook(*admin, 10, "Dune", "Frank Herbert", ENG);
  library.AddBookCopy(*admin, 1, 10);
  library.CreateStudent(*admin, 2, "John", "Doe", 200);
  library.CreateStudent(*admin, 3, "Jane", "Doe", 201);
  User *student1 = library.FindUserById(2);
  User *student2 = library.FindUserById(3);
  library.BorrowBookCopy(*student1, 1);
  EXPECT_FALSE(library.ReturnBookCopy(*student2, 1));
}

TEST(LibraryServiceTest, ReturnBookWithCorrectUser) {
  LibraryService library;
  User *admin = library.FindUserById(1);
  library.CreateBook(*admin, 10, "Dune", "Frank Herbert", ENG);
  library.AddBookCopy(*admin, 1, 10);
  library.CreateStudent(*admin, 2, "John", "Doe", 200);
  User *student = library.FindUserById(2);
  library.BorrowBookCopy(*student, 1);
  EXPECT_TRUE(library.ReturnBookCopy(*student, 1));
}
TEST(LibraryServiceTest, BorrowWhenBlocked) {
  LibraryService library;
  User *admin = library.FindUserById(1);
  library.CreateBook(*admin, 10, "Dune", "Frank Herbert", ENG);
  library.AddBookCopy(*admin, 1, 10);
  library.CreateStudent(*admin, 2, "John", "Doe", 200);
  User *student = library.FindUserById(2);
  student->AddToBalance(-5.0);
  EXPECT_FALSE(library.BorrowBookCopy(*student, 1));
}

TEST(LibraryServiceTest, BorrowAfterPayingPenalty) {
  LibraryService library;
  User *admin = library.FindUserById(1);
  library.CreateBook(*admin, 10, "Dune", "Frank Herbert", ENG);
  library.AddBookCopy(*admin, 1, 10);
  library.CreateStudent(*admin, 2, "John", "Doe", 200);
  User *student = library.FindUserById(2);
  student->AddToBalance(-5.0);
  library.PayPenalty(*student);
  EXPECT_TRUE(library.BorrowBookCopy(*student, 1));
}

TEST(LibraryServiceTest, CreateDuplicateBook) {
  LibraryService library;
  User *admin = library.FindUserById(1);
  library.CreateBook(*admin, 10, "Dune", "Frank Herbert", ENG);
  EXPECT_FALSE(library.CreateBook(*admin, 10, "Dune2", "Author", ENG));
}

TEST(LibraryServiceTest, CreateDuplicateUser) {
  LibraryService library;
  User *admin = library.FindUserById(1);
  library.CreateStudent(*admin, 2, "John", "Doe", 200);
  EXPECT_FALSE(library.CreateStudent(*admin, 2, "Jane", "Doe", 201));
}
