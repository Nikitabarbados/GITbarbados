#ifndef CONTACTS_H
#define CONTACTS_H

struct Contact { // ������� ��������� Contact.
    char name[50]; // ��'� �������� 50
	char phone[20]; // ������� �������� 20
};

// ��������� �������
void addContact(Contact*& arr, int& size, const Contact& c);
void saveContactsToFile(Contact* arr, int size, const char* filename);
void loadContactsFromFile(Contact*& arr, int& size, const char* filename);
void printContacts(Contact* arr, int size);
void freeContacts(Contact*& arr);

#endif