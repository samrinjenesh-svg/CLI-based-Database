#include <iostream>
#include <string>
#include <vector>
using namespace std;

int no_of_records = 0;

class record {
    public:
    int id;
    string name;
    int age;
};

vector<record> table;

int searchExistingIDs(int i, int k) {
    for (int j = 0; j < k; j++) {
        if (j != i && table[j].id == i) {
            return 1;
        }
    }
    return 0;
}

void addRecord() {
    table.push_back(record());
    iddupe:
    cout << "Enter id: ";
    cin >> table[no_of_records].id;
    if (searchExistingIDs(table[no_of_records].id, no_of_records)) {
        cout << "ID already exists" << endl;
        goto iddupe;
    }
    cout << "Enter name: ";
    cin >> table[no_of_records].name;
    cout << "Enter age: ";
    cin >> table[no_of_records].age;
    no_of_records++;
}

int searchRecord() {
    int i, n, f = 0;
    cout << "Enter ID no." << endl;
    cin >> i;
    for (int j = 0; j < no_of_records; j++) {
        if (table[j].id == i) {
            n = j;
            f++;
        }
    }
    if (f == 0) {
        return -1;
    }
    else {
        return n;
    }
}

void intializeRecords() {
    reenter:
    cout << "Enter number of record: ";
    cin >> no_of_records;
    for (int i = 0; i < no_of_records; i++) {
        table.push_back(record());
        iddupe:
        cout << "Enter id: ";
        cin >> table[i].id;
        if (searchExistingIDs(table[i].id, i)) {
            cout << "ID already exists" << endl;
            goto iddupe;
        }
        cout << "Enter name: ";
        cin >> table[i].name;
        cout << "Enter age: ";
        cin >> table[i].age;
    }
    if (no_of_records == 0) {
        goto reenter;
    }
}

void modifyRecord() {
    int i, n, t;
    string tname;
    i = searchRecord();
    if (i == -1) {
        cout << "No records found" << endl;
        return;
    }
    cout << "What do you want to modify: " << endl;
    cout << "Enter one for name";
    cout << "Enter two for age";
    cout << "Enter three for id";
    cin >> n;
    if (n == 1) {
        cout << "Enter new name: " << endl;
        cin >> tname;
        table[i].name = tname;
    }
    else if (n == 2) {
        cout << "Enter new age: " << endl;
        cin >> t;
        table[i].age = t;
    }
    else if (n == 3) {
        iddupe:
        cout << "Enter new id: " << endl;
        cin >> t;
        if (searchExistingIDs(t, no_of_records)) {
            cout << "ID already exists" << endl;
            goto iddupe;
        }
        table[i].id = t;
    }
    else {
        cout << "Invalid input" << endl;
    }
}

void deleteRecord() {
    int i;
    i = searchRecord();
    if (i == -1) {
        cout << "No records found" << endl;
    }
    else {
        table.erase(table.begin() + i);
        no_of_records--;
    }
}

int main() {
    intializeRecords();
    start:
    cout << "Press one for adding records" << endl;
    cout << "Press two for searching records" << endl;
    cout << "Press three for deleting records" << endl;
    cout << "Press four for modifying records" << endl;
    cout << "Press five for exit" << endl;
    int x = 0;
    cin >> x;
    switch (x) {
        case 1:
            addRecord();
            break;
        case 2: {
            int v = searchRecord();
            if (v == -1) {
                cout << "No records found" << endl;
            }
            else {
                cout << "Name: " << table[v].name << endl;
                cout << "Age: " << table[v].age << endl;
                cout << "ID: " << table[v].id << endl;
            }
            break;
        }
        case 3:
            deleteRecord();
            break;
        case 4:
            modifyRecord();
            break;
        case 5:
            return 1;
        default:
            cout << "Invalid input" << endl;
            goto start;
    }
    if (x == 0) {
        return 1;
    }
    else {
        goto start;
    }
}