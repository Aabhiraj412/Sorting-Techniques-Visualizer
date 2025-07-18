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
    cout << "Cocktail Sort Visualization\n\n";

    int maxHeight = *max_element(arr.begin(), arr.end());

    for (int level = maxHeight; level >= 1; level--)
    {
        for (int i = 0; i < arr.size(); i++)
        {
            if (arr[i] >= level)
            {
                if (i == cur || i == next)
                    cout << "\033[1;31m █ \033[0m"; // Red (comparing)
                else if (sorted.count(i))
                    cout << "\033[1;32m █ \033[0m"; // Green (sorted)
                else
                    cout << "\033[1;34m █ \033[0m"; // Blue (unsorted)
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

void cocktailSort(vector<int> &arr)
{
    bool swapped = true;
    int start = 0;
    int end = arr.size() - 1;
    unordered_set<int> sorted;

    while (swapped)
    {
        swapped = false;

        // Left to right
        for (int i = start; i < end; ++i)
        {
            printVerticalBars(arr, i, i + 1, sorted);
            if (arr[i] > arr[i + 1])
            {
                swap(arr[i], arr[i + 1]);
                swapped = true;
                printVerticalBars(arr, i, i + 1, sorted);
            }
        }

        if (!swapped)
            break;

        swapped = false;
        sorted.insert(end);
        --end;

        // Right to left
        for (int i = end - 1; i >= start; --i)
        {
            printVerticalBars(arr, i, i + 1, sorted);
            if (arr[i] > arr[i + 1])
            {
                swap(arr[i], arr[i + 1]);
                swapped = true;
                printVerticalBars(arr, i, i + 1, sorted);
            }
        }

        sorted.insert(start);
        // printVerticalBars(arr, start, end, sorted);
        ++start;

    }

    for (int i = 0; i < arr.size(); i++)
        sorted.insert(i);
    printVerticalBars(arr, -1, -1, sorted);
}

int main()
{
    srand(time(0));
    unordered_set<int> s;
    vector<int> data;

    // Generate 40 unique random integers between 1 and 100
    while (s.size() < 40)
        s.insert(rand() % 40 + 1);

    data.assign(s.begin(), s.end());
    shuffle(data.begin(), data.end(), default_random_engine(time(0)));

    printVerticalBars(data);
    cocktailSort(data);

    return 0;
}
