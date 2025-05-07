#include <iostream>
#include <string>
#include <fstream>
#include <map>
using namespace std;

struct Violation {
    string date;
    string time;
    string location;
    string type;
    Violation* next;
};

Violation* head = nullptr;

void displayViolation(Violation* v) {
    cout << "Date: " << v->date << ", Time: " << v->time
         << ", Location: " << v->location << ", Type: " << v->type << endl;
}

void logViolation() {
    Violation* newViolation = new Violation;
    cout << "Enter Date: "; cin >> newViolation->date;
    cout << "Enter Time: "; cin >> newViolation->time;
    cout << "Enter Location: "; cin >> newViolation->location;
    cout << "Enter Type: "; getline(cin >> ws, newViolation->type);

    if (!head) {
        head = newViolation;
        head->next = head; // circular?? idk bruh i think singly rani
    } else {
        Violation* temp = head;
        while (temp->next != head) temp = temp->next;
        temp->next = newViolation;
        newViolation->next = head;
    }

    cout << "Violation logged successfully.\n";
}

void filterViolationsByType(const string& targetType) {
    if (!head) return;
    Violation* current = head;
    do {
        if (current->type == targetType) displayViolation(current);
        current = current->next;
    } while (current != head);
}

void filterViolationsByLocation(const string& targetLocation) {
    if (!head) return;
    Violation* current = head;
    do {
        if (current->location == targetLocation) displayViolation(current);
        current = current->next;
    } while (current != head);
}

void filterViolationsByDateRange(const string& startDate, const string& endDate) {
    if (!head) return;
    Violation* current = head;
    do {
        if (current->date >= startDate && current->date <= endDate)
            displayViolation(current);
        current = current->next;
    } while (current != head);
}

void searchViolation(const string& keyword) {
    if (!head) return;
    Violation* current = head;
    do {
        if (current->date == keyword || current->time == keyword ||
            current->location == keyword || current->type == keyword)
            displayViolation(current);
        current = current->next;
    } while (current != head);
}

void summaryReport() {
    map<string, int> typeCount, locationCount;
    if (!head) return;

    Violation* current = head;
    do {
        typeCount[current->type]++;
        locationCount[current->location]++;
        current = current->next;
    } while (current != head);

    cout << "\nTotal Violations by Type:\n";
    for (auto& pair : typeCount)
        cout << pair.first << ": " << pair.second << endl;

    cout << "\nViolations by Location:\n";
    for (auto& pair : locationCount)
        cout << pair.first << ": " << pair.second << endl;
}

void saveToFile(const string& filename) {
    ofstream fout(filename);
    if (!fout) {
        cout << "Error opening file.\n";
        return;
    }

    Violation* current = head;
    if (!head) return;

    do {
        fout << current->date << "," << current->time << ","
             << current->location << "," << current->type << endl;
        current = current->next;
    } while (current != head);

    fout.close();
    cout << "Data saved successfully.\n";
}

// Load from file
void loadFromFile(const string& filename) {
    ifstream fin(filename);
    if (!fin) {
        cout << "File not found.\n";
        return;
    }

    string date, time, location, type;
    while (getline(fin, date, ',') &&
           getline(fin, time, ',') &&
           getline(fin, location, ',') &&
           getline(fin, type)) {
        Violation* newViolation = new Violation{date, time, location, type, nullptr};
        if (!head) {
            head = newViolation;
            head->next = head;
        } else {
            Violation* temp = head;
            while (temp->next != head) temp = temp->next;
            temp->next = newViolation;
            newViolation->next = head;
        }
    }

    fin.close();
    cout << "Data loaded successfully.\n";
}

// Main Menu
void mainMenu() {
    int choice;
    string keyword, type, location, startDate, endDate, filename;

    do {
        cout << "\n--- TrafficEye Main Menu ---\n";
        cout << "1. Log Violation\n2. Search Violations\n3. Filter by Type\n";
        cout << "4. Filter by Location\n5. Filter by Date Range\n6. Summary Report\n";
        cout << "7. Save to File\n8. Load from File\n9. Exit\nChoice: ";
        cin >> choice;

        switch (choice) {
            case 1: logViolation(); break;
            case 2: cout << "Enter keyword: "; getline(cin >> ws, keyword); searchViolation(keyword); break;
            case 3: cout << "Enter type: "; getline(cin >> ws, type); filterViolationsByType(type); break;
            case 4: cout << "Enter location: "; getline(cin >> ws, location); filterViolationsByLocation(location); break;
            case 5:
                cout << "Enter start date: "; cin >> startDate;
                cout << "Enter end date: "; cin >> endDate;
                filterViolationsByDateRange(startDate, endDate);
                break;
            case 6: summaryReport(); break;
            case 7: cout << "Enter filename: "; cin >> filename; saveToFile(filename); break;
            case 8: cout << "Enter filename: "; cin >> filename; loadFromFile(filename); break;
        }
    } while (choice != 9);

    cout << "Exiting TrafficEye. Goodbye!\n";
}

int main() {
    mainMenu();
    return 0;
}
