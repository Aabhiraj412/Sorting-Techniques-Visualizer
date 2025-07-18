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
    cout << "Heap Sort Visualization\n\n";

    int maxHeight = *max_element(arr.begin(), arr.end());

    for (int level = maxHeight; level >= 1; level--)
    {
        for (int i = 0; i < arr.size(); i++)
        {
            if (arr[i] >= level)
            {
                if (i == cur || i == next)
                    cout << "\033[1;31m █ \033[0m"; // Red: currently comparing/swapping
                else if (sorted.count(i))
                    cout << "\033[1;32m █ \033[0m"; // Green: sorted
                else
                    cout << "\033[1;34m █ \033[0m"; // Blue: unsorted
            }
            else
            {
                cout << "   ";
            }
        }
        cout << '\n';
    }

    for (int i = 0; i < arr.size(); i++)
        cout << "---";
    cout << '\n';

    for (int i = 0; i < arr.size(); i++)
        cout << setw(2) << i << " ";
    cout << '\n';

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

void heapify(vector<int> &arr, int n, int i, unordered_set<int> &sorted)
{
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    if (l < n && arr[l] > arr[largest])
        largest = l;
    if (r < n && arr[r] > arr[largest])
        largest = r;

    if (largest != i)
    {
        swap(arr[i], arr[largest]);
        printVerticalBars(arr, i, largest, sorted);
        heapify(arr, n, largest, sorted);
    }
    else
    {
        printVerticalBars(arr, i, largest, sorted);
    }
}

void heapSort(vector<int> &arr)
{
    int n = arr.size();
    unordered_set<int> sorted;

    // Build heap
    for (int i = n / 2 - 1; i >= 0; i--)
    {
        heapify(arr, n, i, sorted);
    }

    // Extract elements one by one
    for (int i = n - 1; i > 0; i--)
    {
        swap(arr[0], arr[i]);
        sorted.insert(i); // Mark as sorted
        printVerticalBars(arr, 0, i, sorted);
        heapify(arr, i, 0, sorted);
    }
    sorted.insert(0);
    printVerticalBars(arr, -1, -1, sorted);
}

int main()
{
    srand(time(0));
    unordered_set<int> s;
    vector<int> data;

    // Generate 40 unique integers between 1 and 100
    while (s.size() < 40)
        s.insert(rand() % 40 + 1);

    data.assign(s.begin(), s.end());
    shuffle(data.begin(), data.end(), default_random_engine(time(0)));

    printVerticalBars(data);
    heapSort(data);

    return 0;
}
