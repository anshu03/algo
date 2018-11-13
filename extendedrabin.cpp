#include <iostream>
#include <vector>
#include <string>
#include <math.h>
using namespace std;

int get_hash(string s,int d,int q){
	int n = 0;
	for(int i=0;i<s.length();i++)
		n = (n * d + s[i]) % q;
	return n;
}

void rabin_karp_extended(string T,vector<string> P,int q,int d){
	int n = T.length();
	int m = P[0].length();
	if(m>n){
		cout << "Error\n";
		exit(true);
	}
	T = "#" + T;
	// Preprocessing
	int t = 0;
	vector<int>p;
	for(int i=1;i<=m;i++)
		t = (t*d + T[i]) % q;
	for(int i=0;i<P.size();i++)
		p.push_back(get_hash(P[i],d,q));
	//Algorithm
	int h = pow(d,m-1);	// h = d^(m-1)
	int compute[n-m+1];
	compute[0] = t;
	for(int s=0;s<=n-m;s++){
		for(int k=0;k<p.size();k++){
			if(t==p[k]){
				int i=1;
				while(T[s+i]==P[k][i-1] and i<=m)
					i++;
				if(i==m+1)
					cout << "Pattern " << P[k] << " occurs with shift " << s << "\n";
			}
		}
		if(s<n-m){
			t = (d * (t - (T[s+1]-'0')*h) + T[s+m+1]-'0') % q;
			if(t<0)
				t += q;
			compute[s+1] = t;
		}
	}
	for(int i=0;i<=n-m;i++)
		cout << compute[i] << " ";	
	cout << "\n";
}

int main(){
	string text, pattern;
	cout << "Enter text: ";
	cin >> text;
	cout << "Number of patterns: ";
	int n_p;
	cin >> n_p;
	vector<string>patterns;		// Patterns should be of each length.
	cout << "Enter the patterns\n";
	while(n_p--){
		string s;
		cin >> s;
		patterns.push_back(s);
	}
	int q,d;
	cout << "Enter the prime and radix number: ";
	cin >> q >> d;
	rabin_karp_extended(text,patterns,q,d);
	return 0;
}