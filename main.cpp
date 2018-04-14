#include <iostream>
#include <string>
#include <vector>
#include "LongDouble.h"

using namespace std;

struct TestT {
	LongDouble op1;
	LongDouble op2;
	LongDouble obtained;
	LongDouble expected;

	char op;
	bool correct;
};

TestT testMe(char op, const LongDouble &op1, const LongDouble &op2, const LongDouble &res) {
	TestT test;

	test.op1 = op1;
	test.op2 = op2;

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
			cout << "OK";
		else
			cout << "Failed: " << tests[i].op1 << " " << tests[i].op << " " << tests[i].op2 << " = " << tests[i].expected << " != " << tests[i].obtained;
		
		cout << endl;
	}

	cout << "-----------------------------" << endl;
	cout << results << " / " << tests.size() << " (" << (100 * results / tests.size()) << "%)" << endl << endl;
}

void addTest() {
	vector<TestT> additions;

	additions.push_back(testMe('+', LongDouble("0"), LongDouble("0"), LongDouble("0")));

	additions.push_back(testMe('+', LongDouble("0"), LongDouble("45"), LongDouble("45")));
	additions.push_back(testMe('+', LongDouble("45"), LongDouble("0"), LongDouble("45")));
	additions.push_back(testMe('+', LongDouble("0"), LongDouble("-45"), LongDouble("-45")));
	additions.push_back(testMe('+', LongDouble("-45"), LongDouble("0"), LongDouble("-45")));

	additions.push_back(testMe('+', LongDouble("-45"), LongDouble("45"), LongDouble("0")));

	additions.push_back(testMe('+', LongDouble("27.5"), LongDouble("1.025"), LongDouble("28.525")));
	additions.push_back(testMe('+', LongDouble("-27.5"), LongDouble("1.025"), LongDouble("-26.475")));
	additions.push_back(testMe('+', LongDouble("1000"), LongDouble("0.0001"), LongDouble("1000.0001")));
	additions.push_back(testMe('+', LongDouble("5"), LongDouble("0.000000001"), LongDouble("5.000000001")));

	additions.push_back(testMe('+', LongDouble("2.7"), LongDouble("0.018281828"), LongDouble("2.718281828")));
	additions.push_back(testMe('+', LongDouble("3.14159"), LongDouble("0.00000265357989"), LongDouble("3.14159265357989")));

	printTestResults(additions);
}

int main() {
	addTest();
}