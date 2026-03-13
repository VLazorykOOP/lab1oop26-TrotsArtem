#include <iostream>
#include <fstream>
#include <vector>
#include <windows.h>

using namespace std;

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

    // введення розміру масиву
    cout << "Введіть розмір масиву: ";
    cin >> n;

    // створення динамічного масиву
    int* A = new int[n];

    cout << "Введіть елементи масиву:\n";

    // введення елементів
    for (int i = 0; i < n; i++)
        cin >> A[i];

    // відкриття текстового файлу
    ofstream file("array.txt");

    // запис розміру масиву
    file << n << endl;

    // запис елементів масиву
    for (int i = 0; i < n; i++)
        file << A[i] << " ";

    file.close();

    // звільнення пам'яті
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

    // запис масиву
    file.write((char*)A, n * sizeof(int));

    file.close();

    delete[] A;

    cout << "Масив записано у бінарний файл array.bin\n";
}

// Завдання 1
// Видалити всі додатні елементи масиву
{
    ifstream file("array.txt");

    int n;
    file >> n;

    int* A = new int[n];

    // зчитування масиву
    for (int i = 0; i < n; i++)
        file >> A[i];

    file.close();

    int count = 0;

    // визначення кількості недодатних елементів
    for (int i = 0; i < n; i++)
        if (A[i] <= 0)
            count++;

    int* B = new int[count];

    int j = 0;

    // формування нового масиву
    for (int i = 0; i < n; i++)
        if (A[i] <= 0)
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
    int index = -1;

    // пошук першого елемента кратного 2
    for (int i = 0; i < n; i++)
    {
        if (*(p + i) % 2 == 0)
        {
            index = i;
            break;
        }
    }

    if (index == -1)
    {
        cout << "Немає елементів кратних 2\n";
        delete[] A;
        return;
    }

    int minValue = 1000000;

    // пошук мінімального додатного елемента правіше
    for (int i = index + 1; i < n; i++)
    {
        if (*(p + i) > 0 && *(p + i) < minValue)
            minValue = *(p + i);
    }

    ofstream result("task2.txt");

    if (minValue == 1000000)
        cout << "Немає додатних елементів після кратного 2\n";
    else
    {
        cout << "Мінімальний елемент = " << minValue << endl;
        result << minValue;
    }

    result.close();

    delete[] A;
}

// Завдання 3
// Обчислення max(min(...))
void task3()
{
    ifstream file("array.txt");

    int n;
    file >> n;

    int* A = new int[n];

    for (int i = 0; i < n; i++)
        file >> A[i];

    file.close();

    int maxValue = -1000000;

    // проходження по масиву з двох сторін
    for (int i = 0; i < n / 2; i++)
    {
        int m;

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

    delete[] A;
}

// Читання даних з файлу у контейнер vector
void readToVector()
{
    ifstream file("array.txt");

    int n;
    file >> n;

    vector<int> arr(n);

    for (int i = 0; i < n; i++)
        file >> arr[i];

    file.close();

    cout << "Елементи vector:\n";

    for (int i = 0; i < arr.size(); i++)
        cout << arr[i] << " ";

    cout << endl;
}

// Головна функція(меню)
int main()
{
    // увімкнення українського кодування
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);

    int choice;

    do
    {
        cout << "\n===== МЕНЮ =====\n";
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

    } while (choice != 0);

    return 0;
}