// Slot.cpp
// implementation file for Slot class

#include "Slot.h"         // header file for Slot class
#include <iostream>       // for cout
#include <string>         // for string formatting
using namespace std;

// default constructor - set default values for key and data
Slot::Slot() {
  key = "KEY";
  data = "DATA";
}

// parametrized constructor sets values for key and data
Slot::Slot(string k, string d) : key(k), data(d) { }

// copy constructor copies key and data values
Slot::Slot(const Slot& rhs) {
  key = rhs.key;
  data = rhs.data;
}

// set values based on arguments
void Slot::set(string k, string d) {
  key = k;
  data = d;
}

// set value based on argument
void Slot::setKey(string k) {
  key = k;
}

// set value based on argument
void Slot::setData(string d) {
  data = d;
}

// copy assignment copies key and data
Slot& Slot::operator=(const Slot& rhs){
  if (this != &rhs) {
    key = rhs.key;
    data = rhs.data;
  }

  return *this;
}
