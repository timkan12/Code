#include <iostream>
#include <string>
#include <cmath>
#include "Hash.hpp"
using namespace std;

hashFunc::hashFunc()
{
  for(int i = 0; i < tableSize; i++)
  {
    hashTable[i] = new patient;
    hashTable[i]->name = "blank";
    hashTable[i]->next = NULL;
  }
}

void hashFunc::addPatient(string name,vector<string> medicalHistory)
{
  int index = hash(name);
  patient *tmp2 = new patient;
  cout << "medical history: " << medicalHistory.size() << endl;
  tmp2->name = name;
  tmp2->next = NULL;
  for(int i = 0; i < medicalHistory.size(); i++)
  {
      tmp2->medicalHistory.push_back(medicalHistory[i]);

  }
  if(hashTable[index]->name == "blank")
  {
    hashTable[index] = tmp2;
  }
  else{
    patient *tmp = hashTable[index];
    while(tmp->next != NULL)
    {
      tmp = tmp->next;
    }
    tmp->next = tmp2;
  }
}

int hashFunc::hash(string name)
{
  int count = 0;

  for(int i = 0; i < name.length(); i++)
  {
    count = count + (int)name[i];
    //cout << (int)name[i] << endl;
    //cout << "hash = " << count << endl;
  }

  return count % tableSize;

}

int hashFunc::numOfPatient(int index)
{
  int counter = 0;
  if(hashTable[index]->name == "blank")
  {
    return counter;
  }
  else
  {
    counter++;
    patient *temp = hashTable[index];
    while(temp->next != NULL)
    {
      counter++;
      temp = temp->next;
    }
    return counter;
  }
}

void hashFunc::printPatient()
{
  int count;
  for(int i = 0; i< tableSize; i++)
  {
    count = numOfPatient(i);
    cout << "--------------------------------" << endl;
    cout << "Location on our list: " << i << endl;
    cout <<  "num of patient = " << count << endl;
    cout << "patient name: " << hashTable[i]->name << endl;
    cout << "--------------------------------" << endl;
  }
}

void hashFunc::printPatientIndex(int index)
{
  patient *temp = hashTable[index];
  if(temp->name == "blank")
  {
    cout << "This index is empty" << endl;
  }
  else
  {
    while(temp != NULL)
    {
      cout << "Patient name is: " << temp->name << endl;
      for(int i = 0; i < temp->medicalHistory.size(); i++)
      {
        cout << "medical history:";
        cout<< temp->medicalHistory[i] << endl;
      }
      temp = temp->next;
    }
  }
}
