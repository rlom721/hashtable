// Hashtable.cpp
// implementation file of Hashtable class

#include "Hashtable.h"  // header file
#include <iostream>     // used for key and data pair type
#include <iomanip>      // for restoring hash
#include <cassert>      // for assert function (debugging)
#include <string>       // used for processing files
#include <vector>       // main table structure
#include <fstream>      // for reading and writing to data files
#include <sstream>      // for parsing lines of data file
using namespace std;

// default constructor sets up hashtable structure (vector) and
// sets default value for nextOFBucket
template <class Bucket>
Hashtable<Bucket>::Hashtable() {
  buckets = vector<Bucket>(CAP);    // table has CAP number of buckets
  nextOFBucket = CAP;         // index of next overflow bucket is after primary
}

// This method (for recursive call) takes a key and data pair, then
// inserts pair into hashtable (do NOT hash key or program will crash!).
template <class Bucket>
void Hashtable<Bucket>::insertToHT(string entryKey, string entryData, int index) {
  int slot = 0;   // slot index in bucket

  // insert key and data in next open slot in bucket
  if (buckets[index].hasFreeSlot()) {
    slot = buckets[index].nextOpenSlot;
    buckets[index].set(entryKey, entryData, slot);

    if (slot > 0) buckets[index].count++;   // keep track of collisions
  }
  // if bucket has overflow bucket index, insert there
  else if (buckets[index].OFindex != -1) {
    buckets[index].count++;         // count as collision for old bucket

    index = buckets[index].OFindex;

    insertToHT(entryKey, entryData, index);   // recursive call
  }
  // create new overflow bucket and add key and data to 1st slot
  else {
    buckets[index].count++;   // keep track of collisions

    // link current bucket to overflow bucket index
    buckets[index].OFindex = nextOFBucket++;

    Bucket newBucket;

    // index of overflow bucket being linked
    index = buckets[index].OFindex;

    // allocate space at end of buckets and add newBucket to end
    buckets.resize(nextOFBucket, newBucket);
    insertToHT(entryKey, entryData, index);
  }
}

// This method takes a key and data pair, hashes the key to an index, then
// inserts pair into hashtable.
template <class Bucket>
void Hashtable<Bucket>::insertToHT(string entryKey, string entryData) {
  int slot = 0;     // slot index in bucket
  int index = -1;   // bucket index

  // determine index in table by hashing the key, if NOT searching OF bucket
  index = hashFunc(entryKey);

  // insert key and data in next open slot in bucket
  if (buckets[index].hasFreeSlot()) {
    slot = buckets[index].nextOpenSlot;
    buckets[index].set(entryKey, entryData, slot);

    if (slot > 0) buckets[index].count++;   // keep track of collisions
  }
  // if bucket has overflow bucket index, insert there
  else if (buckets[index].OFindex != -1) {
    buckets[index].count++;         // count as collision for old bucket

    index = buckets[index].OFindex;

    insertToHT(entryKey, entryData, index);   // recursive call
  }
  // create new overflow bucket and add key and data to 1st slot
  else {
    buckets[index].count++;   // keep track of collisions

    // link current bucket to overflow bucket index
    buckets[index].OFindex = nextOFBucket++;

    Bucket newBucket;

    // index of overflow bucket being linked
    index = buckets[index].OFindex;

    // allocate space at end of buckets and add newBucket to end
    buckets.resize(nextOFBucket, newBucket);
    insertToHT(entryKey, entryData, index);
  }
}

// Hash function takes ordinal value of 2nd, 4th and 6th chars of a key
// then modulo by the number of primary buckets (20) to obtain index of table
template <class Bucket>
int Hashtable<Bucket>::hashFunc(string key) const {
  int sum = key[2] + key[4] + key[6];

  return (sum % CAP);
}

// This helper function takes an index from a hashed key and determines bucket
// and slot of item if already present in table
// Prerequisite: hashFunc was called on the key before this is called
template <class Bucket>
void Hashtable<Bucket>::findRecord(string key, bool& found, int& slot, int& index) {
  int s = 0;        // counter for while loop below for slots
  string currKey;   // current slot's key
  found = false;    // false until found

  // loop until all slots searched, key or empty found
  while (s < 3 && !found) {
    currKey = buckets[index].getKey(s);

    // found EXACT match so set found to true and get slot number
    if (currKey == key) {
      found = true;
      slot = s;
    }
    s++;
  }

  // if not found, search overflow bucket for key IF ALLOCATED
  if (!found && (buckets[index].OFindex != -1) && index < size()) {
    index = buckets[index].OFindex;
    findRecord(key, found, slot, index);
  }
}

