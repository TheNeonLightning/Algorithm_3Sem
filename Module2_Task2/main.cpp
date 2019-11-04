#include <iostream>
#include <vector>
#include <string>
#include <map>

using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::string;
using std::map;

const int ALPHABET_SIZE = 123; /// used the alphabet up to letter 'z'

class SufTrie {
public:
  int position = -1; /// position in text (what letter is being added right now)

  int active_node = 0; /// the three values are showing the position from which
  int active_edge = 0; /// the new suffix will be implemented actively
  int active_length = 0;

  int stored_link = 0; /// the saved link to connect
  int remainder = 0; /// number of suffixes to insert actively

  struct Node {
    int left = -1;
    int right = -1; /// using -1 for the leaves
    int link = 0; ///default link pointing to the root
    vector<int> next = vector<int>(ALPHABET_SIZE, -1);

    explicit Node(int left = -1, int right = -1):
        left(left),
        right(right),
        link(0){}

    int Length(int current_position) {
      return (right == -1 ? current_position + 1 - left : right - left); /// if right == -1 =>
    }                                                                    /// the node is leaf =>
  };                                                                     /// right = current_position

  int first_size = 0; /// size of first string
  int second_size = 0; /// size of second string

  string text = "";
  vector<Node> trie;


  SufTrie(int first_size = 0, int second_size = 0):
  first_size(first_size),
  second_size(second_size)
  {
    trie.emplace_back(-1, -1); /// init the root
  }

  ///BuildingSufTrie////////////////////////////////////////////////////////////

  void StoreLink(int current_node);

  bool ProceedToNext(int next_node);

  void SetParamsForNextPhase();

  void Split(int next_node, char symbol);

  void CreateLeaf();

  void NextChar(char symbol);

  ///DFS////////////////////////////////////////////////////////////////////////

  void DFS(int previous, int vertex, vector<bool>& visited, int& number);

  void ResultOutput();

};


int main() {
  string str1, str2, str;
  cin >> str1 >> str2;
  str = str1 + str2;
  SufTrie tree(str1.size(), str2.size());
  for (size_t index = 0; index < str.size(); ++index) {
    tree.NextChar(str[index]);
  }
  tree.ResultOutput();
  return 0;
}

///SufTrie//////////////////////////////////////////////////////////////////////

void SufTrie::StoreLink(int current_node) {
  if (stored_link != 0) { /// if there is already link to connect
    trie[stored_link].link = current_node;
  }
  stored_link = current_node; /// save new link
}

bool SufTrie::ProceedToNext(int next_node) {
  int edge_length = trie[next_node].Length(position);
  if (active_length >= edge_length) {
    active_edge += edge_length;
    active_length -= edge_length;
    active_node = next_node;
    return true;
  }
  return false;
}

void SufTrie::SetParamsForNextPhase() {
  --remainder;
  if (active_node == 0 && active_length > 0) {
    --active_length;
    active_edge = position - remainder + 1;
  } else {
    active_node = trie[active_node].link;
  }
}

void SufTrie::Split(int next_node, char symbol) {
  trie.emplace_back(trie[next_node].left, trie[next_node].left + active_length);
  int internal_node = trie.size() - 1;
  trie[active_node].next[text[active_edge]] = internal_node;
  trie.emplace_back(position);
  trie[internal_node].next[symbol] = trie.size() - 1;
  trie[next_node].left += active_length;
  trie[internal_node].next[text[trie[next_node].left]] = next_node;
  StoreLink(internal_node);
}

void SufTrie::CreateLeaf() {
  trie.emplace_back(position);
  trie[active_node].next[text[active_edge]] = trie.size() - 1;
  StoreLink(active_node);
}

void SufTrie::NextChar(char symbol) {
  text += symbol;
  stored_link = 0;
  ++remainder; /// new symbol - one more suffix to insert actively
  ++position;
  while (remainder > 0) {

    if (active_length == 0) {
      active_edge = position;
    }

    if (trie[active_node].next[text[active_edge]] == -1) { /// the node is not existing
      CreateLeaf();
    } else {

      int next_node = trie[active_node].next[text[active_edge]];

      if (ProceedToNext(next_node)) {
        continue;
      }

      if (text[trie[next_node].left + active_length] == symbol) { /// the node is existing implicitly (between two real nodes)
        ++active_length;
        StoreLink(active_node);
        return;
      }

      Split(next_node, symbol);
    }
    SetParamsForNextPhase();
  }
}

///DFS_SufTrie//////////////////////////////////////////////////////////////////

void SufTrie::DFS(int previous, int vertex, vector<bool>& visited, int& number) {
  visited[vertex] = true;
  if (previous != -1) {
    if (trie[vertex].left < first_size) {
      printf("%d 0 %d ", previous, trie[vertex].left);
      if (trie[vertex].right == -1) {
        printf("%d\n", first_size);
      } else {
        printf("%d\n", trie[vertex].right);
      }
    } else {
      printf("%d 1 %d ", previous, trie[vertex].left - first_size);
      if (trie[vertex].right == -1) {
        printf("%d\n", second_size);
      } else {
        printf("%d\n", trie[vertex].right - first_size);
      }
    }
  }
  previous = number;
  ++number;

  for (int index = 0; index < ALPHABET_SIZE; ++index) {
    if (trie[vertex].next[index] != -1) {
      if (visited[trie[vertex].next[index]] != true) {
        DFS(previous, trie[vertex].next[index], visited, number);
      }
    }
  }
}

void SufTrie::ResultOutput() {
  vector<bool> visited(trie.size());
  int number = 0;
  cout << trie.size() << endl;
  DFS(-1, 0, visited, number);
}
