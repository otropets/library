#include "LibraryService.h"
#include "Student.h"
#include <gtest/gtest.h>

TEST(LibraryServiceTest, CreateBookAsLibrarian) {
  LibraryService library;
  User *admin = library.FindUserById(1);
  EXPECT_TRUE(library.CreateBook(*admin, 10, "Dune", "Frank Herbert", ENG));
}

TEST(LibraryServiceTest, CreateBookAsStudent) {
  LibraryService library;
  library.CreateStudent(*library.FindUserById(1), 2, "John", "Doe", 200);
  User *student = library.FindUserById(2);
  EXPECT_FALSE(library.CreateBook(*student, 10, "Dune", "Frank Herbert", ENG));
}