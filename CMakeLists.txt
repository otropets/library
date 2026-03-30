cmake_minimum_required(VERSION 3.14)
project(Library)
set(CMAKE_CXX_STANDARD 17)

include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
FetchContent_MakeAvailable(googletest)
add_executable(Library
    src/main.cpp
    src/Book.cpp
    src/BookCopy.cpp
    src/User.cpp
    src/Student.cpp
    src/Teacher.cpp
    src/Librarian.cpp
    src/Rent.cpp
    src/LibraryService.cpp
)

target_include_directories(Library PRIVATE include)


add_executable(LibraryTests
tests/LibraryServiceTest.cpp
src/Book.cpp
src/BookCopy.cpp
src/User.cpp
src/Student.cpp
src/Teacher.cpp
src/Librarian.cpp
src/Rent.cpp
src/LibraryService.cpp)

target_include_directories(LibraryTests PRIVATE include)
target_link_libraries(LibraryTests gtest_main)

enable_testing()
add_test(NAME LibraryTests COMMAND LibraryTests)


