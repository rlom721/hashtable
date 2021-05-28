// Specification file for Hashtable class
//
// Hashtable is a template class dependent on the Bucket class that provides
// features of a hashtable data structure.
// Allows multiple entries to hash to same index by inserting into slots
// and allocating overflow buckets.
// Also contains search and hashtable report features.

#ifndef HASHTABLE_H
#define HASHTABLE_H
#include <iostream>
#include <string>       // used for key and data pair type
#include <vector>       // main table structure
using namespace std;

template <class Bucket>
class Hashtable {
public:
  static const int CAP = 20;    // size or number of PRIMARY buckets
  int nextOFBucket;             // index of available overflow bucket
  Hashtable();
  void insertToHT(string entryKey, string entryData, int index);
  void insertToHT(string entryKey, string entryData);
  void GenStatReport();
  void hashRecords(string dataFileName);
  void writeHTtoDisk();
  void restoreHTtoMem();
  void ReportHT(string reportFileName, string reportName);
  void SearchHT(string searchFileName);
  void collisionReport();
  void resetHT();
  int size() const { return buckets.size(); }
  int numEntries();
private:
  vector<Bucket> buckets;
  // helper functions below!
  int hashFunc(string key) const;
  void findRecord(string key, bool &found, int& slot, int& index);
  string centerText(string s);
};

#endif
