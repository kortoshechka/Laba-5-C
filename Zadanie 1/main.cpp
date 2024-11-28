#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib> //  rand � srand
#include <ctime>   //  time

// ����� ��� ���������� ��������� ����� ���������� �������
void fillBinaryFile(const std::string& filename, size_t size) {
    std::ofstream ofs(filename, std::ios::binary);
    if (!ofs) {
        std::cerr << "������ �������� ����� ��� ������" << std::endl;
        return;
    }

    for (size_t i = 0; i < size; ++i) {
        int num = rand() % 100; // ���������� ���������� ������� 
        ofs.write(reinterpret_cast<char*>(&num), sizeof(num));
    }

    ofs.close();
}

// ����� ��� ���������� ����� � ������ �� � ����� �������� ����
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
    srand(static_cast<unsigned int>(time(0))); // ��������� ��������� �����

    std::string inputFile = "Zadanie1.bin";
    std::string outputFile = "filtered_data.bin";
    const size_t size = 50; // ���-�� ��������� �����
    int m = 3; // �� ��� ������ �������
    int n = 5; // �� ��� �� ������

    // ���������  
    fillBinaryFile(inputFile, size);

    // ��������� 
    filterBinaryFile(inputFile, outputFile, m, n);

    std::cout << "Complite." << std::endl;

    return 0;
}
