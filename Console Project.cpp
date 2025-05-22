#include <iostream>
#include <string>
#include <cstring>

struct Contact { // структура для хранения контакта
	char name[50]; // имя контакта
	char phone[20]; // телефон контакта
};

void addContact(Contact*& arr, int& size, const Contact& c); // добавляем новый контакт
void saveContactsToFile(Contact* arr, int size, const char* filename); // записываем все контакты в файл
void loadContactsFromFile(Contact*& arr, int& size, const char* filename); // загружаем контакты из файла
void printContacts(Contact* arr, int size); // выводим все контакты на экран
void freeContacts(Contact*& arr); // освобождаем память

using namespace std;

// добавляем новый контакт в массив
void addContact(Contact*& arr, int& size, const Contact& c) {
    Contact* temp = new Contact[size + 1]; // создаем массив на один элемент больше
    for (int i = 0; i < size; ++i) {
        temp[i] = arr[i]; // переносим старый массив в новый
    }
    temp[size] = c; // добавляем новый контакт
    delete[] arr; // удаляем старый массив
    arr = temp; // присваиваем новый
    size++;
}

// записываем все контакты в файл
void saveContactsToFile(Contact* arr, int size, const char* filename) {
    FILE* file;
    fopen_s(&file, filename, "w"); // открываем файл для записи
    if (!file) {
        cout << "Ошибка открытия файла!" << "\n";
        return;
    }
    for (int i = 0; i < size; ++i) {
        fprintf(file, "%s;%s\n", arr[i].name, arr[i].phone); // записываем в формате имя;телефон
    }
    fclose(file); // закрываем файл
}

// загружаем контакты из файла
void loadContactsFromFile(Contact*& arr, int& size, const char* filename) {
    FILE* file;
    fopen_s(&file, filename, "r"); // открываем файл для чтения
    if (!file) {
        cout << "Ошибка открытия файла!" << "\n";
        return;
    }

    char line[100]; // буфер для чтения строки
	while (fgets(line, sizeof(line), file)) { // читаем строку из файла
        // убираем символ новой строки
        line[strcspn(line, "\n")] = 0;

        // разбиваем строку на имя и телефон
        char* context = nullptr; // контекст для strtok_s
		char* name = strtok_s(line, ";", &context); // имя
		char* phone = strtok_s(nullptr, ";", &context); // телефон

        // проверяем, что оба поля успешно считаны
		if (name && phone) { // если оба поля не пустые
			// создаем новый контакт и добавляем его в массив
			Contact c; // создаем новый контакт
            strncpy_s(c.name, sizeof(c.name), name, _TRUNCATE); // безопасное копирование имени
            c.name[sizeof(c.name) - 1] = '\0'; // гарантируем завершающий нуль
            strncpy_s(c.phone, sizeof(c.phone), phone, _TRUNCATE); // безопасное копирование телефона
            c.phone[sizeof(c.phone) - 1] = '\0'; // гарантируем завершающий нуль
			addContact(arr, size, c); // добавляем контакт в массив
        }
    }
    fclose(file); // закрываем файл
}

// выводим все контакты на экран
void printContacts(Contact* arr, int size) {
    cout << "\nКонтакты в памяти:\n";
    for (int i = 0; i < size; ++i) {
        cout << i + 1 << ". " << arr[i].name << " - " << arr[i].phone << "\n";
    }
}

// освобождаем память
void freeContacts(Contact*& arr) {
    delete[] arr; // удаляем массив
    arr = nullptr; // обнуляем указатель
}

// основная функция программы
int main() {
	setlocale(0, ""); // устанавливаем локал для поддержки кириллицы
	Contact* contacts = nullptr; // указатель на массив контактов
	int size = 0; // размер массива
    const char* filename = "contacts.txt"; 
    int choice; 

    do {
        cout << "\nМеню:\n";
        cout << "1. Добавить контакт\n";
        cout << "2. Показать все контакты\n";
        cout << "3. Сохранить контакты в файл\n";
        cout << "4. Загрузить контакты из файла\n";
        cout << "5. Выход\n";
        cout << "Выберите действие: ";
        cin >> choice;
        cin.ignore(); // очищаем буфер после ввода числа

		switch (choice) { // обработка выбора
        case 1: {
            Contact c; 
            cout << "Введите имя (макс. 49 символов): "; 
			cin.getline(c.name, sizeof(c.name)); // вводим имя
            cout << "Введите телефон (макс. 19 символов): ";
			cin.getline(c.phone, sizeof(c.phone)); // вводим телефон
			addContact(contacts, size, c); // добавляем контакт в массив
            cout << "Контакт добавлен!" << "\n";
            break;
        }
        case 2:
			printContacts(contacts, size); // выводим все контакты
            break;
        case 3:
			saveContactsToFile(contacts, size, filename); // сохраняем контакты в файл
            cout << "Контакты сохранены в файл " << filename << "\n";
            break;
        case 4:
            freeContacts(contacts); // очищаем текущий массив
            size = 0; //
			loadContactsFromFile(contacts, size, filename); // загружаем контакты из файла
            cout << "Контакты загружены из файла " << filename << "\n";
            break;
        case 5:
            cout << "Выход из программы..." << '\n';
            break;
        default:
            cout << "Неверный выбор, попробуйте снова!" << "\n";
        }
	} while (choice != 5); // выход из цикла

    freeContacts(contacts); // освобождаем память перед выходом
    return 0; //
}