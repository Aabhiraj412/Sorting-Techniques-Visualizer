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
    cout << "Shell Sort Visualization\n\n";

    int maxHeight = *max_element(arr.begin(), arr.end());

    for (int level = maxHeight; level >= 1; level--)
    {
        for (int i = 0; i < arr.size(); i++)
        {
            if (arr[i] >= level)
            {
                if (i == cur || i == next)
                    cout << "\033[1;31m █ \033[0m"; // Red
                else if (sorted.count(i))
                    cout << "\033[1;32m █ \033[0m"; // Green
                else
                    cout << "\033[1;34m █ \033[0m"; // Blue
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

void shellSort(vector<int> &arr)
{
    int n = arr.size();
    unordered_set<int> sorted;

    for (int gap = n / 2; gap > 0; gap /= 2)
    {
        for (int i = gap; i < n; i++)
        {
            int temp = arr[i];
            int j = i;

            while (j >= gap && arr[j - gap] > temp)
            {
                arr[j] = arr[j - gap];
                printVerticalBars(arr, j, j - gap, sorted);
                j -= gap;
            }

            arr[j] = temp;
            printVerticalBars(arr, j, i, sorted);
        }
    }

    for (int i = 0; i < n; ++i)
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
    shellSort(data);

    return 0;
}
