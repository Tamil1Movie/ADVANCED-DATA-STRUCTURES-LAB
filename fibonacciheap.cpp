#include <iostream>
#include <cmath>
#include <vector>
#include <limits.h>
using namespace std;

struct Node {
    int key;
    int degree;
    Node* parent;
    Node* child;
    Node* left;
    Node* right;
    bool marked;

    Node(int val) {
        key = val;
        degree = 0;
        parent = child = nullptr;
        left = right = this;
        marked = false;
    }
};

class FibonacciHeap {
private:
    Node* minNode;
    int n;

    void link(Node* y, Node* x) {
        y->left->right = y->right;
        y->right->left = y->left;
        y->parent = x;
        if (x->child == nullptr) {
            x->child = y;
            y->left = y->right = y;
        } else {
            y->right = x->child;
            y->left = x->child->left;
            x->child->left->right = y;
            x->child->left = y;
        }
        x->degree++;
        y->marked = false;
    }

    void cut(Node* x, Node* y) {
        if (x->right == x) {
            y->child = nullptr;
        } else {
            x->right->left = x->left;
            x->left->right = x->right;
            if (y->child == x) {
                y->child = x->right;
            }
        }
        y->degree--;
        x->parent = nullptr;
        x->marked = false;
        x->right = minNode;
        x->left = minNode->left;
        minNode->left->right = x;
        minNode->left = x;
        if (x->key < minNode->key) {
            minNode = x;
        }
    }

    void cascadingCut(Node* y) {
        Node* z = y->parent;
        if (z) {
            if (!y->marked) {
                y->marked = true;
            } else {
                cut(y, z);
                cascadingCut(z);
            }
        }
    }

    void consolidate() {
        int D = log2(n) + 1;
        vector<Node*> A(D, nullptr);
        vector<Node*> rootList;
        Node* x = minNode;
        if (x) {
            do {
                rootList.push_back(x);
                x = x->right;
            } while (x != minNode);
        }

        for (Node* w : rootList) {
            x = w;
            int d = x->degree;
            while (A[d]) {
                Node* y = A[d];
                if (x->key > y->key) swap(x, y);
                link(y, x);
                A[d] = nullptr;
                d++;
            }
            A[d] = x;
        }

        minNode = nullptr;
        for (Node* y : A) {
            if (y) {
                if (!minNode || y->key < minNode->key) {
                    minNode = y;
                }
            }
        }
    }

public:
    FibonacciHeap() : minNode(nullptr), n(0) {}

    void insert(int key) {
        Node* newNode = new Node(key);
        if (!minNode) {
            minNode = newNode;
        } else {
            newNode->right = minNode;
            newNode->left = minNode->left;
            minNode->left->right = newNode;
            minNode->left = newNode;
            if (key < minNode->key) {
                minNode = newNode;
            }
        }
        n++;
    }

    int getMin() {
        return minNode ? minNode->key : -1;
    }

    int extractMin() {
        if (!minNode) return -1;
        Node* z = minNode;
        if (z->child) {
            Node* x = z->child;
            do {
                x->parent = nullptr;
                x = x->right;
            } while (x != z->child);

            Node* minLeft = minNode->left;
            Node* childLeft = z->child->left;
            minLeft->right = z->child;
            z->child->left = minLeft;
            childLeft->right = minNode;
            minNode->left = childLeft;
        }

        z->left->right = z->right;
        z->right->left = z->left;

        if (z == z->right) {
            minNode = nullptr;
        } else {
            minNode = z->right;
            consolidate();
        }

        int minKey = z->key;
        delete z;
        n--;
        return minKey;
    }

    void merge(FibonacciHeap& other) {
        if (!other.minNode) return;
        if (!minNode) {
            minNode = other.minNode;
        } else {
            Node* left1 = minNode->left;
            Node* left2 = other.minNode->left;
            left1->right = other.minNode;
            other.minNode->left = left1;
            left2->right = minNode;
            minNode->left = left2;
            if (other.minNode->key < minNode->key) {
                minNode = other.minNode;
            }
        }
        n += other.n;
        other.minNode = nullptr;
    }

    void display() {
        if (!minNode) {
            cout << "Heap is empty." << endl;
            return;
        }
        Node* temp = minNode;
        do {
            cout << temp->key << " ";
            temp = temp->right;
        } while (temp != minNode);
        cout << endl;
    }
};

int main() {
    FibonacciHeap heap1, heap2;
    int choice, value;
           cout << "1. Insert into Heap1\n2. Insert into Heap2\n3. Get Min from Heap1\n4. Extract Min from Heap1\n5. Merge Heaps\n6. Exit\n";
    while (true) {
       cout << "Enter choice: ";
        cin >> choice;
        switch (choice) {
            case 1:
                cout << "Enter value: ";
                cin >> value;
                heap1.insert(value);
                break;
            case 2:
                cout << "Enter value: ";
                cin >> value;
                heap2.insert(value);
                break;
            case 3:
                cout << "Minimum: " << heap1.getMin() << endl;
                break;
            case 4:
                cout << "Extracted Min: " << heap1.extractMin() << endl;
                break;
            case 5:
                heap1.merge(heap2);
                cout << "Heaps merged successfully." << endl;
                heap1.display();
                break;
            case 6:
                return 0;
            default:
                cout << "Invalid choice!" << endl;
        }
    }
    return 0;
}
