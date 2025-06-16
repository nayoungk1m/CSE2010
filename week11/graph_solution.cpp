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
#include "min_heap.hpp"
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
public:
// TODO. Define a constructor, a destructor, and proper methods
  /* GRAPH REPRESENTATIONS */
  int nVertices;
  int nEdges;
  pair<int, int>** neighbors;   // nVertices * (edge, weight)
  int* nNeighbors;
  int* distance;
  int* predecessor;
  Graph():neighbors(nullptr), nNeighbors(nullptr), distance(nullptr), predecessor(nullptr) {}
  ~Graph();
  void printGraph();
  void build(int, int, vector<tuple<int, int, int>>&);
  bool isAdjacent(int, int);
  vector<int> getNeighbors(int);
  vector<int> breadthFirstSearch(int);
  vector<int> depthFirstSearch(int);
  bool isReachable(int, int);
  bool runDijstra(int, int, vector<int>&);
  bool topologicalSort(vector<int>&);
};

Graph::~Graph() {
  if (neighbors != nullptr) {
    for (int i = 0; i < nVertices; i++) {
      if (neighbors[i] != nullptr)
        delete neighbors[i];
    }
    neighbors = nullptr;
  }
  if (nNeighbors != nullptr) {
    delete nNeighbors;
    nNeighbors = nullptr;
  }
  if (distance != nullptr) {
    delete distance;
    distance = nullptr;
  }
  if (predecessor != nullptr) {
    delete predecessor;
    predecessor = nullptr;
  }
}

void Graph::build(int n, int m, vector<tuple<int, int, int>>& data) {
  int u, v, wgt;
  nVertices = n;
  nEdges = m;
  nNeighbors = new int[n]();
  distance = new int[n];
  predecessor = new int[n];
  vector<tuple<int, int, int>>::iterator it;
  for (it = data.begin(); it != data.end(); ++it) {
    tie(u, v, wgt) = *it;
    assert(u >= 0 && u < nVertices);
    assert(v >= 0 && v < nVertices);
    ++nNeighbors[u];
  }
  neighbors = new pair<int, int>*[nVertices];
  for (int i = 0; i < nVertices; ++i) {
    if (nNeighbors[i] > 0) 
      neighbors[i] = new pair<int, int>[nNeighbors[i]];
    else
      neighbors[i] = nullptr;
  }
  memset(nNeighbors, 0, sizeof(int) * nVertices);
  for (it = data.begin(); it != data.end(); ++it) {
    tie(u, v, wgt) = *it;
    neighbors[u][nNeighbors[u]++] = make_pair(v, wgt);
  }
}

bool Graph::isAdjacent(int u, int v) {
  assert(u >= 0 && u < nVertices);
  assert(v >= 0 && v < nVertices);
  for (int j = 0; j < nNeighbors[u]; ++j) {
    if (neighbors[u][j].first == v) {
      return true;
    }
  }
  return false;
}

vector<int> Graph::getNeighbors(int u) {
  assert(u >= 0 && u < nVertices);
  vector<int> nbrs(nNeighbors[u]);
  for (int j = 0; j < nNeighbors[u]; ++j) {
    nbrs[j] = neighbors[u][j].first;
  }
  return nbrs;
}

vector<int> Graph::depthFirstSearch(int s) {
  vector<bool> visited(nVertices, false);
  stack<int> st;
  vector<int> result;
  
  st.push(s);
  while (!st.empty()) {
    int u = st.top();
    st.pop();

    if (!visited[u]) {
      result.push_back(u);
      cout << "visit " << u << " " << endl;
      visited[u] = true;

      vector<int> nbrs = getNeighbors(u);
      for (const int v : nbrs) {
        if (!visited[v]) {
        st.push(v);
        }
      }
    }
  }
  return result;
}

bool Graph::topologicalSort(vector<int>& out) {
  out.clear();
  queue<int> q;
  int cnt = 0;
  
  // in-degree 계산
  // Time complexity: O(|V| + |E|)
  int* inCnt = new int[nVertices]();
  for (int u = 0; u < nVertices; ++u) {
    for (int i = 0; i < nNeighbors[u]; ++i) {
      ++inCnt[neighbors[u][i].first];
    }
  }

  for (int u = 0; u < nVertices; ++u) {
    if (inCnt[u] == 0)
      q.push(u);
  }
  // while loop iterates |V| times
  // (1 + indegree(v)) * every vertex v
  // Time complexity: O(|V| + |E|)
  while (!q.empty()) {
    int u = q.front();
    q.pop();
    out.push_back(u);
    for (int i = 0; i < nNeighbors[u]; ++i) {
      int v = neighbors[u][i].first;
      --inCnt[v];
      if (inCnt[v] == 0)
        q.push(v);
    }
    ++cnt;
  }
  delete inCnt;
  return (cnt == nVertices);
}

bool Graph::runDijstra(int s, int t, vector<int>& output) {
  fill(distance, distance+nVertices, INT_MAX);
  memset(predecessor, -1, sizeof(int) * nVertices);
  assert(s >= 0 && s < nVertices);
  assert(t >= 0 && t < nVertices);
  distance[s] = 0;
  
  // Build min priority queue Q with keys of distance[v] for all v
  MinHeap pq(nVertices);
  pq.build(distance, nVertices);
  while (!pq.isEmpty()) {
    int u = pq.deleteMinimum();
    int v, wgt;
    for (int i = 0; i < nNeighbors[u]; ++i) {
      tie(v, wgt) = neighbors[u][i];
      if (distance[u] < (INT_MAX - wgt) && distance[u] + wgt < distance[u]) {
        distance[v] = distance[u] + wgt;
        pq.decreaseKey(v, distance[v]);
        predecessor[v] = u;
      }
    }
  }

  int u = t;
  while (u != s) {
    output.push_back(u);
    u = predecessor[u];
    if (u < 0) {
      output.clear();
      return false;
    }
  }
  output.push_back(s);
  reverse(output.begin(), output.end());
  return true;
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
        g.build(nVertices, nEdges, data);
        break;
      case IS_ADJACENT:
        if (!(iss >> u >> v)) {
          cerr<<"isAdjacent: invalid input"<<endl;
          exit(1);
        }
        // TODO. Check if edge (u, v) exists in the graph
        break;
      case GET_NEIGHBORS:
        if (!(iss >> u)) {
          cerr<<"getNeighbors: invalid input"<<endl;
          exit(1);
        }
        // TODO. Get all the neighbors of u
        break;
      case DFS:
        g.depthFirstSearch(0);
      default:
        cerr<<"Undefined operator"<<endl;
        exit(1);
    }
  }
  outFile.close();
  inFile.close();
}
