#include<bits/stdc++.h>
using namespace std;
stack<int> st;
bool vis[100]={0};
bool vis2[100]={0};
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
}

void dfs2(vector<int> tran[100], int i){
	vis2[i]=1;
	int j;
	for(j=0;j<tran[i].size();j++){
		if(!vis2[tran[i][j]]){
			dfs2(tran,tran[i][j]);
		}
	}
}

void strong(vector<int> tran[100], int n){
	int i,cnt=0;
	while(!st.empty()){
		i=st.top();
		st.pop();
		if(vis2[i]==0){
			dfs2(tran,i);
			cnt++;
		}
	}
	cout<<"\n"<<cnt+1;
}

int main(){
	int n,e;
	cin>>n>>e;
	int u,v,i,j;
	vector<int> graph[100];
	for(i=0;i<e;i++){
		cin>>u>>v;
		graph[u].push_back(v);
	}
	topo(graph,n);
	vector<int> tran[100];
	for(i=0;i<n;i++){
		for(j=0;j<graph[i].size();j++){
			tran[graph[i][j]].push_back(i);
		}
	}
	strong(tran,n);
	return 0;
}
