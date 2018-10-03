// Copyright Alexander Trinh aktrinh@bu.edu
// Copyright Zach Halvorson zthalv@bu.edu

// This program simulates stone movement and collisions in 2-D space
// if given initial velocities, mass, position
#include <iostream>
#include <algorithm>
#include <cmath>
#include <iostream>
#include <map>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

using std::ostream;
using std::istream;
using std::cout;
using std::cin;
using std::string;
using std::vector;

#define NOCOLLISION -1

class vector2d {
  public:
  double x,y;

  vector2d() {
    x=y=0;
  }

  vector2d(double xx, double yy) :x(xx) , y(yy) {}

  // defines operator for adding a vector comprising
  // of x and y components
  vector2d operator+(const vector2d& other) const {
    return vector2d(x+other.x,y+other.y);
  }

  //defines operator for subtracting a vector comprising
  // of x and y components
  vector2d operator-(const vector2d& other) const {
    return vector2d(x-other.x,y-other.y);
  }

  // defines dot operator
  friend vector2d operator*(const double &scalar, const vector2d &v) { //looks good
    return vector2d(scalar*v.x, scalar*v.y);
  }

  // defines dot operator for vector multiplication
  friend double operator*(const vector2d &u, const vector2d &v) { //confirmed
    return u.x*v.x + u.y*v.y;
  }

  friend ostream& operator<<(std::ostream& os, const vector2d &v) {
  os << "(" << v.x <<  "," << v.y << ")";
    return os;
  }

  friend istream& operator>>(istream& is, vector2d &v) {
    cin >> v.x >> v.y;
    return is;
  }
};

class Stone {
 public:
  vector2d pos, vel;
  double mass;
  double radius;
  string name;

  // calculates the position as a function of time
  void move(double time) {
    pos.x += vel.x*time;
    pos.y += vel.y*time;
  }

  // solves a quadratic equation to calculate the time
  // of collision of the stones
  double collide_time(const Stone& s) {

    vector2d u = pos-s.pos;
    vector2d w = vel-s.vel;

    double radsq = (radius+s.radius)*(radius+s.radius);
    double c = u*u - radsq;
    double b = 2*(w*u);
    double a = w*w;
    double discr = (b*b) - (4*a*c);
    double posroot  = (-b + sqrt(discr))/(2*a);
    double negroot  = (-b - sqrt(discr))/(2*a);

    if (negroot > 0.0) {
      return negroot;
    }
    if (posroot <= 0.0) { //if there is no collision, return a value that is greater
    return 1001;
    }
    return posroot;
  }

  // handles the changing velocities of stones
  void collide(Stone* s) {
    vector2d vi = vel;
    vector2d vj = s->vel;

    double m1factor = (2*s->mass)/(mass+s->mass);
    double m2factor = (2*mass)/(mass+s->mass);

    vector2d w1 = (vel-s->vel);
    vector2d w2 = (s->vel-vel);

    vector2d u1 = (pos-s->pos);
    vector2d u2 = (s->pos-pos);

    // formulas for calculating the new velocities of collided stones
    vector2d via = vel - ((m1factor)*((w1*u1)/(u1*u1))*u1);
    vector2d vja = s->vel - ((m2factor)*((w2*u2)/(u2*u2))*u2);

    vel = via;
    s->vel = vja;
  }

  // used for sorting the stones in alphabetical order
  // not completed needs work
  bool operator<(const Stone & other) {
/*
    if (other.name<) {
      return true;
    }*/
    return true;
  }

  vector2d momentum() const {
    return mass * vel;
  }

  double energy() const {
    return 0.5 * mass * vel * vel;
  }

  friend std::ostream& operator<<(std::ostream& os, const Stone& i) {
    os << i.name << " m=" << i.mass << " R=" << i.radius
       << " p=" << i.pos << " v=" << i.vel << "\n";
    return os;
  }

  friend std::istream& operator>>(std::istream& is, Stone& i) {
    cin >> i.mass >> i.radius >> i.pos >> i.vel >> i.name;
    return is;
  }
};

// class for the collision of two stone objects
class Collision {
 public:
  Stone* one;
  Stone* two;
  double time;

  // tests for valid collisions be observing the dot product of 
  // the difference in position and velocity
  bool valid() {
    // calculates the position between the two stones
    vector2d u = (one->pos) - (two->pos);

    //calculates the velocity between the two stones
    vector2d v = (one->vel) - (two->vel);

    double test = u*v;
    if (test < 0.00) {
      return true;
    }
    return false;
  }

  Collision() {
  time = 0;
  }

  Collision(double t, Stone* p1, Stone* p2) {
    time = t;
    one = p1;
    two = p2;
  }


  friend std::ostream& operator<<(std::ostream& os, const Collision& i) {
    os << i.one->name << " " << i.two->name << "\n";
    return os;
  }

};


Collision get_next_collision(vector<Stone> * ps) {
double time;
double first = 1000.0;

Stone* one;
Stone* two;

  for (int i = 0; i < ps->size(); i++) {
    for (int j = i+1; j < ps->size(); j++) {
      Stone* p1 = &ps->at(i);
      Stone* p2 = &ps->at(j);
      time = p1->collide_time(*p2);

      if (time < first) {
        first = time;
        one = p1;
        two = p2;
      }
    }
  }
  // creates a collision object with stones one and two from the
  // passed in vector<Stone>
  Collision c(first, one, two);
  return c;
}

void show_stones(vector<Stone> const & stones) {
  double energy{0};
  vector2d momentum;
  for (auto & s : stones) {
    cout << s;
    momentum = momentum +  s.momentum();
    energy += s.energy();
  }
  cout << "energy: " << energy << "\n";
  cout << "momentum: " << momentum << "\n";
}

int main() {
  double overall_time = 0;

  cout << "Please enter the mass, radius, x/y position, x/y velocity\n";
  cout << "and name of each stone\n";
  cout << "When complete, use EOF / Ctrl-D to stop entering\n";

  vector<Stone> stones;
  Stone s;
  while (cin >> s)
    stones.push_back(s);
  sort(stones.begin(), stones.end());

  cout << "\nHere are the initial stones.\n";
  show_stones(stones);

  cout << "\nHere are the collision events.\n";
  while (true) {
    Collision c = get_next_collision(&stones);//this line deletes/doesn't create the right x position for one of our two stones

    if (c.time >= 1000) break;

    if (!c.valid()) break;

    double newtime = c.time;
    for (auto & s : stones)
    s.move(newtime);
    overall_time += newtime;
    cout << "\ntime of event: " << overall_time << "\n";
    cout << "colliding " << c;
    c.one->collide(c.two);
    show_stones(stones);
  }
}
