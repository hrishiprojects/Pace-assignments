/*************************************************************************
*
*  Pace University
*  Spring 2024
*  Algorithms and Computing Theory
*
*  Course: CS 608
*  Team members: Adhikari Vidhyadhar, Rushab Ramesh Vaza , Hrishikesh shah
*  Other collaborators: NONE.
*  References: NONE.
*
*  Assignment No.: 1
*
*  Input:  
*  Output: 
*
*  Visible data fields:
*  
* 
* Problem 1. 
* CODE IS SHOWN BELOW.
* 
* Problem 2. 
*                     	|n = 7^1| n = 7^2| n = 7^3| n = 7^4| n = 7^5|
* Brute force         	0			8		654		22247		591461
* Divide and conquer	1			5		47		396			1744
* Kadane’s				0			0		9		41			152
* 
* 
* Problem 3.
* Basically for brute force the run-time increases with the increase in load(the number of n)
* For divide and conquer it has a real good balance as there is an increases in run-time along with the increase in load but not a drastic increase as compare to the brute force.
* Kadane’s algo is super-efficient when compared with other two as there is only very small run-time increase even when the load increases drastically.
*
* 
* Problem 4.
* CODE IS SHOWN BELOW.
*************************************************************************/

{

/* 
Problem 1 and 4 : Brute force algorithm / Divide and conquer algorithm / Kadane’s algorithm
*/

#include <iostream>
#include <vector>
#include <chrono>
#include <algorithm>
#include <functional>
#include <climits>
#include <string>

using namespace std;
		using namespace chrono;

		int bruteForceMaxSubarray(vector<int>& A) {
		int n = A.size();
		int Smax = INT_MIN;

		for (int i = 0; i < n; ++i) {
		int sum = 0;
		for (int j = i; j < n; ++j) {
		sum += A[j];
		Smax = max(Smax, sum);
		}
		}

		return Smax;
		}

		int maxCrossingSubarray(vector<int>& A, int low, int mid, int high) {
		int leftsum = INT_MIN;
		int sum = 0;

		for (int i = mid; i >= low; --i) {
		sum += A[i];
		leftsum = max(leftsum, sum);
		}

		int rightsum = INT_MIN;
		sum = 0;

		for (int j = mid + 1; j <= high; ++j) {
		sum += A[j];
		rightsum = max(rightsum, sum);
		}

		return leftsum + rightsum;
		}

		int divideAndConquerMaxSubarray(vector<int>& A, int low, int high) {
		if (low == high) {
		return A[low];
		} else {
		int mid = (low + high) / 2;
		int leftsum = divideAndConquerMaxSubarray(A, low, mid);
		int rightsum = divideAndConquerMaxSubarray(A, mid + 1, high);
		int crosssum = maxCrossingSubarray(A, low, mid, high);

		return max({leftsum, rightsum, crosssum});
		}
		}

		int kadaneMaxSubarray(vector<int>& A) {
		int n = A.size();
		int maxEndingHere = A[0];
		int maxSoFar = A[0];

		for (int i = 1; i < n; ++i) {
		maxEndingHere = max(A[i], maxEndingHere + A[i]);
		maxSoFar = max(maxSoFar, maxEndingHere);
		}

		return maxSoFar;
		}

		void measureTime(function<int(vector<int>&)> algorithm, vector<int>& A, const string& name) {
		auto start = high_resolution_clock::now();
		int result = algorithm(A);
		auto stop = high_resolution_clock::now();
		auto duration = duration_cast<microseconds>(stop - start);

		cout << name << " Algorithm: " << result << " Time taken: " << duration.count() << " microseconds" << endl;
		}

		int main() {
		int n;
		cout << "Enter the size of the vector n: ";
		cin >> n;

		vector<int> A(n);
		cout << "Enter " << n << " numbers: ";
		for (int i = 0; i < n; ++i) {
		cin >> A[i];
		}

		measureTime([](vector<int>& A) { return bruteForceMaxSubarray(A); }, A, "Brute Force");
		measureTime([](vector<int>& A) { return divideAndConquerMaxSubarray(A, 0, A.size() - 1); }, A, "Divide and Conquer");
		measureTime([](vector<int>& A) { return kadaneMaxSubarray(A); }, A, "Kadane's");

		return 0;
		}



/*
Problem 2 : Run-time with different values of n (includes Kadane’s algorithm)
*/

#include <iostream>
#include <vector>
#include <chrono>
#include <algorithm>
#include <functional>
#include <cmath>
#include <climits>

using namespace std;
		using namespace chrono;

// Function prototypes
		int bruteForceMaxSubarray(vector<int>& A);
		int divideAndConquerMaxSubarray(vector<int>& A, int low, int high);
		int maxCrossingSubarray(vector<int>& A, int low, int mid, int high);
		int kadaneMaxSubarray(vector<int>& A);
		void measureTime(function<int(vector<int>&)> algorithm, vector<int>& A, const string& name);

		int main() {
		// Table header
		cout << "n\tBrute Force\tDivide and Conquer\tKadane's Algorithm" << endl;

		// Test the algorithms with different values of n
		for (int i = 1; i <= 5; ++i) {
		int n = pow(7, i);
		vector<int> A(n, 1);  // Filling the array with 1 for simplicity, adjust as needed

		// Measure time for Brute Force
		measureTime([](vector<int>& A) { return bruteForceMaxSubarray(A); }, A, "Brute Force");

		// Measure time for Divide and Conquer
		measureTime([](vector<int>& A) { return divideAndConquerMaxSubarray(A, 0, A.size() - 1); }, A, "Divide and Conquer");

		// Measure time for Kadane's Algorithm
		measureTime([](vector<int>& A) { return kadaneMaxSubarray(A); }, A, "Kadane's Algorithm");

		cout << endl;  // Separate rows in the table
		}

		return 0;
		}

		int bruteForceMaxSubarray(vector<int>& A) {
		int n = A.size();
		int Smax = INT_MIN;

		for (int i = 0; i < n; ++i) {
		int sum = 0;
		for (int j = i; j < n; ++j) {
		sum += A[j];
		Smax = max(Smax, sum);
		}
		}

		return Smax;
		}

		int maxCrossingSubarray(vector<int>& A, int low, int mid, int high) {
		int leftsum = INT_MIN;
		int sum = 0;

		for (int i = mid; i >= low; --i) {
		sum += A[i];
		leftsum = max(leftsum, sum);
		}

		int rightsum = INT_MIN;
		sum = 0;

		for (int j = mid + 1; j <= high; ++j) {
		sum += A[j];
		rightsum = max(rightsum, sum);
		}

		return leftsum + rightsum;
		}

		int divideAndConquerMaxSubarray(vector<int>& A, int low, int high) {
		if (low == high) {
		return A[low];
		} else {
		int mid = (low + high) / 2;
		int leftsum = divideAndConquerMaxSubarray(A, low, mid);
		int rightsum = divideAndConquerMaxSubarray(A, mid + 1, high);
		int crosssum = maxCrossingSubarray(A, low, mid, high);

		return max({leftsum, rightsum, crosssum});
		}
		}

		int kadaneMaxSubarray(vector<int>& A) {
		int n = A.size();
		int maxEndingHere = A[0];
		int maxSoFar = A[0];

		for (int i = 1; i < n; ++i) {
		maxEndingHere = max(A[i], maxEndingHere + A[i]);
		maxSoFar = max(maxSoFar, maxEndingHere);
		}

		return maxSoFar;
		}

		void measureTime(function<int(vector<int>&)> algorithm, vector<int>& A, const string& name) {
		auto start = high_resolution_clock::now();
		int result = algorithm(A);
		auto stop = high_resolution_clock::now();
		auto duration = duration_cast<microseconds>(stop - start);

		cout << A.size() << "\t" << duration.count() << "\t\t";  // Output n and running time
		cout << name << endl;
		}