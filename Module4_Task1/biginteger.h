#include <iostream>
#include <vector>
#include <string>

using std::vector;
using std::string;
using std::ostream;
using std::istream;

const int BASE = 10;
const int SHIFT_TO_ZERO = 48;
const size_t ORDINARY_MUL_LENGTH = 128;

void AdjustLengthToThePowerOfTwo(vector<int>& digits, size_t length);

void FixResultToBase(vector<int>& result, size_t base);

vector<int> Mul(const vector<int>& left, const vector<int>& right);

vector<int> QuickMul(const vector<int>& left, const vector<int>& right);

class BigInteger {
public:

  bool negative = false;
  vector<int> digits;

  BigInteger(bool negative, vector<int>& digits):
  negative(negative), digits(digits) {}

  BigInteger() = default;

  BigInteger(string value);

  BigInteger(int value);

  string toString() const;

  BigInteger& operator += (const BigInteger & value);
  BigInteger& operator -= (const BigInteger & value);
  BigInteger& operator *= (const BigInteger & value);
  BigInteger& operator /= (const BigInteger & value);
  BigInteger& operator %= (const BigInteger & value);

  BigInteger operator + () const;
  BigInteger operator - () const;

  BigInteger & operator ++ ();
  const BigInteger operator ++ (int);
  BigInteger & operator -- ();
  const BigInteger operator -- (int);

  explicit operator bool ();

  friend BigInteger operator + (const BigInteger & left,
                                const BigInteger & right);
  friend BigInteger operator - (const BigInteger & left,
                                const BigInteger & right);
  friend BigInteger operator * (const BigInteger & left,
                                const BigInteger & right);
  friend BigInteger operator / (const BigInteger & left,
                                const BigInteger & right);
  friend BigInteger operator % (const BigInteger & left,
                                const BigInteger & right);

  friend bool operator <  (const BigInteger & left, const BigInteger & right);
  friend bool operator >  (const BigInteger & left, const BigInteger & right);
  friend bool operator == (const BigInteger & left, const BigInteger & right);
  friend bool operator != (const BigInteger & left, const BigInteger & right);
  friend bool operator <= (const BigInteger & left, const BigInteger & right);
  friend bool operator >= (const BigInteger & left, const BigInteger & right);

  friend istream& operator >> (istream& in, BigInteger & number);
  friend ostream& operator << (ostream& out, const BigInteger & number);

private:

  void RemoveZeros();

  void ShiftRight();
};

////////////////////////////////////////////////////////////////////////////////
/// Friend functions of BigInteger class.

BigInteger operator + (const BigInteger& left, const BigInteger& right) {
  BigInteger result = left;
  return result += right;
}

BigInteger operator - (const BigInteger& left, const BigInteger& right) {
  BigInteger result = left;
  return result -= right;
}

BigInteger operator * (const BigInteger& left, const BigInteger& right) {

  vector<int> first = left.digits;
  vector<int> second = right.digits;

  size_t length = std::max(left.digits.size(), right.digits.size());

  AdjustLengthToThePowerOfTwo(first, length);
  AdjustLengthToThePowerOfTwo(second, length);

  vector<int> result_digits = QuickMul(first, second);
  FixResultToBase(result_digits, BASE);

  bool negative = left.negative != right.negative;
  BigInteger result(negative, result_digits);
  result.RemoveZeros();
  return result;
}

BigInteger operator / (const BigInteger& left, const BigInteger& right) {
  BigInteger result;
  BigInteger current;
  result.digits.resize(left.digits.size());
  result.negative = left.negative != right.negative;

  BigInteger divider = right;
  divider.negative = false;
  for (int index = static_cast<int>(left.digits.size() - 1); index >= 0;
       --index) {

    current.ShiftRight();
    current.digits[0] = left.digits[index];
    current.RemoveZeros();
    int digit = 0, start = 0, end = BASE;
    while (start <= end) {
      int mid = (start + end) / 2;
      BigInteger local = divider * mid;
      if (local <= current) {
        digit = mid;
        start = mid + 1;
      } else {
        end = mid - 1;
      }
    }

    result.digits[index] = digit;
    current = current - divider * digit;
  }
  result.RemoveZeros();
  return result;
}

BigInteger operator % (const BigInteger& left, const BigInteger& right) {
  BigInteger result = left - (left / right) * right;
  return result;
}

