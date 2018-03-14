// Copyright 2018 Alexander Trinh aktrinh@bu.edu
// this is the starting point for happygen. please modify

// these are required
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <unordered_map>
//#include "timer.h"
using std::string;
// add addtional libraries if you need them

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

// converts a number form one base to another
string convertBase(const string& numstr, const int frombase, const int tobase) {
  string newBase = "";
  int distance = 0;
  int baseMulti = 1;
  // loops from the end of the string to the beginning
  for (int i = numstr.length() - 1; i >= 0; i--) {
    distance = distance + (numstr[i] - '0') * baseMulti;
    baseMulti = baseMulti * frombase;
  }

  while (distance > 0) {
    string pad = "";
    int addVar = (distance % tobase) + '0';
    distance = distance / tobase;
    pad = pad + (static_cast<char>(addVar));
    newBase.insert(0, pad);
  }

  return newBase;
}

// finds if a number is happy in a certain base
bool is_happy(int number, int base = 10)
{
  string num = convertBase(std::to_string(number), 10, base);
  number = std::stoi(num);
  int checkNext = number;

  std::unordered_map<int, int> happyMap;
  do
  {
    checkNext = digitSquareSum(checkNext);
    happyMap[checkNext] = checkNext;
  } while (happyMap.find(checkNext) == happyMap.end());

  return checkNext;
}

// finds all happy numbers up to and including last in a certain base
std::vector<int> find_happy_up_to(int last, const int base = 10)
{
  std::vector<int> happyNums;
  for (int i = 1; i <= last; i++)
  {
    if (is_happy(i, base))
      happyNums.push_back(i);
  }
}

std::vector<int> happiness_cycle(int number, int base = 10)
{

}

struct HappyGenerator {
  std::vector<int> find_happy_up_to(int last, const int base = 10) {}
  std::vector<int> happiness_cycle(int number, int base = 10) {}
  bool is_happy(int number, int base = 10) {}
};

main ()
{
  bool x = is_happy(10,2);
  if (x == true)
    std::cout << "yes";
  else
    std::cout << "no";
  return 0;
}
