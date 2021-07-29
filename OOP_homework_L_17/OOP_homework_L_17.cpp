#include <iostream>
#include "Expression.h"
using namespace std;

int main() {

	Expression express;
	string example = "2+40.5-6^4";
	double answer = express.Computation(example);
	cout << "Input an expression : ";
	cin >> example;
	cout << endl << endl;
	if (answer != 0) {
		cout << example;
		cout << " = " << answer;
	}
	cout << "\nDone";
	system("pause>>NUL");
	return 0;
}