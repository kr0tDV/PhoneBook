#include "phonebook.h"

int main() {
    // Настройка кодировки для русских символов
    setConsoleEncoding();

    PhoneBook phoneBook;
    int choice = -1;

    do {
        system("cls");
        displayHeader();

        cout << "\nКонтактов в книге: " << phoneBook.getContactCount() << "\n\n";

        cout << "1. Добавить контакт\n";
        cout << "2. Показать все контакты\n";
        cout << "3. Найти контакт\n";
        cout << "4. Удалить контакт\n";
        cout << "5. Редактировать контакт\n";
        cout << "6. Очистить всю книгу\n";
        cout << "0. Выход\n";
        cout << "\nВыберите действие: ";

        // Проверяем корректность ввода
        if (!(cin >> choice)) {
            cin.clear();
            while (cin.get() != '\n' && cin.peek() != EOF) {}
            cout << "Ошибка ввода! Введите число от 0 до 6.\n";
            waitForEnter();
            continue;
        }

        // Очищаем буфер после ввода числа
        while (cin.get() != '\n' && cin.peek() != EOF) {}

        switch (choice) {
        case 1: {
            string name, phone, email;

            cout << "\n--- Добавление нового контакта ---\n";
            cout << "Введите имя: ";
            getline(cin, name);

            cout << "Введите телефон: ";
            getline(cin, phone);

            cout << "Введите email (можно пропустить): ";
            getline(cin, email);

            phoneBook.addContact(name, phone, email);
            cout << "Контакт успешно добавлен!\n";
            break;
        }

        case 2:
            phoneBook.displayAllContacts();
            break;

        case 3: {
            string query;
            cout << "\n--- Поиск контакта ---\n";
            cout << "Введите имя для поиска: ";
            getline(cin, query);
            phoneBook.searchContacts(query);
            break;
        }

        case 4:
            phoneBook.displayAllContacts();
            if (!phoneBook.isEmpty()) {
                int index;
                cout << "\n--- Удаление контакта ---\n";
                cout << "Введите номер контакта для удаления: ";
                cin >> index;
                while (cin.get() != '\n' && cin.peek() != EOF) {}
                phoneBook.deleteContact(index);
            }
            break;

        case 5:
            phoneBook.displayAllContacts();
            if (!phoneBook.isEmpty()) {
                int index;
                cout << "\n--- Редактирование контакта ---\n";
                cout << "Введите номер контакта для редактирования: ";
                cin >> index;
                while (cin.get() != '\n' && cin.peek() != EOF) {}
                phoneBook.editContact(index);
            }
            break;

        case 6:
            phoneBook.clearAllContacts();
            break;

        case 0:
            cout << "\nСохранение данных...\n";
            cout << "Выход из программы...\n";
            break;

        default:
            cout << "Неверный выбор! Введите число от 0 до 6.\n";
        }

        if (choice != 0) {
            waitForEnter();
        }

    } while (choice != 0);

    return 0;
}