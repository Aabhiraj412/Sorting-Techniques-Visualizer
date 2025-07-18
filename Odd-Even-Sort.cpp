#include <bits/stdc++.h>
#include <unistd.h>
using namespace std;

void printBars(const vector<int> &arr, int curr1 = -1, int curr2 = -1, unordered_set<int> sorted = {})
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif

    static int step = 0;
    cout << "Step: " << step++ << "\n";
    cout << "Odd-Even Sort Visualization\n\n";

    int maxVal = *max_element(arr.begin(), arr.end());
    for (int h = maxVal; h >= 1; h--)
    {
        for (int i = 0; i < arr.size(); i++)
        {
            if (arr[i] >= h)
            {
                if (sorted.count(i))
                    cout << "\033[1;32m █ \033[0m"; // Green
                else if (i == curr1 || i == curr2)
                    cout << "\033[1;31m █ \033[0m"; // Red
                else
                    cout << "\033[1;34m █ \033[0m"; // Blue
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
        if (i == curr1 || i == curr2)
            cout << "\033[1;31m" << setw(2) << arr[i] << "\033[0m ";
        else if (sorted.count(i))
            cout << "\033[1;32m" << setw(2) << arr[i] << "\033[0m ";
        else
            cout << setw(2) << arr[i] << " ";
    }
    cout << '\n';

    this_thread::sleep_for(chrono::milliseconds(10));
}

void oddEvenSort(vector<int> &arr)
{
    bool sorted = false;
    int n = arr.size();
    unordered_set<int> done;

    while (!sorted)
    {
        sorted = true;

        // Odd phase
        for (int i = 1; i < n - 1; i += 2)
        {
            if (arr[i] > arr[i + 1])
            {
                swap(arr[i], arr[i + 1]);
                sorted = false;
                printBars(arr, i, i + 1, done);
            }
        }

        // Even phase
        for (int i = 0; i < n - 1; i += 2)
        {
            if (arr[i] > arr[i + 1])
            {
                swap(arr[i], arr[i + 1]);
                sorted = false;
                printBars(arr, i, i + 1, done);
            }
        }
    }

    // Final pass with green highlight
    for (int i = 0; i < n; ++i)
    {
        done.insert(i);
        printBars(arr, -1, -1, done);
    }
}

int main()
{
    srand(time(0));
    unordered_set<int> s;
    while (s.size() < 40)
        s.insert(rand() % 40 + 1);

    vector<int> data(s.begin(), s.end());
    shuffle(data.begin(), data.end(), default_random_engine(time(0)));

    printBars(data);
    oddEvenSort(data);
    // printBars(data);

    return 0;
}
