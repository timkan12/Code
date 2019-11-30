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
  string condition = ""; //If changed, this means the complication can only be caused by a condition
  bool visited = false;
  bool complication;
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
    //Prints vertices
    void displayComplications();
    void displaySymptoms();
    //Functions that modifies bestMatch for pinpointing a complication
    void updateBestMatch(string symptom);
    void printBestMatch();
    void refreshBestMatch();
};

#endif
