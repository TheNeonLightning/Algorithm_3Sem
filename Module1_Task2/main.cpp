#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::vector;

void StringFromPrefixFunction(const vector<size_t>& prefix_function,
    vector<char>& string);

void ZFunctionFromString(const vector<char>& string,
    vector<size_t>& z_function);

void PrefixFunctionFromZFunction(const vector<size_t>& z_function,
    vector<size_t>& prefix_function);

void PrefixFunctionFromString(const vector<char>& string,
    vector<size_t>&prefix_function);

void StringFromZFunction(const vector<size_t>& z_function,
    vector<char>& string);

void ZFunctionFromPrefixFunction(const vector<size_t>& prefix_function,
    vector<size_t>& z_function);

void B1Solution();

void B2Solution();

int main() {
  B1Solution();
  return 0;
}

void StringFromPrefixFunction(const vector<size_t>& prefix_function,
    vector<char>& string) {
  char a_letter = 'a';
  string[0] = a_letter;
  int current_index = 0;
  for (size_t index = 1; index < prefix_function.size(); ++index) {
    if (prefix_function[index] == 0) {
      vector<bool> available(26, true);
      current_index = prefix_function[index - 1];
      while (current_index > 0) {
        available[string[current_index] - a_letter] = false;
        current_index = prefix_function[current_index - 1];
      }
      current_index = 1;
      while(true) {
        if (available[current_index]) {
          string[index] = a_letter + current_index;
          break;
        }
        ++current_index;
      }
    } else {
      string[index] = string[prefix_function[index] - 1];
    }
  }
}

void ZFunctionFromString(const vector<char>& string,
    vector<size_t>& z_function) {
  size_t left = 0, right = 0;
  for (size_t index = 1; index < string.size(); ++index) {
    if (index <= right) {
      z_function[index] = std::min(right - index + 1, z_function[index - left]);
    }
    while ((index + z_function[index] < string.size()) &&
           (string[index + z_function[index]] == string[z_function[index]])) {
      ++z_function[index];
    }
    if (index + z_function[index] > right) {
      left = index;
      right = index + z_function[index] - 1;
    }
  }
}

void PrefixFunctionFromZFunction(const vector<size_t>& z_function,
    vector<size_t>& prefix_function) {
  for (size_t index = 1; index < z_function.size(); ++index) {
    for (size_t current_index = z_function[index]; current_index > 0;
         --current_index) {
      if (prefix_function[index + current_index - 1] > 0) {
        break;
      } else {
        prefix_function[index + current_index - 1] = current_index;
      }
    }
  }
}

void PrefixFunctionFromString(const vector<char>& string,
    vector<size_t>&prefix_function) {
  vector<size_t> z_function(string.size(), 0);
  ZFunctionFromString(string, z_function);
  PrefixFunctionFromZFunction(z_function, prefix_function);
}

void StringFromZFunction(const vector<size_t>& z_function,
    vector<char>& string) {
  vector<size_t> prefix_function(z_function.size(), 0);
  PrefixFunctionFromZFunction(z_function, prefix_function);
  StringFromPrefixFunction(prefix_function, string);
}

void ZFunctionFromPrefixFunction(const vector<size_t>& prefix_function,
    vector<size_t>& z_function) {
  vector<char> string(prefix_function.size());
  StringFromPrefixFunction(prefix_function, string);
  ZFunctionFromString(string, z_function);
}

void B1Solution() {
  vector<size_t> prefix_function;
  int value = 0;
  size_t index = 0;
  while (std::cin >> value) {
    prefix_function.push_back(value);
    ++index;
  }
  vector<char> string(prefix_function.size());
  StringFromPrefixFunction(prefix_function, string);
  for (index = 0; index < prefix_function.size(); ++index) {
    cout << string[index];
  }
}

void B2Solution() {
  vector<size_t> z_function;
  int value = 0;
  size_t index = 0;
  while (std::cin >> value) {
    z_function.push_back(value);
    ++index;
  }
  z_function[0] = 0;
  vector<char> string(z_function.size());
  StringFromZFunction(z_function, string);
  for (index = 0; index < string.size(); ++index) {
    cout << string[index];
  }
}