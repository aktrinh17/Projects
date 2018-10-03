// Copyright 2018 Alexander Trinh aktrinh@bu.edu

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include "timer.h"
using std::string;

// divides a number into its digits and finds its square
int digitSquareSum(int num, const int base = 10) {
  int sum = 0;
  while (num) {
    sum += (num % base) * (num % base);
    num /= base;
  }
  return sum;
}

// finds if a number is happy in a certain base
bool is_happy(int number, int base = 10) {
  // converts the new base in vector form to int 

  std::unordered_map<int, int> happyMap;
  // Adds digitSS to map until it finds a duplicate
  do {
    happyMap[number] = number;
    number = digitSquareSum(number, base);

    if (number == 1) 
      return true;

  } while (happyMap.find(number) == happyMap.end());
  return false;
}

// finds all happy numbers up to and including last in a certain base
std::vector<int> find_happy_up_to(int last, const int base = 10) {
  std::vector<int> happyNums;
  for (int i = 1; i <= last; i++) {
    if (is_happy(i, base)) {
      happyNums.push_back(i);
      std::cout << i << ' ';
    }
  }
  return happyNums;
}

std::vector<int> happiness_cycle(int number, int base = 10) {
  std::vector<int> numCycle;
  std::unordered_map<int, int> happyMap;

  // Adds digitSS to map until it finds a cycle
  do {
    happyMap[number] = number;
    number = digitSquareSum(number, base);
    // returns 1 if a happy number is found
    if (number == 1) {
      numCycle.push_back(number);
      return numCycle;
    }
  } while (happyMap.find(number) == happyMap.end());
  
  numCycle.push_back(number);
  int startOfCycle = number;

  // loops until the first number is encountered again
  // meaning that the cycle has ended
  while (digitSquareSum(number, base) != startOfCycle)
  {
    number = digitSquareSum(number, base);
    numCycle.push_back(number);
  }

 /* for (int i = 0; i < numCycle.size(); i++)
  {
   std::cout << numCycle[i] << ' ';
  }*/
  return numCycle;
}

struct HappyGenerator {
  std::vector<int> find_happy_up_to(int last, const int base = 10) {}
  std::vector<int> happiness_cycle(int number, int base = 10) {}
  bool is_happy(int number, int base = 10) {}
};

int main() {
  return 0;
}
