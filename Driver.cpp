#include <iostream>
#include <fstream>
#include <sstream>
#include "Graph.hpp"

using namespace std;

/********************************************************************************
* Functions for Driver.cpp
*********************************************************************************/
void pause()
{
  cout << "...Enter anything to continue..." << endl;
  cin.get();
}

/********************************************************************************
* Functions/Structs for Patient
*********************************************************************************/
struct Patient
{
  string name;
  vector<string> medicalHistory;
};

void displayPatientData(vector<Patient> patientData)
{
  for(int i = 0; i < patientData.size(); i++)
  {
    cout << patientData[i].name << endl;
  }
}

bool duplicateName(vector<Patient> patientData, string name)
{
  for(int i = 0; i < patientData.size(); i++)
  {
    if(name == patientData[i].name)
    {
      return true;
    }
  }
  return false;
}

/********************************************************************************
* Full List of Menus
*********************************************************************************/
void patientMenu() //1. If Patient Database is selected
{
  cout << "----------------------------------------------------------------------" << endl;
  cout << "1. New Patient" << endl;
  cout << "2. View Current Patient" << endl;
  cout << "3. Exit" << endl;
  cout << "----------------------------------------------------------------------" << endl;
}

void medicalBackgroundMenu()
{
  cout << "----------------------------------------------------------------------" << endl;
  cout << "Please enter medical conditions (Ex: Asthma, Epilepsy, etc)" << endl;
  cout << "Type 'Done' once completed" << endl;
  cout << "----------------------------------------------------------------------" << endl;
}

void mainMenu()
{
  cout << "----------------------------------------------------------------------" << endl;
  cout << "EXCLAIMER: PLEASE CALL 911 IF SYMPTOMS ARE LIFE-THREATENING!" << endl;
  cout << "1. Run Program" << endl;
  cout << "2. Create new Patient" << endl;
  cout << "3. Patient Database" << endl;
  cout << "4. Complications Database" << endl;
  cout << "5. Exit program" << endl;
  cout << "----------------------------------------------------------------------" << endl;
}

int main()
{
  //Graph Initialization//
  Graph medicalData;
  medicalData.loadComplications("Complications.txt");
  medicalData.loadConditions("Conditions.txt");

  //Patient Database Initialization//
  vector<Patient> patientData; //TURN INTO HASH TABLE LATER

  //Menu Selection//
  string patientName;
  string mainMenu_choice, medicalBackground_choice, program_choice = "";
  while(mainMenu_choice != "5")
  {
    mainMenu();
    getline(cin, mainMenu_choice);
    switch(stoi(mainMenu_choice))
    {
      /* 1. Run Program **/
      case 1:
      {
        //Test Patient
        // Patient Adam;
        // Adam.name = "Adam";
        // Adam.medicalHistory.push_back("Asthma");
        while(program_choice != "Done")
        {
          cout << "Please enter symptoms you are experiencing from the list (Ex: Headache, Cough, etc)" << endl << "Symptoms: ";
          medicalData.displaySymptoms();
          cout << endl;
          cout << "Type 'Done' once completed: ";
          getline(cin, program_choice);
          cout << endl;
          if(medicalData.checkSymptom(program_choice) == true)
          {
            medicalData.updateBestMatch(program_choice);
          }
          else if(program_choice != "Done")
          {
            cout << "Please enter a symptom that is part of the list!" << endl;
            pause();
          }
        }
        medicalData.removeConditionsFromBestMatch(Adam.medicalHistory);
        cout << "Based on your symptoms you most likely are suffering from: " << endl;
        medicalData.printBestMatch();
        pause();
        medicalData.refreshBestMatch();
        program_choice = "";
        break;
      }

      /* 2. Create New Patient **/
      case 2:
      {
        Patient newPatient; //Initialize new patient
        //Enter patient's name
        cout << "Please enter the patient's full name" << endl;
        getline(cin, patientName);
        newPatient.name = patientName;
        cout << "Added " << patientName << " to the database!" << endl;
        pause();

        //Enter patient's medical background
        while(medicalBackground_choice != "Done")
        {
          cout << "Please enter " << patientName << "'s medical conditions from the list (Ex: Asthma, Allergies, etc)" << endl << "Medical Conditions: ";
          medicalData.displayConditions();
          cout << endl;
          cout << "Type 'Done' once completed: ";
          getline(cin, medicalBackground_choice);
          cout << endl;
          if(medicalData.checkCondition(medicalBackground_choice) == true)
          {
            cout << "Added " << medicalBackground_choice << " to " << patientName << "'s patient profile!" << endl;
            newPatient.medicalHistory.push_back(medicalBackground_choice);
            pause();
          }
          else if(medicalBackground_choice != "Done")
          {
            cout << "Please enter a condition that is part of the list!" << endl;
            pause();
          }
        }
        patientData.push_back(newPatient);
        medicalBackground_choice = "";
        break;
      }

      /* 3. Patient Database **/
      case 3:
      {
        displayPatientData(patientData);
        pause();
        break;
      }

      /* 4. Complications Database **/
      case 4:
      {
        medicalData.displayComplicationsWithSymptomsAndConditions();
        pause();
        break;
      }

      /* 5. Exit **/
      case 5:
      {
        cout << "Goodbye!" << endl;
        break;
      }
      case 420: //Debug
      {
        cout << "**Debug Mode: **" << endl;
        cout << "------------------------------------------------------------------------------" << endl;
        cout << "Conditions" << endl;
        cout << "------------------------------------------------------------------------------" << endl;
        medicalData.displayConditions();
        cout << endl;
        cout << "------------------------------------------------------------------------------" << endl;
        cout << "Complications" << endl;
        cout << "------------------------------------------------------------------------------" << endl;
        medicalData.displayComplications();
        cout << "------------------------------------------------------------------------------" << endl;
        cout << "Symptoms" << endl;
        cout << "------------------------------------------------------------------------------" << endl;
        medicalData.displaySymptoms();
        cout << endl;
        cout << "------------------------------------------------------------------------------" << endl;
        cout << "Complication Vertices with Symptom Edges" << endl;
        cout << "------------------------------------------------------------------------------" << endl;
        medicalData.displayComplicationsWithSymptoms();
        cout << "------------------------------------------------------------------------------" << endl;
        cout << "Symptom Vertices with Complication Edges" << endl;
        cout << "------------------------------------------------------------------------------" << endl;
        medicalData.displaySymptomsWithComplications();
        cout << "------------------------------------------------------------------------------" << endl;
      }
    }
  }
}
