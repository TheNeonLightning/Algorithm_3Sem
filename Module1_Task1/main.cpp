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

void PositionSearch(vector<int>& result, const string& line, size_t size) {
  vector<int> prefix_function(size); // значение префикс-функции для паттерна
  prefix_function[0] = 0;
  size_t current_index = 0; // индекс, который указывает на символ, с
  // которым сравнивается текущий рассматриваемый (в описаниях алгоритма обычно
  // обозначается как j)
  for (size_t index = 1; index < size; ++index) { // вычисление префикс функции
    // для паттерна
    current_index = prefix_function[index - 1];
    bool flag = false;
    while (!flag) {
      if (line[index] == line[current_index]) {
        prefix_function[index] = current_index + 1;
        flag = true;
      } else {
        if (current_index == 0) { // если дошли до первого символа и не нашли
          // совпадения, то значение префикс функции равно 0
          prefix_function[index] = 0;
          flag = true;
        }
        current_index = prefix_function[current_index - 1];
      }
    }
  }
  size_t previous_value = 0;
  for (size_t index = size + 1; index < line.length(); ++index) { // вычисление
    // префикс функции для остальной части общей строки (без сохранения)
    current_index = previous_value; // достаточно зранить только значение
    // префикс функции на предыдущем символе
    bool flag = false;
    while (!flag) {
      if (line[index] == line[current_index]) {
        previous_value = current_index + 1;
        flag = true;
      } else {
        if (current_index == 0) {
          previous_value = 0;
          flag = true;
        }
        current_index = prefix_function[current_index - 1];
      }
    }
    if (previous_value == size) { // если значение префикс функции равно длине
      // паттерна => нашли ещё одно вхождение
      result.push_back(index - 2 * size);
    }
  }
}

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
