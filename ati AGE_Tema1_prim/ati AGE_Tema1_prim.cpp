// ati AGE_Tema0.cpp : Defines the entry point for the console application.
#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <ctime> 
#include <cstdlib>
#include <cmath>
#include <math.h>
#include <map>
#define MIN_VAL 9999999.0
#define MAX_VAL 0
#define DMAX 32
#define NMAX 10000
#define numberOfBits 5

using namespace std;

int base2[numberOfBits], basin[DMAX], basinLen, maximum = MAX_VAL, globalMax = MAX_VAL;
bool used[DMAX], usedMax[NMAX];
multimap<int, int> mymm;

int Function(int x) {
	return x*x*x - 60*x*x + 900*x + 100;
}

int ToBase10(int base2[numberOfBits]) {
	int number = 0;

	for (int index = 0; index < numberOfBits; index++) {
		if (base2[index] == 1) {
			number += pow(2, numberOfBits - index - 1);
		}
	}
	return number;
}

void ToBase2(int number, int base2[numberOfBits]) {
	int index = 0;
	while (number) {
		base2[numberOfBits - 1 - index] = number % 2;
		number /= 2;
		index++;
	}
}

int Best_Neighbour(int base2[numberOfBits], int maximum) {
	
	int number, result, bestPos;
	int ok = false;
	for (int index = numberOfBits - 1; index >= 0; index--) {
		base2[index] = 1 - base2[index];
		number = ToBase10(base2);
		base2[index] = 1 - base2[index];

		//used[number] = true;
		result = Function(number);
		if (result > maximum) {
			maximum = result;
			bestPos = index;
			ok = true;
		}
	}
	if (ok)
		base2[bestPos] = 1 - base2[bestPos];
	return maximum;
}

int First_Neighbour(int base2[numberOfBits], int maximum) {

	int number, result, bestPos;
	int ok = false;
	for (int index = numberOfBits - 1; index >=0; index--) {
		base2[index] = 1 - base2[index];
		number = ToBase10(base2);
		base2[index] = 1 - base2[index];

		//used[number] = true;
		result = Function(number);
		if (result > maximum) {
			maximum = result;
			bestPos = index;
			ok = true;
			break;
		}
	}
	if (ok)
		base2[bestPos] = 1 - base2[bestPos];
	return maximum;
}

int HillClimbing(int value, int type) {
	bool ok = true;
	int localMax;

	maximum = Function(value);
	for (int index = 0; index < numberOfBits; index++)
		base2[index] = 0;

	ToBase2(value, base2);

	while(ok == true){
		
		ok = false;
		if (type == 0) {
			localMax = Best_Neighbour(base2, maximum);
		}
		else {
			localMax = First_Neighbour(base2, maximum);
		}
				
		value = ToBase10(base2);
		if (localMax > maximum) {
			maximum = localMax;	
				ok = true;
		}
	}
	return maximum;
}

int main() {

	int max = MAX_VAL, globalMax = MAX_VAL;
	for (int value = 0; value < DMAX; value++) {

		if (used[value] == false){
			used[value] = true;

			max = HillClimbing(value, 0); //best - 0, first - 1
			mymm.insert(std::pair<int, int>(max, value));
			basin[basinLen++] = maximum;
			
			if (max > globalMax) {
				globalMax = max;
			}
		}
	}
	
	for (int index = 0; index < basinLen; index++) {
		usedMax[basin[index]] = true;
	}

	for (int index = 0; index < NMAX; index++)
	{
		if (usedMax[index] == true) {
			pair <multimap<int, int>::iterator, multimap<int, int>::iterator> ret;
			ret = mymm.equal_range(index);
			cout << "Bazinul lui f(" << index << ") este: ";
			for (multimap<int, int>::iterator it = ret.first; it != ret.second; ++it)
				cout << ' ' << it->second;
			cout << '\n';
		}
	}
	cout << "Maximul global este: " << globalMax << '\n';
	return 0;
}
