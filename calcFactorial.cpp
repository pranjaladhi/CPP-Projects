//Evaluating and outputting the factorial function at a given location up to a max location, both arguments given by the user  
#include <iostream>
#include <cmath>
#include <cstdlib>

using namespace std;

//Calculating the function given at n location from 1 to k
int cFunc(int n, int k) {
	double storeValue;
	int nFactorial = 1;
	for (int i = 2; i <= n; i++) {
		nFactorial *= i;
	}
	for (int a = 1; a <= k; a++) {
		int kFactorial = 1, nkFactorial = 1;
		double nk = n - a;
		for (int h = 2; h <= a; h++) {
			kFactorial *= h;
		}
		for (int j = 2; j <= nk; j++) {
			nkFactorial *= j;
		}
		storeValue = nFactorial / (kFactorial*nkFactorial); //The factorial function
		cout << "For c(" << n << ", " << a << ") " << "= " << storeValue << endl;
	}
	return 0;
}

//Takes the user's input for n and k variables and calls the function above
int main() {
	int nN, kK;
	cout << "Enter a value for n: "; cin >> nN;
	cout << "Enter a value for maximum k: "; cin >> kK;
	cFunc(nN, kK);
	return 0;
}
