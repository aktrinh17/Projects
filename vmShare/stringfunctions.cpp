// Copyright 2018 Alexander Trinh aktrinh@bu.edu

// stringfunctions_original.cpp is a template
//
// make a copy of this file to stringfunctions.cpp to submit.
//
// error  output  is coded as follows:

// w - is_word
// p - is_palindrome
// a - add
// c - convertbase
// m - multibase

#include <iostream>
#include <string>
using std::string;
using std::cerr;
using std::cout;
using std::cin;

// checks if a string is a valid word
bool is_word(string s) {
  int checkCapital = 0;
  int checkLower = 0;

  if (!s.length()) {
    return false;
  }

  for (int i = 0; i < s.length(); i++) {
    if (s[i] >= 'A' && s[i] <= 'Z') {
      checkCapital += 1;
    } else if (s[i] >= 'a' && s[i] <= 'z') {
      checkLower += 1;
    }
  }

  // its all capital letters
  if (checkCapital == s.length()) {
    return true;
  } else if (checkLower == s.length()) {
    return true;  // all lower
  } else if ((checkLower == s.length() - 1) && s[0] >= 'A' && s[0] <= 'Z') {
    // only the first letter is capital
    return true;
  }
  return false;
}

// checks for palindromes for number strings
bool is_palindrome(string num, bool * error) {
  *error = false;
  if (num.length() == 1) {
    return true;
  }
  if (num.length() > 1 && num[0] == '0') {
    *error = true;
    return false;
  }
  if (num[0] == '-') {
    *error = true;
    return false;
  }
  for (int j = 0; j < num.length(); j++) {
    if (num[j] >= 'A' && num[j] <= 'z') {
      *error = true;
      return false;
    }
  }

  for (int i = 0; i <= num.length() / 2; i++) {
    if (num[i] == '.') {
      *error = true;
      return false;
    }
    if (num[i] != (num[num.length() - 1 - i])) {
      return false;
    }
  }
  return true;
}

// adds two numbers in string form
string add(const string& num1, const string& num2) {
  string number1 = num1;
  string number2 = num2;
  string result = "";
  string zero = "0";
  int carry = 0;
  int sum = 0;
  int remainder = 0;

  // pads the shorter number with zeros to create numbers
  // of equal length
  while (number1.length() > number2.length()) {
    number2 = zero + number2;
  }

  while (number2.length() > number1.length()) {
    number1 = zero + number1;
  }
  // convert [i] index to int and add from num1 and num2
  // if number is 10 or above, add 1 to the next digit
  // otherwise, just take the sum
  for (int i = number1.length() - 1; i >= 0; i--) {
    sum = (number1[i] - '0') + (number2[i] - '0') + carry;

    // is triggered if there is an overflow within the single
    // digit addition, then sets carry to 1 to add to the next
    // round of addition
    if (sum >= 10) {
      remainder = sum % 10;
      carry = 1;
    } else {
      remainder = sum;
      carry = 0;
    }
    // convert remainder to string and add it as the most significant digit
    result = std::to_string(remainder) + result;
  }

  // is only triggered if there is still a carry after the for loop finishes
  // adds the carry to the beginning of the number to finish the adding
  if (carry == 1) {
    result = std::to_string(carry) + result;
  }
  return result;
}

