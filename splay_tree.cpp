#include <iostream>
#include <queue>
#include <vector>
using namespace std;

struct Node {
    int key;
    Node* left;
    Node* right;
    Node(int k) : key(k), left(NULL), right(NULL) {}
};

class SplayTree {
    Node* root;

    Node* rightRotate(Node* x) {
        Node* y = x->left;
        x->left = y->right;
        y->right = x;
        return y;
    }

    Node* leftRotate(Node* x) {
        Node* y = x->right;
        x->right = y->left;
        y->left = x;
        return y;
    }

    Node* splay(Node* root, int key) {
        if (!root || root->key == key) return root;
        if (key < root->key) {
            if (!root->left) return root;
            if (key < root->left->key) {
                root->left->left = splay(root->left->left, key);
                root = rightRotate(root);
            } else if (key > root->left->key) {
                root->left->right = splay(root->left->right, key);
                if (root->left->right) root->left = leftRotate(root->left);
            }
            return root->left ? rightRotate(root) : root;
        } else {
            if (!root->right) return root;
            if (key > root->right->key) {
                root->right->right = splay(root->right->right, key);
                root = leftRotate(root);
            } else if (key < root->right->key) {
                root->right->left = splay(root->right->left, key);
                if (root->right->left) root->right = rightRotate(root->right);
            }
            return root->right ? leftRotate(root) : root;
        }
    }

    Node* insert(Node* root, int key) {
        if (!root) return new Node(key);
        root = splay(root, key);
        if (root->key == key) return root;
        Node* newNode = new Node(key);
        if (key < root->key) {
            newNode->right = root;
            newNode->left = root->left;
            root->left = NULL;
        } else {
            newNode->left = root;
            newNode->right = root->right;
            root->right = NULL;
        }
        return newNode;
    }

    Node* deleteNode(Node* root, int key) {
        if (!root) return NULL;
        root = splay(root, key);
        if (root->key != key) return root;
        if (!root->left) {
            Node* temp = root->right;
            delete root;
            return temp;
        } else {
            Node* temp = root->left;
            temp = splay(temp, key);
            temp->right = root->right;
            delete root;
            return temp;
        }
    }

    void inorder(Node* root) {
        if (root) {
            inorder(root->left);
            cout << root->key << " ";
            inorder(root->right);
        }
    }

    void printTree(Node* root, int space = 0, int height = 10) {
        if (!root) return;
        space += height;
        printTree(root->right, space);
        cout << endl;
        for (int i = height; i < space; i++) cout << " ";
        cout << root->key << "\n";
        printTree(root->left, space);
    }

    void levelOrder(Node* root) {
        if (root == NULL) return;

        queue<Node*> q;
        q.push(root);

 
        vector<int> currentLevel;

        while (!q.empty()) {
            int levelSize = q.size();
            
           
            currentLevel.clear();
            
            for (int i = 0; i < levelSize; i++) {
                Node* current = q.front();
                q.pop();
                currentLevel.push_back(current->key);

                if (current->left != NULL) {
                    q.push(current->left);
                }
                if (current->right != NULL) {
                    q.push(current->right);
                }
            }

           
            cout << "[ ";
            for (int i = 0; i < currentLevel.size(); i++) {
                cout << currentLevel[i] << " ";
            }
            cout << "] ";
            cout << endl;  
        }
    }

public:
    SplayTree() : root(NULL) {}

    void insert(int key) {
        root = insert(root, key);
    }

    void deleteNode(int key) {
        root = deleteNode(root, key);
    }

    void display() {
        levelOrder(root);  
    }
};

int main() {
    SplayTree tree;
    int choice, key;
    cout << "\n1. Insert\n2. Delete\n3. Display (Level Order)\n4. Exit\n";
    while (true) {
        cout << "Enter choice: ";
        cin >> choice;
        switch (choice) {
            case 1: cout << "Enter key: "; cin >> key; tree.insert(key); break;
            case 2: cout << "Enter key: "; cin >> key; tree.deleteNode(key); break;
            case 3: tree.display(); break;
            case 4: return 0;
            default: cout << "Invalid choice\n";
        }
    }
}

