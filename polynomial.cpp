#include <iostream>
#include <istream>
#include <ostream>
#include <vector>
#include <iterator>
#include <cmath>
#include <algorithm>
using namespace std;

struct complex{
	// Constructors
	complex(): r(0),i(0){}
	complex(int n){
		r = cos((2*M_PI)/n);
		i = sin((2*M_PI)/n);
	}
	complex(float R,float I){
		r = R;
		i = I;
	}
	// Addding two complex numbers
	complex add(complex b){
		return complex(r+b.r,i+b.i);
	}
	// Subtracting two complex numbers
	complex subtract(complex b){
		return complex(r-b.r,i-b.i);
	}
	// Multiplying two complex numbers
	complex multiply(complex b){
		return complex(r*b.r-i*b.i,r*b.i+i*b.r);
	}
	// Inverse of a complex number
	void inverse(){
		float mag = sqrt(r*r+i*i);
		r /= mag;
		i = -i/mag;
	}
	// Real and imaginary part
	float r,i;
};

vector<complex> compute_product(vector<complex> A,vector<complex> B){
	vector<complex> C;
	for(int i=0;i<A.size();++i){
		complex c = A[i].multiply(B[i]);
		C.push_back(c);
	}
	return C;
}

class polynomial{
	vector<float> coeff;
	int degree;
	public:
		/// Default Constructor
		polynomial(): degree(-1){}
		/// @param deg degree of the polynomial
		polynomial(int deg): degree(deg){}
		/// Copy Constructor
		polynomial(polynomial const& p){
			degree = p.degree;
			coeff = p.coeff;
		}
		/// Getting the input
		void input(){
			cout << "Enter the coefficient vector: ";
			float element;
			for(int i=0;i<=degree;++i){
				cin >> element;
				coeff.push_back(element);
			}
		}
		void input(int deg){
			if(deg==-1)
				return;
			degree = deg;
			coeff.clear();
			input();
		}
		/// Accessing the coefficient vector
		vector<float> get_coefficient(){
			return coeff;
		}
		/// Accessing the degree bound
		int get_bound(){
			return degree+1;
		}
		/// Adding two polynomials of same degree
		polynomial add(polynomial const&);
		/// Multiplying two polynomials of same degree
		polynomial multiply(polynomial const&);
		/// Multiplying two polynomial using FAST FOURIER TRANSFORM
		void multiply(vector<float>,vector<float>);
		/// Coefficient form to point form representation
		vector<complex> to_point(vector<float>);
		/// Point form to coefficient form representation
		vector<complex> to_coefficient(vector<complex>);
		/// Evaluate for x: Horner's Rule
		int evaluate(float x){
			if(degree==-1)
				return -1;
			float ans = 0;
			for(int i=degree;i>=0;--i)
				ans = x*ans + coeff[i];
			return ans;
		}
		/// Print the coefficient vector
		void print(){
			if(degree==-1){
				cout << "Empty vector\n";
				return;
			}
			cout << "Coefficient Vector: ";
			copy(coeff.begin(),coeff.end(),ostream_iterator<float>(cout," "));
			cout << endl;
		}
};
polynomial polynomial::add(polynomial const& p){
	if(degree!=p.degree || degree<0){
		cout << "Degree of two polynomial must be same and >= 0.\n";
		return polynomial(-1);
	}
	polynomial add_(degree);
	for(int i=0;i<=degree;++i)
		add_.coeff.push_back(coeff[i] + p.coeff[i]);
	return add_;
}
// Time Complexity: O(n*n)
polynomial polynomial::multiply(polynomial const& p){
	if(degree!=p.degree || degree<0){
		cout << "Degree of two polynomial must be same and >= 0.\n";
		return polynomial(-1);
	}
	polynomial mult(2*degree-1);
	for(int i=0;i<=mult.degree;++i){
		mult.coeff.push_back(0);
		for(int j=0;j<=i;j++)
			if(j<=degree and i-j<=degree)
				mult.coeff[i] += coeff[j] * p.coeff[i-j];
	}
	return mult;
}
/// Applying FFT to convert the polynomial from coefficient form to point form
vector<complex> polynomial::to_point(vector<float> a){
	vector<complex> y;
	int n = a.size();
	if((n&(n-1))!=0){
		cout << "Degree bound must be power of 2\n";
		return y;
	}
	if(n==1){
		complex y1(a[0],0);
		y.push_back(y1);
		return y;
	}
	complex wN(n);
	complex w(1,0);
	vector<float> a0, a1;
	for(int i=0;i<n;i++){
		if(i%2==0)
			a0.push_back(a[i]);
		else a1.push_back(a[i]);
	}
	/*copy(a0.begin(),a0.end(),ostream_iterator<float>(cout," "));
	copy(a1.begin(),a1.end(),ostream_iterator<float>(cout," "));*/
	vector<complex> y0 = to_point(a0);
	vector<complex> y1 = to_point(a1);
	// Initialising y
	for(int i=0;i<n;i++)
		y.push_back(complex());
	// Combining the subproblems
	for(int k=0;k<=n/2-1;++k){
		y[k] = y0[k].add(w.multiply(y1[k]));
		y[k+n/2] = y0[k].subtract(w.multiply(y1[k]));
		w = w.multiply(wN);
	}
	return y;
}
/// Applying Inverse FFT to convert the polynomial from point form to coefficient form
vector<complex> polynomial::to_coefficient(vector<complex> y){
	vector<complex> coeff;
	int n = y.size();
	if((n&(n-1))!=0){
		cout << "Degree bound must be power of 2\n";
		return coeff;
	}
	if(n==1){
		coeff.push_back(y[0]);
		return coeff;
	}
	complex wN(n);
	wN.inverse();
	complex w(1,0);
	vector<complex> y0, y1;
	for(int i=0;i<n;i++){
		if(i%2==0)
			y0.push_back(y[i]);
		else y1.push_back(y[i]);
	}
	/*copy(a0.begin(),a0.end(),ostream_iterator<float>(cout," "));
	copy(a1.begin(),a1.end(),ostream_iterator<float>(cout," "));*/
	vector<complex> coeff0 = to_coefficient(y0);
	vector<complex> coeff1 = to_coefficient(y1);
	// Initialising y
	for(int i=0;i<n;i++)
		coeff.push_back(complex());
	// Combining the subproblems
	for(int k=0;k<=n/2-1;++k){
		coeff[k] = coeff0[k].add(w.multiply(coeff1[k]));
		coeff[k+n/2] = coeff0[k].subtract(w.multiply(coeff1[k]));
		w = w.multiply(wN);
	}
	return coeff;
}
// This function modifies the object itself to be the multiplication of the 
// two polynomials whose coefficient vectors are passed as parameters
void polynomial::multiply(vector<float> coeff_poly1,vector<float> coeff_poly2){
	/**
	  * NOTE: Assuming both the polynomial have degree d
	  *		  Also, the degree bound i.e. d+1 is a power of 2
	  *
	  * Time Complexity: O(n*log(n))
	*/
	// Empty the current the coeff vector
	coeff.clear();
	int d = coeff_poly2.size();
	if((d&(d-1))!=0){
		cout << "Error: Check the degree bound\n";
		return;
	}
	while(coeff_poly2.size()<2*d){
		coeff_poly2.push_back(0);
		coeff_poly1.push_back(0);
	}
	vector<complex> A = to_point(coeff_poly1);
	vector<complex> B = to_point(coeff_poly2);
	vector<complex> C = compute_product(A,B);
	//cout << C.size() << "\n";
	vector<complex> coeff_complex = to_coefficient(C);
	for(int i=0;i<coeff_complex.size();++i){
		if(abs(coeff_complex[i].r)<1e-5)
			coeff.push_back(0);
		else coeff.push_back(coeff_complex[i].r/coeff_complex.size());
	}
	return;
}

