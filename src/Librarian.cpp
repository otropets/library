#include "Librarian.h"

int Librarian::GetLibrarianId() { return LibrarianId; }
void Librarian::AddBookCopy() { // todo
}
void Librarian::CreateBook(int bookId, std::string title, std::string author,
                           Language lang) {
  Book *book = new Book(bookId, title, author, lang);
  libraryService.AddBook(book);
}
void Librarian::DeleteBook() {
  // todo
}

int Librarian::GetMaxBooksAmount() { return 0; }
