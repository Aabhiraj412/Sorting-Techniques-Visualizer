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
    cout << "Counting Sort Visualization\n\n";

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

    // Baseline
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

void countSort(vector<int> &arr)
{
    int n = arr.size();
    int maxVal = *max_element(arr.begin(), arr.end());

    vector<int> count(maxVal + 1, 0);

    // Step 1: Count occurrences
    for (int num : arr)
    {
        count[num]++;
    }

    // Step 2: Rebuild the array and visualize
    int index = 0;
    unordered_set<int> sortedSet;

    for (int i = 0; i <= maxVal; i++)
    {
        while (count[i]--)
        {
            arr[index] = i;
            sortedSet.insert(index);
            printVerticalBars(arr, index); // Visualize after each placement
            index++;
        }
    }
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
    countSort(data);

    // Final state
    unordered_set<int> sortedIndexes;
    for (int i = 0; i < data.size(); ++i)
        sortedIndexes.insert(i);
    printVerticalBars(data, -1, -1, sortedIndexes);

    return 0;
}
