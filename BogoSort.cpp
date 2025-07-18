#include <bits/stdc++.h>
#include <unistd.h>
using namespace std;

void printBars(const vector<int> &arr, int attempt = -1, bool sorted = false)
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif

    cout << "Bogo Sort Visualization | Attempt: " << attempt << "\n\n";

    int maxH = *max_element(arr.begin(), arr.end());

    for (int h = maxH; h >= 1; h--)
    {
        for (int i = 0; i < arr.size(); i++)
        {
            if (arr[i] >= h)
            {
                if (sorted)
                    cout << "\033[1;32m █ \033[0m"; // Green
                else
                    cout << "\033[1;31m █ \033[0m"; // Red
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

    for (int x : arr)
        cout << setw(2) << x << " ";
    cout << "\n";

    this_thread::sleep_for(chrono::milliseconds(10));
}

bool isSorted(const vector<int> &arr)
{
    for (int i = 1; i < arr.size(); i++)
        if (arr[i - 1] > arr[i])
            return false;
    return true;
}

void bogoSort(vector<int> &arr)
{
    int attempts = 0;
    while (!isSorted(arr))
    {
        printBars(arr, ++attempts);
        shuffle(arr.begin(), arr.end(), default_random_engine(time(0)));
    }
    printBars(arr, ++attempts, true);
}

int main()
{
    srand(time(0));
    vector<int> data;

    // SMALL size only (e.g. 6 elements)
    unordered_set<int> s;
    while (s.size() < 4)
        s.insert(rand() % 4 + 1);

    data.assign(s.begin(), s.end());
    shuffle(data.begin(), data.end(), default_random_engine(time(0)));

    printBars(data, 0);
    bogoSort(data);

    cout << "\n🎉 Finally sorted in " << data.size() << "! Long live Bogo Sort!\n";
    return 0;
}
