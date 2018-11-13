#include <iostream>
#include <istream>
#include <ostream>
#include <algorithm>
using namespace std;

int modified_gcd(int a,int b,int &x,int &y){
	if(b==0){
		x = 1;
		y = 0;
		return a;
	}
	int d,x1,y1;
	d = modified_gcd(b,a%b,x1,y1);
	x = y1;
	y = x1 - (a/b)*y1;
	return d;
}

int main(void){
	int a,b;
	cout << "Enter two numbers: ";
	cin >> a >> b;
	if(b>a)
		swap(a,b);
	int gcd,x,y;
	gcd = modified_gcd(a,b,x,y);
	cout << "GCD of the above numbers is: " << gcd << endl;
	if(gcd==1){
		cout << "Modulo multiplicative inverse of " << a << " under " << b << " is: " << x << endl;
		cout << "Modulo multiplicative inverse of " << b << " under " << a << " is: " << y << endl;
	}
	return 0;	
}