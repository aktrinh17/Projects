// Copyright 2018 Alexander Trinh aktrinh@bu.edu
// Copyright 2018 Zach Halvorson zthalv@bu.edu
#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

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
  explicit Tile(vector<string>);
  void show() const;  // print out tile in tilebox format
  void rotate();
  void flipud();
  void fliplr();
};

class Blokus : public Tile {
  Tile first;
 public:
  vector<string> board;
  vector<string> hangboard;
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

void Tile::show() const {
  if (Tile::ID == 103)  // this means no tiles exist
    return;
  if (abs(tileNum - 3) > Tile::ID - 4)
    return;
  for (auto row : tileLayoutData) {
    cout << row << "\n";
  }
}

vector<string> shifter(vector<string> input) {
  int counter = 0;
  vector<string> rough;
  vector<string> polished;

  int tilesize = input.size();
  int index = tilesize;

  string filler;
  for (int i = 0; i < tilesize; i++) {
    filler.append(".", 1);
  }

  for (int i = 0; i < tilesize; i++) {
    string row = input.at(i);
    if (counter == 0) {
      if (row.find("*") != std::string::npos) {
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

  for (auto i : rough) {
    string clipped = i.substr(index);
    for (int i = 0; i < index; i++) {
      clipped.append(".", 1);
    }
    polished.push_back(clipped);
  }
  while (polished.size() != tilesize) {
    polished.push_back(filler);
  }
  return polished;
}

void Tile::rotate() {
  vector<string> tile = tileLayoutData;
  //  size of the rows
  int lastChar = tile.at(0).size();
  int range = tile.size();

  //  moves from rightmost column to left
  for (int i = 0; i < tileLayoutData.size(); i++) {
    // moves from topmost row to bottom
    for (int j = 0; j < tileLayoutData.size(); j++) {
      tile.at(i) += tileLayoutData.at(j).at(lastChar - i - 1);
    }
    // remove the old string formation
    tile.at(i).erase(0, range);
  }
  tileLayoutData = shifter(tile);
}


void Tile::flipud() {
  vector<string> tile = tileLayoutData;
  int range =  tile.size();
  for (int i = 0; i <= range / 2 - 1; i++) {
    std::swap(tile.at(0 + i), tile.at(range - 1 - i));
  }
  tileLayoutData = shifter(tile);
}

void Tile::fliplr() {
  vector<string> tile = tileLayoutData;
  for (int i = 0; i < tile.size(); i++) {
    string row = tile.at(i);
    int length =  row.size();
    for (int j = 0; j <= length / 2 - 1; j++) {
      std::swap(row.at(0 + j), row.at(length - 1 - j));
      tile.at(i) = row;
    }
  }
  tileLayoutData = shifter(tile);
}


vector<Tile*> pointerlist;  // index 0 would correspond to ID 100

Tile* Blokus::find_tile(TileID input) {
  /*  if (input < 100)
      return nullptr;
    if (input > Tile::ID)
      return nullptr;*/
  for (Tile* t : tiles) {
    if (t -> tileNum == input + 3)
      return t;
  }
}

void Blokus::show_tiles() const {
  cout << "tile inventory\n";
  for (int i = 0; i < tiles.size(); i++) {
    cout << (tiles.at(i) -> tileNum) - 3 << "\n";
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
  if (id < 100) {
    cout << id << " not played" << "\n";
    return;
  }

  if (id - 100 >= tiles.size()) {
    cout << id << " not played" << "\n";
    return;
  }

  vector<string> tile = tiles.at(id - 100) -> tileLayoutData;
  int maxsize = board.size();
  bool overlapindicator = false;
  r++;
  c++;

  for (int i = 0; i < tile.size(); i++) {
    for (int j = 0; j < tile.size(); j++) {
      if (i + r > maxsize) {
        if (static_cast<char>(tile.at(i).at(j)) == '*') {
          cout << id << " not played" << "\n";
          return;
        }
      } else if (j + c > maxsize) {
        if (static_cast<char>(tile.at(i).at(j)) == '*') {
          cout << id << " not played" << "\n";
          return;
        }
      }
    }
  }

  for (int i = 0; i < tile.size(); i++) {
    for (int j = 0; j < tile.size(); j++) {
      if ((i + r <= maxsize) && (j + c <= maxsize)) {
        string boardrow = board.at(i + r - 1);
        string tilerow = tile.at(i);
        if ((static_cast<char>(tilerow.at(j)) == '*') &&
            (static_cast<char>(boardrow.at(j + c - 1)) == '*')) {
          overlapindicator = true;
          cout << id << " not played" << "\n";
        }
      }
    }
  }
  if (!overlapindicator) {
    for (int i = 0; i < tile.size(); i++) {
      for (int j = 0; j < tile.size(); j++) {
        if ((i + r <= maxsize) && (j + c <= maxsize)) {
          string boardrow = board.at(i + r - 1);
          string tilerow = tile.at(i);
          if (static_cast<char>(tilerow.at(j) == '*'))
            board.at(i + r - 1).at(c + j - 1) = '*';
          // hangboard.at(r+i-1).at(c+j-1) = 'a';
        }
      }
    }
    cout << "played " << id << "\n";
  }
}

void Blokus::reset() {
  board.clear();
  tiles.clear();
  Tile::ID = 103;
  cout << "game reset" << "\n";
}

void Blokus::set_size(int newsize) {  // board is a vector of strings
//  stored in the Blokus class that represents the board
  if (board.size() == 0) {  // checks if the board exists/is size 0
    string row;
    for (int i = 0; i < newsize; i++) {
      row.append(".", 1);
    }
    for (int i = 0; i < newsize; i++) {
      board.push_back(row);  // pushes back this string that is newsize
      // characters long until the vector has newsize number of elements
    }
  } else {
    int current = board.size();
    int grow = newsize - current;  // only for making the board larger
    for (string& row : board) {  // loops through the existing board and
      // adds on periods to extend the board horizontally
      for (int i = 0; i < grow; i++) {
        row.append(".", 1);
      }
    }
    for (int i = current; i < newsize; i++) {  // this adds on the rows at
      string row;
      for (int i = 0; i < newsize; i++) {
        row.append(".", 1);
      }
      board.push_back(row);
    }
  }
}

void Blokus::create_piece() {
  int counter = 0;
  bool isempty = true;
  vector<string> rough;
  vector<string> polished;

  int tilesize;
  cin >> tilesize;
  int index = tilesize;

  string filler;
  for (int i = 0; i < tilesize; i++) {
    filler.append(".", 1);
  }

  for (int i = 0; i < tilesize; i++) {  // each time this loop occurs it takes
    // in the next row from CIN
    string row;
    cin >> row;
    if (row.size() != tilesize) {
      cout << "invalid tile" << "\n";
      return;
    }
    if (counter == 0) {
      if (row.find("*") != std::string::npos) {
        rough.push_back(row);
        counter++;
        isempty = false;
        if (row.find("*") < index)
          index = row.find("*");
      }
    } else {
      rough.push_back(row);
      if (row.find("*") < index)
        index = row.find("*");
    }
  }

  // the following occurs after the entire tile has been read in from CIN

  for (auto i : rough) {
    string clipped = i.substr(index);
    for (int i = 0; i < index; i++) {
      clipped.append(".", 1);
    }
    polished.push_back(clipped);
  }
  while (polished.size() != tilesize) {  // this ensures that the
    // tile is of the proper height by making
    // sure that the vector has the same number of elements as the tilesize
    polished.push_back(filler);  // pushes back a row of decimal
    // points of the proper width until the tile is now square
  }

  // here I would make the 8 alternate orientations and store
  // those in a seperate map based on the weight of the tile to
  // error check for duplicates

  for (int i = 0; i < tilesize; i++) {  // this makes sure that
    // the tile only contains * or .
    for (int j = 0; j < tilesize; j++) {
      if (polished.at(i).at(j) != '*') {
        if (polished.at(i).at(j) != '.') {
          cout << "invalid tile" << "\n";
          return;
        }
      }
    }
  }

  for (int row = 0; row < polished.size(); row++) {
    for (int col = 0; col < polished.size(); col++) {

      if(polished.at(row).at(col) == '*') {

        // rightmost star check
        if ((col+1) == polished.size()) {

          // right and top checking for one left and below
          if (row == 0) {
            if (polished.at(row).at(col-1) != '*' &&
              polished.at(row+1).at(col) != '*') {
              cout << "removed disconnected tile" << "\n";
              return;
            }
          }
          // right and bottom checking for one left and above
          if ((row+1) == polished.size()) {
            if (polished.at(row).at(col-1) != '*' &&
              polished.at(row-1).at(col) != '*') {
              cout << "removed disconnected tile" << "\n";
              return;
            }
          }
          // right middle star checking for one above, below, left
          if ((row+1) != polished.size() && row != 0) {
            if ((polished.at(row-1).at(col) != '*') &&
              (polished.at(row+1).at(col) != '*') &&
              polished.at(row).at(col-1) != '*') {
              cout << "removed disconnected tile" << "\n";
              return;
            }
          }
        }
        
        // leftmost star check
        if (col == 0) {

          // left and top checking for one right and below
          if (row == 0) {
            if ((polished.at(row).at(col+1) != '*') &&
              (polished.at(row+1).at(col) != '*')) {
              cout << "removed disconnected tile" << "\n";
              return;
            }
          }

          // left and bottom checking for one right and above
          if ((row+1) == polished.size()) {
            if ((polished.at(row).at(col+1) != '*') &&
              (polished.at(row-1).at(col) != '*')) {
              cout << "removed disconnected tile" << "\n";
              return;
            }
          }

          // left middle star checking one above, below, right
          if (row != 0 && (row + 1) != polished.size()) {
            if ((polished.at(row-1).at(col) != '*') &&
             (polished.at(row).at(col+1) != '*') &&
             (polished.at(row+1).at(col) != '*')) {
              cout << "removed disconnected tile" << "\n";
              return;
            }
          }
        }

        // top row star (not corner) checking for below, left, right
        if (row == 0 && col != 0 && (col+1) != polished.size()) {
          if (polished.at(row+1).at(col) != '*' &&
            polished.at(row).at(col-1) != '*' &&
            polished.at(row).at(col+1) != '*') {
            cout << "removed disconnected tile" << "\n";
            return;
          }
        }

        // bottom row star (not corner) checking for one above, left, right
        if ((row+1) == polished.size() && col != 0 && (col+1) != polished.size()) {
        if (polished.at(row-1).at(col) != '*' &&
            polished.at(row).at(col-1) != '*' &&
            polished.at(row).at(col+1) != '*') {
            cout << "removed disconnected tile" << "\n";
            return;
          }
        }

        // middle stars checking for one above, below, left, right
         if (row != 0 && (row + 1) != polished.size() &&
          col != 0 && (col + 1) != polished.size()) {
          if ((row+1) != polished.size() && row != 0 &&
            (col+1) != polished.size() && col != 0) {
            if (polished.at(row-1).at(col) != '*' &&
              polished.at(row+1).at(col) != '*' &&
              polished.at(row).at(col-1) != '*' &&
              polished.at(row).at(col+1) != '*') {
              cout << "removed disconnected tile" << "\n";
              return;
            }
          }
        } 
      } 
    }
  } 


  if (isempty) {
    cout << "invalid tile" << "\n";
    return;
  }
  

  tiles.push_back(new Tile(polished));
  cout << "created tile " << Tile::ID - 4 << "\n";
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
      getline(cin, command);
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
