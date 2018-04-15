#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>

class LongDouble {
	int sign;
	std::vector<int> digits;
	long exponent;

	void initFromString(const std::string& s);
	void removeZeroes();

public:
	LongDouble();
	LongDouble(const LongDouble& x);
	LongDouble(long double value);
	LongDouble(const std::string& s);

	bool operator>(const LongDouble& x) const;
	bool operator<(const LongDouble& x) const;
	bool operator>=(const LongDouble& x) const;
	bool operator<=(const LongDouble& x) const;
	bool operator==(const LongDouble& x) const;
	bool operator!=(const LongDouble& x) const;

	LongDouble operator-() const;

	LongDouble operator+(const LongDouble& x) const;
	LongDouble operator-(const LongDouble& x) const;
	LongDouble operator*(const LongDouble& x) const;

	friend std::ostream& operator<<(std::ostream& os, const LongDouble& value);
};