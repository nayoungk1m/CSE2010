// Practice 10. Graph Representation
#include <algorithm>
#include <cassert>
#include <climits>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <queue> // BFS
#include <sstream>
#include <stack> // DFS
#include <tuple>
#include <vector>
using namespace std;
const char CONSTRUCT = 'C';
const char IS_ADJACENT = 'I';
const char GET_NEIGHBORS = 'N';
const char BFS = 'B';
const char DFS = 'D';
const char REACHABLITY = 'R';
const char TOPOLOGICAL_SORT = 'T';
const char SHORTEST_PATH = 'S';

class Graph {
private:
  int nVertices;
  vector<vector<pair<int, int>>> adjList;

public:
// TODO. Define a constructor, a destructor, and proper methods
  Graph(){
    nVertices = 0;
  } ~Graph() = default;
  void construct(vector<tuple<int, int, int>>&, int, int);
  bool isAdjacent(int, int);
  vector<int> getNeighbors(int);
};

void Graph::construct(vector<tuple<int, int, int>> &data, int nV, int nE) {
  if (data.size() != nE) {
    cerr << "CONSTRUCT: Edge count mismatch" << endl;
    exit(1);
  }
  nVertices = nV;
  adjList.assign(nVertices, vector<pair<int, int>>());

  for (int i = 0; i < nE; ++i) {
    int u, v, wgt;
    u = get<0>(data[i]);
    v = get<1>(data[i]);
    wgt = get<2>(data[i]);
    if (u < 0 || u >= nVertices || v < 0 || v >= nVertices) {
      cerr << "CONSTRUCT: Invalid vertex value" << endl;
      exit(1);
    }
    adjList[u].emplace_back(v, wgt);
  }
}
 
bool Graph::isAdjacent(int u, int v) {
  if (u >= nVertices || v >= nVertices || u < 0 || v < 0) {
    cerr << "isAdjacent: Invalid vertex value" << endl;
    return false;
  }
  for (const auto& [neighbor, weight] : adjList[u]) {
    if (neighbor == v) return true;
  }
  return false;
}

vector<int> Graph::getNeighbors(int u) {
  vector<int> neighbors;
  for (const auto& [v, _] : adjList[u]) {
    neighbors.push_back(v);
  }
  return neighbors;
}

int main(int argc, char* argv[]) {
  if (argc != 3) {
    cerr<<"Correct usage: [exe] [input] [output]"<<endl;
    exit(1);
  }
  Graph g;
  ifstream inFile(argv[1]);
  ofstream outFile(argv[2]);
  string line;
  while (getline(inFile, line))
  {
    char op = line[0];
    istringstream iss(line.substr(1));
    int u, v, wgt, nVertices, nEdges, cnt;
    vector<tuple<int, int, int>> data;
    vector<int> p, nbrs;
    bool ad;
    switch(op)
    {
      case CONSTRUCT:
        if (!(iss >> nVertices >> nEdges)) {
          cerr<<"CONSTRUCT: invalid input"<<endl;
          exit(1);
        }
        // TODO. Construct a graph
        for (int i = 0; i < nEdges; ++i) {
          if (!getline(inFile, line)) {
            cerr << "CONSTRUCT: not enough edge data" << endl;
            exit(1);
          }
          istringstream edgeStream(line);
          if (!(edgeStream >> u >> v >> wgt)) {
            cerr << "CONSTRUCT: invalid edge format" << endl;
            exit(1);
          }
          data.emplace_back(u, v, wgt);
        }
        g.construct(data, nVertices, nEdges);
        break;
      case IS_ADJACENT:
        if (!(iss >> u >> v)) {
          cerr<<"isAdjacent: invalid input"<<endl;
          exit(1);
        }
        // TODO. Check if edge (u, v) exists in the graph
        ad = g.isAdjacent(u, v);
        if (ad == true) {
          outFile << u << " " << v << " " << "T" << endl;
        } else {
          outFile << u << " " << v << " " << "F" << endl;
        }
        break;
      case GET_NEIGHBORS:
        if (!(iss >> u)) {
          cerr<<"getNeighbors: invalid input"<<endl;
          exit(1);
        }
        // TODO. Get all the neighbors of u
        nbrs = g.getNeighbors(u);
        for (auto& n : nbrs) {
          outFile << n << " ";
        }
        outFile << endl;
        break;
      default:
        cerr<<"Undefined operator"<<endl;
        exit(1);
    }
  }
  outFile.close();
  inFile.close();
}
