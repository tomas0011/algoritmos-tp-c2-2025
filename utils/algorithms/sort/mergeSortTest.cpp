#include "../../dataStructures/list/List.h"
#include "mergeSort.cpp"
#include <string>
#include <iostream>
using namespace std;

// Test: cd utils/algorithms/sort && g++ mergeSortTest.cpp -o mergeSortTest && ./mergeSortTest

int main() {
    List intList;
    intList.push(64);
    intList.push(34);
    intList.push(25);
    intList.push(12);
    intList.push(22);
    intList.push(11);
    intList.push(90);

    cout << "\nLista de enteros original:" << endl;
    intList.display();

    auto intComparator = [](const any& a, const any& b) -> bool {
        return any_cast<int>(a) < any_cast<int>(b);
    };

    List sortedIntList = mergeSort(intList, intComparator);
    cout << "Lista de enteros ordenada:" << endl;
    sortedIntList.display();

    // Test merge sort with strings
    List stringList;
    stringList.push(string("zebra"));
    stringList.push(string("apple"));
    stringList.push(string("banana"));
    stringList.push(string("cherry"));

    cout << "\nLista de strings original:" << endl;
    stringList.display();

    auto stringComparator = [](const any& a, const any& b) -> bool {
        return any_cast<string>(a) < any_cast<string>(b);
    };

    List sortedStringList = mergeSort(stringList, stringComparator);
    cout << "Lista de strings ordenada:" << endl;
    sortedStringList.display();

    return 0;
}
