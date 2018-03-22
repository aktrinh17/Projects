// Copyright 2018 Alexander Trinh aktrinh@bu.edu

#include <algorithm>
#include <iostream>
#include <set>
#include <string>
#include <unordered_map>
#include <vector>
#include "timer.h"

// lookup for optimization
std::unordered_map<int, std::vector<int>> Happies;

//std::unordered_map<int, std::vector<int>> foundHappy;

struct HappyGenerator {
  std::vector<int> find_happy_up_to(int last, const int base);
  std::vector<int> happiness_cycle(int number, int base);
  bool is_happy(int number, int base);
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
bool HappyGenerator::is_happy(int number, int base = 10) {
  // checks for if a certain base is not already there
  if (Happies.find(base) == Happies.end()){
    return (happiness_cycle(number, base).front() == 1);
  } else { 
    number = digitSquareSum(number, base);
    if (std::find(Happies.at(base).begin(), Happies.at(base).end(), number) != Happies.at(base).end())
      return true;
    return false;
 }
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

  } while(std::find(happyVec.begin(), happyVec.end(), number) == happyVec.end());
  return false;
}

// finds all happy numbers up to and including last in a certain base
std::vector<int> findHappyPrecalc(int last, const int base = 10) {
  // if a number in base 10 is already calulated, it retrieves it
  std::vector<int> happyNums;
  for (int i = 1; i <= 500; i++) {
    if (happyFind(i, base)) {
      happyNums.push_back(i);
    }
  }
  return happyNums;
}

// finds all happy numbers up to and including last in a certain base
std::vector<int> HappyGenerator::find_happy_up_to
(int last, const int base = 10) {
  // if a base isn't found, generate it
  if (Happies.find(base) == Happies.end())
  {
    Happies.insert(std::pair<int, std::vector<int>>(base, findHappyPrecalc(last, base)));
  }

  std::vector<int> happyNums;
  for (int i = 1; i <= last; i++) {
    if (is_happy(i, base)) {
      happyNums.push_back(i);
    }
  }
  return happyNums;
}

std::vector<int> HappyGenerator::happiness_cycle(int number, int base = 10) {
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
  } while(std::find(happyVec.begin(), happyVec.end(), number) == happyVec.end());

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


const int SLIMIT = 4'000'000;

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
  Timer t3("million1"), t4("million2");


  std::vector<std::pair<int, int>> res;

  t0.start();
  HappyGenerator h;
  t0.stop();

  // Test case definitions.
  std::vector<int> happy_tests_one{1, 4, 7, 145, 91, 31435135};
  std::vector<std::vector<int>> happy_tests_two{{14500, 10}, {2, 3},
    {255, 2}, {255, 4}, {998, 998}, {4, 10}, {7, 3},
    {41, 100}, {234, 100}, {124, 100}, {22357, 1000}, {1049, 1000}};
  std::vector<std::vector<int>> find_upto_tests_two{{100, 3},
    {1000, 11}, {20, 2}};
  std::vector<int> find_upto_tests_one{10, 100};

  std::cout << "Testing is_happy (two parameters)\n";
  for (auto e : happy_tests_two) {
    std::cout << "is_happy(" << e.at(0) << "," << e.at(1) << ") = ";
    std::cout << h.is_happy(e.at(0), e.at(1)) << "\n";
  }

  std::cout << "Testing is_happy (one parameter)\n";
  for (auto e : happy_tests_one) {
    std::cout << "is_happy(" << e << ") = ";
    std::cout << h.is_happy(e) << "\n";
  }

  std::cout << "Testing happiness_cycle (two parameters)\n";
  for (auto e : happy_tests_two) {
    std::cout << "happiness_cycle(" << e.at(0) << "," << e.at(1) << ") = ";
    for (auto cyc_val : h.happiness_cycle(e.at(0), e.at(1)))
      std::cout << cyc_val << " ";
    std::cout << "\n";
  }

  std::cout << "Testing happiness_cycle (one parameter)\n";
  for (auto e : happy_tests_one) {
    std::cout << "happiness_cycle(" << e << ") = ";
    for (auto cyc_val : h.happiness_cycle(e))
      std::cout << cyc_val << " ";
    std::cout << "\n";
  }

  std::cout << "Testing find_happy_up_to (two parameters)\n";
  for (auto e : find_upto_tests_two) {
    std::cout << "find_happy_up_to(" << e.at(0) << "," << e.at(1) << ") = ";
    for (auto happyval : h.find_happy_up_to(e.at(0), e.at(1)))
      std::cout << happyval << " ";
    std::cout << "\n";
  }


  std::cout << "Testing find_happy_up_to (one parameter)\n";
  for (auto e : find_upto_tests_one) {
    std::cout << "find_happy_up_to(" << e << ") = ";
    for (auto happynum : h.find_happy_up_to(e))
      std::cout << happynum << " ";
    std::cout << "\n";
  }


  std::cout << "Finding the happiest bases\n";

  t1.start();
  for (int i = 2; i < 100; i++) {
    auto v = h.find_happy_up_to(100, i);
    res.push_back(std::make_pair(v.size(), i));
  }
  t1.stop();

  std::sort(res.begin(), res.end());

  std::cout << "The ten happiest bases (for 1 to 100) are \n";
  for (auto it = res.rbegin(); it != res.rbegin() + 10 ; it++)
    std::cout << "base "  << it -> second << " has "
              << it -> first << " happy\n";


  t3.start();
  int count1 = h.find_happy_up_to(SLIMIT).size();
  t3.stop();

  t4.start();
  int count2 = h.find_happy_up_to(SLIMIT).size();
  t4.stop();


  std::cout << "In first " << SLIMIT << " "
            << count1 << " are happy (base 10)\n";

  std::cout << "In first " << SLIMIT << " "
            << count2 << " are happy (base 10)\n";
}


void interactive_main() {
  std::string asktype;
  int number, parameters, base;
  HappyGenerator h;

  while (true) {
    std::cin >> asktype;
    if (asktype == "quit") break;
    std::cin >> parameters >> number;
    if (parameters > 1) std::cin >> base;
    if (asktype == "i" and parameters == 2) {
      std::cout << "is_happy(" << number << "," << base << ") = ";
      std::cout << h.is_happy(number, base) << "\n";
    } else if (asktype == "i" and parameters == 1) {
      std::cout << "is_happy(" << number << ") = ";
      std::cout << h.is_happy(number) << "\n";
    } else if (asktype == "c" and parameters == 2) {
      std::cout << "happiness_cycle(" << number << "," << base << ") = ";
      for (auto cyc_val : h.happiness_cycle(number, base) )
        std::cout << cyc_val << " ";
      std::cout << "\n";
    } else if (asktype == "c" and parameters == 1) {
      std::cout << "happiness_cycle(" << number << ") = ";
      for (auto cyc_val : h.happiness_cycle(number))
        std::cout << cyc_val << " ";
      std::cout << "\n";
    } else if (asktype == "f" and parameters == 2) {
      std::cout << "find_happy_up_to(" << number << "," << base << ") = ";
      for (auto happyval : h.find_happy_up_to(number, base))
        std::cout << happyval << " ";
      std::cout << "\n";
    } else if (asktype == "f" and parameters == 1) {
      std::cout << "find_happy_up_to(" << number << ") = ";
      for (auto happynum : h.find_happy_up_to(number))
        std::cout << happynum << " ";
      std::cout << "\n";
    }
  }
}

