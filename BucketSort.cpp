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
    cout << "Bucket Sort Visualization\n\n";

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

void bucketSort(vector<int> &arr, int bucketCount = 10)
{
    int n = arr.size();
    if (n <= 0)
        return;

    int maxVal = *max_element(arr.begin(), arr.end());
    int minVal = *min_element(arr.begin(), arr.end());
    int range = (maxVal - minVal + 1);

    // Create empty buckets
    vector<vector<int>> buckets(bucketCount);

    // Step 1: Distribute input into buckets
    for (int i = 0; i < n; ++i)
    {
        int idx = (arr[i] - minVal) * bucketCount / range;
        if (idx == bucketCount)
            idx--; // Clamp index
        buckets[idx].push_back(arr[i]);
    }

    // Step 2: Sort each bucket
    for (int i = 0; i < bucketCount; ++i)
    {
        sort(buckets[i].begin(), buckets[i].end());
    }

    // Step 3: Merge buckets back to original array
    int index = 0;
    unordered_set<int> sortedSet;
    for (int i = 0; i < bucketCount; ++i)
    {
        for (int val : buckets[i])
        {
            arr[index] = val;
            sortedSet.insert(index);
            printVerticalBars(arr, index);
            index++;
        }
    }
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
    bucketSort(data);

    // Final state
    unordered_set<int> sortedIndexes;
    for (int i = 0; i < data.size(); ++i)
        sortedIndexes.insert(i);
    printVerticalBars(data, -1, -1, sortedIndexes);

    return 0;
}
