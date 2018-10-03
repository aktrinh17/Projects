// Copyright 2018 Alexander Trinh aktrinh@bu.edu
#include <iostream>

int digitSquareSum(int);

int main() {
  int userInput;

  // runs until the user enters a 0
  while (true) {
    std::cin >> userInput;
    if (userInput == 0)
      break;

    int checkNext = userInput;
    int checkNextNext = userInput;

    // checks for when the numbers meet at 1 or reach 4
    do {
      checkNext = digitSquareSum(checkNext);
      checkNextNext = digitSquareSum(digitSquareSum(checkNextNext));
      if (checkNextNext == 4) {
        break;
      }
    } while (checkNext != checkNextNext);

    // if the number is equal to 1 it means the number is happy
    if (checkNextNext == 1) {
      printf("%d is happy\n", userInput);
    } else {
      printf("%d is not happy\n", userInput);
    }
  }
}

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


