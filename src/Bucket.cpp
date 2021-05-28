// Bucket.cpp
// implementation file for Bucket class

#include "Bucket.h"       // header file for Bucket class
#include "Slot.h"         // Bucket contains array of 3 slots
#include <iostream>       // for cout
#include <string>         // for string formatting
using namespace std;

// default constructor
Bucket::Bucket() {
  // set defaults of key and data fields
  for (int i = 0; i < numSlots; i++) {
    slots[i].setKey("EMPTY");
    slots[i].setData("EMPTY");
  }
}

// parametrized constructor sets first slot's key and data to arguments
Bucket::Bucket(string key, string data) {
  slots[0].setKey(key);
  slots[0].setData(data);
  nextOpenSlot++;
}

// copy constructor
Bucket::Bucket(const Bucket& rhs) {
  OFindex = rhs.OFindex;
  count = rhs.count;
  nextOpenSlot = rhs.nextOpenSlot;

  // copy each slot
  for (int i = 0; i < numSlots; i++)
    slots[i] = rhs.slots[i];
}

// sets key and data of slot using index argument
void Bucket::set(string key, string data, int slotIndex) {
  slots[slotIndex].setKey(key);
  slots[slotIndex].setData(data);

  nextOpenSlot++;
}

// set key of specific slot
void Bucket::setKey(string k, int slotIndex) {
  slots[slotIndex].setKey(k);
}

// set data of specific slot
void Bucket::setData(string d, int slotIndex) {
  slots[slotIndex].setData(d);
}

// copy assignment
Bucket& Bucket::operator=(const Bucket& rhs) {
  if (this != &rhs) {
    OFindex = rhs.OFindex;
    count = rhs.count;
    nextOpenSlot = rhs.nextOpenSlot;

    // copy each slot
    for (int i = 0; i < numSlots; i++)
      slots[i] = rhs.slots[i];
  }

  return *this;
}

// overload outstream operator for generating report on console (or diagnostics)
ostream &operator<<(ostream& out, const Bucket& Bucket) {
  // loop over each slot in bucket and display its formatted data
  for (int j = 0; j < 3; j++) {
    out << "     Slot " << j + 1 << ": ";

    if (Bucket.getKey(j) == "EMPTY")
      out << "---EMPTY---" << '\n';
    else
      out << Bucket.getKey(j) << Bucket.getData(j) << '\n';
  }

  // display bucket number of overflow pointer
  out << "     Overflow Pointer: " << Bucket.OFindex + 1 << '\n';
  out << "     Count: " << Bucket.count << '\n';
  
  return out;
}
