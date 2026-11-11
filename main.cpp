// Contact Book / Phone Directory - OOP mini project in C++
// Features: add, delete, search, sorted display, save/load, export to HTML

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>
using namespace std;

// Converts a string to lowercase (so "Riya" and "riya" are treated the same)
string toLower(string s) {
    for (char &c : s) {
        c = tolower(c);
    }
    return s;
}

// ---------------------------------------------------------
// Class 1: Contact - stores one person's name and phone
// ---------------------------------------------------------
class Contact {
private:
    string name;
    string phone;

public:
    Contact(const string &n, const string &p) {
        name = n;
        phone = p;
    }

    string getName() const { return name; }
    string getPhone() const { return phone; }

    // Used by sort() to arrange contacts alphabetically by name
    bool operator<(const Contact &other) const {
        return toLower(name) < toLower(other.name);
    }
};

// ---------------------------------------------------------
// Class 2: ContactBook - manages all contacts
// ---------------------------------------------------------
class ContactBook {
private:
    vector<Contact> contacts;
    string fileName = "contacts.txt";

    // Returns position of a contact with this exact name, or -1 if not found
    int findIndex(const string &name) const {
        for (int i = 0; i < (int)contacts.size(); i++) {
            if (toLower(contacts[i].getName()) == toLower(name)) {
                return i;
            }
        }
        return -1;
    }

    // Saves all contacts to contacts.txt (one per line: name|phone)
    void saveToFile() const {
        ofstream file(fileName);
        for (const Contact &c : contacts) {
            file << c.getName() << "|" << c.getPhone() << "\n";
        }
    }

    // Loads contacts from contacts.txt when the program starts
    void loadFromFile() {
        ifstream file(fileName);
        string line;
        while (getline(file, line)) {
            size_t pos = line.find('|');
            if (pos != string::npos) {
                string n = line.substr(0, pos);
                string p = line.substr(pos + 1);
                contacts.push_back(Contact(n, p));
            }
        }
    }

public:
    ContactBook() {
        loadFromFile();
    }

    // 1. Add a contact (no duplicate names allowed)
    void addContact(const string &name, const string &phone) {
        if (findIndex(name) != -1) {
            cout << "A contact with this name already exists!\n";
            return;
        }
        contacts.push_back(Contact(name, phone));
        saveToFile();
        cout << "Contact added successfully.\n";
    }

    // 2. Delete a contact by name
    void deleteContact(const string &name) {
        int index = findIndex(name);
        if (index == -1) {
            cout << "Contact not found.\n";
            return;
        }
        contacts.erase(contacts.begin() + index);
        saveToFile();
        cout << "Contact deleted.\n";
    }

    // 3. Search contacts (matches any part of the name)
    void searchContact(const string &keyword) const {
        bool found = false;
        for (const Contact &c : contacts) {
            if (toLower(c.getName()).find(toLower(keyword)) != string::npos) {
                cout << left << setw(25) << c.getName() << c.getPhone() << "\n";
                found = true;
            }
        }
        if (!found) {
            cout << "No contact found.\n";
        }
    }

    // 4. Display all contacts in alphabetical order
    void displayContacts() {
        if (contacts.empty()) {
            cout << "Phone directory is empty.\n";
            return;
        }
        sort(contacts.begin(), contacts.end());   // uses operator< of Contact

        cout << left << setw(5) << "No." << setw(25) << "Name" << "Phone\n";
        cout << "-----------------------------------------\n";
        for (int i = 0; i < (int)contacts.size(); i++) {
            cout << left << setw(5) << i + 1
                 << setw(25) << contacts[i].getName()
                 << contacts[i].getPhone() << "\n";
        }
    }

    // 5. Export all contacts to a styled HTML page
    void exportToHTML() {
        sort(contacts.begin(), contacts.end());

        ofstream file("contacts.html");
        file << "<!DOCTYPE html>\n<html>\n<head>\n";
        file << "  <meta charset=\"UTF-8\">\n";
        file << "  <title>Phone Directory</title>\n";
        file << "  <link rel=\"stylesheet\" href=\"style.css\">\n";
        file << "</head>\n<body>\n";
        file << "  <h1>Phone Directory</h1>\n";
        file << "  <table>\n";
        file << "    <tr><th>No.</th><th>Name</th><th>Phone</th></tr>\n";
        for (int i = 0; i < (int)contacts.size(); i++) {
            file << "    <tr><td>" << i + 1 << "</td><td>" << contacts[i].getName()
                 << "</td><td>" << contacts[i].getPhone() << "</td></tr>\n";
        }
        file << "  </table>\n";
        file << "  <p>Total contacts: " << contacts.size() << "</p>\n";
        file << "</body>\n</html>\n";

        cout << "Exported to contacts.html - open it in your browser.\n";
    }
};

// Checks that the phone number has only digits and is 10 digits long
bool isValidPhone(const string &phone) {
    if (phone.length() != 10) {
        return false;
    }
    for (char c : phone) {
        if (!isdigit(c)) {
            return false;
        }
    }
    return true;
}

int main() {
    ContactBook book;
    string choice, name, phone;

    while (true) {
        cout << "\n===== PHONE DIRECTORY =====\n";
        cout << "1. Add contact\n";
        cout << "2. Delete contact\n";
        cout << "3. Search contact\n";
        cout << "4. Display all (A-Z)\n";
        cout << "5. Export to HTML\n";
        cout << "6. Exit\n";
        cout << "Enter choice: ";
        getline(cin, choice);

        if (choice == "1") {
            cout << "Enter name: ";
            getline(cin, name);
            cout << "Enter phone (10 digits): ";
            getline(cin, phone);
            if (name.empty()) {
                cout << "Name cannot be empty.\n";
            } else if (!isValidPhone(phone)) {
                cout << "Invalid phone number.\n";
            } else {
                book.addContact(name, phone);
            }
        } else if (choice == "2") {
            cout << "Enter name to delete: ";
            getline(cin, name);
            book.deleteContact(name);
        } else if (choice == "3") {
            cout << "Enter name to search: ";
            getline(cin, name);
            book.searchContact(name);
        } else if (choice == "4") {
            book.displayContacts();
        } else if (choice == "5") {
            book.exportToHTML();
        } else if (choice == "6") {
            cout << "Goodbye!\n";
            break;
        } else {
            cout << "Invalid choice, try again.\n";
        }
    }
    return 0;
}