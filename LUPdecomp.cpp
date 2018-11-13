// LINEAR EQUATION SOLVER
#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;
/*
	AX = B
	PA = LU , P is permutation matrix
	PA.X = PB
	LU.X = PB
	LY = PB where Y = UX
*/
int main(){
	int size;
	cout << "Size of the matrix: ";
	cin >> size;
	cout << "Enter the matrix:\n";
	float mat[size+1][size+1];
	for(int i=1;i<=size;i++){
		for(int j=1;j<=size;j++)
			cin >> mat[i][j];
	}
	cout << "Answer matrix: ";
	float b[size+1];
	for(int i=1;i<=size;i++)
		cin >> b[i];
	cout << "Performing decomposition...\n";
	int p[size+1];
	for(int i=1;i<=size;i++)
		p[i] = i;
	for(int k=1;k<=size;k++){
		float pi = 0;
		int k1;
		for(int i=k;i<=size;i++){
			if(abs(mat[i][k])>pi){
				pi = abs(mat[i][k]);
				k1 = i;
			}
		}
		if(pi==0){
			cout << "Error\n";
			return 1;	
		}
		swap(p[k],p[k1]);
		for(int i=1;i<=size;i++)
			swap(mat[k][i],mat[k1][i]);
		for(int i=k+1;i<=size;i++){
			mat[i][k] /= mat[k][k];
			for(int j=k+1;j<=size;j++)
				mat[i][j] = mat[i][j] - mat[i][k] * mat[k][j];
		}
	}
	float l[size+1][size+1];
	float u[size+1][size+1];
	float y[size+1];
	float x[size+1];
	for(int i=1;i<=size;i++){
		for(int j=1;j<=size;j++){
			if(i>j){
				l[i][j] = mat[i][j];
				u[i][j] = 0;			
			}
			else if(i==j){
				l[i][j] = 1;
				u[i][j] = mat[i][j];
			}
			else if(i<j){
				l[i][j] = 0;
				u[i][j] = mat[i][j];
			}
		}
	}
	cout << "L Matrix\n";
	for(int i=1;i<=size;i++){
		for(int j=1;j<=size;j++)
			cout << l[i][j] << "\t";
		cout << "\n";
	}
	cout << "U Matrix\n";
	for(int i=1;i<=size;i++){
		for(int j=1;j<=size;j++)
			cout << u[i][j] << "\t";
		cout << "\n";
	}
	cout << "Decomposition done\n";
	for(int i=1;i<=size;i++){
		if(i==1){
			y[i] = b[p[i]];
			continue;
		}
		float sum = 0;
		for(int j=1;j<i;j++)
			sum += y[j] * l[i][j];
		y[i] = (b[p[i]] - sum) / l[i][i];
	}
	// Answer Vector
	for(int i=size;i>=1;i--){
		if(i==size){
			x[i] = y[i] / u[i][i];
			continue;
		}
		float sum = 0;
		for(int j=size;j>i;j--)
			sum += x[j] * u[i][j];
		x[i] = (y[i] - sum) / u[i][i];
	}
	// Print Answer
	cout << "Answer: ";
	for(int i=1;i<=size;i++)
		cout << x[i] << " ";
	cout << "\n";
	return 0;
}