// This helper function centers text for reports.
template <class Bucket>
string Hashtable<Bucket>::centerText(string s) {
  const int consoleWidth = 80;
  int length = 0,   // length of combined string with space
      spaces = 0;   // spaces to pad to center
  string centered = "";   // centered text

  length = s.length() + 1;
  spaces = (consoleWidth - length) / 2;

  // center by adding padding with spaces before string
  centered = string(spaces, ' ') + s + '\n';

  return centered;
}

// This method outputs current hashtable items to console.
template <class Bucket>
void Hashtable<Bucket>::GenStatReport() {
  cout << centerText("Hash Table")
       << centerText("Verification Report")
       << centerText("Before | After Restoration");

  // loop over ALL buckets in hash table and display their contents
  for (int i = 0; i < size(); i++)
    cout << "\nBucket " << i + 1 << "\n" << buckets[i];
}

// This method takes a data file name and hashes all records into hashtable
// from file, line by line.
template <class Bucket>
void Hashtable<Bucket>::hashRecords(string dataFileName) {
  ifstream inFile;
  string line, st10, st20;  // for parsing out lines of data file
  inFile.open(dataFileName);

  // check for failure in opening file
  assert(inFile);

  // read data in from file loop until end of file reached
  while (getline(inFile, line)) {
    if (line.length() >= 20) {
      // parse line into KEY (st10) and DATA (st20)
      st10 = line.substr(0, 10);
      st20 = line.substr(10, 20);

      // hash the records using their key
      insertToHT(st10, st20);
    }
  }

  inFile.close();
}

// save hashtable contents by writing to file 'HASHTABLE.txt' as default name
template <class Bucket>
void Hashtable<Bucket>::writeHTtoDisk() {
  ofstream outFile;                // for storing file data

  outFile.open("HASHTABLE.txt");

  // adds header
  outFile << centerText("Hash Table")
          << centerText("Verification Report")
          << centerText("Before | After Restoration") << '\n';

  // loop over ALL buckets in hash table and write their contents to file
  for (int i = 0; i < size(); i++)
    outFile << "Bucket " << i + 1 << '\n'<< buckets[i] << '\n';

  outFile.close();
}

// This method restores hashtable to memory from a file.
// Note: dependent on writeHTtoDisk method!
template <class Bucket>
void Hashtable<Bucket>::restoreHTtoMem() {
  ifstream getData;   // for retrieving file data
  string line,        // for parsing line in file
         kd, word, word2,
         key, data;   // separate key and data pair
  int bNum = 0, sNum = 0,   // for reinserting data in hash table
      overflowPtr = -1;

  nextOFBucket = 20;

  getData.open("HASHTABLE.txt");

  // check for failure in opening file
  assert("HASHTABLE.txt");

  if (getData.fail())
    cout << "File not found.\n";
  // read data from restoration file 'HASHTABLE.txt' then insert each key and
  // data pair back into hashtable by parsing out each line
  else {
    // read data in from file loop until end of file reached
    while (getline(getData, line)) {
      istringstream str(line);     // process line of input

      // skip blank lines
      if (!line.empty()) {
        // read first string of line
        str >> word;

        // increment bucket number if encountered
        if (word == "Bucket")
          bNum++;
        // get slot number then read its key and data, then insert back in table
        else if (word == "Slot") {
          str >> sNum;

          // ignore colon and space then read data from line
          str.ignore(2);
          getline(str, kd, '\n');

          // skip empty slots and reinsert key and data into hash table
          if (kd != "---EMPTY---") {
            // add new bucket once primary bucket number is exceeded
            if (bNum > 20 && sNum == 1) {
              nextOFBucket++;

              Bucket newBucket;
              buckets.resize(nextOFBucket, newBucket);
            }

            // parse line into KEY and DATA
            key = kd.substr(0, 10);
            data = kd.substr(10, 20);

            // put data in its corresponding bucket and slot
            buckets[bNum-1].set(key, data, sNum - 1);
          }
        }
        // set OF index of a bucket
        else if (word == "Overflow") {

          // skip word "pointer" then read overflow pointer number
          str >> word2;
          str >> overflowPtr;

          // set bucket's overflow pointer to INDEX
          buckets[bNum - 1].OFindex = overflowPtr - 1;
        }
      }
    }
  }
    getData.close();
}

