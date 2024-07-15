// normal bubble merge -01
#include <SFML/Graphics.hpp>
#include <vector>
#include <algorithm>
#include <chrono>
#include <random>
#include <iostream>

using namespace std;

// Initialize the size with the total numbers to be sorted
const int size = 200;
const int gap = 4;
vector<int> numbers(size);

// Function to draw the lines
void draw(sf::RenderWindow& window) {
    window.clear();

    for (int k = 0; k < size; ++k) {
        sf::RectangleShape line(sf::Vector2f(gap - 1, numbers[k]));
        line.setPosition(k * gap, size);
        line.setRotation(180);
        line.setFillColor(sf::Color::White);
        window.draw(line);
    }

    window.display();
}

// Function for swapping the lines graphically (for Bubble Sort)
void swap(sf::RenderWindow& window, int i, int j) {
    std::swap(numbers[i], numbers[j]);
    draw(window);
    sf::sleep(sf::milliseconds(10));
}

// Bubble sort function
void bubbleSort(sf::RenderWindow& window) {
    for (int i = 0; i < size - 1; ++i) {
        for (int j = 0; j < size - i - 1; ++j) {
            if (numbers[j] > numbers[j + 1]) {
                swap(window, j, j + 1);
            }
        }
    }
}

// Merge function
void merge(sf::RenderWindow& window, vector<int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<int> L(n1), R(n2);

    for (int i = 0; i < n1; ++i)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; ++j)
        R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
        draw(window);
        sf::sleep(sf::milliseconds(10));
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
        draw(window);
        sf::sleep(sf::milliseconds(10));
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
        draw(window);
        sf::sleep(sf::milliseconds(10));
    }
}

// Merge sort function
void mergeSort(sf::RenderWindow& window, vector<int>& arr, int left, int right) {
    if (left >= right)
        return;

    int mid = left + (right - left) / 2;
    mergeSort(window, arr, left, mid);
    mergeSort(window, arr, mid + 1, right);
    merge(window, arr, left, mid, right);
}

// Driver program
int main() {
    int choice;

    // Prompt the user to choose the sorting algorithm
    cout << "Choose the sorting algorithm:" << endl;
    cout << "1. Bubble Sort" << endl;
    cout << "2. Merge Sort" << endl;
    cout << "Enter your choice (1 or 2): ";
    cin >> choice;

    // Create the window
    sf::RenderWindow window(sf::VideoMode(gap * size, size), "Sorting Algorithm Visualization");

    // Initializing the array
    for (int i = 0; i < size; ++i)
        numbers[i] = i + 1;

    // Find a seed and shuffle the array to make it random
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    shuffle(numbers.begin(), numbers.end(), default_random_engine(seed));

    // Initial plot of numbers in graph taking the vector position as x-axis and its corresponding value will be the height of line
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        draw(window);

        // Call the selected sorting algorithm
        if (choice == 1) {
            bubbleSort(window);
        } else if (choice == 2) {
            mergeSort(window, numbers, 0, size - 1);
        } else {
            cout << "Invalid choice!" << endl;
            window.close();
        }
        
        // Break the loop after sorting is done
        break;
    }

    // Print the sorted array
    for (int i = 0; i < size; ++i) {
        cout << numbers[i] << " ";
    }
    cout << endl;

    return 0;
}
