#include<cstdio>
#include<cassert>
#include<iostream>
#include<algorithm>
#include "Box.cpp"
using namespace std;

class Cube {
public:
	Interval Intx;
	Interval Inty;
	Interval Intz;
	Cube();
	Cube(Interval Intx, Interval Inty, Interval Intz);
	float diameter();
	float lenx();
	float leny();
	float lenz();
	Cube& operator =(const Cube& x);
	Cube lll();
	Cube llr();
	Cube lrl();
	Cube lrr();
	Cube rll();
	Cube rlr();
	Cube rrl();
	Cube rrr();
	//Cube l();
	//Cube r();
	//Cube u();
	//Cube d();
	friend ostream& operator<<(ostream& o, const Cube& b);
};

Cube::Cube(Interval x, Interval y, Interval z) :Intx(x), Inty(y), Intz(z) { }

Cube::Cube() { }



float Cube::diameter() {
	float res = 0;
	res = max(Intx.len(), Inty.len());
	res = max(res, Intz.len());
	return res;
}

float Cube::lenx() {
	float res = 0;
	return Intx.len();
}

float Cube::leny() {
	float res = 0;
	return Inty.len();
}

float Cube::lenz() {
	float res = 0;
	return Intz.len();
}

Cube& Cube::operator =(const Cube& x)
{
	Intx = x.Intx;
	Inty = x.Inty;
	Intz = x.Intz;
	return *this;
}


Cube Cube::lll() {
	float midx = Intx.mid();
	float midy = Inty.mid();
	float midz = Intz.mid();
	Interval newx(Intx.left, Intx.mid());
	Interval newy(Inty.left, Inty.mid());
	Interval newz(Intz.left, Intz.mid());
	Cube llb(newx, newy, newz);
	return llb;
}

Cube Cube::lrl() {
	float midx = Intx.mid();
	float midy = Inty.mid();
	float midz = Intz.mid();
	Interval newx(Intx.left, Intx.mid());
	Interval newy(Inty.mid(), Inty.right);
	Interval newz(Intz.left, Intz.mid());
	Cube llb(newx, newy, newz);
	return llb;
}

Cube Cube::rll() {
	float midx = Intx.mid();
	float midy = Inty.mid();
	float midz = Intz.mid();
	Interval newx(Intx.mid(), Intx.right);
	Interval newy(Inty.left, Inty.mid());
	Interval newz(Intz.left, Intz.mid());
	Cube llb(newx, newy, newz);
	return llb;
}

Cube Cube::rrl() {
	float midx = Intx.mid();
	float midy = Inty.mid();
	float midz = Intz.mid();
	Interval newx(Intx.mid(), Intx.right);
	Interval newy(Inty.mid(), Inty.right);
	Interval newz(Intz.left, Intz.mid());
	Cube llb(newx, newy, newz);
	return llb;
}



Cube Cube::llr() {
	float midx = Intx.mid();
	float midy = Inty.mid();
	float midz = Intz.mid();
	Interval newx(Intx.left, Intx.mid());
	Interval newy(Inty.left, Inty.mid());
	Interval newz(Intz.mid(), Intz.right);
	Cube llb(newx, newy, newz);
	return llb;
}

Cube Cube::lrr() {
	float midx = Intx.mid();
	float midy = Inty.mid();
	float midz = Intz.mid();
	Interval newx(Intx.left, Intx.mid());
	Interval newy(Inty.mid(), Inty.right);
	Interval newz(Intz.mid(), Intz.right);
	Cube llb(newx, newy, newz);
	return llb;
}

Cube Cube::rlr() {
	float midx = Intx.mid();
	float midy = Inty.mid();
	float midz = Intz.mid();
	Interval newx(Intx.mid(), Intx.right);
	Interval newy(Inty.left, Inty.mid());
	Interval newz(Intz.mid(), Intz.right);
	Cube llb(newx, newy, newz);
	return llb;
}

Cube Cube::rrr() {
	float midx = Intx.mid();
	float midy = Inty.mid();
	float midz = Intz.mid();
	Interval newx(Intx.mid(), Intx.right);
	Interval newy(Inty.mid(), Inty.right);
	Interval newz(Intz.mid(), Intz.right);
	Cube llb(newx, newy, newz);
	return llb;
}


ostream& operator<<(ostream& o, const Cube& b)
{
	o << "[" << b.Intx.left << "," << b.Intx.right << "]*[" << b.Inty.left << "," << b.Inty.right << "]*[" << b.Intz.left << ", " << b.Intz.right << "]";
	return o;
}




