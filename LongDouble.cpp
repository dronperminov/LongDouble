#include "LongDouble.h"

using namespace std;

void LongDouble::removeZeroes() {
	size_t n = max((long) 1, exponent);

	while (digits.size() > n && digits[digits.size() - 1] == 0)
		digits.erase(digits.end() - 1);

	while (digits.size() > 1 && digits[0] == 0) {
		digits.erase(digits.begin());
		exponent--;
	}

	if (digits.size() == 1 && digits[0] == 0)
		sign = 1;
}

LongDouble::LongDouble() {
	sign = 1;
	digits = vector<int>(1, 0);
	exponent = 0;
}

LongDouble::LongDouble(const LongDouble& x) {
	sign = x.sign;
	exponent = x.exponent;
	digits = vector<int>(x.digits.size());

	for (size_t i = 0; i < x.digits.size(); i++)
		digits[i] = x.digits[i];
}

LongDouble::LongDouble(const std::string& s) {
	size_t index;

	if (s[0] == '-') {
		sign = -1;
		index = 1;
	} else {
		sign = 1;
		index = 0;
	}

	exponent = s.length() - index;

	while (index < s.length()) {
		if (s[index] == '.')
			exponent = sign == 1 ? index : index - 1;
		else
			digits.push_back(s[index] - '0');

		index++;
	}

	removeZeroes();
}

bool LongDouble::operator>(const LongDouble& x) const {
	if (sign != x.sign)
		return sign > x.sign;

	if (exponent != x.exponent)
		return (exponent > x.exponent) ^ (sign == -1);

	vector<int> d1(digits);
	vector<int> d2(x.digits);
	size_t size = max(d1.size(), d2.size());

	while (d1.size() != size)
		d1.push_back(0);

	while (d2.size() != size)
		d2.push_back(0);

	for (size_t i = 0; i < size; i++)
		if (d1[i] != d2[i])
			return (d1[i] > d2[i]) ^ (sign == -1);

	return false;
}

bool LongDouble::operator<(const LongDouble& x) const {
	return !(*this > x || *this == x);
}

bool LongDouble::operator>=(const LongDouble& x) const {
	return (*this > x || *this == x);
}

bool LongDouble::operator<=(const LongDouble& x) const {
	return *this < x || *this == x;
}

bool LongDouble::operator==(const LongDouble& x) const {
	if (sign != x.sign)
		return false;

	if (exponent != x.exponent)
		return false;

	if (digits.size() != x.digits.size())
		return false;

	for (size_t i = 0; i < digits.size(); i++)
		if (digits[i] != x.digits[i])
			return false;

	return true;
}

bool LongDouble::operator!=(const LongDouble& x) const {
	return !(*this == x);
}

LongDouble LongDouble::operator-() const {
	LongDouble res(*this);
	res.sign = -sign;

	return res;
}

LongDouble LongDouble::operator+(const LongDouble& x) const {
	if (sign == x.sign) {
		long exp1 = exponent;
		long exp2 = x.exponent;
		long exp = max(exp1, exp2);

		vector<int> d1(digits);
		vector<int> d2(x.digits);

		while (exp1 != exp) {
			d1.insert(d1.begin(), 0);
			exp1++;
		}

		while (exp2 != exp) {
			d2.insert(d2.begin(), 0);
			exp2++;
		}

		size_t size = max(d1.size(), d2.size());

		while (d1.size() != size)
			d1.push_back(0);

		while (d2.size() != size)
			d2.push_back(0);

		size_t len = 1 + size;

		LongDouble res;

		res.sign = sign;
		res.digits = vector<int>(len, 0);

		for (int i = d1.size() - 1; i >= 0; i--)
			res.digits[len - d1.size() + i] = d1[i];

		for (int i = d2.size() - 1; i >= 0; i--)
			res.digits[len - d2.size() + i] += d2[i];

		for (size_t i = len - 1; i > 0; i--) {
			res.digits[i - 1] += res.digits[i] / 10;
			res.digits[i] %= 10;
		}

		res.exponent = exp + (res.digits[0] == 0);
		res.removeZeroes();

		return res;
	}

	if (sign == -1)
		return x - (-(*this));
	
	return *this - (-x);
}

LongDouble LongDouble::operator-(const LongDouble& x) const {
	if (sign == 1 && x.sign == 1) {
		bool cmp = *this > x;

		long exp1 = cmp ? exponent : x.exponent;
		long exp2 = cmp ? x.exponent : exponent;
		long exp = max(exp1, exp2);

		vector<int> d1(cmp ? digits : x.digits);
		vector<int> d2(cmp ? x.digits : digits);

		while (exp1 != exp) {
			d1.insert(d1.begin(), 0);
			exp1++;
		}

		while (exp2 != exp) {
			d2.insert(d2.begin(), 0);
			exp2++;
		}

		size_t size = max(d1.size(), d2.size());

		while (d1.size() != size)
			d1.push_back(0);

		while (d2.size() != size)
			d2.push_back(0);

		size_t len = 1 + size;

		LongDouble res;

		res.sign = cmp ? 1 : -1;
		res.digits = vector<int>(len, 0);

		for (int i = d1.size() - 1; i >= 0; i--)
			res.digits[len - d1.size() + i] = d1[i];

		for (int i = d2.size() - 1; i >= 0; i--)
			res.digits[len - d2.size() + i] -= d2[i];

		for (size_t i = len - 1; i > 0; i--) {
			if (res.digits[i] < 0) {
				res.digits[i] += 10;
				res.digits[i - 1]--;
			}
		}

		res.exponent = exp + (res.digits[0] == 0);
		res.removeZeroes();

		return res;
	}

	if (sign == -1 && x.sign == -1)
		return (-x) - (-(*this));
	
	return *this + (-x);
}

LongDouble LongDouble::operator*(const LongDouble& x) const {
	size_t len = digits.size() + x.digits.size();

	LongDouble res;

	res.sign = sign * x.sign;
	res.digits = vector<int>(len, 0);
	res.exponent = exponent + x.exponent;

	for (size_t i = 0; i < digits.size(); i++)
		for (size_t j = 0; j < x.digits.size(); j++)
			res.digits[len - 1 - i - j] += digits[digits.size() - 1 - i] * x.digits[x.digits.size() - 1 - j];

	for (size_t i = len - 1; i > 0; i--) {
		res.digits[i - 1] += res.digits[i] / 10;
		res.digits[i] %= 10;
	}

	res.removeZeroes();

	return res;
}

ostream& operator<<(ostream& os, const LongDouble& value) {
	if (value.sign == -1)
		os << '-';

	if (value.exponent > 0) {
		size_t i = 0;
		size_t e = value.exponent;

		while(i < value.digits.size() && i < e)
			os << value.digits[i++];

		while (i < e) {
			os << "0";
			i++;
		}

		if (i < value.digits.size()) {
			os << ".";

			while(i < value.digits.size())
				os << value.digits[i++];
		}
	}
	else if (value.exponent == 0) {
		os << "0.";

		for (size_t i = 0; i < value.digits.size(); i++)
			os << value.digits[i];
	}
	else {
		os << "0.";

		for (long i = 0; i < -value.exponent; i++)
			os << "0";

		for (size_t i = 0; i < value.digits.size(); i++)
			os << value.digits[i];
	}

	os << "\t(";
	if (value.sign == -1)
		os << '-';	
	for (size_t i = 0; i < value.digits.size(); i++)
		os << value.digits[i];
	os << ", exp: " << value.exponent << ")";

	return os;
}