#ifndef LAB4_LN_H
#define LAB4_LN_H

#include "string_view"

#include <cmath>
#include <deque>
#include <iostream>
#include <string>

using namespace std;

class LN
{
  public:
	/*
	------------
	Constructors
	------------
	*/
	LN();
	explicit LN(long long number);
	explicit LN(string number);
	LN(const char *number);
	LN(string_view number);

	/*
	-----------------------------------------
	Output operator && copy/replace operators
	-----------------------------------------
	*/
	friend ostream &operator<<(ostream &os, LN num);
	LN &operator=(const LN &r);

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
	friend LN operator+(const LN &lhs, const LN &rhs);
	friend LN operator-(const LN &lhs, const LN &rhs);
	friend LN operator*(const LN &lhs, const LN &rhs);
	friend LN operator/(const LN &lhs, const LN &rhs);
	friend LN operator%(const LN &lhs, const LN &rhs);

	/*
	-----------------
	Compare operators
	-----------------
	*/
	friend bool operator<(const LN &lhs, const LN &rhs);
	friend bool operator>(const LN &lhs, const LN &rhs);
	friend bool operator==(const LN &lhs, const LN &rhs);
	friend bool operator!=(const LN &lhs, const LN &rhs);

	/*
	--------------------------------------------------
	Combine of binary operations and compare operators
	--------------------------------------------------
	*/
	friend bool operator<=(const LN &lhs, const LN &rhs);
	friend bool operator>=(const LN &lhs, const LN &rhs);
	friend LN operator+=(const LN &lhs, const LN &rhs);
	friend LN operator-=(const LN &lhs, const LN &rhs);
	friend LN operator*=(const LN &lhs, const LN &rhs);
	friend LN operator/=(const LN &lhs, const LN &rhs);
	friend LN operator%=(const LN &lhs, const LN &rhs);

	/*
	----------------
	Unary operations
	----------------
	*/
	LN operator-() const &;
	LN operator~();

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
	static int compare(const LN &lhs, const LN &rhs);
	void skip_zeroes();
	static LN absolute(const LN &value);

	/*
	 * Pred:
	 * 	  ln - exists,
	 *    str == "10..000...0", where count of '0' is positive or 0
	 *
	 * Post:
	 *    R is LN(long(LN) * string_to_long(str))
	 */
	static LN multi_ten(const LN &ln, const string &num);
	static LN multiply(const LN &ln, int num);

	static int get_divisor(const LN &lhs, const LN &rhs);
	static LN division(const LN &lhs, const LN &rhs);

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

#endif	  // LAB4_LN_H
