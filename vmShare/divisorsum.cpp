// Copyright 2018 Alexander Trinh aktrinh@bu.edu
#include <iostream>

int main() {
  int64_t runSum;
  int i;
  while (true) {
    std::cin >> i;
    if (i == 0)
      break;
    runSum = 1;
    printf("%d: 1", i);
    for (int j = 2; j <= i / 2; j++) {
      if ((i % j) == 0) {
        printf("+%d", j);
        runSum += j;
      }
    }
    if (i != 0) {
      printf(" = %ld", runSum);
      printf("\n");
    }
  }
  return 0;
  printf("\n");
}
