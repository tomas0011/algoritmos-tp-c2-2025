#ifndef MERGE_SORT_H
#define MERGE_SORT_H

#include "../../dataStructures/list/List.h"
#include <functional>

List merge(const List& left, const List& right, std::function<bool(const std::any&, const std::any&)> comparator);
List mergeSort(const List& list, std::function<bool(const std::any&, const std::any&)> comparator);

#endif