// This method produces a report with table contents in file with reportFileName
// template <class Bucket>
template <class Bucket>
void Hashtable<Bucket>::ReportHT(string reportFileName, string reportName){
  ofstream outFile;                // for storing file data

  outFile.open(reportFileName);

  // adds header
  outFile << centerText("Hash Table")
          << centerText("Verification Report")
          << centerText(reportName) << '\n';

  // loop over ALL buckets in hash table and write their contents to file
  for (int i = 0; i < size(); i++)
    outFile << "Bucket " << i + 1 << '\n' << buckets[i] << '\n';

  outFile.close();
}

// This method reads keys from a data file and searches from a match in the table
template <class Bucket>
void Hashtable<Bucket>::SearchHT(string searchFileName) {
  ifstream inFile;    // to read keys from file
  ofstream outFile;   // for storing search report
  string key;         // use key in find function
  bool found = false;
  int index = -1, sIndex = -1;

  inFile.open(searchFileName);
  outFile.open("SearchReport.txt");

  // check for failure in opening file
  assert(inFile);

  // show header
  outFile << centerText("Search and Retrieval")
          << centerText("Transactions") << endl;
  outFile << "\tSearch Key\tBucket/Slot\tRecord\n";

  // read data in from file loop until end of file reached
  while (getline(inFile, key)) {

    // hash key from file then find record in hash table
    if (key.length() >= 10) {
     key = key.substr(0, 10);     // remove newline char

     index = hashFunc(key);
     findRecord(key, found, sIndex, index);

     // display search result and matching data if found
     if (found) {
       outFile << '\t' << key
            << "\t   " << setw(2) << right << index+1 << "/"
            << setw(2) << left << sIndex + 1
            << "\t" << buckets[index].getData(sIndex) << endl;
      }
      else {
        outFile << '\t' << key
             << "\t   " << setw(2) << right << "--/--"
             << "\t" << "Record not found" << endl;
      }
    }
  }

  inFile.close();
  outFile.close();
}

// This method produces a file 'CollisionReport.txt' that shows each primary
// bucket's collision count and the average count for all primary buckets.
template <class Bucket>
void Hashtable<Bucket>::collisionReport() {
  ofstream outFile;         // for storing file data
  double totCols = 0,       // total collisions (used to calculate average)
         noCols = 0;        // only count buckets with no collisions to avg

  outFile.open("CollisionReport.txt");

  // adds header
  outFile << "HashTable\nCollision Chain Length Report\n\n";

  outFile << "      Bucket ID\tCollisions\n";

  // loop over ALL buckets in hash table and write their contents to file
  for (int i = 0; i < CAP; i++) {
    outFile << "\tBucket " << i + 1 << "\t    " << buckets[i].count << '\n';

    // exclude empty buckets (empty first slot) from average
    if (buckets[i].count != 0) noCols++;

    totCols += buckets[i].count;
  }

  outFile << "\n    Avg Collision Length = "
         << fixed << setprecision(2) << totCols / noCols << endl;

  outFile.close();
}

// This method resets the hashtable in memory by clearing data and resizing.
template <class Bucket>
void Hashtable<Bucket>::resetHT() {
  buckets.clear();                  // clear current contents of buckets
  buckets = vector<Bucket>(CAP);    // shrink to default size
  nextOFBucket = CAP;   // reset index of available overflow bucket
}

// This method returns total number of used entries in table (for debugging).
template <class Bucket>
int Hashtable<Bucket>::numEntries() {
  int count = 0;
  for (int i = 0; i < size(); i++) {
    for (int slot = 0; slot < 3; slot++)
      if (buckets[i].getKey(slot) != "EMPTY") count++;
  } return count;
}
