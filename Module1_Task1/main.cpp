// Найдите все вхождения шаблона в строку. Длина шаблона – p, длина строки – n.
// Время O(n + p), доп. память – O(p).
// p <= 30000, n <= 300000.
// Использовать один из методов:
// - С помощью префикс-функции;
// - С помощью z-функции.

#include <iostream>
#include <vector>
#include <string>

using std::cin;
using std::cout;
using std::string;
using std::vector;

size_t PrefixFunctionNextValue(const string& line, vector<int>& prefix_function,
    size_t current_index, size_t previous_value);

void PrefixFunctionForPattern(const string& line,
    const vector<int>& prefix_function, size_t size);

void PositionSearch(vector<int>& result, const string& line, size_t size);

int main() {
  string pattern, str, line;
  cin >> pattern;
  cin >> str;
  line = pattern + '#' + str;
  vector<int> result; // массив для хранения результата
  PositionSearch(result, line, pattern.length());
  for (size_t index = 0; index < result.size(); ++index) {
    cout << result[index] << ' ';
  }
  return 0;
}

size_t PrefixFunctionNextValue(const string& line,
    const vector<int>& prefix_function, size_t current_index,
    size_t previous_value) {
  bool flag = false;
  while (!flag) {
    if (line[current_index] == line[previous_value]) {
      previous_value = previous_value + 1;
      flag = true;
    } else {
      if (previous_value == 0) {
        flag = true;
      }
      previous_value = prefix_function[previous_value - 1];
    }
  }
  return previous_value;
}

void PrefixFunctionForPattern(const string& line, vector<int>& prefix_function,
    size_t size) {
  for (size_t index = 1; index < size; ++index) {
    prefix_function[index] = PrefixFunctionNextValue(line, prefix_function,
        index, prefix_function[index - 1]);
  }
}

void PositionSearch(vector<int>& result, const string& line, size_t size) {
  vector<int> prefix_function(size); // значение префикс-функции для паттерна
  prefix_function[0] = 0;
  PrefixFunctionForPattern(line, prefix_function, size);
  size_t previous_value = 0; // достаточно хранить предыдущее значение префикс
  // функции
  for (size_t index = size + 1; index < line.length(); ++index) { // вычисление
    // префикс функции для остальной части общей строки (без сохранения)
    previous_value = PrefixFunctionNextValue(line, prefix_function, index,
        previous_value);
    if (previous_value == size) { // если значение префикс функции равно длине
      // паттерна => нашли ещё одно вхождение
      result.push_back(index - 2 * size);
    }
  }
}