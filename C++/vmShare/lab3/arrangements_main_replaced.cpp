// Copyright 2018 Alexander Trinh aktrinh@bu.edu
#include <algorithm>
#include <array>
#include <cmath>
#include <cstdint>
#include <iomanip>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include "timer.h"

using std::vector;
using std::string;
using std::cout;
using std::sort;
using std::unordered_map;

class Arrangements {
  private:
  public:
  string thenames;
  Arrangements() {
    thenames = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
  }
  explicit Arrangements(string names) {
    thenames = names;
  }
  vector<string> panel_shuffles(int n);
  vector<string> dinner_shuffles(int n);
  double panel_count(int n);
  double dinner_count(int n);
  void errorChecker(int n);
};

// checks for if n > number of people
void Arrangements::errorChecker(int n) {
  if (n > thenames.length())
    throw n;
}

// returns a vector of all the possible seating
// combinations with n people in a panel
vector<string> Arrangements::panel_shuffles(int n) {
  errorChecker(n);
  vector<string> v;
  // create a map for reference in generating
  // higher n seating combinations
  unordered_map<int, vector<string>> refMap;

  // creates the first 2 vectors in the map
  // to start the fibonacci-like sequence
  string str1;
  str1 = thenames.at(0);

  vector<string> first;
  first.push_back(str1);

  refMap.emplace(0, first);

  string str2;
  str2 += thenames.at(0);
  str2 += thenames.at(1);

  string str3;
  str3 += thenames.at(1);
  str3 += thenames.at(0);

  vector<string> second;
  second.push_back(str2);
  second.push_back(str3);

  refMap.emplace(1, second);
  // generates seating combinations for n > 2
  // by referring to previous vectors in refMap
  for (int i = 2; i < n; i++) {
    vector<string> xi;
    // combos for if n stays in their original seat
    for (int j = 0; j < refMap.at(i - 1).size(); j++) {
      str1 = "";
      str1 = refMap.at(i - 1).at(j) + thenames.at(i);
      xi.push_back(str1);
    }
    // combos for if n switches one to the left
    for (int k = 0; k < refMap.at(i - 2).size(); k++) {
      str2 = "";
      str2 = refMap.at(i - 2).at(k) + thenames.at(i) + thenames.at(i - 1);
      xi.push_back(str2);
    }
    refMap.emplace(i, xi);
  }
  v = refMap.at(n - 1);
  return v;
}

// returns a vector of all the possible seating
// combinations with n people in a circular table
vector<string> Arrangements::dinner_shuffles(int n) {
  errorChecker(n);
  // the dinner arrangements are the panel arrangements with a few extra combos
  vector<string> v = panel_shuffles(n);
  string str;
  // the extra seating combos are not needed unless n > 2
  if (n > 2) {
    // checks for if the first letter and last letter are
    // the same as the original seating
    // if so, swap the first and last chars and keep the middle
    for (int i = 0; i < v.size(); i++) {
      if (v.at(i).at(0) == thenames.at(0)) {
        if (v.at(i).at(n - 1) == thenames.at(n - 1)) {
          str = "";
          str += v.at(i);
          std::swap(str.at(0), str.at(n - 1));
          v.push_back(str);
        }
      }
    }
    str = "";
    // original shifted to the left one
    str += thenames.substr(1, n - 1) + thenames.at(0);
    v.push_back(str);

    str = "";
    // original shifted to the right one
    str += thenames.at(n - 1) + thenames.substr(0, n - 1);
    v.push_back(str);
  }
  return v;
}

// calculates the number of ways the panelists can be arranged
// if there are n panelists
double Arrangements::panel_count(int n) {
  errorChecker(n);
  vector<double> seats;
  seats.push_back(1);
  seats.push_back(2);
  // calculates the next number by referring to the previous 2 numbers
  for (int i = 2; i <= n; i ++) {
    seats.push_back(seats.at(i - 1) + seats.at(i - 2));
  }
  cout.precision(15);
  return seats.at(n - 1);
}

