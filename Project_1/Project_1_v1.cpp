// Project_1.cpp 
// Author: UsuaoSilver


// Include necessary libraries
#include <iostream>
#include <fstream>
#include <vector>
#include <time.h>
#include <math.h>
#include <algorithm>
#include <numeric>
#include <chrono>

using namespace std;

// Function prototypes
vector<int> randomVector(int, int, int);
double sampleSD(const vector<double>);
void runBubbleSort();
void runInsertionSort();
void runSelectionSort();
void runQuickSort();
void runAlgoOnRandomVectors(const string&);
void findTime(vector<int>&, const string&, vector<double>&);
void print(const string&, const vector<double>&);
void saveRuntimeDataToCSV(const string&, int, const string&, const vector<double>&, ofstream&);
void collectRuntimeData();
void collectRuntimeDataForSizeAndScenario(int, const string&, int, ofstream&);
vector<int> generateRandomVectorOfSizeAndScenario(int, const string&);


/********************************
 * 1. CODING QUESTIONS Solution *
 * *****************************/

 // Function to check if a vector is sorted
bool isSorted(vector<int>& L) {
     for (int i = 1; i < L.size(); ++i) {
          if (L[i - 1] > L[i]) return false;
     }
     return true;
}

// Bubble sort algorithm
vector<int> bubbleSort(vector<int>& L) {
     bool sorted = false;
     while (!sorted) {
          sorted = true;
          for (int i = 1; i < L.size(); ++i) {
               if (L[i - 1] > L[i]) {
                    int temp = L[i - 1];
                    L[i - 1] = L[i];
                    L[i] = temp;
                    sorted = false;
               }
          }
     }
     return L;
}

// Insertion sort algorithm
vector<int> insertionSort(vector<int>& L) {
     int i = 1;
     while (i < L.size()) {
          int j = i;
          while (j > 0 && L[j - 1] > L[j]) {
               int temp = L[j - 1];
               L[j - 1] = L[j];
               L[j] = temp;
               j = j - 1;
          }
          i = i + 1;
     }
     return L;
}

// Selection sort algorithm
vector<int> selectionSort(vector<int>& L) {
     for (int i = 0; i < L.size() - 1; ++i) {
          int uMin = i;
          for (int j = i + 1; j < L.size(); ++j) {
               if (L[j] < L[uMin]) {
                    uMin = j;
               }
          }
          int temp = L[i];
          L[i] = L[uMin];
          L[uMin] = temp;
     }
     return L;
}

// Partition function for quick sort
int partition(vector<int>& L, int start, int end) {

     int pivot = L[start];

     int i = start + 1;

     for (int j = start + 1; j <= end; j++) {
          if (L[j] <= pivot) { 
               swap(L[i], L[j]); 
               i++;
          }
     }

     // Give pivot element correct position
     int pivotIndex = i - 1;
     swap(L[pivotIndex], L[start]);

     return pivotIndex;
}

// Quick sort algorithm
void quickSort(vector<int>& L, int start, int end) {
     
     if (start >= end) return; // base case

     int p = partition(L, start, end); // partition array

     quickSort(L, start, p - 1); // Sorting left part
     quickSort(L, p + 1, end); // Sorting right part
}


/***********************************************
 * Main and helper functions for quick testing *
 * *********************************************/
int main(int argc, char* argv[]) {
     srand(time(NULL));

     char ans;

     cout << "Which test would you like to run?" << endl;
     cout << "1. Run each sorting algorithm on ten random vectors of length 100" << endl;
     cout << "2. Collect worst-, average-, and best-case run time data associated with each algorithm" << endl;
     cin >> ans;

     switch (ans) {
     case '1':
          cout << "Which sorting algorithm would you like to test?" << endl;
          cout << "A. Bubble Sort" << endl;
          cout << "B. Insertion Sort" << endl;
          cout << "C. Selection Sort" << endl;
          cout << "D. Quick Sort" << endl;
          cin >> ans;
          switch (ans) {
          case 'A':
          case 'a':
               runAlgoOnRandomVectors("Bubble");
               break;
          case 'B':
          case 'b':
               runAlgoOnRandomVectors("Insertion");
               break;
          case 'C':
          case 'c':
               runAlgoOnRandomVectors("Selection");
               break;
          case 'D':
          case 'd':
               runAlgoOnRandomVectors("Quick");
               break;
          default:
               cout << "Invalid choice. Please enter A, B, C, or D." << endl;
               return 1;
          }
          break;
     case '2':
          collectRuntimeData();
          break;
     default:
          cout << "Invalid choice. Please enter 1 or 2." << endl;
          return 1;
     }

     return 0;
}


/**************************************
 * 2. TESTING & EXPERIMENTS Solution *
 * ***********************************/


// Function to run and test individual algorithms on random vectors
void runAlgoOnRandomVectors(const string& algorithm) {
     const int numVectors = 10;
     const int vectorSize = 100;

     vector<double> times;

     for (int i = 0; i < numVectors; ++i) {
          vector<int> _randomVector = randomVector(vectorSize, 1, 1000);
          findTime(_randomVector, algorithm, times);
     }

     print(algorithm, times);
}

