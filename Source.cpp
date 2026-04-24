#include <iostream>

class MyStore {
public:
    int** data;
    int rows, cols;
    int* id;
    double* scale;

    MyStore(int r, int c, int val, double s) {
        rows = r;
        cols = c;
        data = new int* [rows];
        for (int i = 0; i < rows; i++) {
            data[i] = new int[cols];
            for (int j = 0; j < cols; j++) {
                data[i][j] = 0;
            }
        }
        id = new int(val);
        scale = new double(s);
    }

    MyStore(const MyStore& other) {
        rows = other.rows;
        cols = other.cols;
        data = new int* [rows];
        for (int i = 0; i < rows; i++) {
            data[i] = new int[cols];
            for (int j = 0; j < cols; j++) {
                data[i][j] = other.data[i][j];
            }
        }
        id = new int(*other.id);
        scale = new double(*other.scale);
    }

    ~MyStore() {
        for (int i = 0; i < rows; i++) {
            delete[] data[i];
        }
        delete[] data;
        delete id;
        delete scale;
    }

    void print() {
        std::cout << "ID: " << *id << " | Scale: " << *scale << std::endl;
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                std::cout << data[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }
};

int main() {
    int r, c;
    std::cin >> r >> c;

    MyStore obj1(r, c, 100, 1.5);
    obj1.data[0][0] = 77;

    MyStore obj2 = obj1;

    obj1.data[0][0] = 999;
    *obj1.id = 555;

    std::cout << "Object 1:" << std::endl;
    obj1.print();

    std::cout << "Object 2:" << std::endl;
    obj2.print();

    return 0;
}