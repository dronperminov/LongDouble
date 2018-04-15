#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include "LongDouble.h"

using namespace std;

struct TestT {
	LongDouble op1;
	LongDouble op2;
	LongDouble obtained;
	LongDouble expected;

	char op;
	bool correct;
	double time;
};

TestT testMe(char op, const LongDouble &op1, const LongDouble &op2, const LongDouble &res) {
	TestT test;

	test.op1 = op1;
	test.op2 = op2;

	clock_t t0 = clock();

	switch (op) {
		case '+':
			test.obtained = op1 + op2;
			break;
		
		case '-':
			test.obtained = op1 - op2;
			break;
		
		case '*':
			test.obtained = op1 * op2;
			break;
	}

	clock_t t1 = clock();

	test.time = ((double) (t1 - t0)) * 1000 / CLOCKS_PER_SEC;
	test.expected = res;
	test.op = op;
	test.correct = test.expected == test.obtained;

	return test;
}

void printTestResults(const vector<TestT>& tests) {
	size_t results = 0;

	for (size_t i = 0; i < tests.size(); i++) {
		results += tests[i].correct;

		cout << "Test" << (i + 1) << ". ";

		if (tests[i].correct)
			cout << "OK (" << tests[i].time << " ms)";
		else
			cout << "Failed: " << tests[i].op1 << " " << tests[i].op << " " << tests[i].op2 << " = " << tests[i].expected << " != " << tests[i].obtained;
		
		cout << endl;
	}

	cout << "-----------------------------" << endl;
	cout << results << " / " << tests.size() << " (" << (100 * results / tests.size()) << "%)" << endl << endl;
}

void addTest() {
	vector<TestT> additions;

	additions.push_back(testMe('+', 0, 0, 0));

	additions.push_back(testMe('+', 0, 45, 45));
	additions.push_back(testMe('+', 45, 0, 45));
	additions.push_back(testMe('+', 0, -45, -45));
	additions.push_back(testMe('+', -45, 0, -45));

	additions.push_back(testMe('+', -45, 45, 0));
	additions.push_back(testMe('+', 9, 1, 10));
	additions.push_back(testMe('+', -9, -1, -10));

	additions.push_back(testMe('+', LongDouble("27.5"), LongDouble("1.025"), LongDouble("28.525")));
	additions.push_back(testMe('+', LongDouble("-27.5"), LongDouble("1.025"), LongDouble("-26.475")));
	additions.push_back(testMe('+', LongDouble("1000"), LongDouble("0.0001"), LongDouble("1000.0001")));
	additions.push_back(testMe('+', LongDouble("5"), LongDouble("0.000000001"), LongDouble("5.000000001")));

	additions.push_back(testMe('+', LongDouble("2.7"), LongDouble("0.018281828"), LongDouble("2.718281828")));
	additions.push_back(testMe('+', LongDouble("3.14159"), LongDouble("0.00000265357989"), LongDouble("3.14159265357989")));

	additions.push_back(testMe('+', -12, 25, 13));
	additions.push_back(testMe('+', 12, -25, -13));
	additions.push_back(testMe('+', -12, -25, -37));
	additions.push_back(testMe('+', 12, 25, 37));

	additions.push_back(testMe('+', 123456789, 987654321, LongDouble("1111111110")));
	additions.push_back(testMe('+', 987654321, 123456789, LongDouble("1111111110")));
	additions.push_back(testMe('+', -123456789, 987654321, LongDouble("864197532")));
	additions.push_back(testMe('+', -987654321, 123456789, LongDouble("-864197532")));
	additions.push_back(testMe('+', -123456789, -987654321, LongDouble("-1111111110")));
	additions.push_back(testMe('+', -987654321, -123456789, LongDouble("-1111111110")));
	
	cout << "Test of additions LongDouble" << endl;
	printTestResults(additions);
}

