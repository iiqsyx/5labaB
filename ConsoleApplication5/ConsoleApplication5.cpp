#include <iostream>
#include <string>
#include <vector>
#include <windows.h>
using namespace std;

struct People {
    string destination;
    int time;
    int num_of_flight;
public:
    void print() {
        cout << "Пункт назначения: " << destination << "\tВремя отправления: " << time << "\tНомер рейса: " << num_of_flight << endl;
    }
};

const int HASH_TABLE_SIZE = 10;

class HashTable {
private:
    vector<People> table;
    int hash1(int key) {
        return key % HASH_TABLE_SIZE;
    }
    int hash2(int key) {
        return (key / HASH_TABLE_SIZE) % HASH_TABLE_SIZE;
    }
public:
    HashTable() {
        table.resize(HASH_TABLE_SIZE);
    }
    void insert(People people) {
        int index = hash1(people.num_of_flight);
        int step = hash2(people.num_of_flight);
        while (!table[index].destination.empty()) {
            index = (index + step) % HASH_TABLE_SIZE;
        }
        table[index] = people;
    }
    People* search(int key) {
        int index = hash1(key);
        int step = hash2(key);
        while (!table[index].destination.empty() && table[index].num_of_flight != key) {
            index = (index + step) % HASH_TABLE_SIZE;
        }
        if (table[index].destination.empty()) {
            return nullptr;
        }
        else {
            return &table[index];
        }
    }
    void print() {
        for (int i = 0; i < HASH_TABLE_SIZE; i++) {
            if (table[i].destination != "")
                cout << "[" << i << "]\t->\t" << "Пункт назначения: " << table[i].destination << "\tВремя отправления: " << table[i].time << "\tНомер рейса: " << table[i].num_of_flight << endl;
            else
                cout << "[" << i << "]\t->\t" << "Нет данных\n";
        }
    }
};

int main(int argc, char* argv[])
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    srand(time(NULL));

    const int n = 8;
    People people[n];
    for (int i = 0; i < n; i++) {
        system("cls");
        cout << "-~<3<3<3 Ввод данных о полете " << i + 1 << endl;
        cout << "<3Введите пункт назначения: ";
        cin >> people[i].destination;
        people[i].time = rand() % 12;
        people[i].num_of_flight = rand() % 1000;

    }

    HashTable table;
    for (int i = 0; i < n; i++) {
        table.insert(people[i]);
    }

    cout << "<3 Исходный массив:" << endl;
    for (int i = 0; i < n; i++) {
        people[i].print();
    }

    cout << "<3 Хеш-таблица:" << endl;
    table.print();
    system("pause");

    char key;
    do
    {
        system("cls");
        system("pause");
        table.print();
        cout << "<3<3<3<3<3<3<3<3<3<3<3<3<3<3<3<3<3<3<3<3<3<3"<<endl<<endl;
        cout << "Введите ключ для поиска (Номер рейса): ";
        int searchObject;
        cin >> searchObject;

        People* result = table.search(searchObject);
        if (result == nullptr) {
            cout << "<3 Элемент не найден" << endl;
            return 0;
        }
        else {
            cout << "<3 Найденный элемент: ";
            result->print();
        }
        cout << "<3<3<3<3<3<3<3<3<3<3<3<3<3<3<3<3<3<3<3<3<3<3"<<endl<<endl;
        cout << "Продолжить поиск? (да - любая клавиша, нет - 1): ";
        cin >> key;
    } while (key != '1');


    return 0;
}