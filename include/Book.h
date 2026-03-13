#pragma once
#include <string>
enum Language { ENG, PL };
class Book {
private:
  int BookId;
  std::string title;
  std::string author;
  Language lang;

public:
  Book(int BookId, std::string title, std::string author, Language lang)
      : BookId(BookId), title(title), author(author), lang(lang) {};

  int GetBookId();
  std::string GetTitle();
  std::string GetAuthor();
  Language GetLang();

  ~Book() {};
};