// Copyright 2018 Alexander Trinh aktrinh@bu.edu
// Copyright 2018 Zach Halvorson zthalv@bu.edu
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <utility>
#include <unordered_map>

// tuple, utility, set, unordered_map, unordered_set,

using std::cin;
using std::cout;
using std::string;
using std::vector;
using std::unordered_map;
using std::map;

/* Blokus command glossary

Notes:
 - the first tile is numbered 100, and each new
   one is assigned the next available integer

 - the upper left corner is 0,0

 - first index is row, second index is column


COMMANDS

QUIT: exit the game
>quit
Goodbye

RESET: start the game from beginning
>reset
game reset

CREATE: create a new tile

>create 4
>..*.
>.**.
>.*..
>....
created tile 100


SHOW ALL TILES: show a tile inventory (unordered.)

>show tiles
tile inventory
102
*
101
**
**
100
***
**.
...


SHOW A TILE: show a tile by ID number
>show 100
***
**.
**.

PLAY A TILE: place a tile on the board at row and column numbers

>play 101 4 5
played 101

>play 99 0 0
99 not played

ROTATE A TILE: rotate a tile 90 degrees counterclockwise
>rotate 100
rotate 100 complete
**.
*..
*..

FLIP A TILE sideways (left becomes right)
>fliplr 100
fliplr 100 complete
**.
.*.
.*.

FLIP A TILE vertically (up becomes down)
>flipud 100
flipud 100 complete
.*.
.*.
**.

RESIZE: make the board bigger or smaller. When smaller,
        played pieces fall off the board. Show the new board.

>resize 5

- end of command glossary -
*/


typedef int TileID;


int increment = 0;

class Tile {
  public:
    static int ID;
    int tileNum;
    vector<string> tileLayoutData;
    static vector<Tile*> tiles;
    Tile();
    Tile(vector<string>);
    void show() const;  // print out tile in tilebox format
    void rotate();
    void flipud();
    void fliplr();

};

class Blokus : public Tile {
  Tile first;
  public:

    vector<string> board;
    Tile data;
    Tile * find_tile(TileID);
    void create_piece();
    void reset();
    void show_tiles() const;
    void show_board() const;
    void play_tile(TileID, int, int);
    void set_size(int);
};

int Tile::ID = 100;
vector<Tile*> Tile::tiles;

// default constructor
Tile::Tile() {
  tileNum = ID;
  ID++;
}

// constructor
Tile::Tile(vector<string> completeTile) {
  tileNum = ID;
  ID++;
  tileLayoutData = completeTile;
}

void Tile::show() const{
  cout << tileNum-3 << "\n";
  for (auto row : tileLayoutData) {
    cout << row << "\n";
  }
}


void Tile::rotate() {

vector<string> tile = tileLayoutData;
  int range = tile.size(); // number of rows
  int lastChar = tile.at(0).size(); // size of row

  // moves from rightmost column to left
  for (int i = 0; i < range; i++) {
    // moves from topmost row to bottom
    for (int j = 0; j < range; j++)
      tile.at(i) += tileLayoutData.at(j).at(lastChar - i - 1); 
  }
  tileLayoutData = tile;
}

void Tile::flipud() {
  vector<string> tile = tileLayoutData;
  int range =  tile.size();
  for (int i = 0; i <= range/2-1; i++) {
    std::swap(tile.at(0+i), tile.at(range-1-i));
  }
  tileLayoutData = tile;
}

void Tile::fliplr() {
  vector<string> tile = tileLayoutData;
  for (int i = 0; i < tile.size(); i++) {
    string row = tile.at(i);
    int length =  row.size();
    for (int j = 0; j <= length/2-1; j++) {
      std::swap(row.at(0+j), row.at(length-1-j));
      tile.at(i) = row;
    }
  }
  tileLayoutData = tile;
}


vector<Tile*> pointerlist; //index 0 would correspond to ID 100

//take in the input, process the tile and create the vector<string>

Tile* Blokus::find_tile(TileID input) {
  for (Tile* t : tiles) {
    if (t -> tileNum == input+3)
      return t;
  }
}

void Blokus::show_tiles() const {
  cout << "tile inventory \n";
  for (int i = 0; i < tiles.size(); i++) {
    cout << (tiles.at(i) -> tileNum)-3 << "\n";
    for (int j = 0; j < (tiles.at(i) -> tileLayoutData).size(); j++) {
      cout << (tiles.at(i) -> tileLayoutData).at(j) << "\n";
    }
  }

}


void Blokus::show_board() const {
  for (auto row : board) {
    cout << row << "\n";
  }
}

