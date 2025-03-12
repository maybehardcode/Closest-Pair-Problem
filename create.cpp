#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <string>

void generateRandomPoints (int n) {
    //Set seed for random number generation
    srand(static_cast<unsigned>(time(0)));

    //Create the output file name
    std::string fileName = "output" + std::to_string(n) + ".txt";

    //Open the output file
    std::ofstream outFile(fileName);
    if (!outFile) {
        std::cerr << "Error: Could not open file " << fileName << " for writing.\n";
        return;
    }

    //Generate n random points and write them to the file
    for (int i = 0; i < n; ++i){
        int x = rand() % 20001 - 10000; //Random x in range [-10000, 10000]
        int y = rand() % 20001 - 10000; //Random y in range [-10000, 10000]
        outFile << x << " " << y << "\n";
    }
    std::cout << "Generated " << n << " random points and saved to " << fileName << ".\n";

    //Close the file
    outFile.close();
}

int main() {
    int n;
    std::cout << "Enter the number of points to generate: ";
    std::cin >> n;

    if (n <= 0){
        std::cerr << "Error: Number of points must be greater than 0.\n";
        return 1;
    }

    generateRandomPoints(n);
    return 0;
}

//How to run on Windows PowerShell
//g++ -o create create.cpp
//./create