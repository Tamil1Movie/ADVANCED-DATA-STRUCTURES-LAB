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

    void transplant(Node *u, Node *v) {
        if (u->parent == nullptr)
            root = v;
        else if (u == u->parent->left)
            u->parent->left = v;
        else
            u->parent->right = v;
        v->parent = u->parent;
    }

    void deleteFix(Node *x) {
        while (x != root && x->color == BLACK) {
            if (x == x->parent->left) {
                Node *s = x->parent->right;
                if (s->color == RED) {
                    s->color = BLACK;
                    x->parent->color = RED;
                    leftRotate(x->parent);
                    s = x->parent->right;
                }
                if (s->left->color == BLACK && s->right->color == BLACK) {
                    s->color = RED;
                    x = x->parent;
                } else {
                    if (s->right->color == BLACK) {
                        s->left->color = BLACK;
                        s->color = RED;
                        rightRotate(s);
                        s = x->parent->right;
                    }
                    s->color = x->parent->color;
                    x->parent->color = BLACK;
                    s->right->color = BLACK;
                    leftRotate(x->parent);
                    x = root;
                }
            } else {
                Node *s = x->parent->left;
                if (s->color == RED) {
                    s->color = BLACK;
                    x->parent->color = RED;
                    rightRotate(x->parent);
                    s = x->parent->left;
                }
                if (s->right->color == BLACK && s->left->color == BLACK) {
                    s->color = RED;
                    x = x->parent;
                } else {
                    if (s->left->color == BLACK) {
                        s->right->color = BLACK;
                        s->color = RED;
                        leftRotate(s);
                        s = x->parent->left;
                    }
                    s->color = x->parent->color;
                    x->parent->color = BLACK;
                    s->left->color = BLACK;
                    rightRotate(x->parent);
                    x = root;
                }
            }
        }
        x->color = BLACK;
    }

    void deleteNodeHelper(Node *node, int key) {
        Node *z = TNULL, *x, *y;
        while (node != TNULL) {
            if (node->data == key) {
                z = node;
            }
            if (node->data <= key) {
                node = node->right;
            } else {
                node = node->left;
            }
        }
        if (z == TNULL) {
            cout << "Key not found!\n";
            return;
        }
        y = z;
        Color y_original_color = y->color;
        if (z->left == TNULL) {
            x = z->right;
            transplant(z, z->right);
        } else if (z->right == TNULL) {
            x = z->left;
            transplant(z, z->left);
        }
        deleteFix(x);
    }

    void printTree(Node *root, string indent, bool last) {
        if (root != TNULL) {
            cout << indent;
            if (last) {
                cout << "R----";
                indent += "   ";
            } else {
                cout << "L----";
                indent += "|  ";
            }
            cout << root->data << "(" << (root->color == RED ? "R" : "B") << ")\n";
            printTree(root->left, indent, false);
            printTree(root->right, indent, true);
        }
    }

public:
    RedBlackTree() { root = TNULL; }

    void insertNode(int key) { insert(key); }
    void deleteNode(int key) { deleteNodeHelper(root, key); }
    void printTree() { printTree(root, "", true); }
};

int main() {
    RedBlackTree rbt;
    int choice, val;

    do {
        cout << "\n1. Insert\n2. Delete\n3. Display Tree\n4. Exit\nEnter choice: ";
        cin >> choice;
        if (choice == 1) {
            cout << "Enter value: "; cin >> val;
            rbt.insertNode(val);
        } else if (choice == 2) {
            cout << "Enter value: "; cin >> val;
            rbt.deleteNode(val);
        } else if (choice == 3) {
            rbt.printTree();
        }
    } while (choice != 4);

    return 0;
}


#include <iostream>
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

    void printTree(Node *root, string indent, bool last) {
        if (root != TNULL) {
            cout << indent;
            if (last) {
                cout << "R----";
                indent += "   ";
            } else {
                cout << "L----";
                indent += "|  ";
            }
            cout << root->data << "(" << (root->color == RED ? "R" : "B") << ")\n";
            printTree(root->left, indent, false);
            printTree(root->right, indent, true);
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
            printTree(root, "", true);
        }
    }

    void deleteNode(int key) {
        cout << "Deletion is not implemented yet. This is a placeholder to prevent segmentation faults.\n";
    }
};

int main() {
    RedBlackTree rbt;
    int choice, val;

    do {
        cout << "\n1. Insert\n2. Delete\n3. Display Tree\n4. Exit\nEnter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter value to insert: ";
                cin >> val;
                rbt.insertNode(val);
                break;
            case 2:
                cout << "Enter value to delete: ";
                cin >> val;
                rbt.deleteNode(val);
                break;
            case 3:
                cout << "Red-Black Tree Structure:\n";
                rbt.printTree();
                break;
            case 4:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice! Try again.\n";
        }
    } while (choice != 4);

    return 0;
}
