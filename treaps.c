#include <iostream>
using namespace std;

struct Node {
    int key, priority;
    Node *left, *right;

    Node(int k, int p) : key(k), priority(p), left(nullptr), right(nullptr) {}
};


Node* rightRotate(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;
    x->right = y;
    y->left = T2;
    return x;
}

Node* leftRotate(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;
    y->left = x;
    x->right = T2;
    return y;
}


Node* insert(Node* root, int key, int priority) {
    if (!root) return new Node(key, priority);

    if (key < root->key) {
        root->left = insert(root->left, key, priority);
        if (root->left->priority > root->priority)
            root = rightRotate(root);
    } else if (key > root->key) {
        root->right = insert(root->right, key, priority);
        if (root->right->priority > root->priority)
            root = leftRotate(root);
    }

    return root;
}


Node* deleteNode(Node* root, int key) {
    if (!root) return root;

    if (key < root->key)
        root->left = deleteNode(root->left, key);
    else if (key > root->key)
        root->right = deleteNode(root->right, key);
    else {
        if (!root->left) {
            Node* temp = root->right;
            delete root;
            return temp;
        } else if (!root->right) {
            Node* temp = root->left;
            delete root;
            return temp;
        }

        if (root->left->priority > root->right->priority) {
            root = rightRotate(root);
            root->right = deleteNode(root->right, key);
        } else {
            root = leftRotate(root);
            root->left = deleteNode(root->left, key);
        }
    }

    return root;
}


void inorder(Node* root) {
    if (root) {
        inorder(root->left);
        cout << "Key: " << root->key << " | Priority: " << root->priority << "\n";
        inorder(root->right);
    }
}

int main() {
    Node* root = nullptr;
    int choice, key, priority;
        cout << "\nTreap Menu:\n";
        cout << "1. Insert\n";
        cout << "2. Delete\n";
        cout << "3. Display (Inorder)\n";
        cout << "4. Exit\n";
   while(true){
	cout<<"Enter your choice :";
	cin>>choice;
        switch (choice) {
            case 1:
                cout << "Enter key to insert: ";
                cin >> key;
                cout << "Enter priority for the node: ";
                cin >> priority;
                root = insert(root, key, priority);
                break;
            case 2:
                cout << "Enter key to delete: ";
                cin >> key;
                root = deleteNode(root, key);
                break;
            case 3:
                cout << "Treap elements (Inorder Traversal):\n";
                inorder(root);
                break;
            case 4:
                cout << "Exiting...\n";
                return 0;
            default:
                cout << "Invalid choice. Try again.\n";
        }
    }

    return 0;
}
