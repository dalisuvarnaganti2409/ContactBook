#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// Self-referential structure (Linked List Node)
struct Contact {
    string name, phone, email;
    Contact* next;
};

// Class for Contact Book
class ContactBook {
private:
    Contact* head;

    // Helper function to create a new contact node
    Contact* createContact(string name, string phone, string email) {
        Contact* newNode = new Contact;
        newNode->name = name;
        newNode->phone = phone;
        newNode->email = email;
        newNode->next = nullptr;
        return newNode;
    }

public:
    ContactBook() {
        head = nullptr;
        loadFromFile();
    }

    // Insert contact in alphabetical order
    void addContact(string name, string phone, string email) {
        Contact* newNode = createContact(name, phone, email);

        // If list is empty OR new contact should be first
        if (!head || name < head->name) {
            newNode->next = head;
            head = newNode;
        } else {
            Contact* current = head;
            while (current->next && current->next->name < name) {
                current = current->next;
            }
            newNode->next = current->next;
            current->next = newNode;
        }

        cout << "✅ Contact added successfully!\n";
        saveToFile();
    }

    // Display all contacts
    void displayContacts() {
        if (!head) {
            cout << "⚠️ No contacts available.\n";
            return;
        }
        cout << "\n--- Contact List ---\n";
        Contact* current = head;
        while (current) {
            cout << current->name << " | " << current->phone << " | " << current->email << endl;
            current = current->next;
        }
    }

    // Search by name
    void searchContact(string name) {
        Contact* current = head;
        while (current) {
            if (current->name == name) {
                cout << "✅ Found: " << current->name << " | " << current->phone << " | " << current->email << endl;
                return;
            }
            current = current->next;
        }
        cout << "⚠️ Contact not found.\n";
    }

    // Delete by name
    void deleteContact(string name) {
        if (!head) {
            cout << "⚠️ Contact list is empty.\n";
            return;
        }

        // If first node needs to be deleted
        if (head->name == name) {
            Contact* temp = head;
            head = head->next;
            delete temp;
            cout << "🗑️ Contact deleted.\n";
            saveToFile();
            return;
        }

        Contact* current = head;
        while (current->next && current->next->name != name) {
            current = current->next;
        }

        if (current->next) {
            Contact* temp = current->next;
            current->next = current->next->next;
            delete temp;
            cout << "🗑️ Contact deleted.\n";
            saveToFile();
        } else {
            cout << "⚠️ Contact not found.\n";
        }
    }

    // Save contacts to file
    void saveToFile() {
        ofstream file("contacts.txt");
        Contact* current = head;
        while (current) {
            file << current->name << " " << current->phone << " " << current->email << "\n";
            current = current->next;
        }
        file.close();
    }

    // Load contacts from file
    void loadFromFile() {
        ifstream file("contacts.txt");
        string name, phone, email;
        while (file >> name >> phone >> email) {
            addContact(name, phone, email);
        }
        file.close();
    }
};

int main() {
    ContactBook book;
    int choice;
    string name, phone, email;

    do {
        cout << "\n====== Contact Book Menu ======\n";
        cout << "1. Add Contact\n";
        cout << "2. Display Contacts\n";
        cout << "3. Search Contact\n";
        cout << "4. Delete Contact\n";
        cout << "5. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter Name: ";
                cin >> name;
                cout << "Enter Phone: ";
                cin >> phone;
                cout << "Enter Email: ";
                cin >> email;
                book.addContact(name, phone, email);
                break;
            case 2:
                book.displayContacts();
                break;
            case 3:
                cout << "Enter name to search: ";
                cin >> name;
                book.searchContact(name);
                break;
            case 4:
                cout << "Enter name to delete: ";
                cin >> name;
                book.deleteContact(name);
                break;
            case 5:
                cout << "👋 Exiting Contact Book...\n";
                break;
            default:
                cout << "⚠️ Invalid choice.\n";
        }
    } while (choice != 5);

    return 0;
}
