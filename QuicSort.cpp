#include <bits/stdc++.h>
#include <unistd.h>
using namespace std;

void printVerticalBars(const vector<int> &arr, int cur = -1, int next = -1, int pivot = -1, unordered_set<int> sorted = {})
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif

    static int step = 0;
    cout << "Step: " << step++ << "\n";
    cout << "QuickSort Visualization\n\n";
    cout << "Legend: \033[1;31mRED\033[0m = Comparing | \033[1;33mYELLOW\033[0m = Pivot | \033[1;32mGREEN\033[0m = Sorted | \033[1;34mBLUE\033[0m = Unsorted\n\n";

    int maxHeight = *max_element(arr.begin(), arr.end());

    for (int level = maxHeight; level >= 1; level--)
    {
        for (int i = 0; i < arr.size(); i++)
        {
            if (arr[i] >= level)
            {
                if (i == cur || i == next)
                    cout << "\033[1;31m █ \033[0m";
                else if (i == pivot)
                    cout << "\033[1;33m █ \033[0m"; // Yellow for pivot
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
int partition(vector<int> &vec, int low, int high)
{
    int pivot = vec[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++)
    {
        printVerticalBars(vec, j, high, pivot); // Only visualize current and pivot

        if (vec[j] <= pivot)
        {
            i++;
            swap(vec[i], vec[j]);
        }

        printVerticalBars(vec, i, j, pivot); // After possible swap
    }

    swap(vec[i + 1], vec[high]);         // Place pivot at right position
    printVerticalBars(vec, i + 1, high, pivot); // Show final placement

    return (i + 1); // Pivot's sorted position
}

void quickSort(vector<int> &vec, int low, int high, unordered_set<int> &sorted)
{
    if (low < high)
    {
        int pi = partition(vec, low, high);
        sorted.insert(pi);                      // Pivot is now at correct position
        printVerticalBars(vec, -1, -1, pi, sorted); // Optional visual after each pivot

        quickSort(vec, low, pi - 1, sorted);
        quickSort(vec, pi + 1, high, sorted);
    }
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

    unordered_set<int> sorted;
    quickSort(data, 0, data.size() - 1, sorted);

    for (int i = 0; i < data.size(); ++i)
        sorted.insert(i);
    printVerticalBars(data, -1, -1, -1, sorted);

    return 0;
}
