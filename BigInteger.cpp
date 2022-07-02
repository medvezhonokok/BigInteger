#include "BigInteger.h"

/*
	------------
	Constructors
	------------
*/
BigInteger::BigInteger()
{
	negative = nan = false;
	zero = true;
	digits.push_back(0);
}
BigInteger::BigInteger(long long number)
{
	nan = false;
	if (number == 0)
	{
		zero = true;
	}

	if (number < 0)
	{
		negative = true;
		number = -number;
	}
	else
	{
		negative = false;
	}

	while (number > 0)
	{
		long long cur = number;
		cur %= 10;
		digits.push_back(cur);

		number /= 10;
	}
}
BigInteger::BigInteger(const char *str)
{
	string number = str;

	if (number == "NaN")
	{
		nan = true;
		negative = false;
		zero = false;
	}

	if (number.empty())
	{
		nan = false;
		negative = false;
		zero = true;
		digits.push_back(0);
	}
	else
	{
		negative = false;
		if (number[0] == '-')
		{
			negative = true;
			number = number.substr(1);
		}

		for (size_t i = 0; i < number.length(); ++i)
		{
			digits.push_back(number[number.length() - i - 1] - '0');
		}

		skip_zeroes();

		if (digits.size() == 0 && digits[0] == 0)
		{
			zero = true;
			nan = negative = false;
		}
	}
}
BigInteger::BigInteger(string number)
{
	if (number == "NaN")
	{
		nan = true;
		negative = false;
		zero = false;
	}

	if (number.empty())
	{
		nan = false;
		negative = false;
		zero = true;
		digits.push_back(0);
	}
	else
	{
		negative = false;
		if (number[0] == '-')
		{
			negative = true;
			number = number.substr(1);
		}

		for (size_t i = 0; i < number.length(); ++i)
		{
			digits.push_back(number[number.length() - i - 1] - '0');
		}

		skip_zeroes();

		if (digits.size() == 0 && digits[0] == 0)
		{
			zero = true;
			nan = negative = false;
		}
	}
}
BigInteger::BigInteger(string_view number)
{
	if (number == "NaN")
	{
		nan = true;
		negative = false;
		zero = false;
	}

	if (number.empty())
	{
		nan = false;
		negative = false;
		zero = true;
		digits.push_back(0);
	}

	else
	{
		negative = false;
		if (number[0] == '-')
		{
			negative = true;
			number = number.substr(1);
		}

		for (size_t i = 0; i < number.length(); ++i)
		{
			digits.push_back(number[number.length() - i - 1] - '0');
		}

		skip_zeroes();

		if (digits.size() == 0 && digits[0] == 0)
		{
			zero = true;
			nan = negative = false;
		}
	}
}

/*
	-----------------------------------------
	Output operator && copy/replace operators
	-----------------------------------------
*/
ostream &operator<<(ostream &os, BigInteger num)
{
	string q = num.to_str();

	if (q == "NaN" || num.nan)
	{
		os << q;
		return os;
	}

	if (num.negative)
	{
		q = q.substr(1);
		os << "-";
	}

	os << q;
	return os;
}
BigInteger &BigInteger::operator=(const BigInteger &r)
{
	BASE = r.BASE;
	zero = r.zero;
	digits = r.digits;
	negative = r.negative;
	nan = r.nan;

	return *this;
}
long long BigInteger::to_long_num()
{
	string s;
	if (negative)
	{
		s = to_str().substr(1);
	}
	else
	{
		s = to_str();
	}

	if (s.length() <= 19 || s == "9223372036854775808")
	{
		long long num = 0;
		long long q = 1;

		for (int digit : digits)
		{
			num += q * digit;
			q *= 10;
		}

		return num;
	}
	else
	{
		throw std::runtime_error("Sorry, this BigInteger can not be casted to long long.");
	}
}
bool BigInteger::to_bool()
{
	return !zero;
}

