#include<bits/stdc++.h>
using namespace std;

int main(){
	int n,e;
	cin>>n>>e;
	int mat[n][n],i,j;
	for(i=0;i<n;i++){
		for(j=0;j<n;j++){
			cin>>mat[i][j];
		}
	}
	int trans[n][n];
	for(i=0;i<n;i++){
		for(j=0;j<n;j++){
			trans[j][i]=mat[i][j];
		}
	}
	cout<<"transpose: \n";
	for(i=0;i<n;i++){
		for(j=0;j<n;j++){
			cout<<trans[i][j]<<" ";
		}
		cout<<"\n";
	}
	cin>>n>>e;
	int u,v; 
	vector<int> mat1[n+1];
	for(i=0;i<e;i++){
		cin>>u>>v;
		mat1[u].push_back(v);
	}
	vector<int> trans1[n];
	for(i=0;i<n;i++){
		for(j=0;j<mat1[i].size();j++){
			trans1[mat1[i][j]].push_back(i);
		}
	}
	cout<<"Transpose: \n";
	for(i=0;i<n;i++){
		cout<<i<<": ";
		for(j=0;j<trans1[i].size();j++){
			cout<<trans1[i][j]<<",";
		}
		cout<<"\n";
	}
	return 0;
}
