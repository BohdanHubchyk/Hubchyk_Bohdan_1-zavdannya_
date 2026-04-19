#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct Seller
{
    string surname;
    string name;
    int reviews;
    double salary;
    string shop;
};
void addSeller()
{
    Seller s;

    cout << "Введіть прізвище: ";
    cin >> s.surname;

    cout << "Введіть ім'я: ";
    cin >> s.name;

    cout << "Введіть кількість відгуків: ";
    cin >> s.reviews;

    cout << "Введіть зарплату: ";
    cin >> s.salary;

    cout << "Введіть магазин: ";
    cin >> s.shop;

    ofstream file("sellers.txt", ios::app);

    if (!file.is_open())
    {
        cout << "Помилка відкриття файлу!" << endl;
        return;
    }
    file << s.surname << " "
        << s.name << " "
        << s.reviews << " "
        << s.salary << " "
        << s.shop << endl;

    file.close();

    cout << "Продавця додано!" << endl;
}
void showAllSellers()
{
    ifstream file("sellers.txt");

    if (!file.is_open())
    {
        cout << "Файл не відкрито!" << endl;
        return;
    }

    Seller s;
    int num = 1;

    while (file >> s.surname >> s.name >> s.reviews >> s.salary >> s.shop)
    {
        cout << "\nПродавець №" << num << endl;
        cout << "Прізвище: " << s.surname << endl;
        cout << "Ім'я: " << s.name << endl;
        cout << "Відгуки: " << s.reviews << endl;
        cout << "ЗП: " << s.salary << endl;
        cout << "Магазин: " << s.shop << endl;

        num++;
    }

    file.close();
}
void showTop3()
{
    Seller arr[100];
    int count = 0;

    ifstream file("sellers.txt");

    if (!file.is_open())
    {
        cout << "Файл не відкрито!" << endl;
        return;
    }

    while (file >> arr[count].surname >> arr[count].name >> arr[count].reviews >> arr[count].salary >> arr[count].shop)
    {
        count++;
    }

    file.close();

    if (count == 0)
    {
        cout << "Немає даних!" << endl;
        return;
    }
    for (int i = 0; i < count - 1; i++)
    {
        for (int j = 0; j < count - i - 1; j++)
        {
            if (arr[j].reviews < arr[j + 1].reviews)
            {
                swap(arr[j], arr[j + 1]);
            }
        }
    }

    cout << "\nТОП 3 продавці:\n";

    int top = (count < 3) ? count : 3;

    for (int i = 0; i < top; i++)
    {
        cout << "\nМісце " << i + 1 << endl;
        cout << arr[i].surname << " " << arr[i].name << endl;
        cout << "Відгуки: " << arr[i].reviews << endl;
        cout << "ЗП: " << arr[i].salary << endl;
        cout << "Магазин: " << arr[i].shop << endl;
    }
}
int main()
{
    system("chcp 65001");

    int choice;

    do
    {
        cout << "\n--- МЕНЮ ---" << endl;
        cout << "1. Додати продавця" << endl;
        cout << "2. Показати всіх продавців" << endl;
        cout << "3. ТОП 3 за відгуками" << endl;
        cout << "0. Вихід" << endl;
        cout << "Вибір: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            addSeller();
            break;
        case 2:
            showAllSellers();
            break;
        case 3:
            showTop3();
            break;
        case 0:
            cout << "Вихід..." << endl;
            break;
        default:
            cout << "Помилка вибору!" << endl;
        }

    } while (choice != 0);

    return 0;
}