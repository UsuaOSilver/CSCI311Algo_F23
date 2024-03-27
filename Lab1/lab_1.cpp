// CSCI 311
// Lab 1
// Author: UsuaoSilver

#include <iostream>
#include <math.h>
#include <chrono>
#include <vector>
using namespace std;

/**************************
 * Your solutions go here *
 * ************************/
int collatzLength(int n){
     int lastI = 0;
     while (n != 1) {
          if ((n % 2) == 0) n /= 2;
          else n = (n * 3) + 1;

          lastI++;
     }
  return lastI;
}

void printStats(const vector<int> &v){
     if (v.empty()) {
          cout << "Empty vector" << endl;
          return;
     }

     // Find minimum and maximum values
     int minVal = v[0];
     int maxVal = v[0];
     int sum = 0;

     for (size_t i = 0; i < v.size(); ++i) {
          if (v[i] < minVal) {
               minVal = v[i];
          }

          if (v[i] > maxVal) {
               maxVal = v[i];
          }

          sum += v[i];
     }

     // Calculate mean value
     double meanVal = static_cast<double>(sum) / v.size();

     // Print the results
     cout << minVal << " " << meanVal << " " << maxVal << endl;
}

int sumMultiples(const vector<int> &nums, int n){
     int sum = 0;

     for (size_t i = 1; i < n; ++i) {
          for (size_t num : nums) {
               if (i % num == 0) {
                    sum += i;
                    break; // Break out of the inner loop once a multiple is found
               }
          }
     }

     return sum;
}

void greaterThanK(vector<int> &v, int k){
     // Iterate through the vector and remove elements less than or equal to k
     for (auto it = v.begin(); it != v.end();) {
          if (*it <= k) {
               it = v.erase(it);
          }
          else {
               ++it;
          }
     }
}

bool isSubarray(const vector<string> &a, const vector<string> &b){
     size_t sizeA = a.size();
     size_t sizeB = b.size();

     if (sizeA > sizeB) {
          // If size of a is greater than b, it cannot be a subarray
          return false;
     }

     // Iterate through vector b
     for (size_t i = 0; i <= sizeB - sizeA; ++i) {
          // Check if a is a subarray of b starting at index i
          bool isMatch = true;
          for (size_t j = 0; j < sizeA; ++j) {
               if (a[j] != b[i + j]) {
                    isMatch = false;
                    break;
               }
          }

          if (isMatch) {
               return true;  // If a is a subarray, return true
          }
     }

     return false; // If no subarray is found, return false
}

bool isPrimeA(int n){
     if (n <= 1) {
          return false;
     }

     for (size_t i = 2; i < n; ++i) {
          if (n % i == 0) {
               return false;
          }
     }

     return true;
}

int sumPrimesA(int n){
     int sum = 0;

     for (size_t i = 2; i < n; ++i) {
          if (isPrimeA(i)) {
               sum += i;
          }
     }

     return sum;
}

bool isPrimeB(int n){
     if (n <= 1) {
          return false;
     }

     for (size_t i = 2; i <= sqrt(n); ++i) {
          if (n % i == 0) {
               return false;
          }
     }

     return true;
}

int sumPrimesB(int n){
     int sum = 0;

     for (size_t i = 2; i < n; ++i) {
          if (isPrimeB(i)) {
               sum += i;
          }
     }

     return sum;
}

int sieveOfEratosthenes(int n){
     vector<int> sieve(n, 1);  // Initialize the sieve with all 1s
     int sum = 0;

     for (size_t i = 2; i <= sqrt(n); ++i) {
          if (sieve[i] == 1) {
               for (size_t j = i * i; j < n; j += i) {
                    sieve[j] = 0;  // Mark multiples of i as non-prime
               }
          }
     }

     for (size_t i = 2; i < n; ++i) {
          if (sieve[i] == 1) {
               sum += i;
          }
     }

     return sum;
}

/***********************************************
 * Main and helper functions for quick testing *
 * *********************************************/
void readIntVector(vector<int> &v, int n);
void timePrimes();

