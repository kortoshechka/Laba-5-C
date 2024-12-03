#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <limits>
#include <algorithm>

//  otkluchetm makros kotoriy zamenal min and max na svoi znachenia
#define NOMINMAX
#include <windows.h>

class TaskManager {
public:
    // task 1: Заполнение и фильтрация бинарного файла
    static void Task1(const std::string& inputFile, const std::string& outputFile, size_t size, int m, int n) {
        fillBinaryFile(inputFile, size);
        filterBinaryFile(inputFile, outputFile, m, n);
        std::cout << "task 1 zavershen: \n " << outputFile << "\n";
    }

    // task 2 : matrica
    static void Task2(const std::string& filename, int numElements, int matrixSize) {
        fillBinaryFile(filename, numElements);
        auto data = readBinaryFile(filename);
        std::vector<std::vector<int>> matrix(matrixSize, std::vector<int>(matrixSize, 0));
        fillMatrix(matrix, data);
        replaceWithRowMin(matrix);

        std::cout << "Matrica posle zameni strok na minimum :\n";
        for (const auto& row : matrix) {
            for (const auto& value : row) {
                std::cout << value << " ";
            }
            std::cout << "\n";
        }
    }

    // task 3: bagage
    static void Task3(const std::string& filename, double maxWeight) {
        SetConsoleOutputCP(CP_UTF8);
        SetConsoleCP(CP_UTF8);
        fillPassengerFile(filename);

        if (hasLightBaggage(filename, maxWeight)) {
            std::cout << "est pasagir s bagage menshe chem " << maxWeight << " KG.\n";
        }
        else {
            std::cout << "takogo nety\n";
        }
    }

    // task 4 : Raznost max and min
    static void Task4(const std::string& filename, int count) {
        fillFileWithRandomNumbers(filename, count);
        int difference = calculateDifference(filename);
        std::cout << "Raznost mezhdy min i max : " << difference << "\n";
    }

    //task 5: naiti min 
    static void Task5(const std::string& filename, int count) {
        fillFileWithRandomNumbers(filename, count);
        int minElement = findMinInFile(filename);

        if (minElement != std::numeric_limits<int>::max()) {
            std::cout << "Min: " << minElement << "\n";
        }
        else {
            std::cout << "Error: ne nashel chislo.\n";
        }
    }

    // task 6 : Filter v textoviy fail
    static void Task6(const std::string& inputFileName, const std::string& outputFileName, char startingCharacter) {
        std::ifstream inputFile(inputFileName);
        if (!inputFile) {
            std::cerr << "Error open file.\n";
            return;
        }

        std::ofstream outputFile(outputFileName);
        if (!outputFile) {
            std::cerr << "error exit file .\n";
            return;
        }

        std::string line;
        while (std::getline(inputFile, line)) {
            if (!line.empty() && line[0] == startingCharacter) {
                outputFile << line << "\n";
            }
        }

        inputFile.close();
        outputFile.close();
        std::cout << "Its over. rezultat in " << outputFileName << "\n";
    }

private:
    // Vspomogatelni metod
    static void fillBinaryFile(const std::string& filename, size_t size) {
        std::ofstream ofs(filename, std::ios::binary);
        for (size_t i = 0; i < size; ++i) {
            int num = rand() % 100;
            ofs.write(reinterpret_cast<const char*>(&num), sizeof(num));
        }
    }

    static void filterBinaryFile(const std::string& inputFile, const std::string& outputFile, int m, int n) {
        std::ifstream ifs(inputFile, std::ios::binary);
        std::ofstream ofs(outputFile, std::ios::binary);
        int num;
        while (ifs.read(reinterpret_cast<char*>(&num), sizeof(num))) {
            if (num % m == 0 && num % n != 0) {
                ofs.write(reinterpret_cast<const char*>(&num), sizeof(num));
            }
        }
    }

    static std::vector<int> readBinaryFile(const std::string& filename) {
        std::ifstream ifs(filename, std::ios::binary);
        std::vector<int> data;
        int num;
        while (ifs.read(reinterpret_cast<char*>(&num), sizeof(num))) {
            data.push_back(num);
        }
        return data;
    }

    static void fillMatrix(std::vector<std::vector<int>>& matrix, const std::vector<int>& data) {
        size_t n = matrix.size();
        for (size_t i = 0; i < n; ++i) {
            for (size_t j = 0; j < n; ++j) {
                if (i * n + j < data.size()) {
                    matrix[i][j] = data[i * n + j];
                }
                else {
                    matrix[i][j] = 0;
                }
            }
        }
    }

