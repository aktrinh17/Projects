// Copyright 2018 Alexander Trinh aktrinh@bu.edu
#include <iostream>
#include <string>

int main() {
  std::string str1 = "\"I will read\n";
  std::string str2 = "all the triangle poems\n";
  std::string str3 = "and present the best ones in class.\"\n";

  std::cout << str1 + str2 + str3;
  return 0;
}

