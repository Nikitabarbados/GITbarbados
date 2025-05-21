#ifndef CONTACTS_H
#define CONTACTS_H

struct Contact { // описуємо структуру Contact.
    char name[50]; // ім'я максимум 50
	char phone[20]; // телефон максимум 20
};

// прототипи функції
void addContact(Contact*& arr, int& size, const Contact& c);
void saveContactsToFile(Contact* arr, int size, const char* filename);
void loadContactsFromFile(Contact*& arr, int& size, const char* filename);
void printContacts(Contact* arr, int size);
void freeContacts(Contact*& arr);

#endif