int main(void){
	int degree;
	cout << "Enter the degree: ";
	cin >> degree;
	polynomial p(degree);
	p.input();
	vector<float> coeff = p.get_coefficient();
	vector<complex> y = p.to_point(coeff);
	cout << "Point form is:\n";
	for(int i=0;i<y.size();++i){
		cout << "(";
		if(abs(y[i].r)<1e-6)
			cout << 0;
		else cout << y[i].r;
		cout << ",";
		if(abs(y[i].i)<1e-6)
			cout << 0;
		else cout << y[i].i; 
		cout << ")" << "\n";
	}
	vector<complex> coeffComplex = p.to_coefficient(y);
	cout << "Coefficient form is:\n";
	int n = p.get_bound();
	for(int i=0;i<coeffComplex.size();++i){
		cout << "(";
		if(abs(coeffComplex[i].r)<1e-6)
			cout << 0;
		else cout << coeffComplex[i].r/n;
		cout << ",";
		if(abs(coeffComplex[i].i)<1e-6)
			cout << 0;
		else cout << coeffComplex[i].i/n; 
		cout << ")" << "\n";
	}
	// Two polynomials for multiplication
	polynomial p1(degree);
	polynomial p2(degree);
	// Get the input coefficient vector for two polynomials
	p1.input();
	p2.input();
	// Get the coefficient vector
	vector<float> coeff_poly1 = p1.get_coefficient();
	vector<float> coeff_poly2 = p2.get_coefficient();
	// Multiplying two polynomials
	polynomial prod;
	prod.multiply(coeff_poly1,coeff_poly2);
	// Get the coefficient vector of the final polynomial
	vector<float> prod_coeff = prod.get_coefficient();
	// Reversing the coefficient vector in the decreasing order of the power of x
	reverse(prod_coeff.begin(),prod_coeff.end());
	// Print the coefficient vector
	cout << "Coefficient vector of the multiplication of two polynomial: ";
	copy(prod_coeff.begin(),prod_coeff.end(),ostream_iterator<float>(cout," "));
	cout << "\n";
	return 0;
}