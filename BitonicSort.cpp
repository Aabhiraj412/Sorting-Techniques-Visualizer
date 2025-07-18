#include <bits/stdc++.h>
#include <unistd.h>
using namespace std;

void printBars(const vector<int> &arr, int curr = -1, unordered_set<int> sortedIndices = {})
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif

    static int steps = 0;
    cout << "Step: " << steps++ << "\n";
    cout << "Bitonic Sort Visualization\n\n";

    // Find max height excluding INT_MAX values (padding)
    int maxH = 0;
    for (int val : arr)
    {
        if (val != INT_MAX && val > maxH)
        {
            maxH = val;
        }
    }

    if (maxH == 0)
        maxH = 1; // Prevent division by zero

    for (int h = maxH; h >= 1; h--)
    {
        for (int i = 0; i < arr.size(); i++)
        {
            if (arr[i] != INT_MAX && arr[i] >= h)
            {
                if (sortedIndices.count(i))
                    cout << "\033[1;32m █ \033[0m"; // Green
                else if (i == curr)
                    cout << "\033[1;31m █ \033[0m"; // Red
                else
                    cout << "\033[1;34m █ \033[0m"; // Blue
            }
            else if (arr[i] == INT_MAX)
            {
                cout << "\033[1;90m ░ \033[0m"; // Gray for padding
            }
            else
            {
                cout << "   ";
            }
        }
        cout << "\n";
    }

    for (int i = 0; i < arr.size(); i++)
        cout << "---";
    cout << "\n";

    for (int i = 0; i < arr.size(); i++)
        cout << setw(2) << i << " ";
    cout << "\n";

    for (int i = 0; i < arr.size(); i++)
    {
        if (arr[i] == INT_MAX)
        {
            cout << "\033[1;90m∞\033[0m ";
        }
        else if (i == curr)
            cout << "\033[1;31m" << setw(2) << arr[i] << "\033[0m ";
        else if (sortedIndices.count(i))
            cout << "\033[1;32m" << setw(2) << arr[i] << "\033[0m ";
        else
            cout << setw(2) << arr[i] << " ";
    }
    cout << '\n';

    this_thread::sleep_for(chrono::milliseconds(10));
}

// Direction constants
#define ASCENDING true
#define DESCENDING false

void bitonicMerge(vector<int> &arr, int low, int count, bool dir)
{
    if (count <= 1)
        return;

    int k = count / 2;
    for (int i = low; i < low + k; i++)
    {
        if ((dir == ASCENDING && arr[i] > arr[i + k]) ||
            (dir == DESCENDING && arr[i] < arr[i + k]))
        {
            swap(arr[i], arr[i + k]);
            printBars(arr, i);
        }
    }

    bitonicMerge(arr, low, k, dir);
    bitonicMerge(arr, low + k, k, dir);
}

void bitonicSort(vector<int> &arr, int low, int count, bool dir)
{
    if (count <= 1)
        return;

    int k = count / 2;

    bitonicSort(arr, low, k, ASCENDING);
    bitonicSort(arr, low + k, k, DESCENDING);
    bitonicMerge(arr, low, count, dir);
}

void sortBitonic(vector<int> &arr)
{
    int n = arr.size();
    int powerOfTwo = 1;
    while (powerOfTwo < n)
        powerOfTwo *= 2;

    // Store original size to remove padding later
    int originalSize = arr.size();

    // Pad with a very large value (INT_MAX) so they go to the end when sorted
    while (arr.size() < powerOfTwo)
        arr.push_back(INT_MAX);

    printBars(arr);
    bitonicSort(arr, 0, arr.size(), ASCENDING);

    // Remove padding (INT_MAX values will be at the end after ascending sort)
    arr.resize(originalSize);

    // Final visualization with all elements sorted
    unordered_set<int> allSorted;
    for (int i = 0; i < arr.size(); i++)
    {
        allSorted.insert(i);
    }
    printBars(arr, -1, allSorted);
}

int main()
{
    srand(time(0));
    vector<int> data;
    unordered_set<int> s;

    // Generate a power of 2 number of elements for better demonstration
    int targetSize = 32; // Power of 2
    while (s.size() < targetSize)
        s.insert(rand() % targetSize + 1); // Range 1-32 to avoid conflicts

    data.assign(s.begin(), s.end());
    shuffle(data.begin(), data.end(), default_random_engine(time(0)));

    cout << "Initial array size: " << data.size() << endl;
    printBars(data);
    sortBitonic(data);

    return 0;
}
