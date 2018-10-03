// Copyright 2018 Alexander Trinh aktrinh@bu.edu

#include <algorithm>
#include <iostream>
#include <set>
#include <string>
#include <unordered_map>
#include <vector>
#include "timer.h"

std::unordered_map<int, std::vector<int>> Happies;
  std::unordered_map<std::string, std::vector<int>> foundHappy;

struct  HappyGenerator {
  std::vector<int> find_happy_up_to(int last, const int base = 10){};
  std::vector<int> happiness_cycle(int number, int base = 10){};
  bool is_happy(int number, int base = 10){};
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
bool happyFind(int number, int base = 10) {
  std::vector<int> happyVec;
  // Adds digitSS to map until it finds a duplicate
  do {
    happyVec.push_back(number);
    number = digitSquareSum(number, base);
    if (number == 1)
      return true;
  } while (std::find(happyVec.begin(), happyVec.end(), number)
           == happyVec.end());
  return false;
}

// finds if a number is happy in a certain base
bool is_happy(int number, int base = 10) {
  // checks for if a certain base is not already there
  if (Happies.find(base) == Happies.end() || Happies.find(base)
      == Happies.begin()) {
    return (happyFind(number, base));
  }
  number = digitSquareSum(number, base);
  if (std::find(Happies.at(base).begin(), Happies.at(base).end(), number)
      != Happies.at(base).end()) {
    return true;
  }
  return false;
}

// finds all happy numbers up to and including last in a certain base
std::vector<int> findhappyPrecalc(int last, const int base = 10) {
  std::vector<int> happyNums;
  for (int i = 1; i <= 400; i++) {
    if (happyFind(i, base)) {
      happyNums.push_back(i);
    }
  }
  return happyNums;
}

// finds all happy numbers up to and including last in a certain base
std::vector<int> find_happy_up_to
(int last, const int base = 10) {
  std::string temp = std::to_string(base) + " " + std::to_string(last);
  if (foundHappy.find(temp) != foundHappy.end())
    return foundHappy.at(temp);

  // if a base isn't found, generate it
  if (Happies.find(base) == Happies.end()) {
    Happies.emplace(base, findhappyPrecalc(last, base));
  }

  std::vector<int> happyNums;
  for (int i = 1; i <= last; i++) {
    if (is_happy(i, base)) {
      happyNums.push_back(i);
    }
  }
  foundHappy.emplace(temp, happyNums);

  return happyNums;
}

std::vector<int> happiness_cycle(int number, int base = 10) {
  std::vector<int> numCycle;
  std::vector<int> happyVec;

  // Adds digitSS to map until it finds a cycle
  do {
    happyVec.push_back(number);
    number = digitSquareSum(number, base);
    // returns 1 if a happy number is found
    if (number == 1) {
      numCycle.push_back(number);
      return numCycle;
    }
  } while (std::find(happyVec.begin(), happyVec.end(), number)
           == happyVec.end());

  numCycle.push_back(number);
  int startOfCycle = number;

  // loops until the first number is encountered again
  // meaning that the cycle has ended
  while (digitSquareSum(number, base) != startOfCycle) {
    number = digitSquareSum(number, base);
    numCycle.push_back(number);
  }
  return numCycle;
}

int main() {
  std::vector<int> temp = find_happy_up_to(20000, 16);
  for (int i = 0; i < temp.size(); i++)
  {
   //std::cout << temp[i] << ' ';
  }
  //std::cout << temp.size();
  std::cout << temp[1680] << ' ';
  std::cout << temp[3360] << ' ';
  std::cout << temp[5040];
//6658 13178, 20000

  return 0;
}

