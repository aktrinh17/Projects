// Copyright 2018 Alexander Trinh aktrinh@bu.edu
#include <array>
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include "movedef.h"

using std::cout;
using std::string;
using std::vector;

int xoWins(string tttboard, char choice) {
  int x = 0;
  // checks for row wins
  if (tttboard[0] == choice && tttboard[1] == choice && tttboard[2] == choice)
    x++;
  if (tttboard[3] == choice && tttboard[4] == choice && tttboard[5] == choice)
    x++;
  if (tttboard[6] == choice && tttboard[7] == choice && tttboard[8] == choice)
    x++;
  // checks for column wins
  if (tttboard[0] == choice && tttboard[3] == choice && tttboard[6] == choice)
    x++;
  if (tttboard[1] == choice && tttboard[4] == choice && tttboard[7] == choice)
    x++;
  if (tttboard[2] == choice && tttboard[5] == choice && tttboard[8] == choice)
    x++;
  // checks for diagonal wins
  if (tttboard[0] == choice && tttboard[4] == choice && tttboard[8] == choice)
    x++;
  if (tttboard[2] == choice && tttboard[4] == choice && tttboard[6] == choice)
    x++;
  return x;
}

int numMoves(string tttboard, char choice) {
  int count = 0;
  for (int i = 0; i < tttboard.length(); i++) {
    if (tttboard[i] == choice)
      count++;
  }
  return count;
}

char tttresult(string tttboard) {
  // checks for invalid boards
  if (tttboard.length() != 9)
    return 'e';
  for (int j = 0; j < 9; j++) {
    if (tttboard[j] != '#' && tttboard[j] != 'x' && tttboard[j] != 'o')
      return 'e';
  }
  // checks for a move out of order
  if ((numMoves(tttboard, 'o')) > (numMoves(tttboard, 'x')))
    return 'i';
  if ((numMoves(tttboard, 'x')) > (numMoves(tttboard, 'o') + 1))
    return 'i';
  // there cant be more than 1 winner
  if (xoWins(tttboard, 'x') == 1 && xoWins(tttboard, 'o') == 1)
    return 'i';
  if (xoWins(tttboard, 'o') > 1)
    return 'i';
  // checks for more than one line of winning or for a valid double win
  if (xoWins(tttboard, 'x') > 1) {
    if (xoWins(tttboard, 'x') == 2 && numMoves(tttboard, 'x') == 5)
      return 'x';
    else
      return 'i';
  }
  // returns for valid x or o wins
  if (xoWins(tttboard, 'x') == 1 && xoWins(tttboard, 'o') == 0) {
    if (numMoves(tttboard, 'x') != numMoves(tttboard, 'o') + 1) return 'i';
    else
      return 'x';
  }
  if (xoWins(tttboard, 'x') == 0 && xoWins(tttboard, 'o') == 1) {
    if (numMoves(tttboard, 'x') != numMoves(tttboard, 'o')) return 'i';
    else
      return 'o';
  }
  // returns for tie game if all spaces are filled and there are no winners
  if ((tttboard.find('#')) == -1) {  // triggered if # is not found
    if (xoWins(tttboard, 'x') == 0 && xoWins(tttboard, 'o') == 0)
      return 't';
  } else {
    return 'c';
  }
  // if there are empty spaces found, then the game continues
}
// converts a string of numbers from a base to another base
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

char tttresult(vector<Move> board) {
  string blankBoard = "#########";
  for (int j = 0; j < board.size(); j++) {
    if (board[j].r == 0) {
      if (board[j].c == 0) blankBoard[0] = board[j].player;
      else if (board[j].c == 1) blankBoard[1] = board[j].player;
      else if (board[j].c == 2) blankBoard[2] = board[j].player;
    }
    if (board[j].r == 1) {
      if (board[j].c == 0) blankBoard[3] = board[j].player;
      else if (board[j].c == 1) blankBoard[4] = board[j].player;
      else if (board[j].c == 2) blankBoard[5] = board[j].player;
    }
    if (board[j].r == 2) {
      if (board[j].c == 0) blankBoard[6] = board[j].player;
      else if (board[j].c == 1) blankBoard[7] = board[j].player;
      else if (board[j].c == 2) blankBoard[8] = board[j].player;
    }
  }
  return tttresult(blankBoard);
}
// converts the decimal number into base 3
// then converts the base 3 number into a ttt format
// and adds it to the vector boards
vector<string> get_all_boards() {
  vector<string> boards;
  string tttcombo;
  char result;
  int x, o, t, i, c;
  x = o = t = i = c = 0;
  for (int loopVar = 0; loopVar < 19683; loopVar++) {
    tttcombo = convertbase(std::to_string(loopVar), 10, 3);
    // pads the front of the number with 0s until it reaches 9 digits
    while (tttcombo.length() < 9) {
      tttcombo = '0' + tttcombo;
    }
    // converts the base 3 number into ttt format
    for (int j = 0; j < tttcombo.length(); j++) {
      if (tttcombo[j] == '0') {
        tttcombo[j] = '#';
      } else if (tttcombo[j] == '1') {
        tttcombo[j] = 'x';
      } else if (tttcombo[j] == '2') {
        tttcombo[j] = 'o';
      }
    }
    std::map<char, int> tally;
    result = tttresult(tttcombo);
    tally[result] += 1;
    boards.push_back(tttcombo);
  }
  return boards;
}

// MAIN

int main() {
  int n;
  std::string board;
  Move m;
  std::vector<Move> moves;
  std::vector<std::string> boards;
  std::string asktype;

  while (std::cin >> asktype) {
    if (asktype == "v") {  // test tttresult vector
      moves.clear();
      std::cin >> n;
      for (int i = 0; i < n; i++) {
        std::cin >> m.r >> m.c >> m.player;
        moves.push_back(m);
      }
      std::cout << tttresult(moves) << "\n";
    } else if (asktype == "s") {  // test tttresult string
      std::cin >> board;
      std::cout << tttresult(board) << "\n";
    } else if (asktype == "a") {  // test get_all_boards
      boards = get_all_boards();
      for (auto b : boards) {
        std::cout << b << "\n";
      }
    } else {
      return 0;
    }
  }
  return 0;
}
