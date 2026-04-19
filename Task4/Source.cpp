#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main()
{
    system("chcp 65001");

    string sentence = "today is a good day and today I study cpp";
    string word;

    cout << "Введіть слово: ";
    cin >> word;

    int count = 0;
    string temp = "";

    for (int i = 0; i < sentence.length(); i++)
    {
        if (sentence[i] != ' ')
        {
            temp += sentence[i];
        }

        if (sentence[i] == ' ' || i == sentence.length() - 1)
        {
            if (temp == word)
            {
                count++;
            }
            temp = "";
        }
    }

    ofstream file("result.txt");

    if (count > 0)
    {
        file << "Кількість входжень слова: " << count;
    }
    else
    {
        file << "Варіант №4";
    }

    file.close();

    cout << "Результат записано у файл result.txt" << endl;

    return 0;
}