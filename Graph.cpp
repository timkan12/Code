#include "Graph.hpp"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
#include <queue>

//Helper Fucntion//
bool isDuplicate(string name, vector<vertex*> vectorOfInterest)
{
  for(int i = 0; i < vectorOfInterest.size(); i++)
  {
    if(name == vectorOfInterest[i]->name)
    {
      return true;
    }
  }
  return false;
}

/*
* Name: loadComplications
* Functionality: Adds preloaded complications and their symptoms to generate a graph
** - Reads from .txt file where each line is a complication
**/
void Graph::loadComplications(string filename)
{
  ifstream complicationsFile(filename);

  if(complicationsFile.is_open())
  {
    string dataLine;
    string complicationName, symptomName;
    while(getline(complicationsFile, dataLine)) //Reads each line for each complication
    {
      stringstream stream(dataLine);
      getline(stream, complicationName, '|'); //Gets complication name
      addComplication(complicationName); //Add it to Graph
      while(getline(stream, symptomName, '|')) //Reads every symptom, adds to graph if not duplicated, connects to complication
      {
        addSymptom(symptomName);
        addEdge(complicationName, symptomName);
      }
    }
  }
  else
  {
    cout << "And error has occured: File could not be opened" << endl;
  }
}

/*
* Name: loadConditions
* Functionality: Adds preloaded complications and their symptoms to generate a graph
** - Reads from .txt file where each line is a complication
**/
void Graph::loadConditions(string filename)
{
  ifstream conditionsFile(filename);

  if(conditionsFile.is_open())
  {
    string dataLine;
    string conditionName, complicationName;
    while(getline(conditionsFile, dataLine)) //Reads each line for each condition
    {
      stringstream stream(dataLine);
      getline(stream, conditionName,'|'); //Gets condition name
      conditions.push_back(conditionName); //Update conditions vector
      while(getline(stream, complicationName, '|')) //Update complication with conidtions thatm ust be satisfied
      {
        addCondition(complicationName, conditionName);
      }
    }
  }
  else
  {
    cout << "And error has occured: File could not be opened" << endl;
  }
}

/*
* Name: addComplication
* Functionality: Allocates data for new complication vertice
**/
void Graph::addComplication(string name)
{
  if(isDuplicate(name, vertices))
  {
    cout << "Complication already exists!" << endl;
    return;
  }
  vertex* newVertex = new vertex; //Allocate data for new vertice
  newVertex->name = name; //Initialize name to new vertice
  newVertex->complication = true; //Label what type of vertice it is
  vertices.push_back(newVertex); //Add vertertice to graph
}

/*
* Name: addSymptom
* Functionality: Allocates data for new symptom vertice
**/
void Graph::addSymptom(string name)
{
  if(isDuplicate(name, vertices))
  {
    return;
  }
  vertex* newVertex = new vertex; //Allocate data for new vertice
  newVertex->name = name; //Initialize name to new vertice
  newVertex->complication = false; //Label what type of vertice it is
  vertices.push_back(newVertex); //Add vertertice to graph
}

/*
* Name: addEdge
* Functionality: Joins vertices between a complication and a symptom
** - No specified direction
**/
void Graph::addEdge(string complication, string symptom)
{
  //Initialize adjacent vertices
  adjVertex adjComplication;
  adjVertex adjSymptom;
  //Initialize vertex variables that will store the variables of the found strings
  vertex* complicationVertex;
  vertex* symptomVertex;
  //Search for vertices with complication and symptom names
  for(int i = 0; i < vertices.size(); i++)
  {
    if(vertices[i]->name == complication)
    {
      complicationVertex = vertices[i];
    }
    else if(vertices[i]->name == symptom)
    {
      symptomVertex = vertices[i];
    }
  }
  //Store the pointer of the adjacent vertex
  adjComplication.vector = symptomVertex;
  adjSymptom.vector = complicationVertex;
  //Place each opposite vertice in to each vertice's adjacency vector
  symptomVertex->adj.push_back(adjSymptom);
  complicationVertex->adj.push_back(adjComplication);
}

