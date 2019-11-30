#include "Graph.hpp"
#include <iostream>
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
    string conditionName;
    while(getline(conditionsFile, dataLine)) //Reads each line for each condition
    {
      stringstream(dataLine);
      getline(stream, conditionName,'|'); //Gets condition name
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
      complicationVertex->condition = condition;
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
* Name: displayComplicationsWithSymptoms
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
    if(vertices[i]->complication == false)
    {
      cout << vertices[i]->name << endl;
    }
  }
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
  //Search for symptom vertice
  for(int i = 0; i < vertices.size(); i++)
  {
    if(symptom == vertices[i]->name)
    {
      symptomVertex = vertices[i];
    }
  }
  //if bestMatch is empty
  if(bestMatch.size() == 0)
  {
    for(int i = 0; i < symptomVertex->adj.size(); i++)
    {
      bestMatch.push_back(symptomVertex->adj[i].vector);
    }
  }
  //if bestMatch is not empty, we will remove vectors to further focus on a complication
  else
  {
    for(int i = 0; i < bestMatch.size(); i++)
    {
      for(int j = 0; j < symptomVertex->adj.size(); j++)
      {
        if(j == (symptomVertex->adj.size() - 1) && symptomVertex->adj[j].vector->name != bestMatch[i]->name)
        {
          bestMatch.erase(bestMatch.begin() + i - 1);
          i = 0; //Reset
        }
      }
    }
  }
}

/*
* Name: printBestMatchFunction
* Functionality: Prints the current bestMatch vector
**/
void Graph::printBestMatch()
{
  for(int i = 0; i < bestMatch.size(); i++)
  {
    cout << bestMatch[i]->name << endl;
  }
}

/*
* Name: refreshBestMatch
* Functionality: Deletes entire vector
**/
void Graph::refreshBestMatch()
{
  bestMatch.clear();
}
