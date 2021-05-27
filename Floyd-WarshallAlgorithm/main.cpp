/*
 * @Kinga Syta
 * Floyd-Warshall algorithm program
 */
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <limits>
#include <ctime>
using namespace std;
const int LIMIT = numeric_limits<int>::max();

class Graph{
    vector< vector<int> > inMatrix; //adjacency matrix of shortest path
    vector< vector<int> > predecessorMatrix;//matrix of predecessors
    bool helper = false;


public:
    int readFile(string filename); //read given csv file
    void makeInMatrix(int first, int last, int weight); //create given as csv file adjacency matrix
    void addVertex(); //add vertex to inMatrix and predecessorMatrix
    void FloydWarshall(); //Floyd-Warshall algorithm
    void coutDistance(string vertexes); //write the distance between given vertexes
    void coutNegativeCycles(); //write information about negative cycle
    void coutPredecessorMatrix(); //write matrix of predecessors
    void createPath(int startV, int endV); //write the path of negative cycle
};

void Graph::coutPredecessorMatrix() {
    for(int i = 0; i < predecessorMatrix.size(); i++){
        for(int j = 0; j < predecessorMatrix.size(); j++){
            cout<<predecessorMatrix[i][j]<<" ";
        }
        cout<<endl;
    }
}

void Graph::createPath(int startV, int endV){
    if( startV == endV  && helper) cout<<startV<<" ";
    else{ helper = true;
        createPath(startV, predecessorMatrix[startV][endV]);
        cout<<endV<<" ";
    }
}

void Graph::coutNegativeCycles() {
    bool isNegativeCycle = false;
    cout<<"\nNegative cycle: ";
    for(int i = 0; i<inMatrix.size(); i++){
        if(inMatrix[i][i] < 0){
            createPath(i,i);
            cout<<endl;
            isNegativeCycle = true;
            helper = false;
        }
    }
    if(!isNegativeCycle) cout<<"DOESN'T EXIST";
    cout<<endl;
}

void Graph::coutDistance(string vertexes) {
    string startingVertex;
    string endVertex;
    bool coma = false;
    for(int i = 1; i < vertexes.size()-1; i++){
        if(!coma && vertexes[i] != ','){
            startingVertex+=vertexes[i];
        }
        else if(coma){
            endVertex+=vertexes[i];
        }
        else if(vertexes[i] == ',') coma = true;
    }
    int sv = atoi(startingVertex.c_str());
    int ev = atoi(endVertex.c_str());
    cout<<inMatrix[sv][ev]<<" ";
}

void Graph::FloydWarshall() {
    int matrixSize = inMatrix.size();

    for(int i = 0; i<matrixSize; i++){
        inMatrix[i][i] = 0;
    }


    for(int k = 0; k < matrixSize; k++ ) {
        for (int i = 0; i < matrixSize; i++)
            for (int j = 0; j < matrixSize; j++) {
                if ((inMatrix[i][k] == LIMIT) || (inMatrix[k][j] == LIMIT)) continue;
                if (inMatrix[i][j] > inMatrix[i][k] + inMatrix[k][j]) {
                    inMatrix[i][j] = inMatrix[i][k] + inMatrix[k][j];
                    predecessorMatrix[i][j] = predecessorMatrix[k][j];
                }
            }
    }
}

void Graph::addVertex() {
    vector<int> newVertex;

    inMatrix.push_back(newVertex);
    predecessorMatrix.push_back(newVertex);
    for(int i = 0; i < inMatrix.size(); i++){
        inMatrix[inMatrix.size()-1].push_back(LIMIT); //firstly, all the values are +INFINITY
        predecessorMatrix[predecessorMatrix.size()-1].push_back(-1);
    }

    for(int i = 0; i < inMatrix.size(); i++){
        inMatrix[i].push_back(LIMIT); //firstly, all the values are +INFINITY
        predecessorMatrix[i].push_back(-1);
    }
}

void Graph::makeInMatrix(int first, int last, int weight) {
    while(inMatrix.size() <= first || inMatrix.size() <= last){
        addVertex();
    }
    inMatrix[first][last] = weight;
    predecessorMatrix[first][last] = first;
}

int Graph::readFile(string filename){

    fstream file;
    file.open(filename,ios::in);
    if(!file.good()){
        cout<<"File doesn't exist\n";
        return 0;
    }

    addVertex();
    string text;
    int first, last, weight;

    while(!file.eof()){
        getline(file, text, ',');
        first = atoi(text.c_str());
        getline(file, text, ',');
        last = atoi(text.c_str());
        getline(file, text, '\n');
        weight = atoi(text.c_str());
        makeInMatrix(first, last, weight);
    }
    file.close();
    return 0;
}



int main(int argc, char *argv[]){

    Graph graph;
    graph.readFile(argv[1]);
    graph.FloydWarshall();

    for(int i = 0; i < argc-2; i++){
        graph.coutDistance(argv[i+2]);
    }
    graph.coutNegativeCycles();
    graph.coutPredecessorMatrix();

    return 0;
}