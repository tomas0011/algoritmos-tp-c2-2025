#include "../../dataStructures/list/List.h"
#include <functional>

List merge(const List& left, const List& right, std::function<bool(const std::any&, const std::any&)> comparator) {
    List result;
    Node* leftCurrent = left.getHead();
    Node* rightCurrent = right.getHead();

    while (leftCurrent != nullptr && rightCurrent != nullptr) {
        if (comparator(leftCurrent->getData(), rightCurrent->getData())) {
            result.push(leftCurrent->getData());
            leftCurrent = leftCurrent->getNext();
        } else {
            result.push(rightCurrent->getData());
            rightCurrent = rightCurrent->getNext();
        }
    }

    // Add remaining elements from left list
    while (leftCurrent != nullptr) {
        result.push(leftCurrent->getData());
        leftCurrent = leftCurrent->getNext();
    }

    // Add remaining elements from right list
    while (rightCurrent != nullptr) {
        result.push(rightCurrent->getData());
        rightCurrent = rightCurrent->getNext();
    }

    return result;
}

List mergeSort(const List& list, std::function<bool(const std::any&, const std::any&)> comparator) {
    int size = list.getSize();
    if (size <= 1) {
        return list; // Already sorted or empty
    }

    int mid = size / 2;

    // Split the list into two halves
    List left = list.getSublist(0, mid);
    List right = list.getSublist(mid, size);

    // Recursively sort both halves
    left = mergeSort(left, comparator);
    right = mergeSort(right, comparator);

    // Merge the sorted halves
    return merge(left, right, comparator);
}