/*
	-----------------
	Binary operations
	-----------------
*/
BigInteger operator+(const BigInteger &lhs, const BigInteger &rhs)
{
	BigInteger res("0");
	res.digits.clear();

	if (lhs.nan || rhs.nan)
	{
		res.nan = true;
		res.negative = false;
		res.zero = false;

		return res;
	}
	else
	{
		res.nan = false;
	}

	size_t min_size = min(lhs.digits.size(), rhs.digits.size());
	size_t max_size = max(lhs.digits.size(), rhs.digits.size());

	bool positive;
	// Case 1: lhs > 0 && rhs > 0 || lhs < 0 && rhs < 0
	if (!lhs.negative && !rhs.negative || lhs.negative && rhs.negative)
	{
		if (!lhs.negative && !rhs.negative)
		{
			positive = false;
		}
		else
		{
			positive = true;
		}

		bool flag = false;

		for (size_t i = 0; i < min_size; ++i)
		{
			int cur_res = lhs.digits[i] + rhs.digits[i];

			if (flag)
			{
				cur_res++;
			}

			if (cur_res < 10)
			{
				res.digits.push_back(cur_res);
				flag = false;
			}
			else
			{
				int c = cur_res;
				c %= 10;
				res.digits.push_back(c);
				flag = true;
			}
		}

		if (flag)
		{
			bool flag1 = true;
			if (lhs > rhs)
			{
				for (size_t i = min_size; i < max_size; ++i)
				{
					int cur = lhs.digits[i];
					if (flag1)
					{
						cur++;
					}

					if (cur < 10)
					{
						res.digits.push_back(cur);
						flag1 = false;
					}
					else
					{
						int q = cur;
						q %= 10;
						res.digits.push_back(q);
						flag1 = true;
					}
				}
				if (flag1)
				{
					res.digits.push_back(1);
				}
			}
			else
			{
				for (size_t i = min_size; i < max_size; ++i)
				{
					int cur = rhs.digits[i];
					if (flag1)
					{
						cur++;
					}

					if (cur < 10)
					{
						res.digits.push_back(cur);
						flag1 = false;
					}
					else
					{
						int q = cur;
						q %= 10;
						res.digits.push_back(q);
						flag1 = true;
					}
				}

				if (flag1)
				{
					res.digits.push_back(1);
				}
			}
		}
		else
		{
			if (BigInteger::absolute(lhs) > BigInteger::absolute(rhs))
			{
				for (size_t i = min_size; i < max_size; ++i)
				{
					int cur = lhs.digits[i];
					res.digits.push_back(cur);
				}
			}
			else
			{
				for (size_t i = min_size; i < max_size; ++i)
				{
					int cur = rhs.digits[i];
					res.digits.push_back(cur);
				}
			}
		}

		res.negative = positive;
		res.skip_zeroes();

		if (res == BigInteger("0"))
		{
			res.zero = true;
		}
		else
		{
			res.zero = false;
		}

		return res;
	}

	// Case 2: lhs * rhs < 0
	if (!lhs.negative && rhs.negative || lhs.negative && !rhs.negative)
	{
		if (!lhs.negative && rhs.negative)
		{
			if (BigInteger::absolute(lhs) >= BigInteger::absolute(rhs))
			{
				positive = true;
			}
			else
			{
				positive = false;
			}
		}

		if (lhs.negative && !rhs.negative)
		{
			if (BigInteger::absolute(lhs) <= BigInteger::absolute(rhs))
			{
				positive = true;
			}
			else
			{
				positive = false;
			}
		}

		BigInteger abs_max("0");
		BigInteger abs_min("0");

		if (BigInteger::absolute(lhs) > BigInteger::absolute(rhs))
		{
			abs_max = BigInteger::absolute(lhs);
			abs_min = BigInteger::absolute(rhs);
		}	 // From a larger number modulo we will subtract the smaller one, at the end we will change the positive to
			 // the positive of the larger one
		else
		{
			abs_min = BigInteger::absolute(lhs);
			abs_max = BigInteger::absolute(rhs);
		}

		bool flag = false;	  // Did we take a unit from the next digit
		for (size_t i = 0; i < min_size; ++i)
		{
			int cur = abs_max.digits[i] - abs_min.digits[i];

			if (flag)
			{
				cur--;
			}

			if (cur >= 0)
			{
				res.digits.push_back(cur);
				flag = false;
			}
			else
			{
				flag = true;
				int q = 10 + cur;
				res.digits.push_back(q);
			}
		}

		if (flag)	 // If we took 1 from the 'min_size' digit
		{
			bool flag1 = true;
			for (size_t i = min_size; i < max_size; ++i)
			{
				int cur = abs_max.digits[i];
				if (flag1)
				{
					cur--;
				}

				if (cur >= 0)
				{
					res.digits.push_back(cur);
					flag1 = false;
				}
				else
				{
					int q = cur;
					q = 10 + q;
					res.digits.push_back(q);
					flag1 = true;
				}
			}
		}
		else
		{
			for (size_t i = min_size; i < max_size; ++i)
			{
				res.digits.push_back(abs_max.digits[i]);
			}
		}

		res.negative = !positive;
		res.skip_zeroes();

		if (res == BigInteger("0"))
		{
			res.zero = true;
		}
		else
		{
			res.zero = false;
		}

		return res;
	}

	return BigInteger("0");
}
BigInteger operator-(const BigInteger &lhs, const BigInteger &rhs)
{
	return lhs + (-rhs);
}
BigInteger operator*(const BigInteger &lhs, const BigInteger &rhs)
{
	if (lhs.nan || rhs.nan)
	{
		BigInteger res("NaN");
		res.nan = true;
		res.negative = false;
		res.zero = false;

		return res;
	}

	if (lhs.zero || rhs.zero)
	{
		BigInteger res("0");
		res.nan = false;
		res.negative = false;
		res.zero = true;

		return res;
	}

	bool flag = false;

	if (lhs.negative && !rhs.negative || !lhs.negative && rhs.negative)
	{
		flag = true;
	}

	BigInteger res("0");
	BigInteger maxi("0");
	BigInteger mini("0");

	size_t min_len = min(lhs.digits.size(), rhs.digits.size());

	maxi = lhs;
	mini = rhs;

	string q = "1";

	res.negative = false;
	maxi.negative = false;
	mini.negative = false;

	if (maxi < mini)
	{
		BigInteger temp = maxi;
		maxi = mini;
		mini = temp;
	}

	for (size_t i = 0; i < min_len; ++i)
	{
		int num = mini.digits[i];

		BigInteger multi = BigInteger::multiply(maxi, num);

		multi = BigInteger::multi_ten(multi, q);
		multi.negative = false;

		BigInteger c = multi + res;
		res = c;

		q += "0";
	}

	res.negative = flag;
	res.skip_zeroes();

	if (res == BigInteger("0"))
	{
		res.zero = true;
		res.negative = false;
	}
	else
	{
		res.zero = false;
	}

	res.nan = false;

	return res;
}
BigInteger operator/(const BigInteger &lhs, const BigInteger &rhs)
{
	return BigInteger::division(lhs, rhs);
}
BigInteger operator%(const BigInteger &lhs, const BigInteger &rhs)
{
	BigInteger res;

	res = lhs - (lhs / rhs) * rhs;

	return res;
}