/*
* Name: addCondition
* Functionality: Joins a complication with its condition
**/
void Graph::addCondition(string complication, string condition)
{
  vertex* complicationVertex;
  for(int i = 0; i < vertices.size(); i++)
  {
    if(vertices[i]->name == complication)
    {
      complicationVertex = vertices[i];
      complicationVertex->conditions.push_back(condition);
      return;
    }
  }
}

/*
* Name: displaySymptomsWithComplications
* Functionality: Prints each symptom in the graph along with its adjacent complications
**/
void Graph::displaySymptomsWithComplications()
{
  for(int i = 0; i < vertices.size(); i++)
  {
    if(vertices[i]->complication == false)
    {
      cout << vertices[i]->name << " --> ";
      for(int j = 0; j < vertices[i]->adj.size(); j++)
      {
        cout << vertices[i]->adj[j].vector->name << " | ";
      }
      cout << endl;
    }
  }
}

/*
* Name: displaySymptomsWithComplications
* Functionality: Prints each complication in the graph along with its adjacent symptoms
**/
void Graph::displayComplicationsWithSymptoms()
{
  for(int i = 0; i < vertices.size(); i++)
  {
    if(vertices[i]->complication == true)
    {
      cout << vertices[i]->name << " --> ";
      for(int j = 0; j < vertices[i]->adj.size(); j++)
      {
        cout << vertices[i]->adj[j].vector->name << " | ";
      }
      cout << endl;
    }
  }
}

/*
* Name: displayComplicationsWithSymptoms
* Functionality: Prints each complication in the graph along with its adjacent symptoms and respectable conditions
**/
void Graph::displayComplicationsWithSymptomsAndConditions()
{
  for(int i = 0; i < vertices.size(); i++)
  {
    if(vertices[i]->complication == true)
    {
      cout << vertices[i]->name << endl << "  Symptoms: ";
      for(int j = 0; j < vertices[i]->adj.size(); j++)
      {
        if(j != vertices[i]->adj.size() - 1)
        {
          cout << vertices[i]->adj[j].vector->name << ", ";
        }
        else
        {
          cout << vertices[i]->adj[j].vector->name;
        }
      }
      cout << endl;
      if(vertices[i]->conditions.size() != 0)
      {
        cout << "  Conditions: ";
        for(int j = 0; j < vertices[i]->conditions.size(); j++)
        {
          if(j != vertices[i]->conditions.size() - 1)
          {
            cout << vertices[i]->conditions[j] << ", ";
          }
          else
          {
            cout << vertices[i]->conditions[j];
          }
        }
        cout << endl;
      }
    }
  }
}

/*
* Name: displayComplications
* Functionality: Prints all complication vertices
**/
void Graph::displayComplications()
{
  for(int i = 0; i < vertices.size(); i++)
  {
    if(vertices[i]->complication == true)
    {
      cout << vertices[i]->name << endl;
    }
  }
}

/*
* Name: displaySymptoms
* Functionality: Prints all symptom vertices
**/
void Graph::displaySymptoms()
{
  for(int i = 0; i < vertices.size(); i++)
  {
    if(i != vertices.size() - 1 && vertices[i]->complication == false)
    {
      cout << vertices[i]->name << ", ";
    }
    else if(vertices[i]->complication == false)
    {
      cout << vertices[i]->name;
    }
  }
}

/*
* Name: displayConditions
* Functionality: Prints all conditions in vector
**/
void Graph::displayConditions()
{
  for(int i = 0; i < conditions.size(); i++)
  {
    if(i != conditions.size() - 1)
    {
      cout << conditions[i] << ", ";
    }
    else
    {
      cout << conditions[i];
    }
  }
}

/*
* Name: checkCondition
* Functionality: Checks if the patient is entering a condition that has been preloaded
**/
bool Graph::checkCondition(string condition)
{
  for(int i = 0; i < conditions.size(); i++)
  {
    if(conditions[i] == condition)
    {
      return true;
    }
  }
  return false;
}

