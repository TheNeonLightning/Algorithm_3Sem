#include <iostream>
#include <string>
#include <vector>

using std::cin;
using std::string;
using std::cin;
using std::cout;
using std::vector;

const int ALPHABET_SIZE = 26;

///SuffixArray//////////////////////////////////////////////////////////////////

void BuildSuffixArray(string str, vector<int>& permutations);

int InitialPhase(string str, vector<int>& count, vector<int>& classes,
    vector<int>& permutations);

void SubsequentPhases(int size, int classes_number, vector<int>& count,
    vector<int>& classes, vector<int>& permutations);

///LCP//////////////////////////////////////////////////////////////////////////

void CalculateLCP(string str, vector<int>& suffix_array, vector<int>& lcp);

///SubstringsCounting///////////////////////////////////////////////////////////

int CountSubstrings(string& str, vector<int>& suffix_array, vector<int>& lcp);

int main() {
  string str;
  cin >> str;
  vector<int> suffix_array;
  vector<int> lcp;
  BuildSuffixArray(str, suffix_array);

  vector<int> suf_array(str.size(), 0);
  for (int index = 0; index < suffix_array.size() - 1; ++index) {
    suf_array[index] = suffix_array[index + 1];
  }

  CalculateLCP(str, suf_array, lcp);
  cout << CountSubstrings(str, suf_array, lcp);
  return 0;
}

void BuildSuffixArray(string str, vector<int>& permutations) {
  str += '`'; /// instead of '$' symbol '`' is used as its code equals to 'a' - 1
  int size = str.size(), classes_number = 1;
  permutations.resize(size, 0);
  vector<int> classes(size, 0);
  vector<int> count(ALPHABET_SIZE + 1, 0);

  classes_number = InitialPhase(str, count, classes, permutations);

  SubsequentPhases(size, classes_number, count, classes, permutations);
}

int InitialPhase(string str, vector<int>& count,
                vector<int>& classes, vector<int>& permutations) {
  int size = str.size(), classes_number = 1;
  for (int index = 0; index < size; ++index) {
    ++count[str[index] - '`'];
  }

  for (int index = 1; index < ALPHABET_SIZE + 1; ++index) {
    count[index] += count[index - 1];
  }

  for (int index = 0; index < size; ++index) {
    permutations[--count[str[index] - '`']] = index;
  }

  classes[permutations[0]] = 0;
  for (int index = 1; index < size; ++index) {
    classes[permutations[index]] = classes[permutations[index - 1]];
    if (str[permutations[index]] != str[permutations[index - 1]]) {
      ++classes[permutations[index]];
      ++classes_number;
    }
  }
  return classes_number;
}

void SubsequentPhases(int size, int classes_number, vector<int>& count,
                      vector<int>& classes, vector<int>& permutations) {

  vector<int> sorted_by_second_half(size, 0);
  vector<int> next_classes(size, 0);
  int half_cmp_size = 1;

  while (half_cmp_size < size) {
    count.clear();
    count.resize(classes_number, 0);

    for (int index = 0; index < size; ++index) {
      sorted_by_second_half[index] = permutations[index] - half_cmp_size;
      if (sorted_by_second_half[index] < 0) {
        sorted_by_second_half[index] += size;
      }
    }

    for (int index = 0; index < size; ++index) {
      ++count[classes[sorted_by_second_half[index]]];
    }

    for (int index = 1; index < classes_number; ++index) {
      count[index] += count[index - 1];
    }

    for (int index = size - 1; index >= 0; --index) {
      permutations[--count[classes[sorted_by_second_half[index]]]] =
          sorted_by_second_half[index];
    }

    next_classes[permutations[0]] = 0;
    classes_number = 1;
    for (int index = 1; index < size; ++index) {
      next_classes[permutations[index]] = next_classes[permutations[index - 1]];
      if (classes[permutations[index]] != classes[permutations[index - 1]] ||
          classes[permutations[index] + half_cmp_size] !=
          classes[permutations[index - 1] + half_cmp_size]) {
        ++next_classes[permutations[index]];
        ++classes_number;
      }
    }
    classes = next_classes;
    half_cmp_size = half_cmp_size << 1;
  }
}

void CalculateLCP(string str, vector<int>& suffix_array, vector<int>& lcp) {
  int size = str.size(), current_value = 0, next = 0;
  lcp.resize(size, 0);
  vector<int> position_in_suf(size, 0); /// suf^(-1)

  for (int index = 0; index < size; ++index) {
    position_in_suf[suffix_array[index]] = index;
  }

  for (int index = 0; index < size; ++index) {
    if (current_value > 0) {
      current_value--;
    }
    if (position_in_suf[index] == size - 1) { /// если попали в последнюю
/// => lcp не определён
      lcp[size - 1] = -1;
      current_value = 0;
      continue;
    } else {
      next = suffix_array[position_in_suf[index] + 1];
      while ((std::max(index + current_value, next + current_value) < size) &&
             (str[index + current_value] == str[next + current_value])) {
        ++current_value;
      }
      lcp[position_in_suf[index]] = current_value;
    }
  }
}

int CountSubstrings(string& str, vector<int>& suffix_array, vector<int>& lcp) {
  int size = str.size(), result = size - suffix_array[0];
  for (int index = 1; index < size ; ++index) {
    result = result + (size - suffix_array[index]) - lcp[index - 1];
  }
  return result;
}