#include <iostream>
using namespace std;
float parallelCapacitance(float capacitors[], int n);
float seriesCapacitance(float capacitors[], int n);
int main()
{
    system("chcp 65001");
    const int n = 6;
    float capacitors[6] = { 1.5, 1.1, 3.6, 5.4, 4.4, 2.1 };
    float parallelCapacitanceResult;
    float seriesCapacitanceResult;
    cout << "Ємності конденсаторів (пФ): ";
    for (int i = 0; i < n; i++)
    {
        cout << capacitors[i] << " ";
    }
    parallelCapacitanceResult = parallelCapacitance(capacitors, n);
    seriesCapacitanceResult = seriesCapacitance(capacitors, n);
    cout << "\n\nПаралельне з'єднання: " << parallelCapacitanceResult << " пФ";

    cout << "\nПослідовне з'єднання: " << seriesCapacitanceResult << " пФ";
    return 0;
}
float parallelCapacitance(float capacitors[], int n)
{
    float sum = 0;
    for (int i = 0; i < n; i++)
    {
        sum += capacitors[i];
    }
    return sum;
}
float seriesCapacitance(float capacitors[], int n)
{
    float sum = 0;
    for (int i = 0; i < n; i++)
    {
        sum += 1 / capacitors[i];
    }
    return 1 / sum;
}
