#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
using namespace std;

static int no_of_records = 0;

static const char *tabledata = "Data.txt";

namespace {
    class record {
        int id = 0;
        string name;
        int age = 0;
    public:

        void setID() {
            cin >> this->id;
        }

        void setID(const int i) {
            this->id = i;
        }

        void setName(const std::string &n) {
            name = n;
        }

        void setAge(const int a) {
            age = a;
        }

        void setName() {
            cin >> this->name;
        }

        void setAge() {
            cin >> this->age;
        }

        [[nodiscard]] int getID() const{
            return id;
        }

        [[nodiscard]] string getName()const {
            return name;
        }

        [[nodiscard]] int getAge() const{
            return age;
        }

    };
}

static vector<record> table;

static bool saveRecords(const string &filename);

static bool loadRecords(const string &filename);

static void sorttable() {
    sort(table.begin(), table.end(), [](const record &r1, const record &r2) {
        return r1.getID() < r2.getID();
    });
}

static int searchExistingIDs(int i, int k) {
    for (int j = 0; j < k; j++) {
        if (j != i && table[j].getID() == i) {
            return 1;
        }
    }
    return 0;
}

static void addRecord() {
    table.emplace_back();
    iddupe:
    cout << "Enter id: ";
    table[no_of_records].setID();
    if (searchExistingIDs(table[no_of_records].getID(), no_of_records)) {
        cout << "ID already exists" << endl;
        goto iddupe;
    }
    cout << "Enter name: ";
    table[no_of_records].setName();
    cout << "Enter age: ";
    table[no_of_records].setAge();
    no_of_records++;
    sorttable();
}

static void searchRecord(int i) {
    if (i == 1) {
        int k, f = 0;
        cout << "Enter ID no." << endl;
        cin >> k;
        for (int j = 0; j < no_of_records; j++) {
            if (table[j].getID() == k) {
                cout << "ID : " << table[j].getID() << endl;
                cout << "Name : " << table[j].getName() << endl;
                cout << "Age : " << table[j].getAge() << endl;
                cout << endl;
                f++;
                break;
            }
        }
        if (f == 0) {
            cout << "No records found" << endl;
        }
    }
    else if (i == 2) {
        int f = 0;
        string ns, found;
        cout << "Enter name: ";
        cin >> ns;
        for (int j = 0; j < no_of_records; j++) {
            if (table[j].getName() == ns) {
                f++;
                cout << "ID : " << table[j].getID() << endl;
                cout << "Name : " << table[j].getName() << endl;
                cout << "Age : " << table[j].getAge() << endl;
                cout << endl;
            }
        }
        if (f == 0) {
            cout << "No records found" << endl;
        }
    }
    else if (i == 3) {
        int f = 0, a;
        cout << "Enter name: ";
        cin >> a;
        for (int j = 0; j < no_of_records; j++) {
            if (table[j].getAge() == a) {
                f++;
                cout << "ID : " << table[j].getID() << endl;
                cout << "Name : " << table[j].getName() << endl;
                cout << "Age : " << table[j].getAge() << endl;
                cout << endl;
            }
        }
    }
    else {
        cout << "Invalid input" << endl;
        cout << endl;
    }
}

static int searchRecord() {
    int i;
    cout << "Enter ID no." << endl;
    cin >> i;
    for (int j = 0; j < no_of_records; j++) {
        if (table[j].getID() == i) {
            return j;
        }
    }
    return -1;
}

static void initializeRecords() {
    if (loadRecords(tabledata) && no_of_records > 0) {
        cout << "Loaded " << no_of_records << " records from " << tabledata << endl;
        return;
    }
    reenter:
    cout << "Enter number of record: ";
    cin >> no_of_records;
    for (int i = 0; i < no_of_records; i++) {
        table.emplace_back();
        iddupe:
        cout << "Enter id: ";
        table[i].setID();
        if (searchExistingIDs(table[i].getID(), i)) {
            cout << "ID already exists" << endl;
            goto iddupe;
        }
        cout << "Enter name: ";
        table[i].setName();
        cout << "Enter age: ";
        table[i].setAge();
    }
    if (no_of_records == 0) {
        goto reenter;
    }
    sorttable();
}

