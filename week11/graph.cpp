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
  vector<vector<pair<int, int>>> adjList;   // nVertices * {(edge, weight), (edge, weight), ... }

public:
  Graph(){
    nVertices = 0;
  } ~Graph() = default;
  void construct(vector<tuple<int, int, int>>&, int, int);
  bool isAdjacent(int, int);
  vector<int> getNeighbors(int);
  vector<int> topologicalSort();
  vector<int> shortestPath(int, int);
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
    adjList[u].emplace_back(v, wgt);  /* emplace_back 사용 시 벡터 내부에서 바로 객체 생성
                                      BUT! push_back 에서는 백터에 넣기전에 일일이 생성해줘야 됨 */
  }
  
  // print adjacent lists
  for (int u = 0; u < nVertices; ++u) {
    cout << u << ":";
    for (const auto& [v, wgt] : adjList[u]) {
      cout << " (" << v << ", " << wgt << ")";
    }
    cout << endl;
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

vector<int> Graph::topologicalSort() {
  // TODO
  vector<int> t;  
  queue<int> q;

  vector<int> inDegree(nVertices, 0);
  for (int u = 0; u < nVertices; u++) {
    for (const auto& [v, _] : adjList[u]){
      inDegree[v]++;
    }
  }

  for (int v = 0; v < nVertices; v++) {
    if (inDegree[v] == 0) {
      q.push(v);
    }
  }

  while (!q.empty()) {
    int u = q.front();
    q.pop();

    t.push_back(u);

    for (const auto& [v, _] : adjList[u]) {
      inDegree[v]--;

      if (inDegree[v] == 0) {
        q.push(v);
      }
    }
  }

  // if cycle exists
  if (t.size() != nVertices) {
    cerr << "Topological Sort: Cycle detected" << endl;
    return {};
  }

  return t;
}

vector<int> Graph::shortestPath(int source, int target) {
  // TODO
  vector<int> distance(nVertices, INT_MAX);    // distance
  vector<int> predecessor(nVertices, -1);         // predecessor
  vector<bool> visited(nVertices, false);

  priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
  pq.push({0, source});   // distance, node
  distance[source] = 0;
  
  while (!pq.empty()) {
    int cur_node = pq.top().second;
    pq.pop();

    if (visited[cur_node]) continue;
    visited[cur_node] = true;

    if (cur_node == target) break;

    for (const auto& [v, wgt] : adjList[cur_node]){
      if (!visited[v] && distance[cur_node] + wgt < distance[v]) {
        distance[v] = distance[cur_node] + wgt; 
        predecessor[v] = cur_node;
        pq.push({distance[v], v});
      }
    }
  }

  vector<int> path;
  if (distance[target] == INT_MAX) return path;

  for (int v = target; v != -1; v = predecessor[v]) {
    path.push_back(v);
  }
  reverse(path.begin(), path.end());
  return path;
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
    int u, v, wgt, nVertices, nEdges, cnt, s, t;
    vector<tuple<int, int, int>> data;
    vector<int> p, nbrs, ts, path;
    bool ad;
    switch(op)
    {
      case CONSTRUCT:
        if (!(iss >> nVertices >> nEdges)) {
          cerr<<"CONSTRUCT: invalid input"<<endl;
          exit(1);
        }
        // Construct a graph
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
        // Check if edge (u, v) exists in the graph
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
        // Get all the neighbors of u
        nbrs = g.getNeighbors(u);
        for (auto& n : nbrs) {
          outFile << n << " ";
        }
        outFile << endl;
        break;
      case TOPOLOGICAL_SORT:
        // TODO: Topological Sort
        ts = g.topologicalSort();
        for (auto& t : ts) {
          outFile << t << " ";
        }
        outFile << endl;
        break;
      case SHORTEST_PATH:
        if (!(iss >> s >> t)){
          cerr<<"shortestPath: invalid input"<<endl;
          exit(1);
        }
        // TODO: Shortest Path
        path = g.shortestPath(s, t);
        for (int i = 0; i < path.size(); i++){
          outFile << path[i];
          if (i != path.size() - 1) {
            outFile << " ";
          }
        }
        break;
      default:
        cerr<<"Undefined operator"<<endl;
        exit(1);
    }
  }
  outFile.close();
  inFile.close();
}
