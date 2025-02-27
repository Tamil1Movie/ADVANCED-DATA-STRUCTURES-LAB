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

    bool search(string word) {
        TrieNode* node = root;
        for (char c : word) {
            if (!node->children[c - 'a']) return false;
            node = node->children[c - 'a'];
        }
        return node->isEnd;
    }

    vector<string> getSuggestions(string prefix) {
        vector<string> suggestions;
        TrieNode* node = root;
        for (char c : prefix) {
            if (!node->children[c - 'a']) return suggestions;
            node = node->children[c - 'a'];
        }
        suggestHelper(node, prefix, suggestions);
        return suggestions;
    }
};

// **Main Function to Accept User Input**
int main() {
    Trie trie;
    int choice;
    string word, prefix;
    vector<string> suggestions;  // Declare it outside of switch

    while (true) {
        cout << "\nMenu:\n";
        cout << "1. Insert a word\n";
        cout << "2. Search for a word\n";
        cout << "3. Get suggestions for a prefix\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter a word to insert: ";
                cin >> word;
                trie.insert(word);
                cout << "Word inserted.\n";
                break;
            case 2:
                cout << "Enter a word to search: ";
                cin >> word;
                cout << (trie.search(word) ? "Word found.\n" : "Word not found.\n");
                break;
            case 3:
                cout << "Enter a prefix: ";
                cin >> prefix;
                suggestions = trie.getSuggestions(prefix);  // Now it's inside the loop, not in switch
                if (suggestions.empty()) 
                    cout << "No suggestions found.\n";
                else {
                    cout << "Suggestions: ";
                    for (string s : suggestions) cout << s << " ";
                    cout << endl;
                }
                break;
            case 4:
                cout << "Exiting program.\n";
                return 0;
            default:
                cout << "Invalid choice! Try again.\n";
        }
    }
}
