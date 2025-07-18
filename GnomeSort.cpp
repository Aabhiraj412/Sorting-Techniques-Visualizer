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
    cout << "Gnome Sort Visualization\n\n";

    int maxH = *max_element(arr.begin(), arr.end());

    for (int h = maxH; h >= 1; h--)
    {
        for (int i = 0; i < arr.size(); i++)
        {
            if (arr[i] >= h)
            {
                if (sortedIndices.count(i))
                    cout << "\033[1;32m █ \033[0m"; // Green for sorted
                else if (i == curr)
                    cout << "\033[1;31m █ \033[0m"; // Red for current
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
        if (i == curr )
            cout << "\033[1;31m" << setw(2) << arr[i] << "\033[0m ";
        else if (sortedIndices.count(i))
            cout << "\033[1;32m" << setw(2) << arr[i] << "\033[0m ";
        else
            cout << setw(2) << arr[i] << " ";
    }
    cout << '\n';

    cout << "\n";

    this_thread::sleep_for(chrono::milliseconds(10));
}

void gnomeSort(vector<int> &arr)
{
    int i = 0;
    unordered_set<int> sorted;
    while (i < arr.size())
    {
        printBars(arr, i, sorted);

        if (i == 0 || arr[i] >= arr[i - 1])
        {
            sorted.insert(i);
            i++;
        }
        else
        {
            swap(arr[i], arr[i - 1]);
            i--;
        }
    }

    // Final print with all green
    for (int i = 0; i < arr.size(); i++)
        sorted.insert(i);
    printBars(arr, -1, sorted);
}

int main()
{
    srand(time(0));
    vector<int> data;
    unordered_set<int> s;

    while (s.size() < 40)
        s.insert(rand() % 40 + 1); // unique values from 1 to 30

    data.assign(s.begin(), s.end());
    shuffle(data.begin(), data.end(), default_random_engine(time(0)));

    printBars(data);
    gnomeSort(data);

    return 0;
}