void Blokus::play_tile(TileID id, int r, int c) {
  vector<string> tile = tiles.at(id-100) -> tileLayoutData;
  int maxsize = board.size();
  cout << tile.size();

  for (int i = 0; i < tile.size(); i++) { //loop through each row
    string boardrow = board.at(i+r);
    string tilerow = tile.at(i);
    cout << tilerow;
    for (int j = 0; j < tile.size(); j++) { //check each piece to see if there is already a * in that spot
      if (j > maxsize) { //special checking for when the board could hang off the edge
        if (char(tilerow.at(j)) == '.')
          cout << "no problemo";
        if (char(tilerow.at(j)) == '*')
          cout << "board hanging bad";
      } else {
        if ((char(tilerow.at(j)) == '*') && (char(boardrow.at(j+c))== '8')) {
          cout << "overlap" << "\n";
        } else if ((char(tilerow.at(j)) == '*') && (char(boardrow.at(j+c)) == '.')) {
          cout << "tile played";
          board.at(i).at(j+c-1) = '*';
        }
      }
      //no conflict because ..... only
    }
  }
}

void Blokus::reset(){ //this needs to be written completely
  board.clear();
}

void Blokus::set_size(int newsize) {//board is a vector of strings stored in the Blokus class that represents the board
  if (board.size() == 0) { //checks if the board exists/is size 0
    string row; //creates a string that represents the row by appending a certain length of this default string
    row.append("......................................",newsize); //where newsize is the size of the board
    for (int i = 0; i < newsize; i++) {
      board.push_back(row); //pushes back this string that is newsize characters long until the vector has newsize number of elements
    }
  } else {
    int current = board.size();
    int grow = newsize - current; //will only work for making the board larger
    for (string& row : board) { //loops through the existing board and adds on periods to extend the board horizontally
      row.append("........................", grow);
    }
    for (int i = current; i < newsize; i++) { //this adds on the rows at the bottom where the board didn't exist to extend it vertically downwards
      string row;
      row.append("......................................",newsize);
      board.push_back(row);
    }
  }
}

void Blokus::create_piece() {
  int counter = 0;
  vector<string> rough;
  vector<string> polished;

  int tilesize;
  cin >> tilesize;
  int index = tilesize;

  string filler;
  filler.append("........................", tilesize);

  for (int i = 0; i < tilesize; i++) { //each time this loop occurs it takes in the next row from CIN
    string row;
    cin >> row;
    if (row.size() != tilesize){
      cout << "invalid row size" << "\n";
      return;
    }
    if (counter == 0) {
      if (row.find("*")!=std::string::npos) {
        rough.push_back(row);
        counter++;
        if (row.find("*") < index)
        index = row.find("*");
      }
    } else {
    rough.push_back(row);
    if (row.find("*") < index)
      index = row.find("*");
    }
  }

  //the following occurs after the entire tile has been read in from CIN

  for (auto i : rough) {
    string clipped = i.substr(index);
    clipped.append("....................",index); //this then appends decimal points to the end of
    //each row to ensure that the tile is of proper width, we haven't corrected the height yet
    polished.push_back(clipped);
  }
  while (polished.size() != tilesize) { //this ensures that the tile is of the proper height by making
  //sure that the vector has the same number of elements as the tilesize
    polished.push_back(filler); //pushes back a row of decimal points of the proper width until the tile is now square
  }

  //here I would make the 8 alternate orientations and store those in a seperate map based on the weight of the tile to error check for duplicates

  tiles.push_back(new Tile(polished));

}


// MAIN. Do not change the below.


int main() {
  string command;
  Blokus b;

  while (true) {
    cin >> command;
    if (command == "quit")  {
      break;
    } else if (command == "//") {
      getline(cin,command);
    } else if (command == "board") {
      b.show_board();
    } else if (command == "create") {
      b.create_piece();
    } else if (command == "reset") {
      b.reset();
    } else if (command == "show") {
      string arg;
      cin >> arg;
      if (arg == "tiles") {
        b.show_tiles();
      } else {
        auto g = b.find_tile(std::stoi(arg));
        g->show();
      }
    } else if (command == "resize") {
      int newsize;
      cin >> newsize;
      b.set_size(newsize);
      b.show_board();
    } else if (command == "play") {
      TileID id;
      int row, col;
      cin >> id >> row >> col;
      b.play_tile(id, row, col);
    } else if (command == "rotate") {
      TileID id;
      cin >> id;
      auto g = b.find_tile(id);
      g-> rotate();
      cout << "rotated " << id << "\n";
      g->show();
    } else if (command == "fliplr") {
      TileID id;
      cin >> id;
      auto g = b.find_tile(id);
      g->fliplr();
      cout << "fliplr " << id << "\n";
      g->show();
    } else if (command == "flipud") {
      TileID id;
      cin >> id;
      auto g = b.find_tile(id);
      g->flipud();
      cout << "flipud " << id << "\n";
      g->show();
    } else {
      cout << "command not understood.\n";
    }
  }
  cout << "Goodbye\n";
  return 0;
}
