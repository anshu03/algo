#include <iostream>
#include <cstring>
#include <limits.h>
#define MAX 100		// Maximum number of vertices
#define MAX_DIST 1000	// Maximum possible distance
using namespace std;

// Adjacency and Parent Matrices
int adj[MAX][MAX];
int parent[MAX][MAX];

// Function for printing the path
void print_path(int v,int src,int des){
	if(src==des){
		cout << src << " ";
		return;
	}
	else if(parent[src][des]==0){
		cout << "Path does not exist";
		return;
	}
	else{
		print_path(v,src,parent[src][des]);
		cout << des << " ";
	}
}

int main(){
	int v,e;
	cout << "Enter number of vertices: ";
	cin >> v;
	cout << "Enter number of edges: ";
	cin >> e;
	// Initializing the adjacency matrix
	for(int i=1;i<=v;i++){
		for(int j=1;j<=v;j++)
			adj[i][j] = MAX_DIST;
	}
	for(int i=1;i<=v;i++)
		adj[i][i] = 0;
	// Initializing the parent values to NIL 
	memset(parent,0,sizeof(parent));
	while(e--){
		int src, des, weight;
		cin >> src >> des >> weight;	// Source, Destination and Weight
		adj[src][des] = weight;
		parent[src][des] = src;
	}
	// Applying Floyd Warshall Algorithm
	for(int k=1;k<=v;k++){
		for(int i=1;i<=v;i++){
			for(int j=1;j<=v;j++){
				if(adj[i][j] > (adj[i][k] + adj[k][j])){
					adj[i][j] = adj[i][k] + adj[k][j];
					parent[i][j] = parent[k][j];
				}
			}
		}
	}
	int src,des;
	cout << "Enter source and destination: ";
	cin >> src >> des;
	if(adj[src][des]!=MAX_DIST){
		cout << "Path length: " << adj[src][des] << "\n";
		print_path(v,src,des);
	}
	else cout << "Path does not exist";
	cout << "\n";
}
