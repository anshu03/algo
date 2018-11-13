#include <iostream>
#include <istream>
#include <ostream>
using namespace std;

// Time Complexity = O(log(m))
// Computation reduced to half at each check of m
int modular_exponentiation(int a,int m,int n){
	if(m<0){
		cout << "Not valid for negative powers\n";
		return -1;
	}
	else if(m==0)
		return (1%n);
	else if(m==1)
		return a;
	if(m%2==0)	// If power is even
		return modular_exponentiation((a*a)%n,m/2,n);	
	else		// If power is odd
		return (a * modular_exponentiation((a*a)%n,m/2,n))%n;
}

int main(void){
	int a,m,n;
	cout << "Enter the number: ";
	cin >> a;
	cout << "Enter the power to be raised to: ";
	cin >> m;
	cout << "Modulo integer: ";
	cin >> n;
	int answer = modular_exponentiation(a%n,m,n);
	if(answer!=-1)
		cout << "(" << a << "^" << m << ")%" << n <<" is: " << answer << "\n";
	return 0;
}