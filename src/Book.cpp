#include "Book.h"

int Book::GetBookId() { return BookId; }
std::string Book::GetTitle() { return title; }
std::string Book::GetAuthor() { return author; }
Language Book::GetLang() { return lang; }