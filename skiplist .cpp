#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

const float PROBABILITY = 0.5;
const int MAX_LEVEL = 4;

template <typename T>
class Node {
public:
    T value;
    Node<T> **forward;

    Node(T val, int level) {
        value = val;
        forward = new Node<T>*[level + 1];
        for (int i = 0; i <= level; i++) {
            forward[i] = nullptr;
        }
    }

    ~Node() {
        delete[] forward;
    }
};

template <typename T>
class SkipList {
private:
    Node<T> *header;
    int currentLevel;

    int randomLevel() {
        int level = 0;
        while ((double)rand() / RAND_MAX < PROBABILITY && level < MAX_LEVEL - 1) {
            level++;
        }
        return level;
    }

public:
    SkipList() {
        header = new Node<T>(T(), MAX_LEVEL);
        currentLevel = 0;
        srand(time(0));
    }

    ~SkipList() {
        Node<T> *current = header;
        while (current) {
            Node<T> *next = current->forward[0];
            delete current;
            current = next;
        }
    }

    void insert(T value) {
        Node<T> *current = header;
        Node<T> *update[MAX_LEVEL];
        for (int i = currentLevel; i >= 0; i--) {
            while (current->forward[i] && current->forward[i]->value < value) {
                current = current->forward[i];
            }
            update[i] = current;
        }
        current = current->forward[0];
        if (!current || current->value != value) {
            int newLevel = randomLevel();
            if (newLevel > currentLevel) {
                for (int i = currentLevel + 1; i <= newLevel; i++) {
                    update[i] = header;
                }
                currentLevel = newLevel;
            }
            Node<T> *newNode = new Node<T>(value, newLevel);
            for (int i = 0; i <= newLevel; i++) {
                newNode->forward[i] = update[i]->forward[i];
                update[i]->forward[i] = newNode;
            }
            cout << "Inserted: " << value << endl;
        }
    }

    void display() {
        cout << "\nSkip List: " << endl;
        for (int i = 0; i <= currentLevel; i++) {
            Node<T> *node = header->forward[i];
            cout << "Level " << i << ": ";
            while (node) {
                cout << node->value << " ";
                node = node->forward[i];
            }
            cout << endl;
        }
    }

    void search(T value) {
        Node<T> *current = header;
        for (int i = currentLevel; i >= 0; i--) {
            while (current->forward[i] && current->forward[i]->value < value) {
                current = current->forward[i];
            }
        }
        current = current->forward[0];
        if (current && current->value == value) {
            cout << "Found: " << value << endl;
        } else {
            cout << "Not Found: " << value << endl;
        }
    }

    void remove(T value) {
        Node<T> *current = header;
        Node<T> *update[MAX_LEVEL];
        for (int i = currentLevel; i >= 0; i--) {
            while (current->forward[i] && current->forward[i]->value < value) {
                current = current->forward[i];
            }
            update[i] = current;
        }
        current = current->forward[0];
        if (current && current->value == value) {
            for (int i = 0; i <= currentLevel; i++) {
                if (update[i]->forward[i] != current) {
                    break;
                }
                update[i]->forward[i] = current->forward[i];
            }
            delete current;
            while (currentLevel > 0 && header->forward[currentLevel] == nullptr) {
                currentLevel--;
            }
            cout << "Deleted: " << value << endl;
        } else {
            cout << "Not Found for Deletion: " << value << endl;
        }
    }
};

int main() {
    SkipList<int> skipList;
    int choice, value;

    do {
        cout << "\n--- Skip List Operations Menu ---" << endl;
        cout << "1. Insert element" << endl;
        cout << "2. Search element" << endl;
        cout << "3. Delete element" << endl;
        cout << "4. Display skip list" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter element to insert: ";
                cin >> value;
                skipList.insert(value);
                break;
            case 2:
                cout << "Enter element to search: ";
                cin >> value;
                skipList.search(value);
                break;
            case 3:
                cout << "Enter element to delete: ";
                cin >> value;
                skipList.remove(value);
                break;
            case 4:
                skipList.display();
                break;
            case 5:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice! Please try again." << endl;
        }
    } while (choice != 5);

    return 0;
}