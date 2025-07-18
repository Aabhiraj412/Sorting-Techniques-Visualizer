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
    cout << "Patience Sort Visualization\n\n";

    int maxH = *max_element(arr.begin(), arr.end());
    for (int h = maxH; h >= 1; h--)
    {
        for (int i = 0; i < arr.size(); i++)
        {
            if (arr[i] >= h)
            {
                if (sortedIndices.count(i))
                    cout << "\033[1;32m █ \033[0m"; // Green
                else if (i == curr)
                    cout << "\033[1;31m █ \033[0m"; // Red
                else
                    cout << "\033[1;34m █ \033[0m"; // Blue
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
    for (int i = 0; i < arr.size(); i++)
        cout << setw(2) << i << " ";
    cout << "\n";

    for (int i = 0; i < arr.size(); i++)
    {
        if (i == curr)
            cout << "\033[1;31m" << setw(2) << arr[i] << "\033[0m ";
        else if (sortedIndices.count(i))
            cout << "\033[1;32m" << setw(2) << arr[i] << "\033[0m ";
        else
            cout << setw(2) << arr[i] << " ";
    }
    cout << '\n';

    this_thread::sleep_for(chrono::milliseconds(10));
}

void patienceSort(vector<int> &arr)
{
    vector<stack<int>> piles;
    unordered_set<int> sortedIndices;

    for (int i = 0; i < arr.size(); ++i)
    {
        int num = arr[i];
        auto it = lower_bound(piles.begin(), piles.end(), num,
                              [](const stack<int> &s, int value)
                              {
                                  return s.top() < value;
                              });

        if (it == piles.end())
        {
            stack<int> newPile;
            newPile.push(num);
            piles.push_back(newPile);
        }
        else
        {
            it->push(num);
        }

        printBars(arr, i, sortedIndices);
    }

    // Merge piles into sorted array using min heap
    struct HeapNode
    {
        int value;
        int pileIndex;
    };

    auto comp = [](const HeapNode &a, const HeapNode &b)
    {
        return a.value > b.value;
    };

    priority_queue<HeapNode, vector<HeapNode>, decltype(comp)> minHeap(comp);

    for (int i = 0; i < piles.size(); ++i)
    {
        if (!piles[i].empty())
        {
            minHeap.push({piles[i].top(), i});
        }
    }

    int index = 0;
    while (!minHeap.empty())
    {
        HeapNode node = minHeap.top();
        minHeap.pop();

        arr[index] = node.value;
        piles[node.pileIndex].pop(); // Pop after using the value
        sortedIndices.insert(index);
        printBars(arr, index, sortedIndices);
        ++index;

        if (!piles[node.pileIndex].empty())
        {
            minHeap.push({piles[node.pileIndex].top(), node.pileIndex});
        }
    }
}

int main()
{
    srand(time(0));
    unordered_set<int> s;
    while (s.size() < 40)
        s.insert(rand() % 40 + 1);

    vector<int> data(s.begin(), s.end());
    shuffle(data.begin(), data.end(), default_random_engine(time(0)));

    printBars(data);
    patienceSort(data);
    
    // Create sortedIndices for final display (all indices are now sorted)
    unordered_set<int> allSorted;
    for (int i = 0; i < data.size(); i++) {
        allSorted.insert(i);
    }
    printBars(data, -1, allSorted);

    return 0;
}