bool operator < (const BigInteger& left, const BigInteger& right) {
  if (left.negative) {
    if (right.negative) {
      return (-right < -left);
    } else {
      return true;
    }
  } else if (right.negative) {
    return false;
  } else {

    if (left.digits.size() != right.digits.size()) {
      return left.digits.size() < right.digits.size();
    } else {

      for (int index = static_cast<int>(left.digits.size() - 1); index >= 0;
           --index) {
        if (left.digits[index] != right.digits[index]) {
          return left.digits[index] < right.digits[index];
        }
      }

      return false;
    }

  }
}

bool operator > (const BigInteger & left, const BigInteger & right) {
  return right < left;
}

bool operator == (const BigInteger & left, const BigInteger & right) {
  return !((left < right) || (right < left));
}

bool operator != (const BigInteger & left, const BigInteger & right) {
  return !(left == right);
}

bool operator <= (const BigInteger& left, const BigInteger & right) {
  return !(left > right);
}

bool operator >= (const BigInteger& left, const BigInteger & right) {
  return !(left < right);
}

ostream& operator << (ostream& out, const BigInteger & number) {
  out << number.toString();
  return out;
}

istream& operator >> (istream& in, BigInteger & number) {

  string value;
  vector<int> digits;

  in >> value;

  number = BigInteger(value);

  return in;
}

////////////////////////////////////////////////////////////////////////////////
/// BigInteger methods

void BigInteger::RemoveZeros() {
  while ((digits.size() > 1) && (digits.back() == 0)) {
    digits.pop_back();
  }

  if ((digits.size() == 1) && (digits.back() == 0)) {
    negative = false;
  }
}

BigInteger::BigInteger(string value) {
  if (value.empty()) {
    return;
  }

  if (value[0] == '-') {
    negative = true;
  } else {
    negative = false;
  }

  for (size_t index = value.size() - 1; index > 0; --index) {
    digits.push_back(value[index] - SHIFT_TO_ZERO);
  }

  if (!negative) {
    digits.push_back(value[0] - SHIFT_TO_ZERO);
  }

  if (digits.size() == 1 && digits[0] == 0) {
    negative = false;
  }
}

BigInteger::BigInteger(int value) {

  negative = value < 0;
  if (negative) {
    value *= -1;
  }

  if (value == 0) {
    digits.push_back(value);
    return;
  }

  while (value != 0) {
    digits.push_back(value % BASE);
    value /= BASE;
  }
}

void BigInteger::ShiftRight() {
  if (digits.empty()) {
    digits.push_back(0);
    return;
  }
  digits.push_back(digits.back());

  for (size_t index = digits.size() - 2; index > 0; --index) {
    digits[index] = digits[index - 1];
  }
  digits[0] = 0;
}


string BigInteger::toString() const {
  string result;

  if (negative) {
    result.push_back('-');
  }

  for (size_t index = 0; index < digits.size(); ++index) {
    result.push_back(digits[digits.size() - index - 1] + SHIFT_TO_ZERO);
  }

  return result;
}

BigInteger& BigInteger::operator += (const BigInteger & value) {

  if (negative && !value.negative) {
    BigInteger copy = -(*this);
    BigInteger copy_value = value;
    copy_value -= copy;
    *this = copy_value;
    return *this;
  }

  if (!negative && value.negative) {
    BigInteger copy_value = -value;
    return *this -= copy_value;
  }

  vector<int> result;
  size_t carry = 0, addition = 0;
  for (size_t index = 0; (index < digits.size()) ||
                         (index < value.digits.size()) || (carry != 0);
       ++index) {
    if (index < value.digits.size()) {
      addition = value.digits[index];
    } else {
      addition = 0;
    }

    if (index < digits.size()) {
      addition += digits[index];
    }

    result.push_back(carry + addition);

    if (result[index] >= BASE) {
      carry = 1;
      result[index] -= BASE;
    } else {
      carry = 0;
    }
  }
  this->digits = result;

  return *this;
}