int main(){
  int question = -1;
  cout << "Question: ";
  cin >> question;

  int n = 0, k = 0, m = 0;
  vector<int> v;
  string s = "";
  vector<string> a;
  vector<string> b;

  switch (question){
    case 1: //collatzLength
      cout << "Collatz Sequence n: ";
      cin >> n;
      cout << collatzLength(n) << endl;
      break;
    case 2: //printStats
      cout << "Print Stats Number of Values: ";
      cin >> n;
      cout << "Values: ";
      readIntVector(v, n);
      cout << "Stats: " << endl;
      printStats(v);
      break;
    case 3: //sumMultiples
      cout << "Sum Multiples Number of Values: ";
      cin >> n;
      cout << "Values: ";
      readIntVector(v, n);
      cout << "Max Value: ";
      cin >> k;
      cout << "Sum: ";
      cout << sumMultiples(v, k) << endl;
      break;
    case 4: //greaterThanK
      cout << "Greater than K Number of Values: ";
      cin >> n;
      cout << "Values: ";
      readIntVector(v, n);
      cout << "k: ";
      cin >> k;
      cout << "Result: ";
      greaterThanK(v, k);
      for (int j = 0; j < v.size(); j++){ cout << v[j] << " "; }
      break;
    case 5: //isSubarray
      cout << "Is Subarray Array Sizes: ";
      cin >> n >> m;
      cout << "Values for First Vector: ";
      for (int i = 0; i < n; i++){
        cin >> s;
        a.push_back(s);
      }
      cout << "Values for Second Vector: ";
      for (int i = 0; i < m; i++){
        cin >> s;
        b.push_back(s);
      }
      cout << "Result: ";
      cout << isSubarray(a, b) << endl;
      break;
    case 6: //naive prime sum
      cout << "Primes Max Value: ";
      cin >> n;
      cout << "Sum: " << sumPrimesA(n) << endl;
      break;
    case 7: //prime sum 2
      cout << "Primes Max Value: ";
      cin >> n;
      cout << "Sum: " << sumPrimesB(n) << endl;
      break;
    case 8: //sieve of eratosthenes
      cout << "Primes Max Value: ";
      cin >> n;
      cout << "Sum: " << sieveOfEratosthenes(n) << endl;
      break;
    case 9: //time primes
      cout << "Time Primes" << endl;
      timePrimes();
      break;
  }

  return 0;
}

/**************************************************
 * Read a vector of integers in from cin          *
 * v - vector<int> & - the integer vector to fill *
 * n - int - the number of integers to read       *
 * ************************************************/
void readIntVector(vector<int> &v, int n){
  int m = 0;
  for (int i = 0; i < n; i++){
    cin >> m;
    v.push_back(m);
  }
}

/***************************************************************************************************
 * Testing run times of different approaches to finding the sum of prime numbers under a threshold *
 * *************************************************************************************************/
void timePrimes(){
  int sum = -1;
  chrono::high_resolution_clock::time_point start;
  chrono::high_resolution_clock::time_point end;
  double elapsed = -1;
  vector<int> x = {10, 100, 1000, 10000, 100000, 500000};
  for (int i = 0; i < x.size(); i++)
  {
    cout << "Value: " << x[i] << endl;

    start = chrono::high_resolution_clock::now();
    sum = sumPrimesA(x[i]);
    end = chrono::high_resolution_clock::now();
    elapsed = chrono::duration_cast<chrono::duration<double>>(end - start).count();
    cout << "A ... Sum: " << sum << ", Time elapsed: " << elapsed << endl;

    start = chrono::high_resolution_clock::now();
    sum = sumPrimesB(x[i]);
    end = chrono::high_resolution_clock::now();
    elapsed = chrono::duration_cast<chrono::duration<double>>(end - start).count();
    cout << "B ... Sum: " << sum << ", Time elapsed: " << elapsed << endl;

    start = chrono::high_resolution_clock::now();
    sum = sieveOfEratosthenes(x[i]);
    end = chrono::high_resolution_clock::now();
    elapsed = chrono::duration_cast<chrono::duration<double>>(end - start).count();
    cout << "C ... Sum: " << sum << ", Time elapsed: " << elapsed << endl;
    cout << endl << endl;
  }

  cout << "Sieve of Eratosthenes on primes below 1 million" << endl;
  start = chrono::high_resolution_clock::now();
  long sum2 = sieveOfEratosthenes(1000000);
  end = chrono::high_resolution_clock::now();
  elapsed = chrono::duration_cast<chrono::duration<double>>(end - start).count();
  cout << "Sum: " << sum2 << ", Time elapsed: " << elapsed << endl;
  cout << endl << endl;
}

