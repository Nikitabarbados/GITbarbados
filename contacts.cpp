#include <iostream>
#include <string>
#include "contacts.h"
using namespace std;

// ������ ����� ������� � �����
void addContact(Contact**& arr, int& size, Contact* c) { 
	Contact** temp = new Contact * [size + 1]; // ��������� ����� �� �� ���� ������� �����
    for (int i = 0; i < size; ++i) {
		temp[i] = arr[i]; // ���������� ������ ����� � �����
    }
    temp[size] = c; // ������ ������ ��������
	delete[] arr; // ��������� ������ �����
	arr = temp; // �� ������ � �����
    size++;
}
// �������� �� �������� � ����
void saveContactsToFile(Contact** arr, int size, const char* filename) {
	FILE* file = fopen(filename, "w"); // ��������� ���� ��� ������, �� ����� ������� ��������
    if (!file) {
		cout << "������� �������� �����!" << "\n"; // ���� �� �������� ����
        return;
    }
    for (int i = 0; i < size; ++i) {
        fprintf(file, "%s;%s\n", arr[i]->name, arr[i]->phone); //�������� � ������ ��� �������.
    }
	fclose(file); // ��������� ����
}

void loadContactsFromFile(Contact**& arr, int& size, const char* filename) {
	FILE* file = fopen(filename, "r"); // ��������� ���� ��� �������
	if (!file) return; // ���� �� �������� ����

    while (!feof(file)) {
		Contact* c = new Contact; // �������� ���'��� �� ����� �������
		if (fscanf(file, "%49[^;];%19[^\n]\n", c->name, c->phone) == 2) { // ������� ��'� �� �������
			addContact(arr, size, c); // ���� ������� ������ � �����
        }
        else {
            delete c; // ���� �� ������� ���������
        }
    }
	fclose(file); // ��������� ����
}

void printContacts(Contact** arr, int size) { // �������� �� �������� �� �����
    cout << "\n�������� � �����:\n"; 
    for (int i = 0; i < size; ++i) { 
		cout << i + 1 << ". " << arr[i]->name << " - " << arr[i]->phone << "\n"; // �������� �����, ��'� �� �������
    }
}

void freeContacts(Contact**& arr, int size) { // ��������� ���'���
    for (int i = 0; i < size; ++i) {
		delete arr[i]; // ��������� ����� �������
    }
	delete[] arr; // ��������� �����
	arr = nullptr; // ��������� ��������
}
