#include<bits/stdc++.h>
using namespace std;
stack<int> st;
bool vis[100]={0};

void dfs(vector<int> graph[100], int i){
	vis[i]=1;
	int j;
	for(j=0;j<graph[j].size();j++){
		if(!vis[graph[i][j]]){
			dfs(graph,graph[i][j]);
		}
	}
	st.push(i);
}

void topo(vector<int> graph[100],int n){
	int i;
	for(i=0;i<n;i++){
		if(vis[i]==0){
			dfs(graph,i);
		}
	}
	while(!st.empty()){
		i=st.top();
		cout<<i<<" ";
		st.pop();
	}
}

int main(){
	int n,e;
	cin>>n>>e;
	int u,v,i;
	vector<int> graph[100];
	for(i=0;i<e;i++){
		cin>>u>>v;
		graph[u].push_back(v);
	}
	topo(graph,n);
	return 0;
}
