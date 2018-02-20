#include <iostream>
#include <string>
using std::string;
using std::cerr;
using std::cout;
using std::cin;

char tttresult(string tttboard, bool * perror)
{
	// checks for invalid boards

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

int main()
{
	return 0;
}