// Function to collect runtime data for all vector sizes of each scenario
void collectRuntimeData() {
     const int numVectors = 50;
     const int vectorSizes[] = { 10, 100, 1000, 5000, 10000 };
     const string scenarios[] = { "Worst", "Average", "Best" };

     // Check if CSV file already exist
     bool filesExist = false;
     for (const string& scenario : scenarios) {
          for (int size : vectorSizes) {
               string filename = scenario + "_Case_times.csv";
               ifstream file(filename);
               if (file.good()) {
                    cout << "CSV files already exist. Do you want to overwrite them? (y/n): ";
                    char choice;
                    cin >> choice;
                    if (tolower(choice) != 'y') {
                         cout << "Existing CSV files will not be overwritten. Exiting." << endl;
                         return;
                    }
                    filesExist = true;
                    break;
               }
          }
     }

     if (filesExist) {
          cout << "Overwriting existing files..." << endl;
     }

     // Iterate over each scenario
     for (const string& scenario : scenarios) {
          // Create filename for the current scenario
          string filename = scenario + "_case_times.csv";

          // Open the file in trunc mode to create it if it doesn't exist or overwrite existing content
          ofstream file(filename, ios::trunc);
          if (!file.is_open()) {
               cerr << "Unable to create file: " << filename << endl;
               continue; // Skip to the next scenario
          }

          // Write the CSV file header
          file << "Algorithm,Size,Time" << endl;

          // Iterate over each vector size
          for (int size : vectorSizes) {
               vector<double> bubbleTimes, insertionTimes, selectionTimes, quickTimes;

               for (int i = 0; i < numVectors; ++i) {
                    vector<int> randomVector = generateRandomVectorOfSizeAndScenario(size, scenario);

                    findTime(randomVector, "Bubble", bubbleTimes);
                    findTime(randomVector, "Insertion", insertionTimes);
                    findTime(randomVector, "Selection", selectionTimes);
                    findTime(randomVector, "Quick", quickTimes);
               }

               saveRuntimeDataToCSV("bubble", size, scenario, bubbleTimes, file);
               saveRuntimeDataToCSV("insertion", size, scenario, insertionTimes, file);
               saveRuntimeDataToCSV("selection", size, scenario, selectionTimes, file);
               saveRuntimeDataToCSV("quick", size, scenario, quickTimes, file);
          }

          // Close the file
          file.close();

          cout << "CSV file generated successfully: " << filename << endl;
     }
}

// Function to save runtime data to CSV file
void saveRuntimeDataToCSV(const string& algorithm, int size, const string& scenario, const vector<double>& times, ofstream& file) {
     for (double time : times) {
          file << algorithm << "," << size << "," << scientific << time << endl;
     }
}

// Function to measure the time taken by each sorting algorithm
void findTime(vector<int>& randomVector, const string& algorithm, vector<double>& times) {
     auto start = chrono::high_resolution_clock::now();

     if (algorithm == "Bubble") {
          bubbleSort(randomVector);
     }
     else if (algorithm == "Insertion") {
          insertionSort(randomVector);
     }
     else if (algorithm == "Selection") {
          selectionSort(randomVector);
     }
     else if (algorithm == "Quick") {
          quickSort(randomVector, 0, randomVector.size() - 1);
     }

     auto end = chrono::high_resolution_clock::now();
     times.push_back(chrono::duration_cast<chrono::duration<double>>(end - start).count());

     if (!isSorted(randomVector)) {
          cerr << algorithm << " sort failed!" << endl;
          exit(1);
     }
}

// Function to generate random vectors based on scenario
vector<int> generateRandomVectorOfSizeAndScenario(int size, const string& scenario) {
     if (scenario == "Worst") {
          // Generate a vector sorted in descending order
          vector<int> vec(size);
          iota(vec.rbegin(), vec.rend(), 1);
          return vec;
     }
     else if (scenario == "Average" || scenario == "Best") {
          // Generate a random vector
          return randomVector(size, 1, 1000);
     }
}


/********************************
 * Print out the time *
 *******************************/
void print(const string& algorithm, const vector<double>& times) {
     cout << "************************" << endl;
     cout << algorithm << " sort on " << times.size() << " vectors of length 100" << endl;
     cout << "Sorting successful" << endl;
     cout << "Minimum: " << *min_element(times.begin(), times.end()) << " sec; ";
     cout << "Mean: " << accumulate(times.begin(), times.end(), 0.0) / times.size() << " sec; ";
     cout << "Standard deviation: " << sampleSD(times) << " sec; ";
     cout << "Maximum: " << *max_element(times.begin(), times.end()) << " sec" << endl;
     cout << "************************" << endl;
}


/*=============================================================================
 * Helper functions*
 *=============================================================================/

/******************************************************************************
* Generate a vector of random integers in a given range. The ends *
* of this range are inclusive. *
* size - int - the number of integers in the resulting vector *
* low, high - int - the range from which to draw random integers (inclusive) *
* return - vector<int> - a vector of random integers *
******************************************************************************/
vector<int> randomVector(int size, int low, int high) {
     vector<int> v(size, 0);
     for (int i = 0; i < size; i++) {
          v[i] = rand() % (high - low + 1) + low;
     }
     return v;
}

/******************************************************************
* Calculate the sample standard deviation of a vector of doubles *
* v - const vector<double> - a vector of doubles *
* return - double - the sample standard deviation of v *
******************************************************************/
double sampleSD(const vector<double> v) {
     double mean = 0;
     for (int i = 0; i < v.size(); i++) {
          mean += v[i];
     }
     mean = mean / v.size();
     double sd = 0;
     for (int i = 0; i < v.size(); i++) {
          sd += (v[i] - mean) * (v[i] - mean);
     }
     sd = sd / (v.size() - 1);
     return sqrt(sd);
}
