#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

//------------------------------------------------
// Введення масиву з консолі -> текстовий файл
//------------------------------------------------
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

//------------------------------------------------
// Генерація масиву -> бінарний файл
//------------------------------------------------
void randomArrayToBinaryFile()
{
    int n;

    cout << "Введіть розмір масиву: ";
    cin >> n;

    int* A = new int[n];

    // проста генерація чисел
    for (int i = 0; i < n; i++)
        A[i] = (i * 7 + 3) % 50 - 25;

    ofstream file("array.bin", ios::binary);

    file.write((char*)&n, sizeof(n));
    file.write((char*)A, n * sizeof(int));

    file.close();

    delete[] A;

    cout << "Масив записано у бінарний файл array.bin\n";
}

//------------------------------------------------
// Завдання 1
// Видалити всі додатні елементи
//------------------------------------------------
void task1()
{
    ifstream file("array.txt");

    int n;
    file >> n;

    int* A = new int[n];

    for (int i = 0; i < n; i++)
        file >> A[i];

    file.close();

    int count = 0;

    for (int i = 0; i < n; i++)
        if (A[i] <= 0)
            count++;

    int* B = new int[count];

    int j = 0;

    for (int i = 0; i < n; i++)
        if (A[i] <= 0)
            B[j++] = A[i];

    ofstream result("task1.txt");

    cout << "Масив без додатних елементів:\n";

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

//------------------------------------------------
// Завдання 2
//------------------------------------------------
void task2()
{
    ifstream file("array.txt");

    int n;
    file >> n;

    int* A = new int[n];

    for (int i = 0; i < n; i++)
        file >> A[i];

    file.close();

    int* p = A;
    int index = -1;

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

//------------------------------------------------
// Завдання 3
//------------------------------------------------
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

    for (int i = 0; i < n / 2; i++)
    {
        int m;

        if (A[i] < A[n - i - 1])
            m = A[i];
        else
            m = A[n - i - 1];

        if (m > maxValue)
            maxValue = m;
    }

    ofstream result("task3.txt");

    cout << "Результат = " << maxValue << endl;

    result << maxValue;

    result.close();

    delete[] A;
}

//------------------------------------------------
// Читання у vector
//------------------------------------------------
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

//------------------------------------------------
// Меню
//------------------------------------------------
int main()
{
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
        }

    } while (choice != 0);

    return 0;
}