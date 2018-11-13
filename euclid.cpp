// EUCLID'S ALGORITHM
#include <iostream>
#include <algorithm>
using namespace std;

/*
	Let gcd(n,m) = d
	So, n%d = 0 and m%d = 0
	IF n%m ==0 subject to n > m then gcd = m
	ELSE n = m*p + r where r = n%m
	Thus n%d = (m*p+r)%d = (m*p)%d + r%d
	0 = 0 + r%d => gcd(n,m) = gcd(m,n%m)
*/

int euclid(int n,int m){
	if(m==0)
		return n;
	return euclid(m,n%m);
}

int main(){
	int n,m;
	cout << "Enter two numbers: ";
	cin >> n >> m;
	cout << "GCD of " << n << " " << m << ": ";
	if(n<m)
		swap(n,m);
	int gcd = euclid(n,m);
	cout << gcd << "\n";
	return 0;
}