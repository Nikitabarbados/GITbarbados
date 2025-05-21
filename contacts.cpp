#include <iostream>
#include <string>
#include "contacts.h"
using namespace std;

// додаємо новий контакт в масив
void addContact(Contact**& arr, int& size, Contact* c) { 
	Contact** temp = new Contact * [size + 1]; // створюємо масив де на один елемент більше
    for (int i = 0; i < size; ++i) {
		temp[i] = arr[i]; // переносимо старий масив в новий
    }
    temp[size] = c; // просто додаємо вказівник
	delete[] arr; // видаляємо старий масив
	arr = temp; // та додаємо в новий
    size++;
}
// записуємо всі контакти у файл
void saveContactsToFile(Contact** arr, int size, const char* filename) {
	FILE* file = fopen(filename, "w"); // відкриваємо файл для запису, та кожен контакт записуємо
    if (!file) {
		cout << "Помилка відкриття файлу!" << "\n"; // якщо не відкрився файл
        return;
    }
    for (int i = 0; i < size; ++i) {
        fprintf(file, "%s;%s\n", arr[i]->name, arr[i]->phone); //записуємо у форматі ім’я телефон.
    }
	fclose(file); // закриваємо файл
}

void loadContactsFromFile(Contact**& arr, int& size, const char* filename) {
	FILE* file = fopen(filename, "r"); // відкриваємо файл для читання
	if (!file) return; // якщо не відкрився файл

    while (!feof(file)) {
		Contact* c = new Contact; // виділяємо пам'ять під новий контакт
		if (fscanf(file, "%49[^;];%19[^\n]\n", c->name, c->phone) == 2) { // зчитуємо ім'я та телефон
			addContact(arr, size, c); // якщо зчитали додаємо в масив
        }
        else {
            delete c; // якщо не зчитано видаляємо
        }
    }
	fclose(file); // закриваємо файл
}

void printContacts(Contact** arr, int size) { // виводимо всі контакти на екран
    cout << "\nКонтакти в пам’яті:\n"; 
    for (int i = 0; i < size; ++i) { 
		cout << i + 1 << ". " << arr[i]->name << " - " << arr[i]->phone << "\n"; // виводимо номер, ім'я та телефон
    }
}

void freeContacts(Contact**& arr, int size) { // звільняємо пам'ять
    for (int i = 0; i < size; ++i) {
		delete arr[i]; // видаляємо кожен контакт
    }
	delete[] arr; // видаляємо масив
	arr = nullptr; // обнуляємо вказівник
}
