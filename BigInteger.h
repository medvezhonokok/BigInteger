#ifndef LAB4_BigInteger_H
#define LAB4_BigInteger_H

#include "string_view"

#include <cmath>
#include <deque>
#include <iostream>
#include <string>

using namespace std;

class BigInteger
{
  public:
	/*
	------------
	Constructors
	------------
	*/
	BigInteger();
	explicit BigInteger(long long number);
	explicit BigInteger(string number);
	BigInteger(const char *number);
	BigInteger(string_view number);

	/*
	-----------------------------------------
	Output operator && copy/replace operators
	-----------------------------------------
	*/
	friend ostream &operator<<(ostream &os, BigInteger num);
	BigInteger &operator=(const BigInteger &r);

	/*
	 * Pred:
	 *    True
	 *
	 * Post:
	 * 	  R is !(*this == 0)
	 */
	bool to_bool();
	string to_str();
	long long to_long_num();

	/*
	-----------------
	Binary operations
	-----------------
	*/
	friend BigInteger operator+(const BigInteger &lhs, const BigInteger &rhs);
	friend BigInteger operator-(const BigInteger &lhs, const BigInteger &rhs);
	friend BigInteger operator*(const BigInteger &lhs, const BigInteger &rhs);
	friend BigInteger operator/(const BigInteger &lhs, const BigInteger &rhs);
	friend BigInteger operator%(const BigInteger &lhs, const BigInteger &rhs);

	/*
	-----------------
	Compare operators
	-----------------
	*/
	friend bool operator<(const BigInteger &lhs, const BigInteger &rhs);
	friend bool operator>(const BigInteger &lhs, const BigInteger &rhs);
	friend bool operator==(const BigInteger &lhs, const BigInteger &rhs);
	friend bool operator!=(const BigInteger &lhs, const BigInteger &rhs);

	/*
	--------------------------------------------------
	Combine of binary operations and compare operators
	--------------------------------------------------
	*/
	friend bool operator<=(const BigInteger &lhs, const BigInteger &rhs);
	friend bool operator>=(const BigInteger &lhs, const BigInteger &rhs);
	friend BigInteger operator+=(const BigInteger &lhs, const BigInteger &rhs);
	friend BigInteger operator-=(const BigInteger &lhs, const BigInteger &rhs);
	friend BigInteger operator*=(const BigInteger &lhs, const BigInteger &rhs);
	friend BigInteger operator/=(const BigInteger &lhs, const BigInteger &rhs);
	friend BigInteger operator%=(const BigInteger &lhs, const BigInteger &rhs);

	/*
	----------------
	Unary operations
	----------------
	*/
	BigInteger operator-() const &;
	BigInteger operator~();

	/*
	----------------
	Support methods
	----------------
	*/

	/*
	 * Pred:
	 *    lhs, rhs - exists
	 *
	 * Post:
	 * 	  lhs == rhs:
	 * 	  	R is 0
	 *
	 *    lhs > rhs:
	 *    	R is 1
	 *
	 *    lhs < rhs:
	 *    	R is -1
	 */
	static int compare(const BigInteger &lhs, const BigInteger &rhs);
	void skip_zeroes();
	static BigInteger absolute(const BigInteger &value);

	/*
	 * Pred:
	 * 	  BigInteger - exists,
	 *    str == "10..000...0", where count of '0' is positive or 0
	 *
	 * Post:
	 *    R is BigInteger(long(BigInteger) * string_to_long(str))
	 */
	static BigInteger multi_ten(const BigInteger &BigInteger, const string &num);
	static BigInteger multiply(const BigInteger &BigInteger, int num);

	static int get_divisor(const BigInteger &lhs, const BigInteger &rhs);
	static BigInteger division(const BigInteger &lhs, const BigInteger &rhs);

  private:
	/*
	------
	Fields
	------
	*/
	int BASE = 10;
	int len;
	bool zero = false;
	bool negative = false;
	bool nan = false;
	deque< int > digits;
};

#endif	  // LAB4_BigInteger_H
