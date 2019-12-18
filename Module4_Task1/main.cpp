#include <vector>
#include "biginteger.h"

using std::cin;
using std::cout;
using std::vector;

typedef BigInteger T;





int main() {
  BigInteger x, y;
  cin >> x >> y;
  cout << (x == y);
}