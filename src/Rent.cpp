#include "Rent.h"

User &Rent::GetUser() { return user; }
BookCopy &Rent::GetBookCopy() { return bookCopy; }
std::time_t Rent::GetStartDate() { return StartDate; }
std::time_t Rent::GetEndDate() { return EndDate; }
bool Rent::GetPenaltyPaid() { return PenaltyPaid; }
bool Rent::IsOverdue() {
  std::time_t now = std::time(nullptr);
  if (now > EndDate) {
    return true;
  } else {
    return false;
  }
}