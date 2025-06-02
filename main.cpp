#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <set>
#include <limits>
using namespace std;

struct Violation {
    string date;
    string time;
    string location;
    string type;
    string plate;
    Violation* next;
};

Violation* head = nullptr;

void printDistinctValues(int option) {
    if (!head) {
        cout << "No violations recorded.\n";
        return;
    }

    set<string> distinctValues; //create an empty string
    Violation* current = head;
    do {
        switch(option) {
            case 1: distinctValues.insert(current->date); break;
            case 2: distinctValues.insert(current->time); break;
            case 3: distinctValues.insert(current->location); break;
            case 4: distinctValues.insert(current->type); break;
        }
        current = current->next;
    } while (current != head);

    cout << "\nAvailable values:\n"; 
    int count = 1;
    for (const auto& val : distinctValues) { 
        cout << count++ << ". " << val << "\n"; //basically this functions prints all the values of a certain type or category depending on the option
    }
}

string getCategoryName(int option) {
    switch(option) {
        case 1: return "date(s)";
        case 2: return "time(s)";
        case 3: return "location(s)";
        case 4: return "type(s)";
        default: return "category"; //for the search log function
    }
}
bool isValidDate(const string& date) {
    if (date.length() != 10) return false; // Expect MM/DD/YYYY exactly

    
    if (date[2] != '/' || date[5] != '/') return false; //checks where the slashes are

    for (int i = 0; i < 10; ++i) {
        if (i == 2 || i == 5) continue;
        if (!isdigit(date[i])) return false; // Check digits in all other positions
    }

    int month = stoi(date.substr(0, 2));
    int day = stoi(date.substr(3, 2));
    int year = stoi(date.substr(6, 4));

    if (year < 1900) return false;
    if (month < 1 || month > 12) return false;

    
    int daysInMonth[] = { 31,28,31,30,31,30,31,31,30,31,30,31 }; //days per month

    bool isLeap = (year % 400 == 0) || (year % 4 == 0 && year % 100 != 0); //lear years
    if (isLeap && month == 2) daysInMonth[1] = 29;

    if (day < 1 || day > daysInMonth[month - 1]) return false;

    return true;
}

bool isValidTime(const string& time) {
    if (time.length() != 5 || time[2] != ':') return false; //must have 5 characters, 01:02 including colon

    string hours = time.substr(0, 2); //starts at index 0 then takes 2 characters to store it to hh
    string mins = time.substr(3, 2); //starts at index 3 then takes 2 characters to store it to mm

    if (!isdigit(hours[0]) || !isdigit(hours[1]) ||
        !isdigit(mins[0]) || !isdigit(mins[1])) 
        return false; //checks if the string is a digit and if yes, then turn to int

    int hour = stoi(hours);
    int minute = stoi(mins);

    if (hour < 0 || hour > 23) return false;
    if (minute < 0 || minute > 59) return false;

    return true;
}

bool isEmptyOrWhitespace(const string& str) {
    for (char c : str) {
        if (!isspace(c)) return false; //well checks if whitespace what elese
    }
    return true;
}

bool isValidPHPlate(const string& plate) {
    string cleaned;
    for (char c : plate) {
        if (c != '-' && c != ' ') cleaned.push_back(c); //this more or less removes the hyphens or spaces essentially cleaning it
    }

    int len = cleaned.length();
    if (len < 5 || len > 7) return false; //the cleaned string must be between 5 - 7 based on 2014 phil license plate numbers

    int letterCount = 0;
    for (char c : cleaned) {
        if (isalpha(c)) letterCount++; //counts the letters what else
        else break;
    }
    if (letterCount < 1 || letterCount > 3) return false; //2014 phil license plates have 1-3 letters
    
    for (int i = letterCount; i < len; i++) {
        if (!isdigit(cleaned[i])) return false; //the next characters must be digits
    }
    return true;
}

bool isDuplicateViolation(const string& plate, const string& date, const string& time) {
    if (!head) return false;

    Violation* current = head;
    do {
        if (current->plate == plate && current->date == date && current->time == time) {
            return true; // duplicate found
        }
        current = current->next;
    } while (current != head);

    return false; //no duplicate found
}

void displayViolation(Violation* v) {
    cout << "Plate: " << v->plate
         << ", Date: " << v->date
         << ", Time: " << v->time
         << ", Location: " << v->location
         << ", Type: " << v->type << endl;
}

