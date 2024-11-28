#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib> //  rand и srand
#include <ctime>   //  time

// Метод для заполнения бинарного файла случайными числами
void fillBinaryFile(const std::string& filename, size_t size) {
    std::ofstream ofs(filename, std::ios::binary);
    if (!ofs) {
        std::cerr << "Ошибка открытия файла для записи" << std::endl;
        return;
    }

    for (size_t i = 0; i < size; ++i) {
        int num = rand() % 100; // Заполнение случайными числами 
        ofs.write(reinterpret_cast<char*>(&num), sizeof(num));
    }

    ofs.close();
}

// Метод для фильтрации чисел и записи их в новый бинарный файл
void filterBinaryFile(const std::string& inputFile, const std::string& outputFile, int m, int n) {
    std::ifstream ifs(inputFile, std::ios::binary);
    if (!ifs) {
        std::cerr << "error of read" << std::endl;
        return;
    }

    std::ofstream ofs(outputFile, std::ios::binary);
    if (!ofs) {
        std::cerr << "error of write" << std::endl;
        return;
    }

    int num;
    while (ifs.read(reinterpret_cast<char*>(&num), sizeof(num))) {
        if (num % m == 0 && num % n != 0) {
            ofs.write(reinterpret_cast<char*>(&num), sizeof(num));
        }
    }

    ifs.close();
    ofs.close();
}

int main() {
    srand(static_cast<unsigned int>(time(0))); // генератор случайных чисел

    std::string inputFile = "Zadanie1.bin";
    std::string outputFile = "filtered_data.bin";
    const size_t size = 50; // Кол-во случайных чисел
    int m = 3; // на что должно делится
    int n = 5; // на что не должно

    // Заполняем  
    fillBinaryFile(inputFile, size);

    // Фильтруем 
    filterBinaryFile(inputFile, outputFile, m, n);

    std::cout << "Complite." << std::endl;

    return 0;
}
