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

		case '/':
			test.obtained = op1 / op2;
			break;

		case '^':
			test.obtained = op1.pow(op2);
	}

	clock_t t1 = clock();

	test.time = ((double) (t1 - t0)) * 1000 / CLOCKS_PER_SEC;
	test.expected = res;
	test.op = op;
	test.correct = test.expected == test.obtained;

	return test;
}

TestT testMe(char op, const LongDouble &op1, const LongDouble &res) {
	TestT test;

	test.op1 = op1;

	clock_t t0 = clock();

	switch (op) {
		case 'v':
			test.obtained = op1.sqrt();
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
		else {
			cout << "Failed: ";

			if (tests[i].op != 'v') {
				cout << tests[i].op1 << " " << tests[i].op << " " << tests[i].op2 << " = " << tests[i].expected << " != " << tests[i].obtained;
			}
			else {
				cout << "sqrt(" << tests[i].op1 << ") = " << tests[i].expected << " != " << tests[i].obtained;	
			}
		}
		
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

void divTest() {
	vector<TestT> divisions;

	divisions.push_back(testMe('/', 0, 5, 0));
	divisions.push_back(testMe('/', 0, 3, 0));
	divisions.push_back(testMe('/', 0, -5, 0));
	divisions.push_back(testMe('/', 0, -3, 0));

	divisions.push_back(testMe('/', 0, 0.125, 0));
	divisions.push_back(testMe('/', 0, 0.0037, 0));
	divisions.push_back(testMe('/', 0, -0.125, 0));
	divisions.push_back(testMe('/', 0, -0.0037, 0));

	divisions.push_back(testMe('/', 1, 2, 0.5));
	divisions.push_back(testMe('/', 1, 4, 0.25));
	divisions.push_back(testMe('/', 1, 5, 0.2));

	divisions.push_back(testMe('/', 1, 0.125, 8));
	divisions.push_back(testMe('/', 1, -0.125, -8));
	divisions.push_back(testMe('/', -1, 0.125, -8));
	divisions.push_back(testMe('/', -1, -0.125, 8));

	divisions.push_back(testMe('/', 3, 5, 0.6));
	divisions.push_back(testMe('/', 3.96, 4, 0.99));
	divisions.push_back(testMe('/', 15, 3, 5));
	divisions.push_back(testMe('/', 45, 6, 7.5));

	divisions.push_back(testMe('/', 6, 3, 2));
	divisions.push_back(testMe('/', 21, 3, 7));
	divisions.push_back(testMe('/', 77777, 7, 11111));

	divisions.push_back(testMe('/', 12345, 800, 15.43125));

	divisions.push_back(testMe('/', LongDouble("121932631112635269"), LongDouble("-987654321"), LongDouble("-123456789")));
	divisions.push_back(testMe('/', LongDouble("121932631112635269"), LongDouble("987654321"), LongDouble("123456789")));
	divisions.push_back(testMe('/', LongDouble("-121932631112635269"), LongDouble("987654321"), LongDouble("-123456789")));
	divisions.push_back(testMe('/', LongDouble("-121932631112635269"), LongDouble("-987654321"), LongDouble("123456789")));

	cout << "Test of divisions LongDouble" << endl;
	printTestResults(divisions);
}

void powTest() {
	vector<TestT> powers;
	
	powers.push_back(testMe('^', 1, 0, 1));
	powers.push_back(testMe('^', 100, 0, 1));
	powers.push_back(testMe('^', -100, 0, 1));
	powers.push_back(testMe('^', 10000, 0, 1));

	powers.push_back(testMe('^', -1, 1, -1));
	powers.push_back(testMe('^', -1, 2, 1));
	powers.push_back(testMe('^', -1, 3, -1));
	powers.push_back(testMe('^', -1, 4, 1));
	powers.push_back(testMe('^', -1, 5, -1));
	powers.push_back(testMe('^', -1, 100, 1));

	powers.push_back(testMe('^', 2, 0, 1));
	powers.push_back(testMe('^', 2, 5, 32));
	powers.push_back(testMe('^', 2, 31, 2147483648));

	powers.push_back(testMe('^', 2, -1, 0.5));	
	powers.push_back(testMe('^', 2, -4, 0.0625));	
	powers.push_back(testMe('^', 2, -10, LongDouble("0.0009765625")));

	powers.push_back(testMe('^', 2.5, -1, 0.4));
	powers.push_back(testMe('^', 0.01, -3, 1000000));
	powers.push_back(testMe('^', 3.25, 2, 10.5625));

	powers.push_back(testMe('^', 5, 3, 125));
	powers.push_back(testMe('^', 125, -3, LongDouble("0.000000512000000")));
	powers.push_back(testMe('^', 2, -23, LongDouble("0.00000011920928955078125")));
	powers.push_back(testMe('^', 2, 100, LongDouble("1267650600228229401496703205376")));
	powers.push_back(testMe('^', 5, 30, LongDouble("931322574615478515625")));

	cout << "Test of powers LongDouble" << endl;
	printTestResults(powers);
}

void sqrtTest() {
	std::vector<TestT> sqrts;

	sqrts.push_back(testMe('v', 0, 0));
	sqrts.push_back(testMe('v', 1, 1));
	sqrts.push_back(testMe('v', 4, 2));
	sqrts.push_back(testMe('v', 9, 3));

	sqrts.push_back(testMe('v', 100, 10));
	sqrts.push_back(testMe('v', 225, 15));
	sqrts.push_back(testMe('v', 10000000000, 100000));

	sqrts.push_back(testMe('v', 1.44, 1.2));
	sqrts.push_back(testMe('v', 2.25, 1.5));
	sqrts.push_back(testMe('v', 0.01, 0.1));
	sqrts.push_back(testMe('v', 0.0001, 0.01));

	cout << "Test of roots LongDouble" << endl;
	printTestResults(sqrts);
}

int main() {
	addTest();
	subTest();
	multTest();
	divTest();
	powTest();
	sqrtTest();
}