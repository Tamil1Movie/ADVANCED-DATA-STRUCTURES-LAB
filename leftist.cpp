#include <iostream>
#include <queue>
#include <vector>
using namespace std;

priority_queue<int, vector<int>, greater<int>> minHeap1, minHeap2, mergedHeap;

void insert(priority_queue<int, vector<int>, greater<int>>& heap, int value) {
    heap.push(value);
}

void deleteMin(priority_queue<int, vector<int>, greater<int>>& heap) {
    if (!heap.empty()) {
        cout << "Deleted minimum element: " << heap.top() << endl;
        heap.pop();
    } else {
        cout << "Heap is empty!" << endl;
    }
}
void mergeHeaps(priority_queue<int, vector<int>, greater<int>>& heap1, priority_queue<int, vector<int>, greater<int>>& heap2) {
    mergedHeap = heap1;  
    while (!heap2.empty()) {
        mergedHeap.push(heap2.top());
        heap2.pop();
    }
    cout << "Heaps merged successfully." << endl;
}
void printHeapLevelOrder(priority_queue<int, vector<int>, greater<int>> heap, const string& heapName) {
    if (heap.empty()) {
        cout << heapName << " is empty!" << endl;
        return;
    }
    vector<int> heapArray;
    while (!heap.empty()) {
        heapArray.push_back(heap.top());
        heap.pop();
    }
    cout << heapName << " Level Order: ";
    int levelSize = 1, index = 0;
    while (index < heapArray.size()) {
        cout << "[ ";
        for (int i = 0; i < levelSize && index < heapArray.size(); i++) {
            cout << heapArray[index++] << " ";
        }
        cout << "] ";
        levelSize *= 2; 
    }
    cout << endl;
}

int main() {
    int choice, value;
    cout << "\nMenu:\n";
        cout << "1. Insert into Heap 1\n";
        cout << "2. Insert into Heap 2\n";
        cout << "3. Delete minimum from Heap 1\n";
        cout << "4. Merge Heap 1 and Heap 2\n";
        cout << "5. Print Heap 1 (Level Order)\n";
        cout << "6. Print Heap 2 (Level Order)\n";
        cout << "7. Print Merged Heap (Level Order)\n";
        cout << "8. Exit\n";

    while (true) {
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter value to insert into Heap 1: ";
                cin >> value;
                insert(minHeap1, value);
                break;
            case 2:
                cout << "Enter value to insert into Heap 2: ";
                cin >> value;
                insert(minHeap2, value);
                break;
            case 3:
                deleteMin(minHeap1);
                break;
            case 4:
                mergeHeaps(minHeap1, minHeap2);
                break;
            case 5:
                printHeapLevelOrder(minHeap1, "Heap 1");
                break;
            case 6:
                printHeapLevelOrder(minHeap2, "Heap 2");
                break;
            case 7:
                printHeapLevelOrder(mergedHeap, "Merged Heap");
                break;
            case 8:
                return 0;
            default:
                cout << "Invalid choice! Try again." << endl;
        }
    }
}

