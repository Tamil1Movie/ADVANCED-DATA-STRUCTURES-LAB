#include <iostream>
#include <queue>
using namespace std;

enum Color { RED, BLACK };

struct Node {
    int data;
    Color color;
    Node *left, *right, *parent;

    Node(int data) {
        this->data = data;
        left = right = parent = nullptr;
        color = RED;
    }
};

class RedBlackTree {
private:
    Node *root;
    Node *TNULL;

    void initializeNULLNode(Node *node, Node *parent) {
        node->data = 0;
        node->parent = parent;
        node->left = node->right = nullptr;
        node->color = BLACK;
    }

    void leftRotate(Node *x) {
        Node *y = x->right;
        x->right = y->left;
        if (y->left != TNULL)
            y->left->parent = x;

        y->parent = x->parent;
        if (x->parent == nullptr)
            root = y;
        else if (x == x->parent->left)
            x->parent->left = y;
        else
            x->parent->right = y;

        y->left = x;
        x->parent = y;
    }

    void rightRotate(Node *x) {
        Node *y = x->left;
        x->left = y->right;
        if (y->right != TNULL)
            y->right->parent = x;

        y->parent = x->parent;
        if (x->parent == nullptr)
            root = y;
        else if (x == x->parent->right)
            x->parent->right = y;
        else
            x->parent->left = y;

        y->right = x;
        x->parent = y;
    }

    void fixInsert(Node *k) {
        Node *uncle;
        while (k->parent->color == RED) {
            if (k->parent == k->parent->parent->right) {
                uncle = k->parent->parent->left;
                if (uncle->color == RED) {
                    uncle->color = BLACK;
                    k->parent->color = BLACK;
                    k->parent->parent->color = RED;
                    k = k->parent->parent;
                } else {
                    if (k == k->parent->left) {
                        k = k->parent;
                        rightRotate(k);
                    }
                    k->parent->color = BLACK;
                    k->parent->parent->color = RED;
                    leftRotate(k->parent->parent);
                }
            } else {
                uncle = k->parent->parent->right;
                if (uncle->color == RED) {
                    uncle->color = BLACK;
                    k->parent->color = BLACK;
                    k->parent->parent->color = RED;
                    k = k->parent->parent;
                } else {
                    if (k == k->parent->right) {
                        k = k->parent;
                        leftRotate(k);
                    }
                    k->parent->color = BLACK;
                    k->parent->parent->color = RED;
                    rightRotate(k->parent->parent);
                }
            }
            if (k == root)
                break;
        }
        root->color = BLACK;
    }

    void insert(int key) {
        Node *node = new Node(key);
        node->parent = nullptr;
        node->left = TNULL;
        node->right = TNULL;

        Node *y = nullptr;
        Node *x = root;

        while (x != TNULL) {
            y = x;
            if (node->data < x->data)
                x = x->left;
            else
                x = x->right;
        }

        node->parent = y;
        if (y == nullptr)
            root = node;
        else if (node->data < y->data)
            y->left = node;
        else
            y->right = node;

        if (node->parent == nullptr) {
            node->color = BLACK;
            return;
        }
        if (node->parent->parent == nullptr)
            return;

        fixInsert(node);
    }

    void printTreeHelper(Node *root, string indent, bool last) {
        if (root != TNULL) {
            cout << indent;
            if (last) {
                cout << "R----";
                indent += "   ";
            } else {
                cout << "L----";
                indent += "|  ";
            }
            cout << root->data << "(" << (root->color == RED ? "R" : "B") << ")" << endl;
            printTreeHelper(root->left, indent, false);
            printTreeHelper(root->right, indent, true);
        }
    }

public:
    RedBlackTree() {
        TNULL = new Node(0);
        TNULL->color = BLACK;
        root = TNULL;
    }

    void insertNode(int key) { insert(key); }
    
    void printTree() {
        if (root == TNULL) {
            cout << "Tree is empty!\n";
        } else {
            printTreeHelper(root, "", true);
        }
    }
};

int main() {
    RedBlackTree rbt;
    int choice, val;

    do {
        cout << "\n1. Insert\n2. Display Tree Structure\n3. Exit\nEnter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter value to insert: ";
                cin >> val;
                rbt.insertNode(val);
                break;
            case 2:
                cout << "Red-Black Tree Structure:\n";
                rbt.printTree();
                break;
            case 3:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice! Try again.\n";
        }
    } while (choice != 3);

    return 0;
}