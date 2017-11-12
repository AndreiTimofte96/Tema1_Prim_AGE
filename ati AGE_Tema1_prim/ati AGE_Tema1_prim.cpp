// ati AGE_Tema0.cpp : Defines the entry point for the console application.
#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <ctime> 
#include <cstdlib>
#include <cmath>
#include <math.h>
#define MIN_VAL 9999999.0
#define MAX_VAL 0
#define DMAX 32
#define numberOfBits 5

using namespace std;

int base2[numberOfBits], basin[DMAX], basinLen, maximum = MAX_VAL, globalMax = MAX_VAL;
bool used[DMAX];


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

void InitializeBasin(int basin[]) {
	basinLen = 0;
	for (int index = 0; index < DMAX; index++) {
		basin[index] = 0;
	}
}

void Best_Neighbour(int base2[numberOfBits]) {

	int localMax = MAX_VAL, position = 0, value, number, bestNumber, ok = false;
	for (int index = 0; index < numberOfBits; index++) {
		base2[index] = 1 - base2[index];
		number = ToBase10(base2);
		base2[index] = 1 - base2[index];

		if (used[number] == false) {

			
			localMax = Function(number);
			if (localMax > maximum) {
				ok = true;
				bestNumber = number;
				maximum = localMax;
				position = index;
			}
		}
	}
	if (ok == true) {
		used[bestNumber] = true;
		base2[position] = 1 - base2[position];
		basin[basinLen++] = bestNumber;
		Best_Neighbour(base2);
	}
}

int First_Neighbour() {

	return 0;
}

void HillClimbing() {


	//for (int index = 0; index < numberOfBits; index++)
		//cout << base2[index];

	maximum = Function(0);
	for (int value = 0; value <= 31; value++) {
		
		if (used[value] == false) {
			InitializeBasin(basin);
			ToBase2(value, base2);
			basin[basinLen++] = value;
			used[value] = true;
			Best_Neighbour(base2);

			if (globalMax < maximum) {
				globalMax = maximum;
			}

			cout << "Maximum: " << maximum << '\n';
			cout << "Basin: ";
			for (int index = 0; index < basinLen; index++) {
				cout << basin[index] << " ";
			}
			cout << '\n';

			maximum = MAX_VAL;
		}
	}
	cout <<"GlobalMax: "<< globalMax<<'\n';
}

int main() {

	HillClimbing();
	return 0;
}