#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include <limits>

void fillBinaryFile(const std::string& filename, int numElements) {
    std::ofstream outFile(filename, std::ios::binary);
    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution(0, 100);

    for (int i = 0; i < numElements; ++i) {
        int randomValue = distribution(generator);
        outFile.write(reinterpret_cast<char*>(&randomValue), sizeof(int));
    }

    outFile.close();
}

std::vector<int> readBinaryFile(const std::string& filename) {
    std::ifstream inFile(filename, std::ios::binary);
    std::vector<int> data;
    int value;

    while (inFile.read(reinterpret_cast<char*>(&value), sizeof(int))) {
        data.push_back(value);
    }

    inFile.close();
    return data;
}

void fillMatrix(std::vector<std::vector<int>>& matrix, const std::vector<int>& data) {
    int n = matrix.size();
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i * n + j < data.size()) {
                matrix[i][j] = data[i * n + j];
            }
            else {
                matrix[i][j] = 0; // Заполняем нулями если нехватка данных
            }
        }
    }
}

void replaceWithRowMin(std::vector<std::vector<int>>& matrix) {
    int n = matrix.size();
    for (int i = 0; i < n; ++i) {
        int minValue = std::numeric_limits<int>::max();
        // Находим минимальное значение строки
        for (int j = 0; j < n; ++j) {
            if (matrix[i][j] < minValue) {
                minValue = matrix[i][j];
            }
        }
        // Заменяем все элементы строки на минимум
        for (int j = 0; j < n; ++j) {
            matrix[i][j] = minValue;
        }
    }
}

int main() {
    const std::string filename = "zadanie2.bin";
    const int numElements = 8; // Количество случайных чисел 
    const int n = 4; 

    fillBinaryFile(filename, numElements);

    std::vector<int> data = readBinaryFile(filename);

    std::vector<std::vector<int>> matrix(n, std::vector<int>(n, 0));
    fillMatrix(matrix, data);

    //  Замена элементов на минимальный элемент
    replaceWithRowMin(matrix);

    std::cout << "Resulting Matrix:" << std::endl;
    for (const auto& row : matrix) {
        for (int value : row) {
            std::cout << value << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}
