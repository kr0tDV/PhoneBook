#include "phonebook.h"

// Реализация методов класса Contact
Contact::Contact() : name(""), phone(""), email("") {}

Contact::Contact(string n, string p, string e)
    : name(n), phone(p), email(e) {
}

string Contact::getName() const { return name; }
string Contact::getPhone() const { return phone; }
string Contact::getEmail() const { return email; }

void Contact::setName(string n) { name = n; }
void Contact::setPhone(string p) { phone = p; }
void Contact::setEmail(string e) { email = e; }

void Contact::display() const {
    cout << left << setw(20) << name
        << setw(15) << phone
        << setw(25) << email << endl;
}

bool Contact::contains(string query) const {
    string lowerQuery = query;
    transform(lowerQuery.begin(), lowerQuery.end(), lowerQuery.begin(), ::tolower);

    string lowerName = name;
    transform(lowerName.begin(), lowerName.end(), lowerName.begin(), ::tolower);

    return lowerName.find(lowerQuery) != string::npos;
}

// Реализация методов класса PhoneBook
PhoneBook::PhoneBook() : filename("phonebook.dat") {
    loadFromFile();
}

PhoneBook::~PhoneBook() {
    saveToFile();
}

void PhoneBook::clearInputBuffer() {
    cin.clear();
    while (cin.get() != '\n' && cin.peek() != EOF) {}
}

void PhoneBook::saveToFile() {
    ofstream file(filename);
    if (!file.is_open()) {
        cerr << "Ошибка открытия файла для записи!" << endl;
        return;
    }

    for (const auto& contact : contacts) {
        file << contact.getName() << endl;
        file << contact.getPhone() << endl;
        file << contact.getEmail() << endl;
    }

    file.close();
}

void PhoneBook::loadFromFile() {
    ifstream file(filename);
    if (!file.is_open()) {
        return; // Файл не существует - нормально при первом запуске
    }

    contacts.clear();
    string name, phone, email;

    while (getline(file, name)) {
        if (getline(file, phone)) {
            getline(file, email);
            contacts.push_back(Contact(name, phone, email));
        }
    }

    file.close();
}

void PhoneBook::addContact(string name, string phone, string email) {
    contacts.push_back(Contact(name, phone, email));
    saveToFile();
}

void PhoneBook::displayAllContacts() const {
    if (contacts.empty()) {
        cout << "\nТелефонная книга пуста!\n";
        return;
    }

    cout << "\n=== Все контакты ===\n";
    cout << "==================================================\n";
    cout << " № | Имя              | Телефон       | Email\n";
    cout << "==================================================\n";

    for (size_t i = 0; i < contacts.size(); ++i) {
        cout << " " << setw(2) << i + 1 << " | ";
        cout << setw(16) << left
            << (contacts[i].getName().length() > 16 ?
                contacts[i].getName().substr(0, 13) + "..." : contacts[i].getName()) << " | ";
        cout << setw(13) << left
            << (contacts[i].getPhone().length() > 13 ?
                contacts[i].getPhone().substr(0, 10) + "..." : contacts[i].getPhone()) << " | ";
        cout << (contacts[i].getEmail().length() > 20 ?
            contacts[i].getEmail().substr(0, 17) + "..." : contacts[i].getEmail()) << endl;
    }

    cout << "==================================================\n";
    cout << "Всего контактов: " << contacts.size() << endl;
}

void PhoneBook::searchContacts(string query) const {
    if (contacts.empty()) {
        cout << "\nТелефонная книга пуста!\n";
        return;
    }

    vector<int> results;
    for (size_t i = 0; i < contacts.size(); ++i) {
        if (contacts[i].contains(query)) {
            results.push_back(i);
        }
    }

    if (results.empty()) {
        cout << "Контакты не найдены!\n";
        return;
    }

    cout << "\n=== Найденные контакты (" << results.size() << ") ===\n";
    cout << "==================================================\n";
    for (int idx : results) {
        cout << " " << idx + 1 << ". " << contacts[idx].getName()
            << " | " << contacts[idx].getPhone()
            << " | " << contacts[idx].getEmail() << endl;
    }
    cout << "==================================================\n";
}

void PhoneBook::deleteContact(int index) {
    if (index < 1 || index > static_cast<int>(contacts.size())) {
        cout << "Неверный номер контакта!\n";
        return;
    }

    cout << "Вы действительно хотите удалить контакт \""
        << contacts[index - 1].getName() << "\"? (y/n): ";
    char confirm;
    cin >> confirm;
    clearInputBuffer();

    if (confirm == 'y' || confirm == 'Y') {
        contacts.erase(contacts.begin() + index - 1);
        saveToFile();
        cout << "Контакт успешно удален!\n";
    }
    else {
        cout << "Удаление отменено.\n";
    }
}

void PhoneBook::editContact(int index) {
    if (index < 1 || index > static_cast<int>(contacts.size())) {
        cout << "Неверный номер контакта!\n";
        return;
    }

    Contact& contact = contacts[index - 1];

    cout << "\nТекущие данные контакта:\n";
    cout << "Имя: " << contact.getName() << endl;
    cout << "Телефон: " << contact.getPhone() << endl;
    cout << "Email: " << contact.getEmail() << endl;

    cout << "\n--- Введите новые данные ---\n";
    cout << "(оставьте пустым, чтобы не менять)\n";

    string input;
    cout << "Новое имя: ";
    getline(cin, input);
    if (!input.empty()) contact.setName(input);

    cout << "Новый телефон: ";
    getline(cin, input);
    if (!input.empty()) contact.setPhone(input);

    cout << "Новый email: ";
    getline(cin, input);
    if (!input.empty()) contact.setEmail(input);

    saveToFile();
    cout << "Контакт успешно обновлен!\n";
}

void PhoneBook::clearAllContacts() {
    if (contacts.empty()) {
        cout << "\nТелефонная книга уже пуста!\n";
        return;
    }

    cout << "\n--- Очистка телефонной книги ---\n";
    cout << "Вы действительно хотите удалить ВСЕ контакты ("
        << contacts.size() << ")? (y/n): ";
    char confirm;
    cin >> confirm;
    clearInputBuffer();

    if (confirm == 'y' || confirm == 'Y') {
        contacts.clear();
        saveToFile();
        cout << "Все контакты успешно удалены!\n";
    }
    else {
        cout << "Очистка отменена.\n";
    }
}

int PhoneBook::getContactCount() const {
    return contacts.size();
}

bool PhoneBook::isEmpty() const {
    return contacts.empty();
}

// Вспомогательные функции
void setConsoleEncoding() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
}

void displayHeader() {
    cout << "\n";
    cout << "========================================\n";
    cout << "        ТЕЛЕФОННАЯ КНИГА v2.0\n";
    cout << "========================================\n";
}

void waitForEnter() {
    cout << "\nНажмите Enter для продолжения...";
    cin.get();
}