// calculates the number of ways the dinner guests can be arranged
// if there are n guests
double Arrangements::dinner_count(int n) {
  errorChecker(n);
  vector<double> seats;
  seats.push_back(1);
  seats.push_back(2);
  seats.push_back(6);
  seats.push_back(9);
  // calculates the next number by referring to the previous 2 numbers
  for (int i = 4; i <= n; i++) {
    seats.push_back(seats.at(i - 1) + seats.at(i - 2) - 2);
  }
  cout.precision(15);
  return seats.at(n - 1);
}


// TESTING: leave this line and below as is.

void show_result(vector<string> v) {
  sort(v.begin(), v.end());
  for (auto c : v)
    cout << c << "\n";
  cout << "\n";
}

void show_partial_result(string testname, vector<string> res, int n) {
  if (res.empty()) return;

  sort(res.begin(), res.end());

  std::vector<uint64_t> locs{0, res.size() / 3,
                             2 * res.size() / 3, res.size() - 1};
  std::cout << "\n" << testname << " " << n << "\n";
  for (auto i : locs) {
    std::cout << " res.at(" << i
              << ") = " << res.at(i) << "\n";
  }
}


const int COUNTLIM = 100;
const int COUNTLIM_SMALL = 30;

void standard_tests();
void alternate_tests();
void interactive_main();

int main(int argc, char const ** argv) {
  if (argc > 1 and string(*(argv+1)) == "alt")
    alternate_tests();
  else if (argc > 1 and (string(*(argv+1)) == string("int")))
    interactive_main();
  else
    standard_tests();
}

// tests to be run for full credit, including performance.
void standard_tests() {
  int n;

  cout.precision(15);

  // Basic test
  Arrangements standard;

  cout << "\nPanel Shuffles for 4 panelists.\n";
  show_result(standard.panel_shuffles(4));

  cout << "\nDinner Shuffles for 4 guests.\n";
  show_result(standard.dinner_shuffles(4));

  // Test other names
  Arrangements numbers("123456789");
  Arrangements symbols("!@#$%^&*()_+");

  std::array<Arrangements*, 3> v{&standard, &numbers, &symbols};

  cout << "\nPanel Shuffles for 6 panelists, 3 sets of names.\n";
  for (auto arr : v)
    show_result(arr->panel_shuffles(6));

  cout << "\nDinner Shuffles for 6 guests, 3 sets of names.\n";
  for (auto arr : v)
    show_result(arr->dinner_shuffles(6));

  // Count tests
  Arrangements large(string(COUNTLIM, 'a'));

  Timer t_pc("panel count", true);
  n = 1;
  cout << "\nPanel Shuffle Count Table (0.1 seconds)\n";
  cout << "     N  panel(N)\n";

  while (n < COUNTLIM and t_pc.time() < 0.1) {
    t_pc.start();
    double pc = large.panel_count(n);
    t_pc.stop();
    cout << std::setw(6) << n << " "
         << std::setw(6) << pc << "\n";
    n++;
  }


  Timer t_dc("dinner count", true);
  n = 1;
  cout << "\nDinner Shuffle Count Table (0.1 seconds)\n";
  cout << "     N  dinner(N)\n";

  while (n < COUNTLIM and t_dc.time() < 0.1) {
    t_dc.start();
    double dc = large.dinner_count(n);
    t_dc.stop();
    cout << std::setw(6) << n << " "
         << std::setw(6) << dc << "\n";
    n++;
  }

  Timer t_panel("panel", true);
  n = 4;
  cout << "\nHow many panel shuffles can be created in 0.5 seconds?\n";

  while (t_panel.time() < 0.5 and n <= 30)  {
    double last = t_panel.time();
    t_panel.start();
    vector<string> res = standard.panel_shuffles(n);
    t_panel.stop();
    show_partial_result("panel", res, n);
    cout << "time " << t_panel.time() - last << "\n";
    n++;
  }

  int largest_panel = n - 1;

  Timer t_dinner("dinner timing", true);
  n = 4;
  cout << "\nHow many dinner shuffles can be created in 0.5 seconds?\n";

  while (t_dinner.time() < 0.5 and n <= 30)  {
    double last = t_dinner.time();
    t_dinner.start();
    vector<string> res = standard.dinner_shuffles(n);
    t_dinner.stop();
    show_partial_result("dinner", res, n);
    cout << "time " << t_dinner.time() - last << "\n";
    n++;
  }
  cout << "\nLargest panel shuffles performed: "
       << largest_panel << "\n";
  cout << "\nLargest dinner shuffles performed: " << n - 1 << "\n";

  // Error checking
  Arrangements small("abcd");
  cout << "\nError Handling Tests\n";

  try {
    small.panel_count(5);
  } catch (int n) {
    cout << n;
  }
  try {
    small.panel_shuffles(6);
  } catch (int n) {
    cout << n;
  }
  try {
    small.dinner_count(7);
  } catch (int n) {
    cout << n;
  }
  try {
    small.dinner_shuffles(89);
  } catch (int n) {
    cout << n;
  }
  try {
    large.dinner_shuffles(122);
  } catch (int n) {
    cout << n;
  }
  try {
    numbers.dinner_shuffles(9);
  } catch (int n) {
    cout << n;
  }
  try {
    numbers.dinner_shuffles(10);
  } catch (int n) {
    cout << n;
  }
  cout << "\n";
}

