// Copyright 2018 Alexander Trinh aktrinh@bu.edu
#include <iostream>
#include <string>
#include <array>
#include <vector>
#include <map>


using std::cout;
using std::string;
using std::vector;

int xWins(string);
int yWins(string);
int numMoves(string, char);

char tttresult(string tttboard, bool * perror)
{
	// checks for invalid boards
	if (tttboard.length() != 9)
		*perror = 1;
	for (int i = 0; i <= 9; i++)
	{
		if (tttboard[i] != '#' && tttboard[i] != 'x' && tttboard[i] != 'o')
			*perror = 1;
	}
	// checks for more than one line of winning
	if (xWins(tttboard) > 1)
		return 'i';
	if (yWins(tttboard) > 1)
		return 'i';
	// checks for a move out of order 
	if (numMoves(tttboard, 'o') > numMoves(tttboard, 'x'))
		return 'i';
	if (numMoves(tttboard, 'x') > (numMoves(tttfunctions, 'o')+1))
		return 'i';


	// returns for valid x or o wins
	if (xWins(tttboard) == 1 && oWins(tttboard) == 0)
	{
		return 'x';
	}
	else if (xWins(tttboard) == 0 && oWins(tttboard) == 1)
	{
		return 'o';
	}

	// returns for tie game if all spaces are filled and there are no winners
	if (!tttboard.find('#'))
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

int xWins(string tttboard)
{
	int x;
	// checks for row wins
	if (tttboard.substr(0,2) == "xxx")
		x++;
	if (tttboard.substr(3,5) == "xxx")
		x++;
	if (tttboard.substr(6,8) == "xxx")
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
	int o;
	// checks for row wins 
	if (tttboard.substr(0,2) == "ooo")
		o++;
	if (tttboard.substr(3,5) == "ooo")
		o++;
	if (tttboard.substr(6,8) == "ooo")
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
	int count;
	for (int i = 0; i < tttboard.length(); i++)
	{
		if (tttboard[i] == choice)
			count++;
	}
	return count;
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

char tttresult(vector<Move> board) {
  return 'i';
}

string charReplace(string orig, string remove, string change)
{
	int position;
	do
	{
		position = orig.find(remove);
		if (position != -1)
			orig.replace(position, remove.length(), change))
	} while (position != -1);

	return orig;
}

vector<string> get_all_boards() {
  vector<string> boards;
  string tttcombo;

  // converts the decimal number into base 3
  // then converts the base 3 number into a ttt format
  // and adds it to the vector boards
  for (int i = 0; i <= 19682; i++)
  {
  	tttcombo = convertbase(i, 10, 3);
  	charReplace(tttcombo, '0', '#');
  	charReplace(tttcombo, '1', 'x');
  	charReplace(tttcombo, '2', 'o');
  	boards.push_back(tttcombo);
  }

  return boards;
}

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
