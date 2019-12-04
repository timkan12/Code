#include <iostream>
#include <string>
#include <vector>
using namespace std;

#ifndef HASH_HPP
#define HASH_HPP

class hashFunc {

private:
  static const int tableSize = 5;

  struct patient
  {
      string name;
      patient *next;
      vector<string> medicalHistory;

  };

  patient* hashTable[tableSize];

public:
    hashFunc(); //constructor
    int hash(string name); // creating hash table
    void addPatient(string name, vector<string> medicalHistory); //adding the patient to data base
    int numOfPatient(int index); //account for #of patient
    void printPatient(); //print patient
    void printPatientIndex(int index); //print patient at a certian index
};


#endif
