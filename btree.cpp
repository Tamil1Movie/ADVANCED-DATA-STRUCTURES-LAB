#include <iostream>
#include <queue>
using namespace std;

class BTreeNode {
    int *keys;
    int t;  // Minimum degree (defines the range for number of keys)
    BTreeNode **C;  // Child pointers
    int n;  // Current number of keys
    bool leaf;  // True if node is a leaf, false otherwise

public:
    BTreeNode(int _t, bool _leaf);  // Constructor
    void traverse();  // Traversal to print keys in the tree
    void levelOrder();  // Level order traversal
    BTreeNode *search(int k);  // Search for key in the tree
    void insertNonFull(int k);  // Insert key in non-full node
    void splitChild(int i, BTreeNode *y);  // Split a full child node
    void remove(int k);  // Remove key from the tree
    void removeFromLeaf(int idx);  // Remove key from a leaf node
    void removeFromNonLeaf(int idx);  // Remove key from a non-leaf node
    int getPred(int idx);  // Get predecessor of key
    int getSucc(int idx);  // Get successor of key
    void fill(int idx);  // Fill a node if it has less than t keys
    void merge(int idx);  // Merge two nodes
    void borrowFromLeft(int idx);  // Borrow key from left sibling
    void borrowFromRight(int idx);  // Borrow key from right sibling

    friend class BTree;
};

class BTree {
    BTreeNode *root;
    int t;  // Minimum degree

public:
    BTree(int _t) { root = nullptr; t = _t; }
    void traverse() { if (root) root->traverse(); }
    void levelOrder() { if (root) root->levelOrder(); }
    BTreeNode *search(int k) { return (root) ? root->search(k) : nullptr; }
    void insert(int k);  // Insert key in the B-tree
    void remove(int k);  // Remove key from the B-tree
};

BTreeNode::BTreeNode(int _t, bool _leaf) {
    t = _t;
    leaf = _leaf;
    keys = new int[2 * t - 1];
    C = new BTreeNode *[2 * t];
    n = 0;
}

void BTree::insert(int k) {
    if (!root) {
        root = new BTreeNode(t, true);
        root->keys[0] = k;
        root->n = 1;
    } else {
        if (root->n == 2 * t - 1) {
            BTreeNode *s = new BTreeNode(t, false);
            s->C[0] = root;
            s->splitChild(0, root);
            int i = (s->keys[0] < k) ? 1 : 0;
            s->C[i]->insertNonFull(k);
            root = s;
        } else {
            root->insertNonFull(k);
        }
    }
}

void BTreeNode::insertNonFull(int k) {
    int i = n - 1;
    if (leaf) {
        while (i >= 0 && keys[i] > k) {
            keys[i + 1] = keys[i];
            i--;
        }
        keys[i + 1] = k;
        n++;
    } else {
        while (i >= 0 && keys[i] > k) i--;
        if (C[i + 1]->n == 2 * t - 1) {
            splitChild(i + 1, C[i + 1]);
            if (keys[i + 1] < k) i++;
        }
        C[i + 1]->insertNonFull(k);
    }
}

void BTreeNode::splitChild(int i, BTreeNode *y) {
    BTreeNode *z = new BTreeNode(y->t, y->leaf);
    z->n = t - 1;
    for (int j = 0; j < t - 1; j++) z->keys[j] = y->keys[j + t];
    if (!y->leaf) {
        for (int j = 0; j < t; j++) z->C[j] = y->C[j + t];
    }
    y->n = t - 1;
    for (int j = n; j >= i + 1; j--) C[j + 1] = C[j];
    C[i + 1] = z;
    for (int j = n - 1; j >= i; j--) keys[j + 1] = keys[j];
    keys[i] = y->keys[t - 1];
    n++;
}

void BTreeNode::traverse() {
    for (int i = 0; i < n; i++) {
        if (!leaf) C[i]->traverse();
        cout << keys[i] << " ";
    }
    if (!leaf) C[n]->traverse();
}

void BTreeNode::levelOrder() {
    queue<BTreeNode *> q;
    q.push(this);

    while (!q.empty()) {
        int size = q.size();
        while (size--) {
            BTreeNode *node = q.front();
            q.pop();

            cout << "[";
            for (int i = 0; i < node->n; i++) {
                cout << node->keys[i];
                if (i < node->n - 1) cout << " ";
            }
            cout << "] ";

            if (!node->leaf) {
                for (int i = 0; i <= node->n; i++) q.push(node->C[i]);
            }
        }
        cout << endl;
    }
}