    static void replaceWithRowMin(std::vector<std::vector<int>>& matrix) {
        for (auto& row : matrix) {
            int minValue = *std::min_element(row.begin(), row.end());
            std::fill(row.begin(), row.end(), minValue);
        }
    }

    static void fillPassengerFile(const std::string& filename) {
        std::ofstream outFile(filename, std::ios::binary);
        int numPassengers;
        std::cout << "Kol-vo passagere : ";
        std::cin >> numPassengers;
        for (int i = 0; i < numPassengers; ++i) {
            int baggageCount;
            std::cout << "Kol-vo bagage to passagere " << i + 1 << ": ";
            std::cin >> baggageCount;
            outFile.write(reinterpret_cast<const char*>(&baggageCount), sizeof(baggageCount));
            for (int j = 0; j < baggageCount; ++j) {
                std::string name;
                double weight;
                std::cout << "Vvedite nazvanie i ves bagage: ";
                std::cin >> name >> weight;
                size_t nameLength = name.size();
                outFile.write(reinterpret_cast<const char*>(&nameLength), sizeof(nameLength));
                outFile.write(name.c_str(), nameLength);
                outFile.write(reinterpret_cast<const char*>(&weight), sizeof(weight));
            }
        }
    }

    static bool hasLightBaggage(const std::string& filename, double maxWeight) {
        std::ifstream inFile(filename, std::ios::binary);
        while (inFile.peek() != EOF) {
            int baggageCount;
            inFile.read(reinterpret_cast<char*>(&baggageCount), sizeof(baggageCount));
            for (int j = 0; j < baggageCount; ++j) {
                size_t nameLength;
                inFile.read(reinterpret_cast<char*>(&nameLength), sizeof(nameLength));
                std::string name(nameLength, ' ');
                inFile.read(&name[0], nameLength);
                double weight;
                inFile.read(reinterpret_cast<char*>(&weight), sizeof(weight));
                if (baggageCount == 1 && weight < maxWeight) return true;
            }
        }
        return false;
    }

    static void fillFileWithRandomNumbers(const std::string& filename, int count) {
        std::ofstream file(filename);
        for (int i = 0; i < count; ++i) {
            file << rand() % 1000 << std::endl;
        }
    }

    static int calculateDifference(const std::string& filename) {
        std::ifstream file(filename);
        int number, minNumber = INT32_MAX, maxNumber = INT32_MIN;
        while (file >> number) {
            minNumber = std::min(minNumber, number);
            maxNumber = std::max(maxNumber, number);
        }
        return maxNumber - minNumber;
    }

    static int findMinInFile(const std::string& filename) {
        std::ifstream inFile(filename);
        int number, minValue = std::numeric_limits<int>::max();
        while (inFile >> number) {
            minValue = std::min(minValue, number);
        }
        return minValue;
    }
};

int main() {
    srand(static_cast<unsigned>(time(nullptr))); // Инициализация генератора случайных чисел

    while (true) {
        std::cout << "\n Vibirite task  (1-6) ili 0 dla vihoda:\n";
        std::cout << "1: filter bin file\n";
        std::cout << "2: Matrix \n";
        std::cout << "3: bagage \n";
        std::cout << "4: Max i min raznitsa\n";
        std::cout << "5: min chislo\n";
        std::cout << "6: filter strok\n";
        std::cout << "Vibiraete : ";

        int choice;
        std::cin >> choice;

        if (choice == 0) {
            std::cout << "ITS OVEEEEEEER .\n";
            break;
        }

        switch (choice) {
        case 1: TaskManager::Task1("task1_input.bin", "task1_output.bin", 50, 3, 5); break;
        case 2: TaskManager::Task2("task2_matrix.bin", 16, 4); break;
        case 3: TaskManager::Task3("task3_baggage.dat", 20.0); break;
        case 4: TaskManager::Task4("task4_numbers.txt", 20); break;
        case 5: TaskManager::Task5("task5_numbers.txt", 20); break;
        case 6: {
            std::string inputFile, outputFile;
            char startingCharacter;
            std::cout << "Name open file: ";
            std::cin >> inputFile;
            std::cout << "Name exit file: ";
            std::cin >> outputFile;
            std::cout << "Vvedite simvol: ";
            std::cin >> startingCharacter;
            TaskManager::Task6(inputFile, outputFile, startingCharacter);
            break;
        }
        default: std::cout << " NE PRAVILNO POVTORITE SNOVA.\n"; break;
        }
    }

    return 0;
}
