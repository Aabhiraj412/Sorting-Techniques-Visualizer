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
    cout << "Cycle Sort Visualization\n\n";

    int maxH = *max_element(arr.begin(), arr.end());

    for (int h = maxH; h >= 1; h--)
    {
        for (int i = 0; i < arr.size(); i++)
        {
            if (arr[i] >= h)
            {
                if (sortedIndices.count(i))
                    cout << "\033[1;32m █ \033[0m"; // Green: sorted
                else if (i == curr)
                    cout << "\033[1;31m █ \033[0m"; // Red: current
                else
                    cout << "\033[1;34m █ \033[0m"; // Blue
            }
            else
                cout << "   ";
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
        if (i == curr)
            cout << "\033[1;31m" << setw(2) << arr[i] << "\033[0m "; // Red
        else if (sortedIndices.count(i))
            cout << "\033[1;32m" << setw(2) << arr[i] << "\033[0m "; // Green
        else
            cout << setw(2) << arr[i] << " "; // Default
    }
    cout << "\n";

    this_thread::sleep_for(chrono::milliseconds(10));
}

void cycleSort(vector<int> &arr)
{
    int n = arr.size();
    unordered_set<int> sorted;

    for (int start = 0; start <= n - 2; start++)
    {
        int item = arr[start];
        int pos = start;

        for (int i = start + 1; i < n; i++)
            if (arr[i] < item)
                pos++;

        if (pos == start)
            continue;

        while (item == arr[pos])
            pos++;

        if (pos != start)
            swap(item, arr[pos]);

        printBars(arr, pos, sorted);

        while (pos != start)
        {
            pos = start;

            for (int i = start + 1; i < n; i++)
                if (arr[i] < item)
                    pos++;

            while (item == arr[pos])
                pos++;

            if (item != arr[pos])
                swap(item, arr[pos]);

            printBars(arr, pos, sorted);
        }

        sorted.insert(start);
    }

    for (int i = 0; i < n; i++)
        sorted.insert(i);

    printBars(arr, -1, sorted);
}

int main()
{
    srand(time(0));
    vector<int> data;
    unordered_set<int> s;

    while (s.size() < 60)
        s.insert(rand() % 60 + 1); // unique values

    data.assign(s.begin(), s.end());
    shuffle(data.begin(), data.end(), default_random_engine(time(0)));

    printBars(data);
    cycleSort(data);

    return 0;
}