/*
* Name: checkSymptom
* Functionality: Checks if the patient is entering a symptom that has been preloaded
**/
bool Graph::checkSymptom(string symptom)
{
  for(int i = 0; i < vertices.size(); i++)
  {
    if(vertices[i]->name == symptom)
    {
      return true;
    }
  }
  return false;
}

/*
* Name: updateBestMatch
* Functionality: Takes in symptom and either generates new bestMatch vector or breaks it down
** - More symptoms provide smaller vector, thus more accurate results
** - Looks at symptom adjacencies in graph for comparisons
**/
void Graph::updateBestMatch(string symptom)
{
  vertex* symptomVertex;
  vector<vertex*> newBestMatch;
  //Search for symptom vertice
  for(int i = 0; i < vertices.size(); i++)
  {
    if(symptom == vertices[i]->name)
    {
      symptomVertex = vertices[i];
    }
  }
  //Add points to all adjacent vertices
  for(int i = 0; i < symptomVertex->adj.size(); i++)
  {
    symptomVertex->adj[i].vector->points++;
  }
  //Place any vertice with points into bestMatch vector
  for(int i = 0; i < vertices.size(); i++)
  {
    if(vertices[i]->points != 0)
    {
      newBestMatch.push_back(vertices[i]);
    }
  }
  bestMatch = newBestMatch;
}

/*
* Name: removeConditionsFromBestMatch
* Functionality: Takes in patient's conditions and removes them from bestMatch vector if they don't match up
** - Ex: Can't have asthma attack if you don't have asthma
**/
void Graph::removeConditionsFromBestMatch(vector<string> patientConditions)
{
  bool match = false;
  for(int i = 0; i < bestMatch.size(); i++) //Look at each bestMatch vector
  {
    //Compare the condition vectors between the patient's medical history and what each bestMatch might contain
    for(int j = 0; j < bestMatch[i]->conditions.size(); j++)
    {
      for(int k = 0; k < patientConditions.size(); k++)
      {
        if(patientConditions[k] == bestMatch[i]->conditions[j]) //A match means we do NOT want to remove complications associate with it
        {
          match = true;
        }
      }
    }
    if(match == false && bestMatch[i]->conditions.size() != 0) //Remove the complication if the patient doesn't have medical history with it
    {
      bestMatch[i]->points = 0; //Remove any points given to the vector
      bestMatch.erase(bestMatch.begin() + i); //Remove it from vector
      i = 0; //Reset to check
    }
    match = false;
  }
}

/*
* Name: printBestMatch
* Functionality: Prints the current bestMatch vector in descending order
** - Totals points as to how popular a complication is per symptom input
**/
void Graph::printBestMatch()
{
  double percentage, total = 0;
  vertex* temp;
  bool doneSorting = true;
  bool done = false;
  //Total all the points
  for(int i = 0; i < bestMatch.size(); i++)
  {
    total = total + bestMatch[i]->points;
  }
  //Sort bestMatch vector
  while(done == false)
  {
    for(int i = 0; i < bestMatch.size() - 1; i++)
    {
      if(bestMatch[i]->points < bestMatch[i+1]->points) //Swap to get descending order
      {
        temp = bestMatch[i+1];
        bestMatch[i+1] = bestMatch[i];
        bestMatch[i] = temp;
        doneSorting = false;
      }
    }
    if(doneSorting == true) //No sorts were made, so we are done!
    {
      done = true;
    }
    doneSorting = true; //Reset check
  }
  //Print top complications
  for(int i = 0; i < bestMatch.size(); i++)
  {
    percentage = bestMatch[i]->points / total;
    cout << bestMatch[i]->name << " (" << setprecision(4) << percentage*100 << "% likely)" << endl;
  }
}

/*
* Name: refreshBestMatch
* Functionality: Deletes entire vector and resets points to all indices
**/
void Graph::refreshBestMatch()
{
  for(int i = 0; i < bestMatch.size(); i++)
  {
    bestMatch[i]->points = 0;
  }
  bestMatch.clear();
}
