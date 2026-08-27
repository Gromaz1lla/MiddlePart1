#include <iostream>
#include <vector>
#include <array>
#include <unordered_map>
#include <algorithm>
#include <iterator>
#include <string>

// std::copy для указателей копирует просто адреса, а не сами данные -
// покажем это на примере, а потом сделаем нормальную глубокую копию
void demo_deep_copy() {
    std::cout << "=== copy with deep copying ===" << std::endl;

    std::vector<int*> original;
    original.push_back(new int(10));
    original.push_back(new int(20));
    original.push_back(new int(30));

    // тут просто копируются адреса
    std::vector<int*> shallow_copy(original.size());
    std::copy(original.begin(), original.end(), shallow_copy.begin());

    *original[0] = 999;

    std::cout << "after shallow copy and changing original[0]:" << std::endl;
    std::cout << "original[0] = " << *original[0] << std::endl;
    std::cout << "shallow_copy[0] = " << *shallow_copy[0]
        << "  (same address, so it changed too)" << std::endl;

    // а тут через transform выделяем новую память под каждое значение -
    // это и есть глубокая копия
    std::vector<int*> deep_copy(original.size());
    std::transform(original.begin(), original.end(), deep_copy.begin(),
        [](int* p) {
            return new int(*p);
        });

    *original[0] = -1;

    std::cout << "\nafter deep copy and changing original[0] again:" << std::endl;
    std::cout << "original[0] = " << *original[0] << std::endl;
    std::cout << "deep_copy[0] = " << *deep_copy[0]
        << "  (didn't change, separate memory)" << std::endl;

    // shallow_copy отдельно чистить не нужно - там те же адреса, что в original
    for (int* p : original) delete p;
    for (int* p : deep_copy) delete p;

    std::cout << std::endl;
}

// у unordered_map нет индексов как у vector, поэтому просто
// std::copy(src.begin(), src.end(), dst.begin()) не сработает -
// нужен inserter, чтобы элементы вставлялись через insert()
void demo_copy_unordered_map() {
    std::cout << "=== copy for std::unordered_map ===" << std::endl;

    std::unordered_map<std::string, int> source = {
        {"apple", 3},
        {"banana", 5},
        {"cherry", 7}
    };

    std::unordered_map<std::string, int> destination;

    std::copy(source.begin(), source.end(), std::inserter(destination, destination.begin()));

    std::cout << "destination contents after copy:" << std::endl;
    for (const auto& item : destination) {
        std::cout << item.first << " -> " << item.second << std::endl;
    }

    std::cout << std::endl;
}

void demo_fill() {
    std::cout << "=== fill for an array ===" << std::endl;

    int plain_array[5];
    std::fill(std::begin(plain_array), std::end(plain_array), 7);

    std::cout << "plain_array after fill(7): ";
    for (int x : plain_array) std::cout << x << " ";
    std::cout << std::endl;

    // std::array работает так же, только с ним безопаснее
    std::array<std::string, 3> names;
    std::fill(names.begin(), names.end(), "unknown");

    std::cout << "names after fill(\"unknown\"): ";
    for (const auto& name : names) std::cout << name << " ";
    std::cout << std::endl;

    std::cout << std::endl;
}

int main() {
    demo_deep_copy();
    demo_copy_unordered_map();
    demo_fill();

    return 0;
}