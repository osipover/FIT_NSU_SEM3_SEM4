#include <iostream>
using namespace std;

class BigInt {
private:
	
public:
	string numInStr;
	BigInt(string input);
	~BigInt();

	bool operator==(const BigInt& other) const;
	bool operator!=(const BigInt& other) const;
	bool operator<(const BigInt& other) const;
	bool operator>(const BigInt& other) const;
	bool operator<=(const BigInt& other) const;
	bool operator>=(const BigInt& other) const;
};

int main() {
	BigInt a("123");
	BigInt b("123");
	
	if (a <= b)
		cout << "true";
	else
		cout << "false";
	return 0;
}

BigInt::BigInt(string input) {
	numInStr = input;
}

BigInt::~BigInt() {

}

bool BigInt::operator==(const BigInt& other) const {
	if (this->numInStr == other.numInStr)
		return true;
	else
		return false;
}

bool BigInt::operator!=(const BigInt& other) const{
	if (this->numInStr != other.numInStr)
		return true;
	else
		return false;
}

bool BigInt::operator<(const BigInt& other) const {
	string first = this->numInStr;
	string second = other.numInStr;

	int sizeOfFirst = this->numInStr.length();
	int sizeOfSecond = other.numInStr.length();

	if (sizeOfFirst < sizeOfSecond)
		return true;
	else if (sizeOfFirst > sizeOfSecond)
		return false;

	for (int i = 0; i < sizeOfFirst; ++i) {
		if (first[i] < second[i])
			return true;
		else if (first[i] > second[i])
			return false;
	}

	return false;
}

bool BigInt::operator>(const BigInt& other) const {
	string first = this->numInStr;
	string second = other.numInStr;

	int sizeOfFirst = this->numInStr.length();
	int sizeOfSecond = other.numInStr.length();

	if (sizeOfFirst > sizeOfSecond)
		return true;
	else if (sizeOfFirst < sizeOfSecond)
		return false;

	for (int i = 0; i < sizeOfFirst; ++i) {
		if (first[i] > second[i])
			return true;
		else if (first[i] < second[i])
			return false;
	}

	return false;
}

bool BigInt::operator<=(const BigInt& other) const {
	string first = this->numInStr;
	string second = other.numInStr;

	int sizeOfFirst = this->numInStr.length();
	int sizeOfSecond = other.numInStr.length();

	if (sizeOfFirst < sizeOfSecond)
		return true;
	else if (sizeOfFirst > sizeOfSecond)
		return false;

	for (int i = 0; i < sizeOfFirst; ++i) {
		if (first[i] < second[i])
			return true;
		else if (first[i] > second[i])
			return false;
	}

	return true;
}

bool BigInt::operator>=(const BigInt& other) const {
	string first = this->numInStr;
	string second = other.numInStr;

	int sizeOfFirst = this->numInStr.length();
	int sizeOfSecond = other.numInStr.length();

	if (sizeOfFirst > sizeOfSecond)
		return true;
	else if (sizeOfFirst < sizeOfSecond)
		return false;

	for (int i = 0; i < sizeOfFirst; ++i) {
		if (first[i] > second[i])
			return true;
		else if (first[i] < second[i])
			return false;
	}

	return true;
}
