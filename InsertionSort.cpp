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
    cout << "InsertionSort Visualization\n\n";

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

void insertionSort(vector<int> &arr)
{
    int n = arr.size();
    unordered_set<int> sorted;

    for (int i = 1; i < n; ++i)
    {
        int key = arr[i];
        int j = i - 1;

        while (j >= 0 && arr[j] > key)
        {
            printVerticalBars(arr, j, j + 1, sorted);
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
        sorted.insert(i);                          // update progress visually
        printVerticalBars(arr, j + 1, -1, sorted); // show insertion
    }

    for (int i = 0; i < n; ++i)
        sorted.insert(i);

    printVerticalBars(arr, -1, -1, sorted);
}

int main()
{
    srand(time(0));
    vector<int> data;
    unordered_set<int> s;

    while (s.size() < 40)
        s.insert(rand() % 40 + 1); // Unique values between 1–40

    data.assign(s.begin(), s.end());
    shuffle(data.begin(), data.end(), default_random_engine(time(0)));

    insertionSort(data);
    return 0;
}
