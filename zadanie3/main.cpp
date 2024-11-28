#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <windows.h>

struct Baggage {
    std::string name; // Название  багажа
    double weight;    // Масса  багажа
};

struct Passenger {
    std::vector<Baggage> baggage; // Массив багажей
};

//  заполнения  файла
void fillBinaryFile(const std::string& filename) {
    std::ofstream outFile(filename, std::ios::binary);
    if (!outFile) {
        std::cerr << "error open" << std::endl;
        return;
    }

    
    int numPassengers;
    std::cout << "kol-vo passagere: ";
    std::cin >> numPassengers;

    for (int i = 0; i < numPassengers; ++i) {
        Passenger passenger;
        int numBaggage;
        std::cout << "kol-vo baggage " << i + 1 << ": ";
        std::cin >> numBaggage;

        for (int j = 0; j < numBaggage; ++j) {
            Baggage bag;
            std::cout << "name and massa bagage (cherez probel): ";
            std::cin >> bag.name >> bag.weight;
            passenger.baggage.push_back(bag);
        }

        // Сохраняем информацию  в файл
        int baggageCount = passenger.baggage.size();
        outFile.write(reinterpret_cast<const char*>(&baggageCount), sizeof(baggageCount));
        for (const auto& bag : passenger.baggage) {
            size_t nameLength = bag.name.size();
            outFile.write(reinterpret_cast<const char*>(&nameLength), sizeof(nameLength));
            outFile.write(bag.name.c_str(), nameLength);
            outFile.write(reinterpret_cast<const char*>(&bag.weight), sizeof(bag.weight));
        }
    }

    outFile.close();
}

// Функция для проверки наличия багажа 
bool hasLightBaggage(const std::string& filename, double maxWeight) {
    std::ifstream inFile(filename, std::ios::binary);
    if (!inFile) {
        std::cerr << "error" << std::endl;
        return false;
    }

    while (inFile.peek() != EOF) { // Пока не конец файла
        int baggageCount;
        inFile.read(reinterpret_cast<char*>(&baggageCount), sizeof(baggageCount));

        for (int j = 0; j < baggageCount; ++j) {
            size_t nameLength;
            inFile.read(reinterpret_cast<char*>(&nameLength), sizeof(nameLength));

            std::string bagName(nameLength, ' ');
            inFile.read(&bagName[0], nameLength); // Чтение названия
            double weight;
            inFile.read(reinterpret_cast<char*>(&weight), sizeof(weight)); // Чтение массы

            if (baggageCount == 1 && weight < maxWeight) {
                return true; // Нашли подходящий багаж
            }
        }
    }

    inFile.close();
    return false; // Подходящего багажа не найдено
}

int main() {

    const std::string filename = "baggage.dat";

    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    fillBinaryFile(filename);

    double m;
    std::cout << "massa dla proverki: ";
    std::cin >> m;

    if (hasLightBaggage(filename, m)) {
        std::cout << "est takoi passagire" << m << " kg." << std::endl;
    }
    else {
        std::cout << "takoro netu" << std::endl;
    }

    return 0;
}
