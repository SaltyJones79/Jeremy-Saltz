#include "type.h"
#include <iomanip>
#include <iostream>

// Define the overloaded methods for struct type here

// to compare for sorting the flight records
bool flightRec::operator<(const flightRec &rhs) const {

  return (destination < rhs.destination);
}

// to check if the city matches the origin city
bool flightRec::operator==(const flightRec &rhs) const {

  return (origin == rhs.origin);
}

// to print out the formatted list of flight records
ostream &operator<<(ostream &os, const flightRec &f) {

  os << f.destination << setw(10) << f.flightNum;
  if (f.price < 100)
    os << setw(8) << "$" << f.price << endl;
  else
    os << setw(7) << "$" << f.price << endl;
  return os;
}