// Specification file for Bucket class
//
// Bucket is a class dependent on the Slot class.
// It provides a container structure of string keys and data, as well as
// information about the object itself.

#ifndef BUCKET_H
#define BUCKET_H

#include "Slot.h"
#include <iostream>
#include <string>
using namespace std;

class Bucket {
  friend ostream &operator<<(ostream& out, const Bucket& Bucket);
public:
  static const int numSlots = 3;  // size of slots array
  int nextOpenSlot = 0;           // next available slot
  int count = 0;                  // number of collisions in bucket
  int OFindex = -1;               // index to overflow bucket
  Slot slots[numSlots];           // array of numSlots slots
  Bucket();
  Bucket(string key, string data);
  Bucket(const Bucket& rhs);
  void set(string key, string data, int slotIndex);
  string getKey(int slotIndex) const { return slots[slotIndex].getKey(); }
  string getData(int slotIndex) const { return slots[slotIndex].getData(); }
  void setKey(string k, int slotIndex);
  void setData(string d, int slotIndex);
  bool hasFreeSlot() { return (nextOpenSlot < 3); }
  bool isOpen(int sIndex) { return (slots[sIndex].getKey() == "EMPTY"); }
  Bucket& operator=(const Bucket& rhs);         // copy assignment
};

#endif
