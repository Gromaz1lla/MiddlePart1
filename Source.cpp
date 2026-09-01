#include <iostream>
#include <array>
#include <set>
#include <algorithm>
#include <vector>

void print_array(const std::array<int, 10>& arr, const std::string& label) {
    std::cout << label << ": ";
    for (int x : arr) std::cout << x << " ";
    std::cout << std::endl;
}

// заполняем массив через generate, потом берём из него 5 самых
// маленьких элементов сразу в отсортированном виде через
// partial_sort_copy - не нужно сортировать весь массив целиком
void demo_partial_sort_copy() {
    std::cout << "=== partial_sort_copy ===" << std::endl;

    std::array<int, 10> source;
    int counter = 50;
    std::generate(source.begin(), source.end(), [&counter]() {
        counter -= 3;
        return counter;
        });

    print_array(source, "source");

    std::array<int, 5> smallest;
    std::partial_sort_copy(source.begin(), source.end(), smallest.begin(), smallest.end());

    std::cout << "5 smallest sorted: ";
    for (int x : smallest) std::cout << x << " ";
    std::cout << std::endl << std::endl;
}

// lower_bound и upper_bound работают на отсортированном диапазоне
// и делают бинарный поиск. lower_bound находит первый элемент,
// который не меньше искомого значения. upper_bound находит первый
// элемент, который строго больше искомого
void demo_lower_upper_bound() {
    std::cout << "=== lower_bound / upper_bound ===" << std::endl;

    std::array<int, 10> nums = { 1, 3, 3, 5, 7, 7, 7, 9, 10, 12 };
    print_array(nums, "array");

    int target = 7;

    auto lb = std::lower_bound(nums.begin(), nums.end(), target);
    auto ub = std::upper_bound(nums.begin(), nums.end(), target);

    std::cout << "lower_bound(" << target << ") points to index "
        << std::distance(nums.begin(), lb) << ", value " << *lb << std::endl;
    std::cout << "upper_bound(" << target << ") points to index "
        << std::distance(nums.begin(), ub) << ", value " << *ub << std::endl;
    std::cout << "count of " << target << " in array: " << std::distance(lb, ub) << std::endl;

    // то же самое, но для set - у set есть свои собственные
    // методы lower_bound / upper_bound, они работают быстрее,
    // чем std::lower_bound на итераторах set, потому что
    // используют внутреннюю структуру дерева, а не линейный бинарный поиск
    std::set<int> nums_set(nums.begin(), nums.end());

    auto set_lb = nums_set.lower_bound(target);
    auto set_ub = nums_set.upper_bound(target);

    std::cout << "set::lower_bound(" << target << ") = " << *set_lb << std::endl;
    std::cout << "set::upper_bound(" << target << ") = " << *set_ub << std::endl;

    std::cout << std::endl;
}

// includes проверяет, содержит ли одно отсортированное множество
// все элементы другого. set_difference находит элементы, которые
// есть в первом множестве, но отсутствуют во втором
void demo_includes_set_difference() {
    std::cout << "=== includes / set_difference ===" << std::endl;

    std::set<int> big_set = { 1, 2, 3, 4, 5, 6, 7, 8 };
    std::set<int> small_set = { 3, 5, 7 };
    std::set<int> not_included = { 3, 5, 100 };

    bool result1 = std::includes(big_set.begin(), big_set.end(), small_set.begin(), small_set.end());
    bool result2 = std::includes(big_set.begin(), big_set.end(), not_included.begin(), not_included.end());

    std::cout << "big_set includes small_set: " << (result1 ? "yes" : "no") << std::endl;
    std::cout << "big_set includes not_included: " << (result2 ? "yes" : "no") << std::endl;

    std::vector<int> difference;
    std::set_difference(big_set.begin(), big_set.end(), small_set.begin(), small_set.end(),
        std::back_inserter(difference));

    std::cout << "elements in big_set but not in small_set: ";
    for (int x : difference) std::cout << x << " ";
    std::cout << std::endl << std::endl;
}

int main() {
    demo_partial_sort_copy();
    demo_lower_upper_bound();
    demo_includes_set_difference();

    return 0;
}