void subTest() {
	vector<TestT> subtractions;

	subtractions.push_back(testMe('-', 0, 0, 0));

	subtractions.push_back(testMe('-', 0, 25, -25));
	subtractions.push_back(testMe('-', 0, -25, 25));
	subtractions.push_back(testMe('-', -25, 0, -25));
	subtractions.push_back(testMe('-', 25, 0, 25));

	subtractions.push_back(testMe('-', -12, 25, -37));
	subtractions.push_back(testMe('-', 12, -25, 37));
	subtractions.push_back(testMe('-', -12, -25, 13));
	subtractions.push_back(testMe('-', 12, 25, -13));

	subtractions.push_back(testMe('-', 10, 1, 9));
	subtractions.push_back(testMe('-', 1000, 1, 999));
	subtractions.push_back(testMe('-', -10, 1, -11));

	subtractions.push_back(testMe('-', 12.5, 1.45, 11.05));
	subtractions.push_back(testMe('-', -12.5, 1.45, -13.95));
	subtractions.push_back(testMe('-', 12.5, -1.45, 13.95));
	subtractions.push_back(testMe('-', -12.5, -1.45, -11.05));

	subtractions.push_back(testMe('-', LongDouble("3.14159265357989"), LongDouble("3.14"), LongDouble("0.00159265357989")));
	subtractions.push_back(testMe('-', LongDouble("2.718281828"), LongDouble("0.018281828"), LongDouble("2.7")));
	subtractions.push_back(testMe('-', LongDouble("5.000000001"), LongDouble("0.000000001"), LongDouble("5")));

	subtractions.push_back(testMe('-', 123456789, 987654321, LongDouble("-864197532")));
	subtractions.push_back(testMe('-', 987654321, 123456789, LongDouble("864197532")));
	subtractions.push_back(testMe('-', -123456789, 987654321, LongDouble("-1111111110")));
	subtractions.push_back(testMe('-', -987654321, 123456789, LongDouble("-1111111110")));
	subtractions.push_back(testMe('-', -123456789, -987654321, LongDouble("864197532")));
	subtractions.push_back(testMe('-', -987654321, -123456789, LongDouble("-864197532")));

	cout << "Test of subtractions LongDouble" << endl;
	printTestResults(subtractions);
}

void multTest() {
	vector<TestT> multiplications;

	multiplications.push_back(testMe('*', 0, 0, 0));
	multiplications.push_back(testMe('*', 0, 123.5, 0));
	multiplications.push_back(testMe('*', 123.5, 0, 0));
	multiplications.push_back(testMe('*', 0, -123.5, 0));
	multiplications.push_back(testMe('*', -123.5, 0, 0));

	multiplications.push_back(testMe('*', 1, 123.5, 123.5));
	multiplications.push_back(testMe('*', 1, -123.5, -123.5));
	multiplications.push_back(testMe('*', 123.5, 1, 123.5));
	multiplications.push_back(testMe('*', 123.5, -1, -123.5));
	multiplications.push_back(testMe('*', -1, -123.5, 123.5));

	multiplications.push_back(testMe('*', 12, 13, 156));
	multiplications.push_back(testMe('*', -12, 13, -156));
	multiplications.push_back(testMe('*', 12, -13, -156));
	multiplications.push_back(testMe('*', -12, -13, 156));

	multiplications.push_back(testMe('*', 12.5, 2.05, 25.625));
	multiplications.push_back(testMe('*', 12.5, -2.05, -25.625));
	multiplications.push_back(testMe('*', -12.5, 2.05, -25.625));
	multiplications.push_back(testMe('*', -12.5, -2.05, 25.625));

	multiplications.push_back(testMe('*', 123456789, 987654321, LongDouble("121932631112635269")));
	multiplications.push_back(testMe('*', 987654321, 123456789, LongDouble("121932631112635269")));
	multiplications.push_back(testMe('*', -123456789, 987654321, LongDouble("-121932631112635269")));
	multiplications.push_back(testMe('*', -987654321, 123456789, LongDouble("-121932631112635269")));
	multiplications.push_back(testMe('*', -123456789, -987654321, LongDouble("121932631112635269")));
	multiplications.push_back(testMe('*', -987654321, -123456789, LongDouble("121932631112635269")));

	cout << "Test of multiplications LongDouble" << endl;
	printTestResults(multiplications);
}

int main() {
	addTest();
	subTest();
	multTest();
}