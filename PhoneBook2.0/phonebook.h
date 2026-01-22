#pragma once
#ifndef PHONEBOOK_H
#define PHONEBOOK_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>
#include <limits>
#include <algorithm>
#include <windows.h>

using namespace std;

// Класс для представления контакта
class Contact {
private:
    string name;
    string phone;
    string email;

public:
    // Конструкторы
    Contact();
    Contact(string n, string p, string e);

    // Геттеры
    string getName() const;
    string getPhone() const;
    string getEmail() const;

    // Сеттеры
    void setName(string n);
    void setPhone(string p);
    void setEmail(string e);

    // Методы работы с данными
    void display() const;
    bool contains(string query) const;
};

// Класс для управления телефонной книгой
class PhoneBook {
private:
    vector<Contact> contacts;
    string filename;

    // Приватные вспомогательные методы
    void saveToFile();
    void loadFromFile();
    void clearInputBuffer();

public:
    // Конструктор и деструктор
    PhoneBook();
    ~PhoneBook();

    // Основные публичные методы
    void addContact(string name, string phone, string email);
    void displayAllContacts() const;
    void searchContacts(string query) const;
    void deleteContact(int index);
    void editContact(int index);
    void clearAllContacts();

    // Вспомогательные публичные методы
    int getContactCount() const;
    bool isEmpty() const;
};

// Вспомогательные функции
void setConsoleEncoding();
void displayHeader();
void waitForEnter();

#endif