#include <iostream>
using namespace std;

class DynamicTable {
private:
    int* table;       
    int capacity;     
    int size;         

public:
  
    DynamicTable(int initialCapacity) {
        capacity = initialCapacity;
        size = 0;
        table = new int[capacity];
    }

    
    void insert(int value) {
        int cost = 1;
        if (size == capacity) {
            resize();
            cost = capacity * 2;
        }
        table[size] = value;
        size++;
        cout << "Inserted Value: " << value
             << ", Cost: " << cost
             << ", Capacity: " << capacity << endl;
    }

    
    void display() {
        cout << "Dynamic Table: ";
        for (int i = 0; i < size; i++) {
            cout << table[i] << " ";
        }
        cout << "\nSize: " << size << ", Capacity: " << capacity << endl;
    }

private:
 
    void resize() {
        int newCapacity = capacity * 2;
        int* newTable = new int[newCapacity];
        for (int i = 0; i < size; i++) {
            newTable[i] = table[i];
        }
        delete[] table;
        table = newTable;
        capacity = newCapacity;
        cout << "Resized Table to Capacity: " << capacity << endl;
    }

public:
 
    ~DynamicTable() {
        delete[] table;
    }
};

int main() {
    DynamicTable dt(2);

    int choice;
    do {
        cout << "\n--- Dynamic Table Menu ---\n";
        cout << "1. Insert a value\n";
        cout << "2. Display table\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                int value;
                cout << "Enter a value to insert: ";
                cin >> value;
                dt.insert(value);
                break;
            }
            case 2: {
                dt.display();
                break;
            }
            case 3: {
                cout << "Exiting the program." << endl;
                break;
            }
            default:
                cout << "Invalid choice! Please try again." << endl;
        }
    } while (choice != 3);

    return 0;
}
