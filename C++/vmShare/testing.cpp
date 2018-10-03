// Copyright 2018 Alexander Trinh aktrinh@bu.edu

#include <algorithm>
#include <iostream>
#include <set>
#include <string>
#include <vector>
#include <unordered_map>
#include "timer.h"
using std::string;

std::vector<int> Happies = {1, 7, 10, 13, 19, 23, 28, 
  31, 32, 44, 49, 68, 70, 79, 82, 86, 91, 94, 97, 100, 103, 
  109, 129, 130, 133, 139, 167, 176, 188, 190, 192, 193, 203, 
  208, 219, 226, 230, 236, 239, 262, 263, 280, 291, 293, 301, 
  302, 310, 313, 319, 320, 326, 329, 331, 338, 356, 362, 365, 
  367, 368, 376, 379, 383, 386, 391, 392, 397, 404, 409, 440, 
  446, 464, 469, 478, 487, 490};

struct HappyGenerator {
  std::vector<int> find_happy_up_to(int last, const int base = 10){};
  std::vector<int> happiness_cycle(int number, int base){};
  bool is_happy(int number, int base){};
};

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

  std::unordered_map<int, int> happyMap;
  if(base == 10){
    number = digitSquareSum(number, base);
    if (std::find(Happies.begin(), Happies.end(), number) != Happies.end())
      return true;
    return false;
  }
  // Adds digitSS to map until it finds a duplicate
  do {
    happyMap[number] = number;
    number = digitSquareSum(number, base);

    if (number == 1) 
      return true;

  } while (happyMap.find(number) == happyMap.end());
  return false;
  /*std::vector<int> finding;
  finding = HappyGenerator::happiness_cycle(number, base);
  if (finding[0] == 1)
    return true;
  return false;*/
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
  for (int i = 0; i < numCycle.size(); i++)
  {
   std::cout << numCycle[i] << ' ';
  }
  return numCycle;
}

int main() {
  find_happy_up_to(1000,1000);
  return 0;
}