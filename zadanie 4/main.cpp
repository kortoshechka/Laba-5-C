#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>  //rand � srand
#include <ctime>    //time

void fillFileWithRandomNumbers(const std::string& filename, int count) {
    std::ofstream file(filename);

    if (!file) {
        std::cerr << "�� ������� ������� ���� ��� ������." << std::endl;
        return;
    }

    for (int i = 0; i < count; ++i) {
        int randomNumber = rand() % 1000; // ��������� ���������� ����� �� 0 �� 999
        file << randomNumber << std::endl;
    }

    file.close();
}

int calculateDifference(const std::string& filename) {
    std::ifstream file(filename);

    if (!file) {
        std::cerr << "�� ������� ������� ���� ��� ������." << std::endl;
        return 0;
    }

    int number;
    int minNumber = INT32_MAX;
    int maxNumber = INT32_MIN;

    while (file >> number) {
        if (number < minNumber) {
            minNumber = number;
        }
        if (number > maxNumber) {
            maxNumber = number;
        }
    }

    file.close();

    return maxNumber - minNumber;
}

int main() {
    srand(static_cast<unsigned int>(time(nullptr))); //  ��������� ��������� �����
    const std::string filename = "numbers.txt";

    fillFileWithRandomNumbers(filename, 20); // ��������� ���� ���������� �������

    int difference = calculateDifference(filename); // ��������

    std::cout << "Raznost = " << difference << std::endl;

    return 0;
}
