#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>
#include <limits>
#include <cmath>
#include <chrono> //For timing

//Structure to represent a point
struct Point {
    int x, y;
};

//Function to calculate the Euclidean distance between two points
double calculateDistance(const Point& p1, const Point& p2) {
    return std::sqrt(static_cast<double>((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y)));
}

//Function to find the closest pair of points using brute-force
void findClosestPair(const std::vector<Point>& points) {
    if (points.size() < 2) {
        std::cerr << "Error: Not enough points to calculate the distance.\n";
        return;
    }
    double minDistance = std::numeric_limits<double>::max();
    Point closestPoint1, closestPoint2;

    //Start measuring time
    auto start = std::chrono::high_resolution_clock::now();

    //Brue-force comparison of all pairs
    for (size_t i = 0; i < points.size(); ++i) {
        for (size_t j = i + 1; j < points.size(); ++j) {
            double distance = calculateDistance(points[i], points[j]);
            if (distance < minDistance) {
                minDistance = distance;
                closestPoint1 = points[i];
                closestPoint2 = points[j];
            }
        }
    }

    //Stop measuring time
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    //Output the results
    std::cout << "Closest Pair: (" << closestPoint1.x << ", " << closestPoint1.y << ") and (" << closestPoint2.x << ", " << closestPoint2.y << ")\n";
    std::cout << "Distance: " << minDistance << "\n";
    std::cout << "Time taken: " << duration.count() << " milliseconds\n";
}

int main() {
    std::string fileName;
    std::cout << "Enter the file name to read points from (e.g., output800.txt): ";
    std::cin >> fileName;

    std::ifstream inFile(fileName);
    if (!inFile) {
        std::cerr << "Error: Could not open file " << fileName << " for reading.\n";
        return 1;
    }
    std::vector<Point> points;
    int x, y;

    //Read points from the file
    while (inFile >> x >> y) {
        points.push_back({x, y});
    }
    inFile.close();

    //Find the closest pair of points
    findClosestPair(points);
    return 0;
}

//How to run on Windows Powershell
//g++ -o bruteforce bruteforce.cpp -std=c++17
//./bruteforce
