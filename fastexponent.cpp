#include <iostream>
#include <istream>
#include <ostream>
using namespace std;

// Time Complexity = O(log(m))
// Computation reduced to half at each check of m
long long int fast_exponentiation(long long int a,int m){
	if(m<0){
		cout << "Not valid for negative powers\n";
		return -1;
	}
	else if(m==0)
		return 1;
	else if(m==1)
		return a;
	if(m%2==0)	// If power is even
		return fast_exponentiation(a*a,m/2);	
	else		// If power is odd
		return a * fast_exponentiation(a*a,m/2);
}

int main(void){
	long long int a;
	int m;
	cout << "Enter the number: ";
	cin >> a;
	cout << "Enter the power to be raised to: ";
	cin >> m;
	long long int answer = fast_exponentiation(a,m);
	if(answer!=-1)
		cout << a << "^" << m << " is: " << answer << "\n";
	return 0;
}