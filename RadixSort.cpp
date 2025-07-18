#include <bits/stdc++.h>
#include <unistd.h>
using namespace std;

void printVerticalBars(const vector<int> &arr, int cur = -1, int next = -1, unordered_set<int> sorted = {})
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif

    static int step = 0;
    cout << "Step: " << step++ << "\n";
    cout << "Radix Sort Visualization\n\n";

    int maxHeight = *max_element(arr.begin(), arr.end());

    for (int level = maxHeight; level >= 1; level--)
    {
        for (int i = 0; i < arr.size(); i++)
        {
            if (arr[i] >= level)
            {
                if (i == cur || i == next)
                    cout << "\033[1;31m █ \033[0m";
                else if (sorted.count(i))
                    cout << "\033[1;32m █ \033[0m";
                else
                    cout << "\033[1;34m █ \033[0m";
            }
            else
                cout << "   ";
        }
        cout << '\n';
    }

    // Base line
    for (int i = 0; i < arr.size(); i++)
        cout << "---";
    cout << '\n';

    // Print indices
    for (int i = 0; i < arr.size(); i++)
        cout << setw(2) << i << " ";
    cout << '\n';

    // Print values
    for (int i = 0; i < arr.size(); i++)
    {
        if (i == cur || i == next)
            cout << "\033[1;31m" << setw(2) << arr[i] << "\033[0m ";
        else if (sorted.count(i))
            cout << "\033[1;32m" << setw(2) << arr[i] << "\033[0m ";
        else
            cout << setw(2) << arr[i] << " ";
    }
    cout << '\n';

    this_thread::sleep_for(chrono::milliseconds(10));
}

// Helper to get max
int getMax(const vector<int> &arr)
{
    return *max_element(arr.begin(), arr.end());
}

// Modified count sort to visualize each step
void countSort(vector<int> &arr, int exp)
{
    int n = arr.size();
    vector<int> output(n);
    int count[10] = {0};

    // Store count of occurrences
    for (int i = 0; i < n; i++)
        count[(arr[i] / exp) % 10]++;

    // Update count[i] to contain position info
    for (int i = 1; i < 10; i++)
        count[i] += count[i - 1];

    // Build output array from right to left
    for (int i = n - 1; i >= 0; i--)
    {
        int idx = (arr[i] / exp) % 10;
        output[count[idx] - 1] = arr[i];
        count[idx]--;
    }

    // Copy back and visualize each update
    for (int i = 0; i < n; i++)
    {
        arr[i] = output[i];
        printVerticalBars(arr, i); // Visualize current insertion
    }
}

// Full radix sort with visualization
void radixsort(vector<int> &arr)
{
    int m = getMax(arr);
    for (int exp = 1; m / exp > 0; exp *= 10)
        countSort(arr, exp);
}

int main()
{
    srand(time(0));
    unordered_set<int> s;
    vector<int> data;

    // Generate 40 unique integers from 1 to 40
    while (s.size() < 40)
        s.insert(rand() % 40 + 1);

    data.assign(s.begin(), s.end());
    shuffle(data.begin(), data.end(), default_random_engine(time(0)));

    printVerticalBars(data);
    radixsort(data);

    // Final state
    unordered_set<int> sortedIndexes;
    for (int i = 0; i < data.size(); ++i)
        sortedIndexes.insert(i);
    printVerticalBars(data, -1, -1, sortedIndexes);

    return 0;
}
