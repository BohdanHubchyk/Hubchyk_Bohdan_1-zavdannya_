#include <iostream>
using namespace std;

void fillMatrixRandom(int** A, int n, int V);
void printMatrix(int** A, int n);
bool inSectorStar2(int i, int j, int n);
bool inSector5_NoDiagonal(int i, int j, int n);
int countZerosInSectorStar2(int** A, int n);
int medianOfMatrix(int** A, int n);
int processSector5ReplaceWithMedian(int** A, int n, int med);
int main()
{
    system("chcp 65001");
    int n, V;
    cout << "Введіть n: ";
    cin >> n;
    cout << "Введіть номер варіанта V: ";
    cin >> V;
    if (n <= 0)
    {
        cout << "n повинно бути > 0\n";
        return 0;
    }
    int** A = new int* [n];
    for (int i = 0; i < n; i++)
        A[i] = new int[n];
    fillMatrixRandom(A, n, V);
    cout << "\nМатриця ДО:\n";
    printMatrix(A, n);
    int zeros = countZerosInSectorStar2(A, n);
    cout << "\nКількість нулів у секторі *2: " << zeros << endl;
    int med = medianOfMatrix(A, n);
    int count5 = processSector5ReplaceWithMedian(A, n, med);
    cout << "\nМедіана матриці: " << med << endl;
    cout << "Кількість елементів у секторі 5: " << count5 << endl;
    cout << "\nМатриця ПІСЛЯ:\n";
    printMatrix(A, n);
    for (int i = 0; i < n; i++)
        delete[] A[i];
    delete[] A;
    return 0;
}
void fillMatrixRandom(int** A, int n, int V)
{
    int low = -10 - V;
    int high = 10 + V;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            A[i][j] = low + rand() % (high - low + 1);
}
void printMatrix(int** A, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            cout << A[i][j] << "\t";
        cout << endl;
    }
}
bool inSectorStar2(int i, int j, int n)
{
    bool mainDiag = (i == j);
    bool sideDiag = (i + j == n - 1);
    bool sector2Inside = (i > j) && (i + j < n - 1);
    return sector2Inside || mainDiag || sideDiag;
}
bool inSector5_NoDiagonal(int i, int j, int n)
{
    return (i + j < n - 1);
}
int countZerosInSectorStar2(int** A, int n)
{
    int count = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (inSectorStar2(i, j, n) && A[i][j] == 0)
                count++;
    return count;
}
int medianOfMatrix(int** A, int n)
{
    int size = n * n;
    int* B = new int[size];
    int k = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            B[k++] = A[i][j];
    for (int i = 0; i < size - 1; i++)
        for (int j = 0; j < size - i - 1; j++)
            if (B[j] > B[j + 1])
            {
                int temp = B[j];
                B[j] = B[j + 1];
                B[j + 1] = temp;
            }
    int median = B[size / 2];
    delete[] B;
    return median;
}

int processSector5ReplaceWithMedian(int** A, int n, int med)
{
    int count = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (inSector5_NoDiagonal(i, j, n))
            {
                count++;
                A[i][j] = med;
            }
    return count;
}
