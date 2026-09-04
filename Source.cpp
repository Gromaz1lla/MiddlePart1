#include <iostream>
#include <vector>
#include <map>
#include <memory>
#include <algorithm>
#include <chrono>
#include <thread>
#include <string>

// класс с тяжёлым конструктором, чтобы показать эффект отложенного
// создания - конструктор занимает 2 секунды
class S {
public:
    std::string m{ "Message string." };

    S() {
        std::cout << "Construction started.\n";
        std::this_thread::sleep_for(std::chrono::seconds(2));
        std::cout << "Constructed.\n";
    }

    ~S() {
        std::cout << "Destroyed.\n";
    }
};

// контейнер, который выделяет память под все элементы сразу, но
// сам объект строится только тогда, когда к нему реально
// обращаются через get(). до этого момента память просто лежит
// неинициализированная
template <typename T>
class LazyContainer {
public:
    explicit LazyContainer(size_t n)
        : size_(n),
        storage_(static_cast<T*>(::operator new(n * sizeof(T)))),
        constructed_(n, false) {
    }

    ~LazyContainer() {
        for (size_t i = 0; i < size_; ++i) {
            if (constructed_[i]) {
                storage_[i].~T();
            }
        }
        ::operator delete(storage_);
    }

    T& get(size_t index) {
        if (!constructed_[index]) {
            new (storage_ + index) T();
            constructed_[index] = true;
        }
        return storage_[index];
    }

    bool is_constructed(size_t index) const {
        return constructed_[index];
    }

private:
    size_t size_;
    T* storage_;
    std::vector<bool> constructed_;
};

void demo_lazy_container() {
    std::cout << "=== lazy container ===" << std::endl;

    LazyContainer<S> container(5);

    std::cout << "container created, nothing built yet" << std::endl;

    // обращаемся только к элементу с индексом 2 - строится
    // только он, остальные четыре так и останутся нетронутыми
    std::cout << "accessing element 2..." << std::endl;
    std::cout << container.get(2).m << std::endl;

    std::cout << "element 0 constructed: " << container.is_constructed(0) << std::endl;
    std::cout << "element 2 constructed: " << container.is_constructed(2) << std::endl;

    std::cout << std::endl;
}

// сравнение элементов по стандартному less
template <typename It>
void sift_down(It first, size_t root, size_t heap_size) {
    while (true) {
        size_t left = 2 * root + 1;
        size_t right = 2 * root + 2;
        size_t largest = root;

        if (left < heap_size && *(first + left) > *(first + largest)) largest = left;
        if (right < heap_size && *(first + right) > *(first + largest)) largest = right;

        if (largest == root) break;

        std::swap(*(first + root), *(first + largest));
        root = largest;
    }
}

// собственная сортировка кучей - строим max-heap, потом по одному
// вытаскиваем максимум в конец
template <typename It>
void my_heap_sort(It first, It last) {
    size_t n = static_cast<size_t>(std::distance(first, last));

    for (size_t i = n / 2; i-- > 0; ) {
        sift_down(first, i, n);
    }

    for (size_t i = n - 1; i > 0; --i) {
        std::swap(*first, *(first + i));
        sift_down(first, 0, i);
    }
}

void demo_heap_sort() {
    std::cout << "=== custom heap sort ===" << std::endl;

    std::vector<int> data = { 9, 3, 7, 1, 8, 2, 5, 6, 4 };

    std::cout << "before: ";
    for (int x : data) std::cout << x << " ";
    std::cout << std::endl;

    my_heap_sort(data.begin(), data.end());

    std::cout << "after:  ";
    for (int x : data) std::cout << x << " ";
    std::cout << std::endl << std::endl;
}

// min/max, сравнение диапазонов, перестановки из <algorithm>
void demo_min_max_comparison_permutation() {
    std::cout << "=== min/max, comparison, permutation ===" << std::endl;

    std::vector<int> nums = { 4, 8, 1, 9, 3, 7 };

    auto min_it = std::min_element(nums.begin(), nums.end());
    auto max_it = std::max_element(nums.begin(), nums.end());
    auto minmax = std::minmax_element(nums.begin(), nums.end());

    std::cout << "min: " << *min_it << ", max: " << *max_it << std::endl;
    std::cout << "minmax_element: " << *minmax.first << " / " << *minmax.second << std::endl;

    std::vector<int> a = { 1, 2, 3 };
    std::vector<int> b = { 1, 2, 3 };
    std::vector<int> c = { 1, 2, 4 };

    std::cout << "equal(a, b): " << std::equal(a.begin(), a.end(), b.begin()) << std::endl;
    std::cout << "equal(a, c): " << std::equal(a.begin(), a.end(), c.begin()) << std::endl;

    std::cout << "lexicographical_compare(a, c): "
        << std::lexicographical_compare(a.begin(), a.end(), c.begin(), c.end()) << std::endl;

    // next_permutation перебирает перестановки в лексикографическом
    // порядке, пока не вернётся к отсортированному по убыванию виду
    std::vector<int> perm = { 1, 2, 3 };
    std::cout << "all permutations of {1, 2, 3}:" << std::endl;
    do {
        for (int x : perm) std::cout << x << " ";
        std::cout << std::endl;
    } while (std::next_permutation(perm.begin(), perm.end()));

    std::cout << std::endl;
}

// собственная проверка, являются ли два набора перестановками друг
// друга - через подсчёт частот каждого значения
template <typename T>
bool my_is_permutation(const std::vector<T>& a, const std::vector<T>& b) {
    if (a.size() != b.size()) return false;

    std::map<T, int> counts;
    for (const auto& x : a) counts[x]++;
    for (const auto& x : b) counts[x]--;

    for (const auto& pair : counts) {
        if (pair.second != 0) return false;
    }

    return true;
}

void demo_is_permutation() {
    std::cout << "=== custom is_permutation ===" << std::endl;

    std::vector<int> a = { 1, 2, 2, 3 };
    std::vector<int> b = { 3, 2, 1, 2 };
    std::vector<int> c = { 1, 2, 3, 3 };

    std::cout << "a and b are permutations: " << my_is_permutation(a, b) << std::endl;
    std::cout << "a and c are permutations: " << my_is_permutation(a, c) << std::endl;

    std::cout << std::endl;
}

int main() {
    demo_lazy_container();
    demo_heap_sort();
    demo_min_max_comparison_permutation();
    demo_is_permutation();

    return 0;
}