void displayAllViolations() {
    if (!head) {
        cout << "No violations recorded.\n";
        return;
    }

    Violation* current = head;
    cout << "\n--- All Logged Violations ---\n";
    do {
        displayViolation(current);
        current = current->next;
    } while (current != head);
}

void logViolation() {
    string plate, date, time, location, type;
    int fieldIndex = 0;
    bool canceled = false;
    bool confirmed = false;

    while (!confirmed && !canceled) {
        switch (fieldIndex) {
            case 0: {
                cout << "Type 'BACK' to go to the previous or 'CANCEL' to return to the menu" << endl;
                cout << "Enter Plate number (LLL-DDDD or LLL DDDD), 3 letters and 4 digits [current: " << plate << "]: ";
                string input; getline(cin, input);
                for (auto & c : input) c = tolower(c);  // convert to lowercase inline
                if (input == "cancel") { canceled = true; break; }
                else if (input == "back") { cout << "Already at the first field. Cannot go back further.\n"; break; }
                else if (!input.empty()) plate = input;
                
                for (int i = 0; i < 3 && i < (int)plate.length(); ++i)
                    plate[i] = toupper(plate[i]); // we uppercase it automatically
                if (!isValidPHPlate(plate)) {
                    cout << "Invalid Philippine plate format. Try again.\n";
                    break;
                }
                fieldIndex++;
                break;
            }
            case 1: {
                cout << "Enter Date (MM/DD/YYYY) [current: " << date << "]: ";
                string input; getline(cin, input);
                for (auto & c : input) c = tolower(c);
                if (input == "cancel") { canceled = true; break; }
                else if (input == "back") { fieldIndex--; break; }
                else if (!input.empty()) date = input;
                if (!isValidDate(date)) {
                    cout << "Invalid date format. Try again.\n";
                    break;
                }
                fieldIndex++;
                break;
            }
            case 2: {
                cout << "Enter Time (HH:MM, 24-hour) [current: " << time << "]: ";
                string input; getline(cin, input);
                for (auto & c : input) c = tolower(c);
                if (input == "cancel") { canceled = true; break; }
                else if (input == "back") { fieldIndex--; break; }
                else if (!input.empty()) time = input;
                if (!isValidTime(time)) {
                    cout << "Invalid time format. Try again.\n";
                    break;
                }
                fieldIndex++;
                break;
            }
            case 3: {
                cout << "Enter Location [current: " << location << "]: ";
                string input; getline(cin, input);
                for (auto & c : input) c = tolower(c);
                if (input == "cancel") { canceled = true; break; }
                else if (input == "back") { fieldIndex--; break; }
                else if (!input.empty()) location = input;
                if (isEmptyOrWhitespace(location)) {
                    cout << "Location cannot be empty. Try again.\n";
                    break;
                }
                fieldIndex++;
                break;
            }
            case 4: {
                cout << "Enter Type [current: " << type << "]: ";
                string input; getline(cin, input);
                for (auto & c : input) c = tolower(c);
                if (input == "cancel") { canceled = true; break; }
                else if (input == "back") { fieldIndex--; break; }
                else if (!input.empty()) type = input;
                if (isEmptyOrWhitespace(type)) {
                    cout << "Type cannot be empty. Try again.\n";
                    break;
                }
                fieldIndex++;
                break;
            }
            case 5: { // review all data i guess
                cout << "\nPlease review the violation details:\n";
                cout << "Plate: " << plate << "\nDate: " << date << "\nTime: " << time 
                     << "\nLocation: " << location << "\nType: " << type << "\n";
                cout << "Type 'back' to edit, 'cancel' to abort, or press ENTER to confirm: ";
                string input; getline(cin, input);
                for (auto & c : input) c = tolower(c);
                if (input == "back") {if (input == "back") {
                    cout << "Enter field number to edit (0: Plate, 1: Date, 2: Time, 3: Location, 4: Type): ";
                    string fieldInput; getline(cin, fieldInput);
                    int f = stoi(fieldInput);
                    if (f >= 0 && f <= 4) fieldIndex = f;
                    else {
                        cout << "Invalid field number. Returning to review.\n";
                        fieldIndex = 5;
                    }
                }} // or choose to jump to specific field if you want
                else if (input == "cancel") { canceled = true; }
                else confirmed = true;
                break;
            }
        }
    }

    if (canceled) {
        cout << "Logging cancelled.\n";
        return;
    }

    if (confirmed) {
        if (isDuplicateViolation(plate, date, time)) {
            cout << "Duplicate violation found. Not saved.\n"; 
            return;
        }
        Violation* newViolation = new Violation{date, time, location, type, plate, nullptr};

        if (!head) {
            head = newViolation;
            head->next = head;
        } else {
            Violation* temp = head;
            while (temp->next != head) temp = temp->next;
            temp->next = newViolation;
            newViolation->next = head;
        }
        cout << "Violation saved successfully.\n";
    }
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
//need to add this on the file manip part 
void filterPlate(const string& targetPlate){
    if(!head){
        return;
    }
    Violation *current = head;
    do {
        if (current->plate == targetPlate) displayViolation(current);
        current = current->next;
    } while (current != head);

}

void searchViolation() {
    while (true) {
        cout << "\nSearch Violations By:\n"
             << "1. Date\n"
             << "2. Time\n"
             << "3. Location\n"
             << "4. Type\n"
             << "Type 'back' to return to main menu.\n"
             << "Enter option number: ";
        
        string input;
        cin >> input;
        if (input == "back") return;

        int option;
        try {
            option = stoi(input); //converts string to integer
        } catch (...) {
            cout << "Invalid input. Please enter a number from 1 to 4 or 'back'.\n";
            continue;
        }
        if (option < 1 || option > 4) {
            cout << "Invalid option. Please enter a number from 1 to 4 or 'back'.\n";
            continue;
        }

        string categoryName = getCategoryName(option); //gets the type of category
        
        cout << "Do you want to print all " << categoryName << "? (y/n): ";
        char printChoice;
        cin >> printChoice;
        if (printChoice == 'y' || printChoice == 'Y') {
            printDistinctValues(option);
        }

        cout << "Enter search keyword (or 'back' to cancel): ";
        string keyword;
        getline(cin >> ws, keyword);
        if (keyword == "back") return;

        if (!head) {
            cout << "No violations recorded.\n";
            return;
        }

        Violation* current = head;
        bool found = false;
        do {
            bool match = false;
            switch(option) {
                case 1: match = (current->date == keyword); break;
                case 2: match = (current->time == keyword); break;
                case 3: match = (current->location == keyword); break;
                case 4: match = (current->type == keyword); break;
            }
            if (match) {
                displayViolation(current);
                found = true;
            }
            current = current->next;
        } while (current != head);

        if (!found) {
            cout << "No violations found for '" << keyword << "'.\n";
        }

        cout << "Search again? (y/n): ";
        char again;
        cin >> again;
        if (again != 'y' && again != 'Y') break;
    }
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
    string keyword, type, location, startDate, endDate, filename, plate;

    do {
        cout << "\n--- TrafficEye Main Menu ---\n";
        cout << "1. Log Violation\n2. Search Violations\n3. Filter by Type\n";
        cout << "4. Filter by Location\n5. Filter by Plate Number\n6. Filter by Date Range\n";
        cout << "7. Summary Report\n8. Save to File\n9. Load from File\n10. Exit\nChoice: ";
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        switch (choice) {
            case 1: logViolation(); break;
            case 2: cout << "Enter keyword: "; getline(cin >> ws, keyword); searchViolation(); break;
            case 3: cout << "Enter type: "; getline(cin >> ws, type); filterViolationsByType(type); break;
            case 4: cout << "Enter location: "; getline(cin >> ws, location); filterViolationsByLocation(location); break;
            case 5: cout << "Enter platenumber: "; getline(cin >> ws, plate); filterPlate(plate);break;
            case 6:
                cout << "Enter start date: "; cin >> startDate;
                cout << "Enter end date: "; cin >> endDate;
                filterViolationsByDateRange(startDate, endDate);
                break;
            case 7: summaryReport(); break;
            case 8: cout << "Enter filename: "; cin >> filename; saveToFile(filename); break;
            case 9: cout << "Enter filename: "; cin >> filename; loadFromFile(filename); break;
        }
    } while (choice != 10);

    cout << "Exiting TrafficEye. Goodbye!\n";
}

int main() {
    mainMenu();
    return 0;
}
