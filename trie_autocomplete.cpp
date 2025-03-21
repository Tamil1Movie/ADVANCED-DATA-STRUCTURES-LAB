#include <iostream>
#include <vector>
#include <string>
using namespace std;

class TrieNode {
public:
    TrieNode* children[26];
    bool isEnd;

    TrieNode() {
        isEnd = false;
        for (int i = 0; i < 26; i++)
            children[i] = nullptr;
    }
};

class Trie {
private:
    TrieNode* root;

    // Recursive function to find suggestions
    void suggestHelper(TrieNode* node, string prefix, vector<string>& suggestions) {
        if (node->isEnd)
            suggestions.push_back(prefix);

        for (char c = 'a'; c <= 'z'; c++) {
            if (node->children[c - 'a'])
                suggestHelper(node->children[c - 'a'], prefix + c, suggestions);
        }
    }

public:
    Trie() { root = new TrieNode(); }

    void insert(string word) {
        TrieNode* node = root;
        for (char c : word) {
            if (!node->children[c - 'a'])
                node->children[c - 'a'] = new TrieNode();
            node = node->children[c - 'a'];
        }
        node->isEnd = true;
    }

    vector<string> autoComplete(string prefix) {
        vector<string> suggestions;
        TrieNode* node = root;
        for (char c : prefix) {
            if (!node->children[c - 'a'])
                return suggestions; // No suggestions if prefix not found
            node = node->children[c - 'a'];
        }
        suggestHelper(node, prefix, suggestions);
        return suggestions;
    }
};

// **Main Function for Testing Auto-Complete**
int main() {
    Trie trie;
    vector<string> dictionary = {"hello", "hell", "help", "helmet", "healthy", "heal"};

    // Insert words into Trie
    for (string word : dictionary)
        trie.insert(word);

    string prefix;
    cout << "Enter text to auto-complete: ";
    cin >> prefix;

    vector<string> suggestions = trie.autoComplete(prefix);

    if (suggestions.empty())
        cout << "No suggestions found.\n";
    else {
        cout << "Auto-complete suggestions: ";
        for (string word : suggestions)
            cout << word << " ";
        cout << endl;
    }

    return 0;
}
