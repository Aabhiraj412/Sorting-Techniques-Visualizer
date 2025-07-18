#include <bits/stdc++.h>
#include <unistd.h>
using namespace std;

void printBars(const vector<int> &arr, int l = -1, int r = -1, unordered_set<int> sorted = {})
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif

    static int step = 0;
    cout << "Step: " << step++ << "\n";
    cout << "Tim Sort Visualization\n\n";

    int maxH = *max_element(arr.begin(), arr.end());

    for (int h = maxH; h >= 1; h--)
    {
        for (int i = 0; i < arr.size(); i++)
        {
            if (arr[i] >= h)
            {
                if (i >= l && i <= r)
                    cout << "\033[1;31m █ \033[0m"; // red: active merge
                else if (sorted.count(i))
                    cout << "\033[1;32m █ \033[0m"; // green: sorted
                else
                    cout << "\033[1;34m █ \033[0m"; // blue: unsorted
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
        cout << setw(2) << arr[i] << " ";
    cout << "\n";

    for (int i = 0; i < arr.size(); i++)
    {
        if (i == l || i == r)
            cout << "\033[1;31m" << setw(2) << arr[i] << "\033[0m ";
        else if (sorted.count(i))
            cout << "\033[1;32m" << setw(2) << arr[i] << "\033[0m ";
        else
            cout << setw(2) << arr[i] << " ";
    }
    cout << '\n';

    this_thread::sleep_for(chrono::milliseconds(10));
}

const int RUN = 32;

void insertionSort(vector<int> &arr, int left, int right, unordered_set<int> &sorted)
{
    for (int i = left + 1; i <= right; i++)
    {
        int temp = arr[i];
        int j = i - 1;
        while (j >= left && arr[j] > temp)
        {
            printBars(arr, j, j + 1, sorted);
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = temp;
        printBars(arr, j + 1, i, sorted);
    }
}

void merge(vector<int> &arr, int l, int m, int r, unordered_set<int> &sorted)
{
    int len1 = m - l + 1, len2 = r - m;
    vector<int> left(arr.begin() + l, arr.begin() + m + 1);
    vector<int> right(arr.begin() + m + 1, arr.begin() + r + 1);

    int i = 0, j = 0, k = l;

    while (i < len1 && j < len2)
    {
        if (left[i] <= right[j])
            arr[k++] = left[i++];
        else
            arr[k++] = right[j++];
        printBars(arr, l, r, sorted);
    }

    while (i < len1)
    {
        arr[k++] = left[i++];
        printBars(arr, l, r, sorted);
    }

    while (j < len2)
    {
        arr[k++] = right[j++];
        printBars(arr, l, r, sorted);
    }
}

void timSort(vector<int> &arr)
{
    int n = arr.size();
    unordered_set<int> sorted;

    for (int i = 0; i < n; i += RUN)
    {
        insertionSort(arr, i, min((i + RUN - 1), (n - 1)), sorted);
    }

    for (int size = RUN; size < n; size = 2 * size)
    {
        for (int left = 0; left < n; left += 2 * size)
        {
            int mid = left + size - 1;
            int right = min((left + 2 * size - 1), (n - 1));

            if (mid < right)
                merge(arr, left, mid, right, sorted);
        }
    }

    for (int i = 0; i < n; ++i)
        sorted.insert(i);

    printBars(arr, -1, -1, sorted);
}

int main()
{
    srand(time(0));
    vector<int> data;
    unordered_set<int> s;
    while (s.size() < 40)
        s.insert(rand() % 40 + 1);

    data.assign(s.begin(), s.end());
    shuffle(data.begin(), data.end(), default_random_engine(time(0)));

    printBars(data, 0);
    timSort(data);

    return 0;
}