// converts a number form one base to another
string convertbase(const string& numstr, const int frombase, const int tobase) {
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

// taken from the end of the is_palindrome function
// returns true if a number is a palindrome
bool palinChecker(string num) {
  for (int i = 0; i <= num.length() / 2; i++) {
    if (num[i] != (num[num.length() - 1 - i])) {
      return false;
    }
  }
  return true;
}

// checks for valid palindromes of a number in bases from 2 to
// one less than the number
string multibase(int x) {
  string strValNum = std::to_string(x);
  string validBases = "";

  // loops from 2 to one less than the number
  for (int i = 2; i <= x - 1; i++) {
    // converts the number into a different base and checks if it
    // is a palindrome, if it is, then it adds the valid base to the string
    if (palinChecker(convertbase(strValNum, 10, i))) {
      validBases = validBases + std::to_string(i) + " ";
    }
  }
  // gets rid of the extra space after the string of valid bases
  validBases = validBases.erase(validBases.length() - 1);

  return validBases;
}

// leave this line and everything below as is
int main() {
  bool error;

  cerr << std::boolalpha;
  cout << std::boolalpha;

  // is_word basic tests
  if (not is_word("test")) cerr << "we1\n";
  if (not is_word("Test")) cerr << "we2\n";
  if (not is_word("TEST")) cerr << "we3\n";
  if (not is_word("thisisaword")) cerr << "we4\n";

  if (is_word("123")) cerr << "we5\n";
  if (is_word("")) cerr << "we6\n";
  if (is_word("abc123abc")) cerr << "we7\n";
  if (is_word("tEst")) cerr << "we8\n";
  if (is_word("tEst")) cerr << "we9\n";
  if (is_word("TESTer")) cerr << "we10\n";


  // is_palindrome basic tests
  if (not is_palindrome("12321", &error) or error) cerr << "pe1\n";
  if (not is_palindrome("9009", &error) or error) cerr  << "pe2\n";
  if (not is_palindrome("9", &error) or error)  cerr << "pe3\n";
  if (not is_palindrome("123456777654321", &error) or error) cerr << "pe4\n";

  if (is_palindrome("abcba", &error) or not error) cerr << "pe5\n";
  if (is_palindrome("12321 a", &error) or not error) cerr << "pe6\n";
  if (is_palindrome("0012100", &error) or not error) cerr << "pe7\n";

  if (is_palindrome("123", &error) or error) cerr << "pe8\n";
  if (is_palindrome("123211", &error) or error) cerr << "pe9\n";
  if (not is_palindrome("0", &error) or error)  cerr << "pe10\n";

  // add basic tests
  if (add("123", "456") != "579") cerr << "ae1\n";
  if (add("123", "4") != "127") cerr << "ae2\n";
  if (add("1234", "9") != "1243") cerr << "ae3\n";
  if (add("88", "12") != "100") cerr << "ae4\n";
  if (add("1234567890123456789", "10000000000000999")
      != "1244567890123457788") cerr << "ae5\n";

  string longone(120, '2');
  longone[0] = '3';
  string longother(123, '1');
  longother[0] = '4';
  longother[3] = '2';
  string longresult(123, '3');
  longresult[0] = '4';
  longresult[1] = '1';
  longresult[2] = '1';
  longresult[3] = '5';

  if (add(longone, longother) != longresult ) cerr << "ae6\n";

  // convertbase tests

  if (convertbase("1111", 2, 10) != "15" ) cerr << "ce1\n";
  if (convertbase("255", 10, 16) != "??")  cerr << "ce2\n";
  if (convertbase("755", 8, 2) != "111101101") cerr << "ce3\n";

  if (convertbase("987123", 30, 30) != "987123" ) cerr << "ce4\n";
  if (convertbase("azbc", 100, 10) != "49745051") cerr << "ce5\n";

  if (convertbase("azbc", 100, 2) != "10111101110000110010011011")
    cerr << "ce6\n";

  // multibase tests

  if (multibase(121) != "3 7 8 10 120") cerr << "me1\n";
  if (multibase(45) != "2 8 14 44") cerr << "me2\n";
  if (multibase(63) != "2 4 8 20 62") cerr << "me3\n";
  if (multibase(10) != "3 4 9") cerr << "me4\n";


  // ad-hoc tests from cin

  string asktype;
  bool res;
  string userinput, num1, num2;
  int mbase, frombase, tobase;



  while (cin >> asktype) {
    if (asktype == "w") {  // is_word
      std::cin >> userinput;
      cout << is_word(userinput) << "\n";
    } else if (asktype == "p") {  // p - is_palindrome
      std::cin >> userinput;
      res = is_palindrome(userinput, &error);
      cout << res << " " << error << "\n";
    } else if (asktype == "a") {  // a - add
      std::cin >> num1 >> num2;
      cout << add(num1, num2) << "\n";
    } else if (asktype == "c") {  // c - convertbase
      std::cin >> userinput >> frombase >> tobase;
      cout << convertbase(userinput, frombase, tobase) << "\n";
    } else if (asktype == "m") {  // m - multibase
      std::cin >> mbase;
      cout << multibase(mbase) << "\n";
    } else {
      return 0;
    }
  }
  return 0;
}
