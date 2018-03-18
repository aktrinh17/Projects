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
      printf("%d ", i);
    }
  }
  return happyNums;
}

std::vector<int> happiness_cycle(int number, int base = 10) {



}

struct HappyGenerator {
  std::vector<int> find_happy_up_to(int last, const int base = 10) {}
  std::vector<int> happiness_cycle(int number, int base = 10) {}
  bool is_happy(int number, int base = 10) {}
};

// MAIN
main() {
  bool x = is_happy(31435135);
  if (x == true)
    std::cout << "1\n";
  else
    std::cout << "0\n";
  return 0;
}
