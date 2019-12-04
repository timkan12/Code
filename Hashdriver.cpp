#include <iostream>
#include <string>
#include "Hash.hpp"

using namespace std;



int main()
{
  hashFunc hashObj;

  vector<string> meme;
  meme.push_back("Headache");
  meme.push_back("cough");
  hashObj.addPatient("Tim L", meme);
  // hashObj.addPatient("Jack");
  hashObj.addPatient("Adam Vaga", meme);
  // hashObj.addPatient("katelynn");
  hashObj.printPatient();

  hashObj.printPatientIndex(1);

}
