// Copyright 2018 Alexander Trinh aktrinh@bu.edu
#include <iostream>
#include <string>
#include <array>
#include <vector>
#include <map>

using std::cout;
using std::string;
using std::vector;

int xWins(string tttboard)
{
	int x = 0;
	// checks for row wins
	if (tttboard[0] == 'x' && tttboard[1] == 'x' && tttboard[2] == 'x')
		x++;
	if (tttboard[3] == 'x' && tttboard[4] == 'x' && tttboard[5] == 'x')
		x++;
	if (tttboard[6] == 'x' && tttboard[7] == 'x' && tttboard[8] == 'x')
		x++;
	// checks for column wins
	if (tttboard[0] == 'x' && tttboard[3] == 'x' && tttboard[6] == 'x')
		x++;
	if (tttboard[1] == 'x' && tttboard[4] == 'x' && tttboard[7] == 'x')
		x++;
	if (tttboard[2] == 'x' && tttboard[5] == 'x' && tttboard[8] == 'x')
		x++;
	// checks for diagonal wins
	if (tttboard[0] == 'x' && tttboard[4] == 'x' && tttboard[8] == 'x')
		x++;
	if (tttboard[2] == 'x' && tttboard[4] == 'x' && tttboard[6] == 'x')
		x++;
	return x;
	
}

int oWins(string tttboard)
{
	int o = 0;
	// checks for row wins 
	if (tttboard[0] == 'o' && tttboard[1] == 'o' && tttboard[2] == 'o')
		o++;
	if (tttboard[3] == 'o' && tttboard[4] == 'o' && tttboard[5] == 'o')
		o++;
	if (tttboard[6] == 'o' && tttboard[7] == 'o' && tttboard[8] == 'o')
		o++;
	// checks for column wins
	if (tttboard[0] == 'o' && tttboard[3] == 'o' && tttboard[6] == 'o')
		o++;
	if (tttboard[1] == 'o' && tttboard[4] == 'o' && tttboard[7] == 'o')
		o++;
	if (tttboard[2] == 'o' && tttboard[5] == 'o' && tttboard[8] == 'o')
		o++;
	// checks for diagonal wins
	if (tttboard[0] == 'o' && tttboard[4] == 'o' && tttboard[8] == 'o')
		o++;
	if (tttboard[2] == 'o' && tttboard[4] == 'o' && tttboard[6] == 'o')
		o++;
	return o;
}

int numMoves(string tttboard, char choice)
{
	int count = 0;
	for (int i = 0; i < tttboard.length(); i++)
	{
		if (tttboard[i] == choice)
			count++;
	}
	return count;
}

char tttresult(string tttboard, bool * perror)
{
	// checks for invalid boards
	if (tttboard.length() != 9)
		*perror = true;
	for (int j = 0; j < 9; j++)
	{
		if (tttboard[j] != '#' && tttboard[j] != 'x' && tttboard[j] != 'o')
			*perror = true;
	}

	// checks for a move out of order 
	if ((numMoves(tttboard, 'o')) > (numMoves(tttboard, 'x')))
		return 'i';
	if ((numMoves(tttboard, 'x')) > (numMoves(tttboard, 'o') + 1))
		return 'i';

	// there cant be more than 1 winner
	if (xWins(tttboard) == 1 && oWins(tttboard) == 1)
		return 'i';

	if (oWins(tttboard) > 1)
		return 'i';

	// checks for more than one line of winning or for a valid double win
	if (xWins(tttboard) > 1)
	{
		if (xWins(tttboard) == 2 && numMoves(tttboard, 'x') == 5)
			return 'x';
		else
			return 'i';
	}

	// returns for valid x or o wins
	if (xWins(tttboard) == 1 && oWins(tttboard) == 0)
		if (numMoves(tttboard, 'x') != numMoves(tttboard, 'o') + 1) {
			return 'i';
		} else {
			return 'x';
		}
	if (xWins(tttboard) == 0 && oWins(tttboard) == 1)
		if (numMoves(tttboard, 'x') != numMoves(tttboard, 'o')) {
			return 'i';
		} else {
			return 'o';
		}

	// returns for tie game if all spaces are filled and there are no winners
	if ((tttboard.find('#')) == -1)  // triggered if # is not found
	{
		if (xWins(tttboard) == 0 && oWins(tttboard) == 0)
			return 't';
	} 
	// if there are empty spaces found, then the game continues
	else
	{
		return 'c';
	}
}

//converts a string of numbers from a base to another base
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

/*
char tttresult(vector<Move> board) {
  return 'i';
}
*/

// converts the decimal number into base 3
  // then converts the base 3 number into a ttt format
  // and adds it to the vector boards
vector<string> get_all_boards() {
  vector<string> boards;
  string tttcombo;
  char result;
  int x, o, t, i, c;
  x = o = t = i = c = 0;
  bool perror;

  for (int loopVar = 0; loopVar < 19683; loopVar++)
  {
  	tttcombo = convertbase(std::to_string(loopVar), 10, 3);
  	// pads the front of the number with 0s until it reaches 9 digits
  	while (tttcombo.length() < 9)
  	{
  		tttcombo = '0' + tttcombo;
  	}

  	// converts the base 3 number into ttt format
  	for (int j = 0; j < tttcombo.length(); j++)
  	{
  		if (tttcombo[j] == '0')
  		{
  			tttcombo[j] = '#';
  		}
  		else if (tttcombo[j] == '1')
  		{
  			tttcombo[j] = 'x';
  		}
  		else if (tttcombo[j] == '2')
  		{
  			tttcombo[j] = 'o';
  		}
  	}
  	result = tttresult(tttcombo, &perror);
  	if (result == 'x')
  	{
  		x++;
  	}
  	else if (result == 'o')
  	{
  		o++;
  	}
  	else if (result == 't')
  	{
  		t++;
  	}
  	else if (result == 'i')
  	{
  		i++;
  	}
  	else if (result == 'c')
  	{
  		c++; 
  	}
  	boards.push_back(tttcombo);
  }
  printf(" x: %d\n o: %d\n t:%d\n i:%d\n c: %d\n", x, o, t, i, c);
  return boards;
}

// MAIN

int main() {
	get_all_boards();
  return 0;
}
