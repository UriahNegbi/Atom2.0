#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <stdexcept>

// Function to process each line
void mapLines(const std::string& line, std::string& mapline, const int structAtom[]) {
    mapline.clear();  // Clear mapline for each new line

    for (size_t i = 0; i < line.size(); ++i) {
        if (line[i] != '{' && line[i] != '}') {
            mapline += line[i];
        }
        else if (line[i] == '}') {
            // Parse mapline for matching values
            std::stringstream ss(mapline);
            std::string token;
            int proton = -1, neutron = -1;

            try {
                // Expect format: DecayType,proton,neutron
                std::getline(ss, token, ','); // DecayType (ignore)
                if (!std::getline(ss, token, ',')) {
                    std::cerr << "Line format error: Missing proton value in line: " << mapline << std::endl;
                    mapline.clear(); // Clear mapline after processing
                    continue;
                }
                proton = std::stoi(token);
                if (!std::getline(ss, token, ',')) {
                    std::cerr << "Line format error: Missing neutron value in line: " << mapline << std::endl;
                    mapline.clear(); // Clear mapline after processing
                    continue;
                }
                neutron = std::stoi(token);

                // Check if the proton and neutron numbers match structAtom
                if (proton == structAtom[0] && neutron == structAtom[1]) {
                    std::cout << mapline << std::endl;
                }
            }
            catch (const std::invalid_argument& e) {
                std::cerr << "Invalid argument in line: " << mapline << std::endl;
            }
            catch (const std::out_of_range& e) {
                std::cerr << "Number out of range in line: " << mapline << std::endl;
            }

            mapline.clear(); // Clear mapline after processing
        }
    }
}

int main() {
    std::string line;
    std::string mapline;
    int input;
    int structAtom[] = { 0, 0 }; // Protons, Neutrons

    std::ifstream file("database.txt");

    // Get user input for structAtom array
    std::cout << "Enter number of protons: ";
    std::cin >> input;
    structAtom[0] = input;

    std::cout << "Enter number of neutrons: ";
    std::cin >> input;
    structAtom[1] = input;

    if (file.is_open()) {
        while (getline(file, line)) {
            mapLines(line, mapline, structAtom);
        }
        file.close();
    }
    else {
        std::cerr << "Unable to open file" << std::endl;
    }

    return 0;
}
