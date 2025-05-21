#include <iostream>
#include "contacts.h"
using namespace std;

int main() {
	Contact* contacts = nullptr; // створюю масив контактів
    int size = 0;
	const char* filename = "contacts.txt"; // ім'я файлу для збереження контактів

    loadContactsFromFile(contacts, size, filename);

    cout << "Телефонна книга\n";

    int choice = 0;
    while (true) {
        cout << "\n1. Додати контакт\n2. Показати всі контакти\n3. Зберегти у файл\n4. Вийти\n";
        cout << "Виберіть опцію: ";
        cin >> choice;

        if (choice == 1) {
			Contact c; // створюємо новий контакт
            cout << "Введіть ім'я (без пробілів): ";
            cin >> c.name;
            cout << "Введіть телефон (без пробілів): ";
            cin >> c.phone;

			addContact(contacts, size, c); // додаємо контакт в масив
        }
		else if (choice == 2) { // виводимо всі контакти
            if (size == 0) {
                cout << "Контактів немає.\n";
            }
            else {
				printContacts(contacts, size); // виводимо всі контакти
            }
        }
		else if (choice == 3) { // зберігаємо контакти у файл
            saveContactsToFile(contacts, size, filename); 
            cout << "Контакти збережено у файл.\n";
        }
		else if (choice == 4) { // виходимо з програми
            break;
        }
        else {
            cout << "Невірний вибір. Спробуйте ще раз.\n";
        }
    }

	freeContacts(contacts); // звільняємо пам'ять

    return 0;
}
