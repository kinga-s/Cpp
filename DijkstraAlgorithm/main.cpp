/*
 * @Kinga Syta
 * DijkstraAlgorithm program
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
    vector< vector<int> > inMatrix; //adjacency matrix of input graph
    vector< vector<int> > dijkstraList; //two dimension table:
                                        //[][0] get the values of the distance between start vertex and this vertex
                                        //[][1] get the values: 0 if the vertex is white (not visited),
                                        // 1 if the vertex is gray(in the queue),
                                        // 2 if the vertex is black (already out of the queue)

public:
    void readFile(string filename); //read given csv file
    void makeInMatrix(int first, int last, int weight); //create given as csv file adjacency matrix
    void addVertex(); //add vertex to inMatrix and dijkstraList
    void Dijkstra(int startVertex); //dijkstra algorithm
    void coutDistance(int vertex1, int vertex2); //write the distance between start vertex and end vertexes
};

void Graph::coutDistance(int vertex1, int vertex2) {
    cout<<dijkstraList[vertex1][0]<<" "<<dijkstraList[vertex2][0]; //add 1 because dijkstraList is from 0
}

void Graph::Dijkstra(int startVertex) {

    dijkstraList[startVertex][0] = 0;
    dijkstraList[startVertex][1] = 1;

    for(int h = 0; h<dijkstraList.size(); h++){ //for every vertex
        double value = LIMIT;
        int actualVertex = 0;
        for(int i = 0; i < dijkstraList.size(); i++){ //look for the smallest element in the queue
            if(dijkstraList[i][1] == 1){
                if(value > dijkstraList[i][0]){
                    value = dijkstraList[i][0];
                    actualVertex = i; //actualVertex is an vertex index that has the smallest element in the queue
                }
            }
        }

        for(int i = 0; i < inMatrix.size(); i++){ //checking all the neighbors
            if(inMatrix[actualVertex][i] != -1 && dijkstraList[i][1] != 2){
                if(dijkstraList[i][0] > (dijkstraList[actualVertex][0] + inMatrix[actualVertex][i])){
                    dijkstraList[i][0] = dijkstraList[actualVertex][0] + inMatrix[actualVertex][i];
                    if(dijkstraList[i][1] == 0){
                        dijkstraList[i][1] = 1; //add element to the queue
                    }
                }
            }
        }
        dijkstraList[actualVertex][1] = 2; //next time we won't search the smallest path
                                            // for this element, cause it already exists

    }

}

void Graph::addVertex() {
    vector<int> newVertex;

    inMatrix.push_back(newVertex);
    for(int i = 0; i < inMatrix.size(); i++){
        inMatrix[inMatrix.size()-1].push_back(-1);
    }

    for(int i = 0; i < inMatrix.size(); i++){
        inMatrix[i].push_back(-1); //the value to use dijkstra algorithm could not be a negative number
    }
    dijkstraList.push_back(newVertex);
    dijkstraList[dijkstraList.size()-1].push_back(LIMIT);
    dijkstraList[dijkstraList.size()-1].push_back(0);
}

void Graph::makeInMatrix(int first, int last, int weight) {
    while(inMatrix.size() <= first || inMatrix.size() <= last){
        addVertex();
    }
    inMatrix[first][last] = weight;
}

void Graph::readFile(string filename){

    fstream file;
    file.open(filename,ios::in);
    if(!file.good()){
        cout<<"File doesn't exist\n";
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
}



int main(int argc, char *argv[]){

    clock_t start = clock();
    Graph graph;

    graph.readFile(argv[1]);
    string startV = argv[2];
    graph.Dijkstra(stoi(startV.c_str()));
    string v1 = argv[3];
    string v2 = argv[4];
    graph.coutDistance(stoi(v1.c_str()), stoi(v2.c_str()));
    printf( "\n%lu ms\n", clock() - start );
    return 0;
}