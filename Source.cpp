#include <iostream>
#include <string>
#include <vector>

class HashTable {
private:
    static const int TABLE_SIZE = 100;
    std::string table[TABLE_SIZE];

    // полиномиальный хеш строки
    long long get_base_hash(const std::string& s) const {
        const int p = 31;
        long long hash_value = 0;
        long long p_pow = 1;
        for (char c : s) {
            hash_value += (c - ' ' + 1) * p_pow;
            p_pow *= p;
        }
        if (hash_value < 0) {
            hash_value = -hash_value;
        }
        return hash_value;
    }

public:
    HashTable() {
        for (int i = 0; i < TABLE_SIZE; i++) {
            table[i] = "";
        }
    }

    // открытая адресация, линейное пробирование
    int get_hash_index(const std::string& key, int attempt) const {
        long long base_hash = get_base_hash(key);
        return (base_hash + attempt) % TABLE_SIZE;
    }

    void add(const std::string& key) {
        for (int i = 0; i < TABLE_SIZE; i++) {
            int index = get_hash_index(key, i);

            if (table[index] == "") {
                table[index] = key;
                std::cout << key << " -> index " << index << " (attempt " << i << ")" << std::endl;
                return;
            }
        }
        std::cout << "table is full, nowhere to insert" << std::endl;
    }

    // просто чтобы глазами посмотреть, что получилось
    void print() const {
        for (int i = 0; i < TABLE_SIZE; i++) {
            if (table[i] != "") {
                std::cout << "[" << i << "] " << table[i] << std::endl;
            }
        }
    }
};

int main() {
    HashTable ht;

    ht.add("hello");
    ht.add("world");
    ht.add("skillbox");

    // проверка коллизий на похожих строках
    ht.add("abc");
    ht.add("acb");

    std::cout << "\ntable contents:" << std::endl;
    ht.print();

    return 0;
}