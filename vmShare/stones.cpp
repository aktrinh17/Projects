// Copyright Alex Trinh aktrinh@bu.edu
// Copyright Zach Halvorson zthalv@bu.edu
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

  vector2d operator+(const vector2d& other) const {
    return vector2d(x+other.x,y+other.y);
  }
  vector2d operator-(const vector2d& other) const {
    return vector2d(x-other.x,y-other.y);
  }

  friend vector2d operator*(const double &scalar, const vector2d &v) {
    return vector2d(scalar*v.x, scalar*v.y);
  }

  friend double operator*(const vector2d &u, const vector2d &v) { //prof commented this out
    return u.x*v.x + u.y*v.y;
  }

  friend ostream& operator<<(std::ostream& os, const vector2d &v) {
  os << "(" << v.x <<  "," << v.y << ")" << "\n";
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

  void move(double time) {
    pos.x += vel.x*time;
    pos.y += vel.y*time;
  }

  double collide_time(const Stone& s) {
    vector2d u = pos-s.pos;
    vector2d w = vel-s.vel;
    double radsq = (radius+s.radius)*(radius+s.radius);
    double c = u*u - radsq;
    double b = 2*(w*u);
    double a = w*w;
    double discr = b*b - 4*a*c;
    double posroot  = ((-b + sqrt(discr))/2*a);
    double negroot  = ((-b - sqrt(discr))/2*a);
    if (negroot > 0.0) {
      return negroot;
    }
    if (posroot < 0.0) {
    return 101;
    }
    return posroot;
  }

  void collide(Stone* s) { //handles the changing velocities
    vector2d vi = vel;
    vector2d vj = s->vel;

    double m1factor = (2*s->mass)/(mass+s->mass);
    double m2factor = (2*mass)/(mass+s->mass);

    vector2d w1 = (vel-s->vel);
    vector2d w2 = (s->vel-vel);

    vector2d u1 = (pos-s->pos);
    vector2d u2 = (s->pos-pos);

    vector2d via = vel - ((m1factor)*((w1*u1)/(u1*u1))*u1);
    vector2d vja = s->vel - ((m2factor)*((w2*u2)/(u2*u2))*u2);

    vel = via;
    s->vel = vja;
  }

  bool operator<(const Stone & other) {

  //this function is meant to reorder them alphabetically
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

class Collision {
 public:
  Stone* one;
  Stone* two;
  double time;

  bool valid() {
  cout << one->pos << "\n";
  cout << two->pos << "\n";
  vector2d u = (one->pos) - (two->pos);
  vector2d v = (one->vel) - (two->vel);

  if ((u*v) < 0) {
    //return true;
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

Collision* get_next_collision(vector<Stone> * ps) {
vector<Stone> temp = *ps;
double time;
double first = 100.0;

Stone* one;
Stone* two;

  for (int i = 0; i < temp.size()-1; i++) {
    for (int j = i+1; j < temp.size(); j++) {
      Stone* p1 = &temp.at(i);
      Stone* p2 = &temp.at(j);
      time = p1->collide_time(*p2);

      if (time < first) {
        first = time;
        one = p1;
        two = p2;
      }
    }
  }
cout << one->pos << "\n";
Collision* c = new Collision(first, one, two);
cout << c->one->pos << "\n";
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
    Collision c* = get_next_collision(&stones);//this line deletes/doesn't create the right x position for one of our two stones

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