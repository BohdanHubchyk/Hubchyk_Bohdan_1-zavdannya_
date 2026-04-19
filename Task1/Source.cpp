#include <iostream>
#include <random>
#include <chrono>
#include <future>

using namespace std;
using namespace std::chrono;

void printArray(int arr[], int n);
void generateArray(int arr[], int n);
void selectionSort(int arr[], int n);
int partition(int arr[], int low, int high);
void quickSort(int arr[], int low, int high);
void bubbleSort(int arr[], int n);
int binarySearch(int arr[], int low, int high, int key);
void copyArray(int from[], int to[], int n);
void swapValues(int& a, int& b);

int main() {
    system("chcp 65001");

    int n;

    do {
        cout << "Введіть кількість елементів у масиві або введіть 0 для завершення програми: ";
        cin >> n;

        if (n <= 0)
            break;

        int* arr = new int[n];
        generateArray(arr, n);

        cout << "\nОригінальний масив для розміру " << n << ": ";
        printArray(arr, n);

        //Сортування вибором
        int* selectionSyncArr = new int[n];
        int* selectionAsyncArr = new int[n];

        copyArray(arr, selectionSyncArr, n);
        copyArray(arr, selectionAsyncArr, n);

        auto s1 = high_resolution_clock::now();
        selectionSort(selectionSyncArr, n);
        auto s2 = high_resolution_clock::now();
        long long selectionSyncTime = duration_cast<microseconds>(s2 - s1).count();

        auto a1 = high_resolution_clock::now();
        auto f1 = async(launch::async, selectionSort, selectionAsyncArr, n);
        f1.get();
        auto a2 = high_resolution_clock::now();
        long long selectionAsyncTime = duration_cast<microseconds>(a2 - a1).count();

        cout << "\nСОРТУВАННЯ ВИБОРОМ:" << endl;
        cout << "Відсортований масив: ";
        printArray(selectionAsyncArr, n);
        cout << "SYNC час: " << selectionSyncTime << " мікросекунди" << endl;
        cout << "ASYNC час: " << selectionAsyncTime << " мікросекунди" << endl;

       
        // Швидке сортування
        int* quickSyncArr = new int[n];
        int* quickAsyncArr = new int[n];

        copyArray(arr, quickSyncArr, n);
        copyArray(arr, quickAsyncArr, n);

        auto q1 = high_resolution_clock::now();
        quickSort(quickSyncArr, 0, n - 1);
        auto q2 = high_resolution_clock::now();
        long long quickSyncTime = duration_cast<microseconds>(q2 - q1).count();

        auto q3 = high_resolution_clock::now();
        auto f2 = async(launch::async, quickSort, quickAsyncArr, 0, n - 1);
        f2.get();
        auto q4 = high_resolution_clock::now();
        long long quickAsyncTime = duration_cast<microseconds>(q4 - q3).count();

        cout << "\nШВИДКЕ СОРТУВАННЯ:" << endl;
        cout << "Відсортований масив: ";
        printArray(quickAsyncArr, n);
        cout << "SYNC час: " << quickSyncTime << " мікросекунди" << endl;
        cout << "ASYNC час: " << quickAsyncTime << " мікросекунди" << endl;

        //Сортування бульбашкою
        int* bubbleSyncArr = new int[n];
        int* bubbleAsyncArr = new int[n];

        copyArray(arr, bubbleSyncArr, n);
        copyArray(arr, bubbleAsyncArr, n);

        auto b1 = high_resolution_clock::now();
        bubbleSort(bubbleSyncArr, n);
        auto b2 = high_resolution_clock::now();
        long long bubbleSyncTime = duration_cast<microseconds>(b2 - b1).count();

        auto b3 = high_resolution_clock::now();
        auto f3 = async(launch::async, bubbleSort, bubbleAsyncArr, n);
        f3.get();
        auto b4 = high_resolution_clock::now();
        long long bubbleAsyncTime = duration_cast<microseconds>(b4 - b3).count();

        cout << "\nСОРТУВАННЯ БУЛЬБАШКОЮ:" << endl;
        cout << "Відсортований масив: ";
        printArray(bubbleAsyncArr, n);
        cout << "SYNC час: " << bubbleSyncTime << " мікросекунди" << endl;
        cout << "ASYNC час: " << bubbleAsyncTime << " мікросекунди" << endl;

        // Бінарний пошук
        int key;
        cout << "\nВведіть елемент для пошуку: ";
        cin >> key;

        auto bs1 = high_resolution_clock::now();
        int result = binarySearch(quickAsyncArr, 0, n - 1, key);
        auto bs2 = high_resolution_clock::now();

        long long searchTime = duration_cast<microseconds>(bs2 - bs1).count();

        if (result == -1)
            cout << "Елемент не знайдено" << endl;
        else
            cout << "Елемент знайдено за індексом " << result << endl;

        cout << "Час, витрачений на бінарний пошук: " << searchTime << " мікросекунди" << endl;

        delete[] arr;
        delete[] selectionSyncArr;
        delete[] selectionAsyncArr;
        delete[] quickSyncArr;
        delete[] quickAsyncArr;
        delete[] bubbleSyncArr;
        delete[] bubbleAsyncArr;

        cout << "\n---------------------------------------------\n" << endl;

    } while (true);

    return 0;
}

void printArray(int arr[], int n) {
    if (n <= 10) {
        for (int i = 0; i < n; ++i) {
            cout << arr[i] << " ";
        }
    }
    else {
        for (int i = 0; i < 5; ++i) {
            cout << arr[i] << " ";
        }

        cout << "... (пропущено " << n - 10 << " елементів) ... ";

        for (int i = n - 5; i < n; ++i) {
            cout << arr[i] << " ";
        }
    }

    cout << endl;
}

void generateArray(int arr[], int n) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(0, 999);

    for (int i = 0; i < n; ++i) {
        arr[i] = dist(gen);
    }
}

void copyArray(int from[], int to[], int n) {
    for (int i = 0; i < n; ++i) {
        to[i] = from[i];
    }
}

void swapValues(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}

void selectionSort(int arr[], int n) {
    for (int i = 0; i < n - 1; ++i) {
        int minIndex = i;

        for (int j = i + 1; j < n; ++j) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }

        if (minIndex != i) {
            swapValues(arr[i], arr[minIndex]);
        }
    }
}

int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j <= high - 1; ++j) {
        if (arr[j] < pivot) {
            ++i;
            swapValues(arr[i], arr[j]);
        }
    }

    swapValues(arr[i + 1], arr[high]);
    return i + 1;
}

void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (arr[j] > arr[j + 1]) {
                swapValues(arr[j], arr[j + 1]);
            }
        }
    }
}

int binarySearch(int arr[], int low, int high, int key) {
    if (high >= low) {
        int mid = low + (high - low) / 2;

        if (arr[mid] == key)
            return mid;

        if (arr[mid] > key)
            return binarySearch(arr, low, mid - 1, key);

        return binarySearch(arr, mid + 1, high, key);
    }

    return -1;
}
// task 1
// fix for PR