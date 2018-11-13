#include <bits/stdc++.h> 
using namespace std; 

class AdjListNode 
{ 
    int v; 
    int weight; 
public: 
    AdjListNode(int _v, int _w) 
    { 
        v = _v; 
        weight = _w; 
    } 
    int getV() 
    { 
        return v; 
    } 
    int getWeight() 
    { 
        return weight; 
    } 
}; 

class Graph 
{ 
    int V;
    list<AdjListNode>* adj;
    void longestPathUtil(int, vector<bool> &, stack<int> &); 
public: 
    Graph(int); // Constructor 
    ~Graph();
    void addEdge(int, int, int); 
  
    void longestPath(int); 
}; 
  
Graph::Graph(int V) // Constructor 
{ 
    this->V = V; 
    adj = new list<AdjListNode>[V]; 
} 
  
Graph::~Graph() // Destructor 
{ 
    delete[] adj; 
} 
  
void Graph::addEdge(int u, int v, int weight) 
{ 
    AdjListNode node(v, weight); 
    adj[u].push_back(node); // Add v to u's list 
} 

void Graph::longestPathUtil(int v, vector<bool> &visited, 
                            stack<int> &Stack) 
{ 
    // Mark the current node as visited 
    visited[v] = true; 
  
    // Recur for all the vertices adjacent to this vertex 
    for (AdjListNode node : adj[v]) 
    { 
        if (!visited[node.getV()]) 
            longestPathUtil(node.getV(), visited, Stack); 
    } 
  
    // Push current vertex to stack which stores topological 
    // sort 
    Stack.push(v); 
} 
  
// The function do Topological Sort and finds longest 
// distances from given source vertex 
void Graph::longestPath(int s) 
{ 
    // Initialize distances to all vertices as infinite and 
    // distance to source as 0 
    int dist[V]; 
    for (int i = 0; i < V; i++) 
        dist[i] = INT_MAX; 
    dist[s] = 0; 
  
    stack<int> Stack; 
  
    // Mark all the vertices as not visited 
    vector<bool> visited(V, false); 
  
    for (int i = 0; i < V; i++) 
        if (visited[i] == false) 
            longestPathUtil(i, visited, Stack); 
  
    // Process vertices in topological order 
    while (!Stack.empty()) 
    { 
        // Get the next vertex from topological order 
        int u = Stack.top(); 
        Stack.pop(); 
  
        if (dist[u] != INT_MAX) 
        { 
        
            for (AdjListNode v : adj[u]) 
            { 
                if (dist[v.getV()] > dist[u] + v.getWeight() * -1) 
                    dist[v.getV()] = dist[u] + v.getWeight() * -1; 
            } 
        } 
    } 
  
    // Print the calculated longest distances 
    for (int i = 0; i < V; i++) 
    { 
        if (dist[i] == INT_MAX) 
            cout << "INT_MIN "; 
        else
            cout << (dist[i] * -1) << " "; 
    } 
} 
  
// Driver code 
int main() 
{ 
    Graph g(6); 
  
    g.addEdge(0, 1, 5); 
    g.addEdge(0, 2, 3); 
    g.addEdge(1, 3, 6); 
    g.addEdge(1, 2, 2); 
    g.addEdge(2, 4, 4); 
    g.addEdge(2, 5, 2); 
    g.addEdge(2, 3, 7); 
    g.addEdge(3, 5, 1); 
    g.addEdge(3, 4, -1); 
    g.addEdge(4, 5, -2); 
  
    int s = 1; 
  
    cout << "Following are longest distances from "
         << "source vertex " << s << " \n"; 
    g.longestPath(s); 
  
    return 0; 
} 