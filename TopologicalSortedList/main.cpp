#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
vector < vector <int> > vertexAdjacencyList; //Adjacency List of input graph
vector < vector <int> > rVertexAdjacencyList; //reverse adjacency List of input graph
class Graph{

    string text;
    int first, last; //first vertex of the edge, last vertex of the edge
    //int weight;


    struct Vertex{
        int parent; //parent of the vertex
        int inTime; //time when we inter into the vertex
        int outTime;//time when we leave the vertex
    };

    vector<Vertex> dfsList; //list of vertexes in dfs algorithm
    int time; //time
    vector<int> topologicalSortList; // topological sorted list after DFS algorithm
    vector<int> roots; //vertexes that have no parents
    int VInTSL; //actual number of vertexes in topological sorted list
    int helperVInTSL;


public:
    void makeVertex(); //create new vertex in vertexAdjacencyList
    void adjacencyListDirected(int first, int last); //create a adjacency list for a directed graph
    void readFile(string filename); //read the file given as filename and create a adjacency list
    void DFS(vector<vector<int>> vertexAdjacencyList); //DFS algorithm
    int dfsVisit(vector<vector<int>> vertexAdjacencyList, int vertex); //recurse function dfs
    void makeDFSVertex(); //make vertex of dfsList with the start values: parent 0, inTime = 0, outTime = 0
    void coutTSL(); // cout topological sorted list
    void makeRoots(); // put vertexes to vector named roots
};


void Graph::makeVertex() {
    vector<int> newVertex;
    vertexAdjacencyList.push_back(newVertex);
    rVertexAdjacencyList.push_back(newVertex);
    makeDFSVertex();
}

void Graph::makeDFSVertex(){
    Vertex v = {0,0,0};
    dfsList.push_back(v);
}

void Graph::adjacencyListDirected(int first, int last){
    while(first > vertexAdjacencyList.size()-1 || last > vertexAdjacencyList.size()-1){
        makeVertex();
    }

    vertexAdjacencyList[first].push_back(last);
    if(first != last) {
        rVertexAdjacencyList[last].push_back(first);
    }
}


void Graph::readFile(string filename){
    fstream file;
    file.open(filename,ios::in);
    while(!file.good()){
        cout<<"File doesn't exist\n";
    }
    makeVertex();
    while(!file.eof()){
        getline(file, text, ',');
        first = stoi(text.c_str());
        getline(file, text, ',');
        last = stoi(text.c_str());
        getline(file, text, '\n');
        //weight = stoi(text.c_str());
        adjacencyListDirected(first, last);
    }
    file.close();
}


void Graph::DFS(vector<vector<int>> vertexAdjacencyList) {
    int parent;
    time = 0;
    dfsList.reserve(vertexAdjacencyList.size()); //time optimization
    topologicalSortList.reserve(vertexAdjacencyList.size()-1); //time optimization
    makeRoots();
    helperVInTSL = 0;
    for(auto vertex: roots){
        VInTSL = helperVInTSL;
        dfsList[vertex].parent = 0;
        parent = dfsVisit(vertexAdjacencyList, vertex);
        while (parent != 0){
            parent = dfsVisit(vertexAdjacencyList, parent);
        }
    }

}

int Graph::dfsVisit(vector<vector<int>> list, int vertex) {
    time++;
    dfsList[vertex].inTime = time;
    int i;
    for(auto v: list[vertex]){
        vector<int>::iterator it;
        it = rVertexAdjacencyList[v].begin();
        i=0;
        while(rVertexAdjacencyList[v][i] != vertex){
            it++;
            i++;
        }
        rVertexAdjacencyList[v].erase(it);

        if(rVertexAdjacencyList[v].empty()){
            dfsList[v].parent = vertex;
            dfsVisit(vertexAdjacencyList, v);
        }

    }
    time++;
    dfsList[vertex].outTime = time;
    helperVInTSL++;
    topologicalSortList.insert(topologicalSortList.begin()+VInTSL, vertex);
    return dfsList[vertex].parent;
}

void Graph::makeRoots() {
    for(int i = 1; i < rVertexAdjacencyList.size(); i++){
        if(rVertexAdjacencyList[i].empty()){
            roots.push_back(i);
        }
    }
}


void Graph::coutTSL() {
    cout<<"Topological sorted list: ";
    for(int i = 0; i < topologicalSortList.size(); i++){
        cout<<topologicalSortList[i]<<" ";
    }
}


int main(int argc, char *argv[]){
    Graph graph;
    graph.readFile(argv[1]);
    graph.DFS(vertexAdjacencyList);
    graph.coutTSL();
    return 0;
}