/*
	----------------
	Unary operations
	----------------
*/
BigInteger BigInteger::operator~()
{
	if (nan || negative)
	{
		BigInteger res("NaN");
		res.nan = true;
		res.zero = false;
		res.negative = false;

		return res;
	}

	BigInteger l("0");
	BigInteger r(*this);
	r = r + BigInteger("1");

	while (r - l > BigInteger("1"))
	{
		BigInteger m = (l + r) / BigInteger("2");
		if (m * m <= *this)
		{
			l = m;
		}
		else
		{
			r = m;
		}
	}

	return l;
}
BigInteger BigInteger::operator-() const &
{
	BigInteger b = *this;
	b.negative = !b.negative;

	return b;
}

/*
	-----------------
	Compare operators
	-----------------
*/
bool operator<(const BigInteger &lhs, const BigInteger &rhs)
{
	if (lhs.nan && !rhs.nan || !lhs.nan && rhs.nan)
	{
		return true;
	}

	return BigInteger::compare(lhs, rhs) == -1;
}
bool operator>(const BigInteger &lhs, const BigInteger &rhs)
{
	if (lhs.nan && !rhs.nan || !lhs.nan && rhs.nan)
	{
		return true;
	}

	return BigInteger::compare(lhs, rhs) == 1;
}
bool operator==(const BigInteger &lhs, const BigInteger &rhs)
{
	if (lhs.nan && !rhs.nan || !lhs.nan && rhs.nan)
	{
		return true;
	}

	return BigInteger::compare(lhs, rhs) == 0;
}
bool operator!=(const BigInteger &lhs, const BigInteger &rhs)
{
	if (lhs.nan && !rhs.nan || !lhs.nan && rhs.nan)
	{
		return true;
	}

	return !(lhs == rhs);
}

