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
    cout << "MergeSort Visualization\n\n";

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

    this_thread::sleep_for(chrono::milliseconds(500));
}

void merge(vector<int> &arr, int left,
           int mid, int right)
{

    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<int> L(n1), R(n2);

    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int i = 0, j = 0;
    int k = left;

    unordered_set<int> sorted;
    for (int idx = left; idx <= right; idx++)
        sorted.insert(idx);

    while (i < n1 && j < n2)
    {
        printVerticalBars(arr, i+left, j+mid+1, sorted);
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1)
    {
        printVerticalBars(arr, k, k+1, sorted);
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2)
    {
        printVerticalBars(arr, k, k + 1, sorted);
        arr[k] = R[j];
        j++;
        k++;
    }
    printVerticalBars(arr, -1, -1, sorted);
}

void mergeSort(vector<int> &arr, int left, int right)
{

    if (left >= right)
        return;

    int mid = left + (right - left) / 2;
    mergeSort(arr, left, mid);
    mergeSort(arr, mid + 1, right);
    merge(arr, left, mid, right);

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

    mergeSort(data, 0, data.size() - 1);
    return 0;
}
