#include <iostream>
#include <string>
#include <utility>
#include <map>
using namespace std;

//Time complexity O(m*z)
map<pair<int,char>,int> compute_transition_function(string P,int z){
	map<pair<int,char>,int> mp;
	int m = P.length();
	P = "#" + P;
	int pi[P.length()];
	pi[0] = pi[1] = 0;
	int k = 0;
	for(int i=2;i<=m;i++){
		while(k>0 and P[k+1]!=P[i] and k<m)
			k = pi[k];
		if(P[k+1]==P[i])
			k = k+1;
		pi[i] = k;
	}
	int q = 0;
	while(q<=m){
		for(char i=0;i<z;i++){
			char a = 'a'+i;
			// Compute transtion(q,a)
			if(P[q+1]==a and q!=m)
				mp[make_pair(q,a)] = q+1;
			else
				mp[make_pair(q,a)] = mp[make_pair(pi[q],a)];
		}
		q++;
	}
	return mp;
}

//Time Complexity O(n)
void finite_automata_matcher(string T,map<pair<int,char>,int>transition,int m,int z){
	/*
	  Arguments: 
		string T 		            Input Text String
		map<pair<int,char>,int> transition  It is the transition function for the automata
						    which map from STATE x CHARACTER to STATE 
		int m				    Length of the pattern
		int z				    Size of the alphabet
	*/
	int n = T.length();
	int q = 0;		// Initial state
	for(int i=0;i<n;i++){
		q = transition[make_pair(q,T[i])];
		if(q==m)
			cout << "Pattern occurs at shift " << i-m+1 << "\n";
	}
}

int main(){
	string text, pattern;
	cout << "Enter Text and Pattern: ";
	cin >> text >> pattern;
	int alphabet_size;
	cout << "Size of the alphabet: ";
	cin >> alphabet_size;
	//Overall Time Complexity O(m*z+n)
	map<pair<int,char>,int> transition = compute_transition_function(pattern,alphabet_size);
	finite_automata_matcher(text,transition,pattern.length(),alphabet_size);
	return 0;
}