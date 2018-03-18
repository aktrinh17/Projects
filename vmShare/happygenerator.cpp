// Copyright 2018 Alexander Trinh aktrinh@bu.edu

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
//#include "timer.h"
using std::string;

// divides a number into its digits and finds its square
int digitSquareSum(int num) {
  int sum = 0;
  // uses modulus to take off the ones digit and adds
  // its square to the sum
  // then divides by 10 to move to the next digit
  while (num) {
    sum += (num % 10) * (num % 10);
    num /= 10;
  }

  return sum;
}

// converts a number from one base to another
int convertbase(int num, const int base) {
  int newNum = 0;
  int place = 1;
  int digit;
  while (num > 0) {
    digit = num % base;
    newNum += digit * place;
    place *= 10;
    num /= base;
  }
  return newNum;
}

// finds if a number is happy in a certain base
bool is_happy(int number, int base = 10) {
  int checkNext = convertbase(number, base);

  std::unordered_map<int, int> happyMap;
  // Adds digitSS to map until it finds a duplicate
  do {
    happyMap[checkNext] = checkNext;
    checkNext = digitSquareSum(checkNext);

    if (checkNext == 1) 
      return true;

  } while (happyMap.find(checkNext) == happyMap.end());
  return false;
}

// finds all happy numbers up to and including last in a certain base
std::vector<int> find_happy_up_to(int last, const int base = 10) {
  std::vector<int> happyNums;
  for (int i = 1; i <= last; i++) {
    if (is_happy(i, base)) {
      happyNums.push_back(i);
    }
  }
  return happyNums;
}

// Finds a cycle of happy numbers in a specific base
std::vector<int> happiness_cycle(int number, int base = 10) {
  int checkNext = convertbase(number, base);
  std::vector<int> numCycle;
  std::unordered_map<int, int> happyMap;

  // Adds digitSS to map until it finds a cycle
  do {
    happyMap[checkNext] = checkNext;
    checkNext = digitSquareSum(checkNext);
    // returns 1 if a happy number is found
    if (checkNext == 1) {
      numCycle.push_back(checkNext);
      return numCycle;
    }
  } while (happyMap.find(checkNext) == happyMap.end());
  
  numCycle.push_back(checkNext);
  int startOfCycle = checkNext;

  // loops until the first number is encountered again
  // meaning that the cycle has ended
  while (digitSquareSum(checkNext) != startOfCycle)
  {
    checkNext = digitSquareSum(checkNext);
    numCycle.push_back(checkNext);
  }

  for (int i = 0; i < numCycle.size(); i++)
  {
    std::cout << numCycle[i] << ' ';
  }
  return numCycle;
}

struct HappyGenerator {
  std::vector<int> find_happy_up_to(int last, const int base = 10) {}
  std::vector<int> happiness_cycle(int number, int base = 10) {}
  bool is_happy(int number, int base = 10) {}
};

// MAIN
main() {


  happiness_cycle(41,100);
  /*
  bool x = is_happy(12,3);
  if (x == true)
    std::cout << "1\n";
  else
    std::cout << "0\n";

    */
  return 0;
}