void alternate_tests() {
  cout.precision(15);
  // Basic test
  Arrangements standard;

  cout << "\nPanel Shuffles for 4 panelists.\n";
  show_result(standard.panel_shuffles(4));

  cout << "\nPanel Shuffles for 10 panelists.\n";
  show_result(standard.panel_shuffles(10));

  int n = 1;

  // Count tests
  Timer t_pc("panel count", true);
  cout << "\nPanel Shuffle Count Table (0.1 seconds)\n";
  cout << "     N  panel(N)\n";
  while (n < 52 and t_pc.time() < 0.1) {
    t_pc.start();
    double pc = standard.panel_count(n);
    t_pc.stop();
    cout << std::setw(6) << n << " "
         << std::setw(6) << pc << "\n";
    n++;
  }

  cout << "\nHow many panel shuffles can be created in 0.5 seconds?\n";
  n = 4;

  Timer t_panel("panel", true);

  while (t_panel.time() < 0.5)  {
    t_panel.start();
    vector<string> res = standard.panel_shuffles(n);
    t_panel.stop();
    show_partial_result("panel", res, n);
    n++;
  }
  cout << "\nLargest panel shuffles performed: "
       << n - 1 << "\n";
}


void interactive_main() {
  std::string asktype, symbols;
  int number;
  cout << "Type quit to exit.\n";
  cout << "Commands:\npc names n\nps names n\ndc names n\nds names n\n";
  cout.precision(15);

  while (true) {
    std::cin >> asktype;
    if (asktype == "quit") break;
    std::cin >> symbols;
    Arrangements h(symbols);
    std::cin >> number;
    if (asktype == "pc") {
      std::cout << "panel_count(" << number <<  ") = ";
      std::cout << h.panel_count(number) << "\n";
    } else if (asktype == "ps") {
      std::cout << "panel_shuffles(" << number <<  ") = ";
      for (auto e : h.panel_shuffles(number) )
        std::cout << e << " ";
      std::cout << "\n";
    } else if (asktype == "dc") {
      std::cout << "dinner_count(" << number << ") = ";
      std::cout << h.dinner_count(number) << "\n";
    } else if (asktype == "ds") {
      std::cout << "dinner_shuffles(" << number <<  ") = ";
      for (auto e : h.dinner_shuffles(number))
        std::cout << e << " ";
      std::cout << "\n";
    }
  }
}
