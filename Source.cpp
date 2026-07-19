#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

// Свой константный forward-итератор для std::vector<T>.
// По сути просто оборачивает указатель на элемент вектора,
// но делает это так, чтобы удовлетворять требованиям LegacyForwardIterator:
// - можно создать без параметров (default constructible)
// - можно копировать
// - можно сравнивать на равенство (== и !=)
// - можно разыменовывать (* и ->)
// - можно двигать вперёд (++it и it++)
// - несколько независимых итераторов могут одновременно проходить контейнер
//   и не мешать друг другу (multipass guarantee) - у нас это выполняется
//   само собой, потому что итератор просто хранит указатель

template <typename T>
class ConstVectorIterator {
public:
    // эти псевдонимы нужны, чтобы итератор дружил со стандартными
    // алгоритмами вроде std::find, std::distance и т.д.
    using iterator_category = std::forward_iterator_tag;
    using value_type = T;
    using difference_type = std::ptrdiff_t;
    using pointer = const T*;
    using reference = const T&;

    // обязателен для ForwardIterator
    ConstVectorIterator() : ptr_(nullptr) {}

    explicit ConstVectorIterator(const T* ptr) : ptr_(ptr) {}

    // разыменование - возвращаем ссылку на элемент, менять его нельзя,
    // поэтому и reference, и pointer у нас const
    reference operator*() const {
        return *ptr_;
    }

    pointer operator->() const {
        return ptr_;
    }

    // префиксный инкремент
    ConstVectorIterator& operator++() {
        ++ptr_;
        return *this;
    }

    // постфиксный инкремент - обязателен по стандарту для forward-итератора,
    // делаем копию до изменения и возвращаем её
    ConstVectorIterator operator++(int) {
        ConstVectorIterator tmp = *this;
        ++ptr_;
        return tmp;
    }

    bool operator==(const ConstVectorIterator& other) const {
        return ptr_ == other.ptr_;
    }

    bool operator!=(const ConstVectorIterator& other) const {
        return ptr_ != other.ptr_;
    }

private:
    const T* ptr_;
};

// пара удобных функций, чтобы получать наш итератор от обычного вектора,
// сам std::vector трогать/наследовать не нужно
template <typename T>
ConstVectorIterator<T> const_begin(const std::vector<T>& v) {
    return ConstVectorIterator<T>(v.data());
}

template <typename T>
ConstVectorIterator<T> const_end(const std::vector<T>& v) {
    return ConstVectorIterator<T>(v.data() + v.size());
}

int main() {
    std::vector<int> nums = { 10, 20, 30, 40, 50 };

    // проход по вектору вручную через наш итератор
    std::cout << "manual iteration:" << std::endl;
    for (ConstVectorIterator<int> it = const_begin(nums); it != const_end(nums); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    // проверяем, что итератор реально совместим со стандартными алгоритмами -
    // если LegacyForwardIterator реализован правильно, std::find просто отработает
    auto found = std::find(const_begin(nums), const_end(nums), 30);
    if (found != const_end(nums)) {
        std::cout << "found value: " << *found << std::endl;
    }
    else {
        std::cout << "value not found" << std::endl;
    }

    // multipass guarantee - два независимых итератора идут по одному
    // и тому же контейнеру и не влияют друг на друга
    ConstVectorIterator<int> it1 = const_begin(nums);
    ConstVectorIterator<int> it2 = it1;
    ++it2;
    std::cout << "it1 points to " << *it1 << ", it2 points to " << *it2 << std::endl;

    return 0;
}