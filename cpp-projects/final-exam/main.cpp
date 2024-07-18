#include <list>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

template <typename T>
class Spisok
{
private:
    list<T> spisok;

public:
    Spisok() = default;
    Spisok(initializer_list<T> _spisok)
    {
        for (const auto &el : _spisok)
        {
            spisok.push_back(el);
        }
    };

    void printSpisok()
    {
        for (const auto &el : spisok)
        {
            cout << el << " ";
        }
        cout << endl;
    }

    void pushBack(const T &value)
    {
        spisok.push_back(value);
    }
    void takeFront()
    {
        spisok.pop_front();
    }

    void takeBack()
    {
        spisok.pop_back();
    }

    void sort()
    {
        spisok.sort([](const string &a, const string &b)
                    { return a.length() > b.length(); });
    }

    void merge(const Spisok<T> &other)
    {
        spisok.insert(spisok.end(), other.spisok.begin(), other.spisok.end());
    }
};

template <typename T>
Spisok<T> mergeSpisok(list<Spisok<T>> &listToMerge)
{
    Spisok<T> mergedList;

    for (const auto &list : listToMerge)
    {
        mergedList.merge(list);
    }

    return mergedList;
}

int main()
{
    Spisok<int> list11 = {1, 2, 3};
    Spisok<int> list22 = {4, 7, 23};

    Spisok<string> list1 = {"apple", "banana", "corn", "potato"};
    Spisok<string> list2 = {"orange", "broccoli"};

    list<Spisok<string>> listOfList = {list1, list2};

    Spisok<string> newList = mergeSpisok(listOfList);

    cout << "Start lists: " << endl
         << endl;

    list1.printSpisok();
    list2.printSpisok();
    list11.printSpisok();
    list22.printSpisok();

    cout << endl;
    cout << "Merged list: " << endl
         << endl;

    newList.printSpisok();

    // Sotring
    list1.sort();
    list2.sort();

    newList.sort();

    cout << endl;
    cout << "Sorted lists: " << endl
         << endl;

    list1.printSpisok();
    list2.printSpisok();

    cout << endl;
    cout << "Sorted merged list: " << endl
         << endl;

    newList.printSpisok();

    return 0;
}
