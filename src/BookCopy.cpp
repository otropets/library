#include "BookCopy.h"

int BookCopy::GetBookCopyId() { return BookCopyId; }

Book *BookCopy::getBook() { return &book; }
bool BookCopy::GetAvailability() { return availability; }
void BookCopy::SetAvailability(bool availability) {
  this->availability = availability;
}