void BTree::remove(int k) {
    if (!root) {
        cout << "Tree is empty\n";
        return;
    }
    root->remove(k);
    if (root->n == 0) {
        BTreeNode *tmp = root;
        root = root->leaf ? nullptr : root->C[0];
        delete tmp;
    }
}

void BTreeNode::remove(int k) {
    int idx = 0;
    while (idx < n && keys[idx] < k) idx++;
    if (idx < n && keys[idx] == k) {
        if (leaf) removeFromLeaf(idx);
        else removeFromNonLeaf(idx);
    } else {
        if (leaf) {
            cout << "Key " << k << " not found\n";
            return;
        }
        bool flag = (idx == n);
        if (C[idx]->n < t) fill(idx);
        if (flag && idx > n) C[idx - 1]->remove(k);
        else C[idx]->remove(k);
    }
}

void BTreeNode::removeFromLeaf(int idx) {
    for (int i = idx + 1; i < n; i++) keys[i - 1] = keys[i];
    n--;
}

void BTreeNode::removeFromNonLeaf(int idx) {
    int k = keys[idx];
    if (C[idx]->n >= t) {
        int pred = getPred(idx);
        keys[idx] = pred;
        C[idx]->remove(pred);
    } else if (C[idx + 1]->n >= t) {
        int succ = getSucc(idx);
        keys[idx] = succ;
        C[idx + 1]->remove(succ);
    } else {
        merge(idx);
        C[idx]->remove(k);
    }
}

int BTreeNode::getPred(int idx) {
    BTreeNode *cur = C[idx];
    while (!cur->leaf) cur = cur->C[cur->n];
    return cur->keys[cur->n - 1];
}

int BTreeNode::getSucc(int idx) {
    BTreeNode *cur = C[idx + 1];
    while (!cur->leaf) cur = cur->C[0];
    return cur->keys[0];
}

void BTreeNode::fill(int idx) {
    if (idx != 0 && C[idx - 1]->n >= t) {
        borrowFromLeft(idx);
    } else if (idx != n && C[idx + 1]->n >= t) {
        borrowFromRight(idx);
    } else {
        if (idx != n) merge(idx);
        else merge(idx - 1);
    }
}

void BTreeNode::merge(int idx) {
    BTreeNode *child = C[idx];
    BTreeNode *sibling = C[idx + 1];

    child->keys[t - 1] = keys[idx];
    for (int i = 0; i < sibling->n; i++) child->keys[i + t] = sibling->keys[i];
    for (int i = 0; i <= sibling->n; i++) child->C[i + t] = sibling->C[i];

    child->n += sibling->n + 1;

    for (int i = idx + 1; i < n; i++) keys[i - 1] = keys[i];
    for (int i = idx + 2; i <= n; i++) C[i - 1] = C[i];

    n--;

    delete sibling;
}

void BTreeNode::borrowFromLeft(int idx) {
    BTreeNode *child = C[idx];
    BTreeNode *sibling = C[idx - 1];

    for (int i = child->n - 1; i >= 0; i--) child->keys[i + 1] = child->keys[i];
    if (!child->leaf) {
        for (int i = child->n; i >= 0; i--) child->C[i + 1] = child->C[i];
    }

    child->keys[0] = keys[idx - 1];

    if (!child->leaf) child->C[0] = sibling->C[sibling->n];

    keys[idx - 1] = sibling->keys[sibling->n - 1];
    child->n++;
    sibling->n--;
}

void BTreeNode::borrowFromRight(int idx) {
    BTreeNode *child = C[idx];
    BTreeNode *sibling = C[idx + 1];

    child->keys[child->n] = keys[idx];

    if (!child->leaf) child->C[child->n + 1] = sibling->C[0];

    keys[idx] = sibling->keys[0];

    for (int i = 1; i < sibling->n; i++) sibling->keys[i - 1] = sibling->keys[i];
    if (!sibling->leaf) {
        for (int i = 1; i <= sibling->n; i++) sibling->C[i - 1] = sibling->C[i];
    }

    child->n++;
    sibling->n--;
}

int main() {
    int m, choice, key;
    cout << "Enter order (m) of B-Tree: ";
    cin >> m;
    int t = (m + 1) / 2;
    
    BTree tree(t);
    cout << "\nMenu:\n1. Insert\n2. Delete\n3. Level Order Traversal\n4. Exit\n";
    while (true) {
        cout << "Enter choice: ";
        cin >> choice;
        if (choice == 1) {
            cout << "Enter key to insert: ";
            cin >> key;
            tree.insert(key);
        } else if (choice == 2) {
            cout << "Enter key to delete: ";
            cin >> key;
            tree.remove(key);
        } else if (choice == 3) {
            cout << "Level Order Traversal:\n";
            tree.levelOrder();
        } else break;
    }
}

