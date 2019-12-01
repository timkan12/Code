#ifndef GRAPH_H
#define GRAPH_H
#include <vector>
#include <iostream>
using namespace std;

struct vertex;
struct adjVertex
{
  vertex* vector;
};

struct vertex
{
  string name;
  bool visited = false;
  bool complication;
  int points = 0; //Updates as bestMatch updates
  vector<string> conditions;
  vector<adjVertex> adj;
};

class Graph
{
  private:
    vector<string> conditions; //Stores possible conditions a patient can have
    vector<vertex*> vertices; //Stores vertices of graph
    vector<vertex*> bestMatch; //Stores best matched indices
  public:
    //Load already uploaded data
    void loadComplications(string filename);
    void loadConditions(string filename);
    //Adds new vertices/edges to the graph
    void addComplication(string name);
    void addSymptom(string name);
    void addEdge(string complication, string symptom);
    void addCondition(string complication, string condition);
    //Prints the vertices + edges of the graph depending on what you want to look at
    void displayComplicationsWithSymptoms();
    void displaySymptomsWithComplications();
    void displayComplicationsWithSymptomsAndConditions();
    //Prints vertices/vectors
    void displayComplications();
    void displaySymptoms();
    void displayConditions();
    //Check conditions
    bool checkCondition(string condition);
    bool checkSymptom(string symptom);
    //Functions that modifies bestMatch for pinpointing a complication
    void updateBestMatch(string symptom);
    void removeConditionsFromBestMatch(vector<string> patientConditions);
    void printBestMatch();
    void refreshBestMatch();
};

#endif
