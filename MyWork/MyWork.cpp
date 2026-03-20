#include <iostream> // бібліотека для роботи з консоллю
#include <fstream> // бібліотека для роботи з файлами
#include <vector> // контейнер vector
#include <windows.h> // бібліотека для налаштування кодування консолі Windows

using namespace std; // дозволяє не писати std:

// Функція видалення файлів при завершенні програми
void deleteFiles()
{
    remove("array.txt");
    remove("array.bin");
    remove("task1.txt");
    remove("task2.txt");
    remove("task3.txt");

    cout << "Тимчасові файли видалено.\n";
}

// Введення масиву з консолі та запис у текстовий файл
void inputArrayToTextFile()
{
    int n;

    cout << "Введіть розмір масиву: ";
    cin >> n;

    int* A = new int[n];

    cout << "Введіть елементи масиву:\n";

    for (int i = 0; i < n; i++)
        cin >> A[i];

    ofstream file("array.txt");

    file << n << endl;

    for (int i = 0; i < n; i++)
        file << A[i] << " ";

    file.close();

    delete[] A;

    cout << "Масив записано у файл array.txt\n";
}

// Генерація масиву та запис у бінарний файл
void randomArrayToBinaryFile()
{
    int n;

    cout << "Введіть розмір масиву: ";
    cin >> n;

    int* A = new int[n];

    // проста генерація чисел
    for (int i = 0; i < n; i++)
        A[i] = (i * 7 + 3) % 50 - 25;

    // відкриття бінарного файлу
    ofstream file("array.bin", ios::binary);

    // запис розміру масиву
    file.write((char*)&n, sizeof(n));

    // запис усіх елементів масиву
    file.write((char*)A, n * sizeof(int));

    file.close()

    delete[] A;

    cout << "Масив записано у бінарний файл array.bin\n";
}

// Завдання 1
// Видалити всі додатні елементи масиву
void task1()
{
    ifstream file("array.txt");

    int n;
    file >> n;

    int* A = new int[n];

    // зчитування масиву
    for (int i = 0; i < n; i++)
        file >> A[i];

    file.close();

    int count = 0; // лічильник

    // визначення кількості недодатних елементів
    for (int i = 0; i < n; i++)
        if (A[i] <= 0) // перевірка чи елемент не додатній
            count++; // лічильник

    int* B = new int[count]; // новbq масив без додатних елементів

    int j = 0; // індекс нового масиву

    // формування нового масиву
    for (int i = 0; i < n; i++)
        if (A[i] <= 0) // перевірка умови
            B[j++] = A[i];

    ofstream result("task1.txt");

    cout << "Масив без додатних елементів:\n";

    // вивід результату
    for (int i = 0; i < count; i++)
    {
        cout << B[i] << " ";
        result << B[i] << " ";
    }

    cout << endl;

    result.close();

    delete[] A;
    delete[] B;
}

// Завдання 2
// Мінімальний додатний елемент правіше першого елемента кратного 2
void task2()
{
    ifstream file("array.txt");

    int n;
    file >> n;

    int* A = new int[n];

    for (int i = 0; i < n; i++)
        file >> A[i];

    file.close();

    int* p = A;  // вказівник на поточний елемент
    int index = -1; // індекс знайденого елемента

    // пошук першого елемента кратного 2
    for (int i = 0; i < n; i++)
    {
        if (*(p + i) % 2 == 0) // перевірка кратності
        {
            index = i; // запам'ятовування позиції
            break;
        }
    }

    if (index == -1) // якщо елемент не знайдено
    {
        cout << "Немає елементів кратних 2\n";
        delete[] A;
        return;
    }

    int minValue = 1000000; // початкове велике значення

    // пошук мінімального додатного елемента правіше
    for (int i = index + 1; i < n; i++) // перегляд правої частини
    {
        if (*(p + i) > 0 && *(p + i) < minValue) // перевірка умови
            minValue = *(p + i);
    }

    ofstream result("task2.txt");

    if (minValue == 1000000) // якщо значення не знайдено
        cout << "Немає додатних елементів після кратного 2\n";
    else
    {
        cout << "Мінімальний елемент = " << minValue << endl;
        result << minValue;
    }

    result.close();

    delete[] A; // звільнення пам'яті
}

// Завдання 3
// Обчислення max(min(...))
void task3()
{
    ifstream file("array.txt");

    int n;
    file >> n;

    int* A = new int[n]; // створення масиву

    for (int i = 0; i < n; i++)
        file >> A[i];

    file.close();

    int maxValue = -1000000; // початкове мінімальне значення

    // проходження по масиву з двох сторін
    for (int i = 0; i < n / 2; i++) // цикл до середини
    {
        int m; //мінімальний елемент пари

        // знаходження мінімального елемента пари
        if (A[i] < A[n - i - 1])
            m = A[i];
        else
            m = A[n - i - 1];

        // пошук максимального серед знайдених
        if (m > maxValue)
            maxValue = m;
    }

    ofstream result("task3.txt");

    cout << "Результат = " << maxValue << endl;

    result << maxValue;

    result.close();

    delete[] A; // звільнення пам'яті
}

// Читання даних з файлу у контейнер vector
void readToVector()
{
    ifstream file("array.txt");

    int n;
    file >> n;

    vector<int> arr(n); // створення vector

    for (int i = 0; i < n; i++) // заповнення контейнера
        file >> arr[i];

    file.close();

    cout << "Елементи vector:\n";

    for (int i = 0; i < arr.size(); i++) // вивід vector
        cout << arr[i] << " ";

    cout << endl;
}

// Головна функція(меню)
int main()
{
    // увімкнення українського кодування
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);

    int choice; // змінна вибору пункту меню

    do
    {
        cout << "\n        МЕНЮ\n";
        cout << "1 - Ввести масив у файл\n";
        cout << "2 - Створити масив (бінарний файл)\n";
        cout << "3 - Завдання 1\n";
        cout << "4 - Завдання 2\n";
        cout << "5 - Завдання 3\n";
        cout << "6 - Читати у vector\n";
        cout << "0 - Вихід\n";

        cin >> choice;

        switch (choice)
        {
        case 1:
            inputArrayToTextFile();
            break;

        case 2:
            randomArrayToBinaryFile();
            break;

        case 3:
            task1();
            break;

        case 4:
            task2();
            break;

        case 5:
            task3();
            break;

        case 6:
            readToVector();
            break;

        case 0:
            deleteFiles();
            break;
        }

    } while (choice != 0); // цикл працює поки не обрано вихід

    return 0;
}