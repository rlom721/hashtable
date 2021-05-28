// Program Name:    Hashtable Demonstration
// File Name:       main.cpp
// Author:          Rafaela Lomboy
// Date:            2021.02.12
// Description:     This program demonstrates features of this Hashtable class,
//                  including:
//                  1. Printing contents to console for monitoring table state
//                  2. Hashing data from a file to the table
//                  3. Writing table contents to disk
//                  4. Restoring hashtable from disk
//                  5. Producing before/after restoration reports as .txt files
//                  6. Reading keys from a file then producing a search report
//                  7. Producing a collision report for each primary bucket

#include "Hashtable.h"    // Hashtable class header
#include "Hashtable.cpp"  // Hashtable class implementation
#include "Bucket.h"       // Bucket class is item type of Hashtable

int main () {
  Hashtable<Bucket> ht;     // hashtable with 20 primary buckets

  // prints current hastable contents to console
  // ht.GenStatReport();

  // takes data file in and hashes records into hashtable
  ht.hashRecords("DATAIN.dat");

  // writes hashtable contents to disk
  // then generate a report file (with title as second argument)
  ht.writeHTtoDisk();
  ht.ReportHT("BeforeRestorationReport.txt", "Before Restoration Report");

  // restore hashtable from memory then generate a report file
  ht.restoreHTtoMem();

  ht.ReportHT("AfterRestorationReport.txt", "After Restoration Report");

  // read keys from a SEARCH.dat then produce a search report SearchReport.txt
  ht.SearchHT("SEARCH.dat");

  // display collisions per primary bucket and average
  // then produce report file CollisionReport.txt
  ht.collisionReport();

  return 0;
}