BigInteger& BigInteger::operator -= (const BigInteger & value) {

  if (value.negative) {
    return *this += (-value);
  }

  if (negative) {
    BigInteger copy = -*this;
    copy += value;
    *this = -copy;
    return *this;
  }

  if (*this < value) {
    BigInteger copy_value = value;
    copy_value -= *this;
    *this = -copy_value;
    return *this;
  }

  size_t carry = 0, subtrahend = 0;
  for (size_t index = 0; (index < value.digits.size()) || (carry != 0);
       ++index) {

    if (index < value.digits.size()) {
      subtrahend = value.digits[index];
    } else {
      subtrahend = 0;
    }

    digits[index] -= carry + subtrahend;

    if (digits[index] < 0) {
      carry = 1;
      digits[index] += BASE;
    } else {
      carry = 0;
    }
  }

  RemoveZeros();

  return *this;
}

BigInteger& BigInteger::operator *= (const BigInteger & value) {
  *this = *this * value;
  return *this;
}

BigInteger& BigInteger::operator /= (const BigInteger & value) {
  *this = *this / value;
  return *this;
}

BigInteger& BigInteger::operator %= (const BigInteger & value) {
  *this = *this % value;
  return *this;
}

BigInteger BigInteger::operator + () const {
  return BigInteger(*this);
}

BigInteger BigInteger::operator - () const {
  BigInteger result(*this);
  if (digits.size() == 1 && digits[0] == 0) {
    result.negative = false;
    result.digits[0] = 0;
  } else {
    result.negative = !this->negative;
  }
  return result;
}

BigInteger &BigInteger::operator ++ () {
  return (*this += 1);
}

const BigInteger BigInteger::operator ++ (int) {
  BigInteger result = *this;
  *this += 1;
  return result;
}

BigInteger &BigInteger::operator -- () {
  return (*this -= 1);
}

const BigInteger BigInteger::operator -- (int) {
  BigInteger result = *this;
  *this -= 1;
  return result;
}

BigInteger::operator bool () {
  if (*this != 0) {
    return true;
  } else {
    return false;
  }
}

////////////////////////////////////////////////////////////////////////////////
/// Quick multiplication

void AdjustLengthToThePowerOfTwo(vector<int>& digits, size_t length) {
  while (length & (length - 1)) {
    ++length;
  } /// a quick way to check if a number is a power of two:
  /// x = 0b1000,
  /// x - 1 = 0b0111,
  /// x & (x - 1) = 0

  digits.resize(length);
}

void FixResultToBase(vector<int>& result, size_t base) {
  for (size_t index = 0; index < result.size(); ++index) {
    result[index + 1] += result[index] / base;
    result[index] %= base;
  }
}

vector<int> Mul(const vector<int>& left, const vector<int>& right) {
  size_t length = left.size(); ///fixed size
  vector<int> result(2 * length);

  for (size_t first = 0; first < length; ++first) {
    for (size_t second = 0; second < length; ++second) {
      result[first + second] += left[first] * right[second];
    }
  }

  return result;
}

vector<int> QuickMul(const vector<int>& left, const vector<int>& right) {
  size_t length = left.size();
  vector<int> result(2 * length);

  if (length <= ORDINARY_MUL_LENGTH) {
    return Mul(left, right);
  }

  size_t shift = length / 2;

  vector<int> left_l {left.begin(), left.begin() + shift};
  vector<int> left_r {left.begin() + shift, left.end()};
  vector<int> right_l {right.begin(), right.begin() + shift};
  vector<int> right_r {right.begin() + shift, right.end()};

  vector<int> part_without_shift = QuickMul(left_l, right_l);
  vector<int> part_shift_squared = QuickMul(left_r, right_r);

  vector<int> left_sum(shift);
  vector<int> right_sum(shift);

  for (size_t index = 0; index < shift; ++index) {
    left_sum[index] = left_l[index] + left_r[index];
    right_sum[index] = right_l[index] + right_r[index];
  }

  vector<int> part_shift = QuickMul(left_sum, right_sum);

  for  (size_t index = 0; index < length; ++index) {
    part_shift[index] -= (part_shift_squared[index] +
                          part_without_shift[index]);
  }

  for (size_t index = 0; index  < length; ++index) {
    result[index] = part_without_shift[index];
  }

  for (size_t index = length; index < 2 * length; ++index) {
    result[index] = part_shift_squared[index - length];
  }

  for (size_t index = shift; index < length + shift; ++index) {
    result[index] += part_shift[index - shift];
  }

  return result;
}