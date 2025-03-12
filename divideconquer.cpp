#include <iostream>
#include <fstream>
#include <vector>
#include <cmath> // For sqrt
#include <limits> // For numeric_limits
#include <algorithm> // For sort
#include <chrono> // For timing

// Structure to represent a point
struct Point {
    int x, y;
};

// Function to calculate the Euclidean distance between two points
double calculateDistance(const Point& p1, const Point& p2) {
    return std::sqrt(static_cast<double>((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y)));
}

// Comparator function for sorting points by x-coordinate
bool compareByX(const Point& p1, const Point& p2) {
    return p1.x < p2.x;
}

// Comparator function for sorting points by y-coordinate
bool compareByY(const Point& p1, const Point& p2) {
    return p1.y < p2.y;
}

// Brute-force solution for a small number of points
double bruteForceClosestPair(const std::vector<Point>& points, size_t start, size_t end, Point& closest1, Point& closest2) {
    double minDistance = std::numeric_limits<double>::max();
    for (size_t i = start; i < end; ++i) {
        for (size_t j = i + 1; j < end; ++j) {
            double distance = calculateDistance(points[i], points[j]);
            if (distance < minDistance) {
                minDistance = distance;
                closest1 = points[i];
                closest2 = points[j];
            }
        }
    }
    return minDistance;
}

// Function to find the closest pair of points in the strip
double closestStripPair(const std::vector<Point>& strip, double d, Point& closest1, Point& closest2) {
    double minDistance = d;

    for (size_t i = 0; i < strip.size(); ++i) {
        for (size_t j = i + 1; j < strip.size() && (strip[j].y - strip[i].y) < minDistance; ++j) {
            double distance = calculateDistance(strip[i], strip[j]);
            if (distance < minDistance) {
                minDistance = distance;
                closest1 = strip[i];
                closest2 = strip[j];
            }
        }
    }

    return minDistance;
}

// Recursive function for the divide-and-conquer algorithm
double closestPairRecursive(std::vector<Point>& points, size_t start, size_t end, Point& closest1, Point& closest2) {
    size_t n = end - start;

    // Base case: Use brute-force for small sets of points
    if (n <= 3) {
        return bruteForceClosestPair(points, start, end, closest1, closest2);
    }

    // Find the middle point
    size_t mid = start + n / 2;
    Point midPoint = points[mid];

    // Recursively find the closest pairs in the left and right halves
    Point leftClosest1, leftClosest2, rightClosest1, rightClosest2;
    double leftDistance = closestPairRecursive(points, start, mid, leftClosest1, leftClosest2);
    double rightDistance = closestPairRecursive(points, mid, end, rightClosest1, rightClosest2);

    // Get the smaller of the two distances
    double d = std::min(leftDistance, rightDistance);
    if (leftDistance < rightDistance) {
        closest1 = leftClosest1;
        closest2 = leftClosest2;
    } else {
        closest1 = rightClosest1;
        closest2 = rightClosest2;
    }

    // Build the strip for points close to the middle line
    std::vector<Point> strip;
    for (size_t i = start; i < end; ++i) {
        if (std::abs(points[i].x - midPoint.x) < d) {
            strip.push_back(points[i]);
        }
    }

    // Sort the strip by y-coordinate
    std::sort(strip.begin(), strip.end(), compareByY);

    // Find the closest pair in the strip
    Point stripClosest1, stripClosest2;
    double stripDistance = closestStripPair(strip, d, stripClosest1, stripClosest2);

    // Update the closest pair if the strip has a closer pair
    if (stripDistance < d) {
        closest1 = stripClosest1;
        closest2 = stripClosest2;
        d = stripDistance;
    }

    return d;
}

// Wrapper function to find the closest pair of points
void findClosestPair(std::vector<Point>& points) {
    if (points.size() < 2) {
        std::cerr << "Error: Not enough points to calculate the distance.\n";
        return;
    }

    // Sort points by x-coordinate
    std::sort(points.begin(), points.end(), compareByX);

    Point closest1, closest2;

    // Start timing
    auto start = std::chrono::high_resolution_clock::now();

    // Call the recursive divide-and-conquer function
    double minDistance = closestPairRecursive(points, 0, points.size(), closest1, closest2);

    // Stop timing
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    // Output the results
    std::cout << "Closest Pair: (" << closest1.x << ", " << closest1.y << ") and ("
              << closest2.x << ", " << closest2.y << ")\n";
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

    // Read points from the file
    while (inFile >> x >> y) {
        points.push_back({x, y});
    }

    inFile.close();

    // Find the closest pair of points
    findClosestPair(points);

    return 0;
}

//How to run on Windows Powershell
//g++ -o divideconquer divideconquer.cpp -std=c++17
//./divideconquer
