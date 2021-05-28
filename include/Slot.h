// Specification file for Slot class
//
// The Slot class is a small container structure of a string key and string
// data (as a key and data pair).

#ifndef SLOT_H
#define SLOT_H

#include <string>
using namespace std;

class Slot {
public:
  Slot();
  Slot(string k, string d);
  Slot(const Slot& rhs);
  void set(string k, string d);
  string getKey() const { return key; };
  string getData() const { return data; };
  void setKey(string k);
  void setData(string d);
  void classTest();
  Slot& operator=(const Slot& rhs);
private:
  string key;
  string data;
};

#endif
