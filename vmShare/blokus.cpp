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

//unordered_map<int, *Tile> tileBank;

class Blokus : public Tile{
  Tile first;
  public:

    std::map<int, vector<string>> duplicates;
    // std::map<int, vector<string>> tilebank;
    vector<string> board;
    // int Tile::id = 100;
    int name = 100;
    Tile data;
    /* // not sure how to iterate through the vector to find the tile
    Tile* find_tile(TileID) {
      for (int i = 0; i < tiles.at(i).size(); i++) {
        if (tiles.at(i).tileNum == TileID)
          return &tiles.at(i).tileLayoutData;
      }
    */

    // this just returns a random tile when called to get past compile errors
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
  tiles.push_back(this);
}

// constructor
Tile::Tile(vector<string> completeTile) {
  tileNum = ID;
  ID++;
  vector<string> tileLayoutData = completeTile;
  tiles.push_back(this);
}

void Tile::show() const{
cout << "test";
//  cout << TileID << "\n";
//  for (loop through all of the strings of the vector for that id)
//  cout <<
  for (auto t: tiles) {
    for (int i = 0; i < t -> tileLayoutData.size(); i++) {
      cout << t -> tileLayoutData.at(i);
    }
  }
}

void Tile::rotate() {

}

void Tile::flipud() {

}

void Tile::fliplr() {

}

Tile* Blokus::find_tile(TileID input) { 
  for (Tile* t : tiles) {
    if (t -> tileNum == input)
      return t;
  }
//this should be the main priority as the rotate, flip, and show functions all rely on being able to generate a Tile*
//to the correct instance of the tile that is being requested

 // return &SOMETHING; 
}

void Blokus::show_tiles() const {
  cout << "tile inventory \n"; //tile inventory is a line that is required by his examples to be printed
 // for (auto tile : tilebank)
 //tile->show();
/* print it out in the following format with the TileID first, then the tile
102
*
101
**
**
*/

}


void Blokus::show_board() const {
/*  
  for (int i = 0; i < tileBoard.size(); i++) {
    for (int j = 0; j < tileBoard.at(i).size(); j++) {
      cout << tileBoard.at(i).at(j) << "\n";
    }
  }
*/
//this should be easier to figure out as it is called b.show_board()

//so here we could just access the vector of strings directly and loop through each string and print
//it row by row

} 

void Blokus::play_tile(TileID, int, int) {


}

void Blokus::reset(){
  //need to clear all instances of the Tile class
  duplicates.clear();
  board.clear();
  set_size(0);// might be unnecassry depending on how the clear command works for board.clear()
  name = 100;//intended to reset the value of name in the blokus class to 100
}

void Blokus::set_size(int newsize) {//board is a vector of strings stored in the Blokus class that represents the board
  if (board.size() == 0) { //checks if the board exists/is size 0
    string row; //creates a string that represents the row by appending a certain length of this default string
    row.append("......................................",newsize); //where newsize is the size of the board
    for (int i = 0; i <= newsize; i++) {
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
  int tilesize;
  cin >> tilesize;

  int index = tilesize; //this term index correpsonds to the first column that contains a *, we set it ot the max size first and then reduce it
  //as we check each row inputted

  string filler;
  filler.append("........................", tilesize);

  vector<string> rough;
  vector<string> polished;

  for (int i = 0; i < tilesize; i++) { //each time this loop occurs it takes in the next row from CIN
    string row;
    cin >> row;
    if (row.size() != tilesize)
      //throw invalid if the row isn't the right size
    if (row.find("*")!=std::string::npos) { //this checks that there is a * in the row, and pushes it back into a vector if it does, otherwise it ignores that row
    //this is intended to make sure that the tile is as far up as possible, but there could be issues if there is an empty row in the middle of creating a tile
    //would only be an issue when the user is trying to make two tiles in one command, as any blank lines are ignored and are not saved
      rough.push_back(row);
      if (row.find("*") < index) //determines the first column that contains a * by checking if the location of the first * in the row is less than the index
      //the index starts at the end of the board, and is shifted left/decreased if the location of the first * is less than the location of all previous *s
        index = row.find("*");
    }
  }

  //the following occurs after the entire tile has been read in from CIN

  for (auto i : rough) { //this function takes the rough vector representing the tile
  //and trims off any empty columns to ensure that the tile is as far left as possible
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

  //Next we need to figure out how to create an instance of the Tile class and then assign the data to that instance.
  /*Tile objectname;
  objectname.tilebank = polished;*/
  //need to figure out how to change the name of the Tile class each time

  //this used to be a map<int vector<string>> where I would emplace the vector into the position correpsonding to the ID
  //tilebank.emplace(ID, polished);

  /*
            // creates a unique tile object
            Tile tileName_increment(ID, polished); 
            // stores the tile in a map
            tileBank.insert(std::make_pair(ID, tileName_increment));
  */

  Tile tileName_increment(polished);
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