static void modifyRecord() {
    int n, i = searchRecord();
    if (i == -1) {
        cout << "No records found" << endl;
        return;
    }
    cout << "What do you want to modify: " << endl;
    cout << "Enter one for name" << endl;
    cout << "Enter two for age" << endl;
    cout << "Enter three for id" << endl;
    cout  << endl;
    cin >> n;
    if (n == 1) {
        cout << "Enter new name: " << endl;
        table[i].setName();
    }
    else if (n == 2) {
        cout << "Enter new age: " << endl;
        table[i].setAge();
    }
    else if (n == 3) {
        iddupe:
        cout << "Enter new id: " << endl;
        table[i].setID();
        if (searchExistingIDs(table[i].getID(), no_of_records)) {
            cout << "ID already exists" << endl;
            goto iddupe;
        }
    }
    else {
        cout << "Invalid input" << endl;
    }
    sorttable();
}

static void deleteRecord() {
    int i = searchRecord();
    if (i == -1) {
        cout << "No records found" << endl;
    }
    else {
        table.erase(table.begin() + i);
        no_of_records--;
    }
    sorttable();
}

static void showAllRecords() {
    if (no_of_records == 0) {
        cout << "No records found" << endl;
        return;
    }
    for (int i = 0; i < no_of_records; i++) {
        cout << "ID: " << table[i].getID() << endl;
        cout << "Name: " << table[i].getName() << endl;
        cout << "Age: " << table[i].getAge() << endl;
        cout << endl;
    }
}

static bool saveRecords(const string &filename) {
    ofstream out(filename);
    if (!out) {
        return false;
    }
    for (const auto &record : table) {
        out << record.getID() << ' ' << record.getName() << ' ' << record.getAge() << '\n';
    }
    return static_cast<bool>(out);
}

static bool loadRecords(const string &filename) {
    ifstream in(filename);
    if (!in) {
        return false;
    }
    vector<record> loaded;
    int id, age;
    string name;
    while (in >> id >> name >> age) {
        record r;
        r.setID(id);
        r.setName(name);
        r.setAge(age);
        loaded.push_back(r);
    }
    if (!in.eof()) {
        return false;
    }
    table = loaded;
    no_of_records = static_cast<int>(loaded.size());
    sorttable();
    return true;
}

static bool deleteFile() {
    table.clear();
    no_of_records = 0;
    cout << "All records deleted" << endl;
    return true;
}

int main() {
    initializeRecords();
    start:
    cout << "Press 1 for adding records" << endl;
    cout << "Press 2 for searching records" << endl;
    cout << "Press 3 for deleting records" << endl;
    cout << "Press 4 for modifying records" << endl;
    cout << "Press 5 to show all records" << endl;
    cout << "Press 6 to save records" << endl;
    cout << "Press 7 to delete file" << endl;
    cout << "Press 8 for exit" << endl;
    int x = 0;
    cin >> x;
    switch (x) {
        case 1:
            addRecord();
            break;
        case 2: {
            int y;
            cout << "Enter one to search by ID" << endl;
            cout << "Enter two to search by Name" << endl;
            cout << "Enter three to search by Age" << endl;
            cin >> y;
            searchRecord(y);
            break;
        }
        case 3:
            deleteRecord();
            break;
        case 4:
            modifyRecord();
            break;
        case 5:
            showAllRecords();
            break;
        case 6:
            saveRecords(tabledata);
            break;
        case 7:
            deleteFile();
            break;
        case 8:
            return 1;
        default:
            cout << "Invalid input" << endl;
            goto start;
    }
    saveRecords(tabledata);
    goto start;
}
