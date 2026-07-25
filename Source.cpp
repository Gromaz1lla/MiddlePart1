#include <iostream>
#include <map>
#include <unordered_map>
#include <set>
#include <algorithm>
#include <string>

// 1. find для std::map
// 
// у map есть свой собственный метод find() (он быстрее, чем
// std::find, потому что использует внутреннее дерево, а не
// линейный перебор), но задание именно про алгоритм из <algorithm>,
// поэтому покажем оба варианта и сравним
void demo_find_map() {
    std::cout << "=== find for std::map ===" << std::endl;

    // список студентов и их баллов за практику
    std::map<std::string, int> scores = {
        {"Ivanov", 85},
        {"Petrov", 92},
        {"Sidorov", 67},
        {"Kuznetsov", 78}
    };

    // std::find из <algorithm> проходит по всем парам {ключ, значение}
    // по очереди, поэтому его нужно сравнивать с целой парой, а не
    // просто с ключом. Тип элемента у map - это pair<const Key, Value>,
    // поэтому и сравнивать нужно именно с таким типом (через make_pair
    // тип получается немного другим, поэтому создаём пару напрямую)
    std::pair<const std::string, int> target("Sidorov", 67);
    auto it = std::find(scores.begin(), scores.end(), target);

    if (it != scores.end()) {
        std::cout << "std::find result: " << it->first << " -> " << it->second << std::endl;
    }
    else {
        std::cout << "std::find found nothing" << std::endl;
    }

    auto it2 = scores.find("Petrov");
    if (it2 != scores.end()) {
        std::cout << "map::find result: " << it2->first << " -> " << it2->second << std::endl;
    }

    std::cout << std::endl;
}

//
// 2. count_if для std::unordered_map
//
void demo_count_if_unordered_map() {
    std::cout << "=== count_if for std::unordered_map ===" << std::endl;

    // остатки товаров на складе: название -> количество
    std::unordered_map<std::string, int> stock = {
        {"apples", 15},
        {"bananas", 0},
        {"oranges", 8},
        {"pears", 0},
        {"grapes", 23}
    };

    // считаем, сколько товаров закончилось на складе (количество == 0)
    int out_of_stock = std::count_if(stock.begin(), stock.end(),
        [](const std::pair<const std::string, int>& item) {
            return item.second == 0;
        });

    std::cout << "items out of stock: " << out_of_stock << std::endl;

    // и второй пример - сколько товаров больше 10 штук
    int well_stocked = std::count_if(stock.begin(), stock.end(),
        [](const auto& item) {
            return item.second > 10;
        });

    std::cout << "items with more than 10 in stock: " << well_stocked << std::endl;

    std::cout << std::endl;
}

//
// 3. for_each для std::set
//
void demo_for_each_set() {
    std::cout << "=== for_each for std::set ===" << std::endl;

    // set хранит только уникальные значения, автоматически отсортированные
    std::set<int> ids = { 42, 7, 15, 23, 7, 42, 1 };

    std::cout << "all elements: ";
    std::for_each(ids.begin(), ids.end(), [](int id) {
        std::cout << id << " ";
        });
    std::cout << std::endl;

    // for_each можно использовать не только для печати, но и чтобы
    // что-то накопить снаружи лямбды (через захват по ссылке)
    int sum = 0;
    std::for_each(ids.begin(), ids.end(), [&sum](int id) {
        sum += id;
        });

    std::cout << "sum of all elements: " << sum << std::endl;

    std::cout << std::endl;
}

int main() {
    demo_find_map();
    demo_count_if_unordered_map();
    demo_for_each_set();

    return 0;
}