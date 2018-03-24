// Copyright 2018 Alexander Trinh aktrinh@bu.edu
// **********************************************
// This project did not allow the use of brackets
// As a result, the syntax seen below is not
// as visually pleasing
// **********************************************
#include <algorithm>
#include <cstdint>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include "timer.h"

struct dizzyGenerator {
  std::unordered_map<int, std::vector<int>> Happies;
  std::unordered_map<std::string, std::vector<int>> foundDizzy;
  std::vector<int> find_dizzy_up_to(int last, const int base);
  std::vector<int> dizziness_cycle(int number, int base);
  bool is_dizzy(int number, int base);
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

// finds if a number is dizzy in a certain base
bool dizzyFind(int number, int base = 10) {
  std::vector<int> dizzyVec;
  // Adds digitSS to vector until it finds a duplicate
  do {
    dizzyVec.push_back(number);
    number = digitSquareSum(number, base);
    if (number == 1)
      return true;
  } while (std::find(dizzyVec.begin(), dizzyVec.end(), number)
           == dizzyVec.end());
  return false;
}

// finds if a number is dizzy in a certain base using a lookup
// or dizzyFind if the lookup is not generated for the base yet
bool dizzyGenerator::is_dizzy(int number, int base = 10) {
  // checks for if a certain base is not already there
  if (Happies.find(base) == Happies.end() ||
      Happies.find(base) == Happies.begin()) {
    return (dizzyFind(number, base));
  }
  number = digitSquareSum(number, base);
  if (std::find(Happies.at(base).begin(), Happies.at(base).end(), number)
      != Happies.at(base).end()) {
    return true;
  }
  return false;
}

// finds all dizzy numbers up to and including last in a certain base
// generates a vector for the precalulation of dizzy numbers
std::vector<int> findDizzyPrecalc(int last, const int base = 10) {
  std::vector<int> dizzyNums;
  for (int i = 1; i <= 500; i++) {
    if (dizzyFind(i, base)) {
      dizzyNums.push_back(i);
    }
  }
  return dizzyNums;
}

// finds all dizzy numbers up to and including last in a certain base
std::vector<int> dizzyGenerator::find_dizzy_up_to
(int last, const int base = 10) {
  // checks for an already calculated vector for a specific base and last
  std::string temp = std::to_string(base) + " " + std::to_string(last);
  if (foundDizzy.find(temp) != foundDizzy.end())
    return foundDizzy.at(temp);

  // only create lookup when necessary
  // ie large numbers or large bases
  // low numbers and low bases dont require the lookup
  // it is only necessary for quickly finding large numbers
  if (last > 100000 || base > 90) {
    // if a base isn't found, generate it
    if (Happies.find(base) == Happies.end()) {
      Happies.emplace(base, findDizzyPrecalc(last, base));
    }
  }
  // creates a vector of dizzy numbers up to last
  std::vector<int> dizzyNums;
  for (int i = 1; i <= last; i++) {
    if (is_dizzy(i, base)) {
      dizzyNums.push_back(i);
    }
  }
  // saves vector for future reference
  foundDizzy.emplace(temp, dizzyNums);
  return dizzyNums;
}

// returns the cycle which non dizzynumbers are stuck in or 1 for happy numbers
std::vector<int> dizzyGenerator::dizziness_cycle(int number, int base = 10) {
  std::vector<int> numCycle;
  std::vector<int> dizzyVec;

  // Adds digitSS to map until it finds a cycle
  do {
    dizzyVec.push_back(number);
    number = digitSquareSum(number, base);
    // returns 1 if a dizzy number is found
    if (number == 1) {
      numCycle.push_back(number);
      return numCycle;
    }
  } while (std::find(dizzyVec.begin(), dizzyVec.end(), number)
           == dizzyVec.end());

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

// MAIN   leave this line and all below as is
//        when submitting


const double TLIMIT = 0.5;

void standard_tests();
void interactive_main();

int main(int argc, const char **argv) {
  if (argc > 1)
    interactive_main();
  else
    standard_tests();
  return 0;
}

void standard_tests() {
  double speed = computer_speed();
  std::cerr << "Your computers speed relative to server: " << speed << "\n";

  Timer tall, t0("setup"), t1("all100");
  Timer t3("lots_of_base_10"), t4("lots_of_bases");


  std::vector<std::pair<int, int>> res;

  t0.start();
  dizzyGenerator h;
  t0.stop();

  // Test case definitions.
  std::vector<int> dizzy_tests_one{1, 4, 7, 145, 91, 31435135};
  std::vector<std::vector<int>> dizzy_tests_two{{14500, 10}, {2, 3},
    {255, 2}, {255, 4}, {998, 998}, {4, 10}, {7, 3},
    {41, 100}, {234, 100}, {124, 100}, {22357, 1000}, {1049, 1000}};
  std::vector<std::vector<int>> find_upto_tests_two{{100, 3},
    {1000, 11}, {20, 2}};
  std::vector<int> find_upto_tests_one{10, 100};

  std::cout << "Testing is_dizzy (two parameters)\n";
  for (auto e : dizzy_tests_two) {
    std::cout << "is_dizzy(" << e.at(0) << "," << e.at(1) << ") = ";
    std::cout << h.is_dizzy(e.at(0), e.at(1)) << "\n";
  }

  std::cout << "Testing is_dizzy (one parameter)\n";
  for (auto e : dizzy_tests_one) {
    std::cout << "is_dizzy(" << e << ") = ";
    std::cout << h.is_dizzy(e) << "\n";
  }

  std::cout << "Testing dizziness_cycle (two parameters)\n";
  for (auto e : dizzy_tests_two) {
    std::cout << "dizziness_cycle(" << e.at(0) << "," << e.at(1) << ") = ";
    for (auto cyc_val : h.dizziness_cycle(e.at(0), e.at(1)))
      std::cout << cyc_val << " ";
    std::cout << "\n";
  }

  std::cout << "Testing dizziness_cycle (one parameter)\n";
  for (auto e : dizzy_tests_one) {
    std::cout << "dizziness_cycle(" << e << ") = ";
    for (auto cyc_val : h.dizziness_cycle(e))
      std::cout << cyc_val << " ";
    std::cout << "\n";
  }

  std::cout << "Testing find_dizzy_up_to (two parameters)\n";
  for (auto e : find_upto_tests_two) {
    std::cout << "find_dizzy_up_to(" << e.at(0) << "," << e.at(1) << ") = ";
    for (auto dizzyval : h.find_dizzy_up_to(e.at(0), e.at(1)))
      std::cout << dizzyval << " ";
    std::cout << "\n";
  }


  std::cout << "Testing find_dizzy_up_to (one parameter)\n";
  for (auto e : find_upto_tests_one) {
    std::cout << "find_dizzy_up_to(" << e << ") = ";
    for (auto dizzynum : h.find_dizzy_up_to(e))
      std::cout << dizzynum << " ";
    std::cout << "\n";
  }


  std::cout << "Finding the dizziest bases\n";

  t1.start();
  for (int i = 2; i < 100; i++) {
    auto v = h.find_dizzy_up_to(100, i);
    res.push_back(std::make_pair(v.size(), i));
  }
  t1.stop();

  std::sort(res.begin(), res.end());

  std::cout << "The ten dizziest bases (for 1 to 100) are \n";
  for (auto it = res.rbegin(); it != res.rbegin() + 10 ; it++)
    std::cout << "base "  << it -> second << " has "
              << it -> first << " dizzy\n";



  std::cout << "\nHow many dizzy can you find in 0.5 seconds, base 10?\n";
  int start_size = 100;
  while (t3.time() < TLIMIT) {
    t3.start();
    std::vector<int> res =  h.find_dizzy_up_to(start_size);
    t3.stop();
    std::vector<uint64_t> locs{0, res.size() / 3,
                               2 * res.size() / 3, res.size() - 1};
    for (auto i : locs) {
      std::cout << "ss:" << start_size << " i: " << i
                << " v: " << res.at(i) << "\n";
    }
    start_size *= 2;
  }



  std::cout << "\nHow many dizzy can you find in 0.5 seconds, all bases?\n";
  int base = 2;
  while (t4.time() < TLIMIT) {
    t4.start();
    std::vector<int> res =  h.find_dizzy_up_to(20000, base);
    t4.stop();
    std::vector<uint64_t> locs{0, res.size() / 3,
                               2 * res.size() / 3, res.size() - 1};
    for (auto i : locs) {
      std::cout << "base:" << base
                << " i: " << i << " v: " << res.at(i) << "\n";
    }
    base *= 2;
  }
}


void interactive_main() {
  std::string asktype;
  int number, parameters, base;
  dizzyGenerator h;

  while (true) {
    std::cin >> asktype;
    if (asktype == "quit") break;
    std::cin >> parameters >> number;
    if (parameters > 1) std::cin >> base;
    if (asktype == "i" and parameters == 2) {
      std::cout << "is_dizzy(" << number << "," << base << ") = ";
      std::cout << h.is_dizzy(number, base) << "\n";
    } else if (asktype == "i" and parameters == 1) {
      std::cout << "is_dizzy(" << number << ") = ";
      std::cout << h.is_dizzy(number) << "\n";
    } else if (asktype == "c" and parameters == 2) {
      std::cout << "dizziness_cycle(" << number << "," << base << ") = ";
      for (auto cyc_val : h.dizziness_cycle(number, base) )
        std::cout << cyc_val << " ";
      std::cout << "\n";
    } else if (asktype == "c" and parameters == 1) {
      std::cout << "dizziness_cycle(" << number << ") = ";
      for (auto cyc_val : h.dizziness_cycle(number))
        std::cout << cyc_val << " ";
      std::cout << "\n";
    } else if (asktype == "f" and parameters == 2) {
      std::cout << "find_dizzy_up_to(" << number << "," << base << ") = ";
      for (auto dizzyval : h.find_dizzy_up_to(number, base))
        std::cout << dizzyval << " ";
      std::cout << "\n";
    } else if (asktype == "f" and parameters == 1) {
      std::cout << "find_dizzy_up_to(" << number << ") = ";
      for (auto dizzynum : h.find_dizzy_up_to(number))
        std::cout << dizzynum << " ";
      std::cout << "\n";
    }
  }
}
