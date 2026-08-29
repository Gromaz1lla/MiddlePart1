#include <iostream>
#include <list>
#include <algorithm>

void print_list(const std::list<int>& lst, const std::string& label) {
    std::cout << label << ": ";
    for (int x : lst) std::cout << x << " ";
    std::cout << std::endl;
}

// generate заполняет список значениями, которые возвращает переданная
// функция - вызывается по разу на каждый элемент
void demo_generate() {
    std::cout << "=== generate ===" << std::endl;

    std::list<int> numbers(10);

    // счётчик снаружи лямбды, чтобы каждый раз возвращать следующее число
    int counter = 1;
    std::generate(numbers.begin(), numbers.end(), [&counter]() {
        return counter++;
        });

    print_list(numbers, "generated");
    std::cout << std::endl;
}

// transform применяет функцию к каждому элементу и кладёт результат
// обратно в тот же список (если передать begin исходного как выходной
// итератор)
void demo_transform() {
    std::cout << "=== transform ===" << std::endl;

    std::list<int> numbers = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    print_list(numbers, "before");

    std::transform(numbers.begin(), numbers.end(), numbers.begin(), [](int x) {
        return x * x;
        });

    print_list(numbers, "after (squared)");
    std::cout << std::endl;
}

// remove_if не удаляет элементы по-настоящему - он просто перемещает
// нужные элементы в начало списка и возвращает итератор на новую
// логическую границу, а размер контейнера остаётся прежним.
// чтобы реально убрать хвост - нужно ещё вызвать erase (erase-remove idiom)
void demo_remove() {
    std::cout << "=== remove (filter > 3) ===" << std::endl;

    std::list<int> numbers = { 5, 2, 8, 1, 3, 9, 4, 3, 7, 6 };
    print_list(numbers, "before");

    auto new_end = std::remove_if(numbers.begin(), numbers.end(), [](int x) {
        return x > 3;
        });

    std::cout << "size right after remove_if: " << numbers.size()
        << " (size hasn't changed yet)" << std::endl;

    numbers.erase(new_end, numbers.end());

    print_list(numbers, "after erase (only <= 3 left)");
    std::cout << "size after erase: " << numbers.size() << std::endl;

    std::cout << std::endl;
}

int main() {
    demo_generate();
    demo_transform();
    demo_remove();

    return 0;
}