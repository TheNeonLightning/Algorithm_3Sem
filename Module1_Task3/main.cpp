#include <iostream>
#include <vector>

using std::vector;
using std::string;
using std::cin;
using std::cout;



class Trie {
public:

  class Node {
  public:
    bool leaf = false;
    int link = -1;
    int terminal_link = -1;
    int previous = -1;
    char previous_char = 0;

    vector<int> next = vector<int>(26, -1);
    vector<int> transition = vector<int>(26, -1);
    vector<int> pattern_indexes;
    vector<int> pattern_sizes;

    Node() = default;
    Node(int previous, char previous_char):previous(previous),
                                           previous_char(previous_char) {};

  };

  vector<Node> trie = vector<Node>(1);


  int Transition(int current_node, char current_char);


  int GetLink(int current_node);


  int GetTerminalLink(int current_node);


  void AddString(const string& str, int pattern_number, int pattern_size);

  /**
   * Counts for each index the number of patterns corresponding to it. The
   * results are stored in vector<int>& count.
   */
  void CountMatches(int patterns_number, int str_size,
      vector<int> &starting_pos, vector<int>& count, string &line);

};

/**
   * Outputs the indexes for which the number of matches is equals to the number
   * of patterns.
   */
void OutputIndexes(int patterns_number, int str_size, int line_size,
                   vector<int>& count);

int PatternSeparating(const string& str, vector<string>& patterns,
                      vector<int>& starting_pos);

////////////////////////////////////////////////////////////////////////////////

int main() {
  Trie trie;
  vector<string> patterns;
  vector<int> starting_pos;

  string str, line;
  cin >> str;
  cin >> line;

  int patterns_number = PatternSeparating(str, patterns, starting_pos);

  for (int index = 0; index < patterns_number; ++index) {
    trie.AddString(patterns[index], starting_pos[index], patterns[index].size());
  }

  vector<int> count(line.size(), 0);

  trie.CountMatches(patterns_number, str.size(), starting_pos, count, line);

  OutputIndexes(patterns_number, str.size(), line.size(), count);

  return 0;
}

////////////////////////////////////////////////////////////////////////////////

//////////Trie//////////////////////////////////////////////////////////////////


int Trie::Transition(int current_node, char current_char) {

  if (trie[current_node].transition[current_char] == -1) {

    if (trie[current_node].next[current_char] != -1) {
      trie[current_node].transition[current_char] =
          trie[current_node].next[current_char];

    } else if (current_node == 0) {
      trie[current_node].transition[current_char] = 0;

    } else {
      trie[current_node].transition[current_char] =
          Transition(GetLink(current_node), current_char);
    }

  }
  return trie[current_node].transition[current_char];
}


int Trie::GetLink(int current_node) {

  if (trie[current_node].link == -1) {

    if ((current_node == 0) || (trie[current_node].previous == 0)) {
      trie[current_node].link = 0;

    } else {
      trie[current_node].link =
        Transition(GetLink(trie[current_node].previous),
                   trie[current_node].previous_char);
    }

  }
  return trie[current_node].link;
}


int Trie::GetTerminalLink(int current_node) {

  if (trie[current_node].terminal_link == -1) {

    if ((trie[GetLink(current_node)].leaf) || (GetLink(current_node) == 0))  {
      trie[current_node].terminal_link = GetLink(current_node);

    } else {
      trie[current_node].terminal_link =
          GetTerminalLink(GetLink(current_node));
    }
  }
  return trie[current_node].terminal_link;
}


void Trie::AddString(const string &str, int pattern_number, int pattern_size) {
  int current_node = 0;

  for (int index = 0; index < str.size(); ++index) {
    char letter = str[index] - 'a';

    if (trie[current_node].next[letter] == -1) {
      trie[current_node].next[letter] = trie.size();
      trie.emplace_back(current_node, letter);
    }
    current_node = trie[current_node].next[letter];

  }

  trie[current_node].leaf = true;
  trie[current_node].pattern_indexes.push_back(pattern_number);
  trie[current_node].pattern_sizes.push_back(pattern_size);
}


void Trie::CountMatches(int patterns_number, int str_size,
    vector<int> &starting_pos, vector<int>& count, string &line) {

  int current_node = 0;

  for (int index = 0; index < line.size(); ++index) {
    char letter = line[index] - 'a';
    current_node = Transition(current_node, letter);
    int local_node = current_node;

    while (local_node != 0) {

      if (trie[local_node].leaf) {
        for (int local_index = 0;
             local_index < trie[local_node].pattern_indexes.size();
             ++local_index) {

          int index_in_counter = index -
              trie[local_node].pattern_sizes[local_index] -
              trie[local_node].pattern_indexes[local_index] + 1;

          if (index_in_counter >= 0) {
            ++count[index_in_counter];
          }
        }

      }

      local_node = GetTerminalLink(local_node);
    }
  }
}

void OutputIndexes(int patterns_number, int str_size, int line_size,
    vector<int>& count) {
  if (line_size >= str_size) {
    for (int index = 0; index < line_size - str_size + 1; ++index) {
      if ((index < line_size) && (count[index] == patterns_number)) {
        cout << index << ' ';
      }
    }
  }
}


////////////////////////////////////////////////////////////////////////////////


int PatternSeparating(const string& str, vector<string>& patterns,
                      vector<int>& starting_pos) {
  int index = 0, beginning = 0, patterns_number = 0;

  while ((str[index] == '?') && (index < str.size())) {
    ++index;
  }
  beginning = index;

  for (; index < str.size(); ++index) {
    if (str[index] == '?') {

      starting_pos.push_back(beginning);
      patterns.push_back(str.substr(beginning, index - beginning));
      ++patterns_number;

      while ((str[index] == '?') && (index < str.size())) {
        ++index;
      }
      beginning = index;
    }
  }

  if (str.back() != '?') {
    starting_pos.push_back(beginning);
    patterns.push_back(str.substr(beginning, index - beginning));
    ++patterns_number;
  }

  return patterns_number;
}