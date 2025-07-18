#include <bits/stdc++.h>
#include <unistd.h>
using namespace std;

void printBars(const vector<int> &arr, unordered_set<int> sortedIndices = {}, int cur = -1)
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif

    static int steps = 0;
    cout<< "Step: " << steps++ << "\n";
    cout << "Pigeonhole Sort Visualization\n\n";

    int maxH = *max_element(arr.begin(), arr.end());

    for (int h = maxH; h >= 1; h--)
    {
        for (int i = 0; i < arr.size(); i++)
        {
            if (arr[i] >= h)
            {
                if (sortedIndices.count(i))
                    cout << "\033[1;32m █ \033[0m"; // Green
                else if (i == cur)
                    cout << "\033[1;31m █ \033[0m"; // Red
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

    for (int x : arr)
        cout << setw(2) << x << " ";
    cout << "\n";

    for (int i = 0; i < arr.size(); i++)
    {
        if (i == cur)
            cout << "\033[1;31m" << setw(2) << arr[i] << "\033[0m ";
        else if (sortedIndices.count(i))
            cout << "\033[1;32m" << setw(2) << arr[i] << "\033[0m ";
        else
            cout << setw(2) << arr[i] << " ";
    }
    cout << '\n';

    this_thread::sleep_for(chrono::milliseconds(10));
}

void pigeonholeSort(vector<int> &arr)
{
    int n = arr.size();
    if (n <= 1)
        return;

    int minVal = *min_element(arr.begin(), arr.end());
    int maxVal = *max_element(arr.begin(), arr.end());
    int range = maxVal - minVal + 1;

    vector<vector<int>> holes(range);

    for (int i = 0; i < n; ++i)
    {
        holes[arr[i] - minVal].push_back(arr[i]);
        printBars(arr, {}, i);
    }

    int index = 0;
    unordered_set<int> sorted;
    for (int i = 0; i < range; ++i)
    {
        for (int val : holes[i])
        {
            arr[index] = val;
            sorted.insert(index);
            printBars(arr, sorted, index);
            ++index;
        }
    }
}

int main()
{
    srand(time(0));
    vector<int> data;
    unordered_set<int> s;

    while (s.size() < 40)
        s.insert(rand() % 40 + 1); // Unique values between 1–30

    data.assign(s.begin(), s.end());
    shuffle(data.begin(), data.end(), default_random_engine(time(0)));

    printBars(data);
    pigeonholeSort(data);
    
    printBars(data,s);

    return 0;
}