/*
	--------------------------------------------------
	Combine of binary operations and compare operators
	--------------------------------------------------
*/
BigInteger operator+=(const BigInteger &lhs, const BigInteger &rhs)
{
	return lhs + rhs;
}
BigInteger operator-=(const BigInteger &lhs, const BigInteger &r)
{
	return lhs - r;
}
BigInteger operator*=(const BigInteger &lhs, const BigInteger &r)
{
	return lhs * r;
}
BigInteger operator/=(const BigInteger &lhs, const BigInteger &r)
{
	return lhs / r;
}
BigInteger operator%=(const BigInteger &lhs, const BigInteger &r)
{
	return lhs % r;
}
bool operator>=(const BigInteger &lhs, const BigInteger &rhs)
{
	if (lhs.nan && !rhs.nan || !lhs.nan && rhs.nan)
	{
		return true;
	}

	return ((lhs > rhs) || (lhs == rhs));
}
bool operator<=(const BigInteger &lhs, const BigInteger &rhs)
{
	if (lhs.nan && !rhs.nan || !lhs.nan && rhs.nan)
	{
		return true;
	}

	return ((lhs < rhs) || (lhs == rhs));
}

/*
	----------------
	Support methods
	----------------
*/
string BigInteger::to_str()
{
	if (nan)
	{
		return "NaN";
	}

	if (zero)
	{
		return "0";
	}

	string res = negative ? "-" : "";

	for (size_t i = 0; i < digits.size(); ++i)
	{
		int a = digits[digits.size() - i - 1];
		res += std::to_string(a);
	}

	return res;
}
void BigInteger::skip_zeroes()
{
	while (digits.back() == 0 && digits.size() > 1)
	{
		digits.pop_back();
	}
	if (digits.size() == 1 && digits[0] == 0)
	{
		zero = true;
		nan = false;
		negative = false;
	}
}
BigInteger BigInteger::absolute(const BigInteger &value)
{
	BigInteger result = value;
	result.negative = false;
	return result;
}
BigInteger BigInteger::multiply(const BigInteger &a, int num)
{
	if (num == 0)
	{
		return BigInteger("0");
	}

	BigInteger res("0");
	res.digits.clear();

	int rest = 0;

	for (size_t i = 0; i < a.digits.size(); ++i)
	{
		int cur = a.digits[i] * num + rest;
		cur %= a.BASE;

		res.digits.push_back(cur);

		rest = (a.digits[i] * num + rest) / a.BASE;
	}

	if (rest > 0)
	{
		if (rest < a.BASE)
		{
			res.digits.push_back(rest);
		}
		else
		{
			while (rest > 0)
			{
				int cur = rest;
				cur %= a.BASE;
				res.digits.push_back(cur);
				rest /= a.BASE;
			}
		}
	}

	return res;
}
BigInteger BigInteger::multi_ten(const BigInteger &a, const string &num)
{
	BigInteger res("0");
	res.digits.clear();

	for (size_t i = 0; i < num.length() - 1; ++i)
	{
		res.digits.push_back(0);
	}

	for (int digit : a.digits)
	{
		res.digits.push_back(digit);
	}

	return res;
}
int BigInteger::get_divisor(const BigInteger &lhs, const BigInteger &rhs)
{
	int r = 0, l = 100;
	int count = l - r, m, it;
	while (count > 0)
	{
		m = count / 2;
		it = r + m;
		if (lhs >= multiply(rhs, it))
		{
			r = ++it;
			count -= m + 1;
		}
		else
		{
			count = m;
		}
	}
	return r - 1;
}
BigInteger BigInteger::division(const BigInteger &lhs, const BigInteger &rhs)
{
	if (lhs.nan || rhs.nan || rhs.zero)
	{
		BigInteger res("NaN");
		res.nan = true;
		res.negative = false;
		res.zero = false;

		return res;
	}

	if (BigInteger::absolute(lhs) < BigInteger::absolute(rhs))
	{
		BigInteger res("0");
		res.nan = false;
		res.negative = false;
		res.zero = true;

		return res;
	}

	if (rhs == BigInteger("1"))
	{
		return lhs;
	}

	if (rhs == lhs)
	{
		BigInteger res("1");
		res.negative = false;
		res.zero = false;
		res.nan = false;

		return res;
	}

	if (lhs.negative && !rhs.negative)
	{
		return -division(-lhs, rhs);
	}

	if (!lhs.negative && rhs.negative)
	{
		return -division(lhs, -rhs);
	}

	if (lhs.negative && rhs.negative)
	{
		return division(-lhs, -rhs);
	}

	BigInteger res("0"), memory("0");

	memory.digits.clear();
	res.digits.clear();

	for (size_t i = 0; i < lhs.digits.size(); i++)
	{
		memory.digits.push_front(lhs.digits[lhs.digits.size() - 1 - i]);
		int div = get_divisor(memory, rhs);
		res.digits.push_front(div);
		memory = memory - multiply(rhs, div);
		if (memory.digits.size() == 1 && memory.digits[0] == 0)
		{
			memory.digits.clear();
		}
	}

	res.skip_zeroes();
	res.nan = false;

	if (res == BigInteger("0"))
	{
		res.zero = true;
		res.nan = res.negative = false;
	}
	else
	{
		res.zero = false;
	}

	return res;
}
/*
 * Pred:
 *    lhs, rhs - exists
 *
 * Post:
 * 	  lhs == rhs : 0
 *    lhs > rhs : 1
 *    lhs < rhs : -1
 */
int BigInteger::compare(const BigInteger &lhs, const BigInteger &rhs)
{
	// if (f == s) -> 0

	if (lhs.digits.size() == 1 && rhs.digits.size() == 1 && lhs.digits[0] == 0 && rhs.digits[0] == 0)
	{
		return 0;	 // 0 == 0
	}

	int min_len;

	if (lhs.digits.size() >= rhs.digits.size())
	{
		min_len = rhs.digits.size();
	}
	else
	{
		min_len = lhs.digits.size();
	}

	int cur_index;
	int count = 0;
	for (size_t i = 0; i < min_len; ++i)
	{
		if (lhs.digits[i] == rhs.digits[i])
		{
			count++;
		}
	}

	if (count > 0)
	{
		if (count == min_len && lhs.digits.size() == rhs.digits.size())
		{
			if ((!rhs.negative && !lhs.negative) || (rhs.negative && lhs.negative))
				return 0;
		}
	}

	// if (f > s) -> 1;

	if (!lhs.negative && rhs.negative)
	{
		return 1;
	}

	if (lhs.negative && !rhs.negative)
	{
		return -1;
	}

	if (!lhs.negative && !rhs.negative)	   // If both number are positive
	{
		if (lhs.digits.size() > rhs.digits.size())
		{
			return 1;
		}

		if (lhs.digits.size() < rhs.digits.size())
		{
			return -1;
		}

		for (size_t i = 0; i < min_len; ++i)
		{
			cur_index = min_len - i - 1;
			if (lhs.digits[cur_index] > rhs.digits[cur_index])
			{
				return 1;
			}
			else
			{
				if (lhs.digits[cur_index] < rhs.digits[cur_index])
				{
					return -1;
				}
			}
		}
	}
	else
	{
		if (lhs.digits.size() < rhs.digits.size())
		{
			return 1;
		}

		if (lhs.digits.size() > rhs.digits.size())
		{
			return -1;
		}

		for (size_t i = 0; i < min_len; ++i)
		{
			cur_index = min_len - i - 1;
			if (lhs.digits[cur_index] > rhs.digits[cur_index])
			{
				return -1;
			}
			else
			{
				if (lhs.digits[cur_index] < rhs.digits[cur_index])
				{
					return 1;
				}
			}
		}
	}

	return -1;
}
