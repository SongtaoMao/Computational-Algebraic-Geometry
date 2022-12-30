#include<cstdio>
#include<cassert>
#include<iostream>
#include<algorithm>
#include "interval.cpp"
using namespace std;

class Box {
public:
	Interval Intx;
	Interval Inty;
	Box();
	Box(Interval Intx, Interval Inty);
	float diameter();
	float lenx();
	float leny();
	Box& operator =(const Box& x);
	Box ll();
	Box lr();
	Box rl();
	Box rr();
	Box l();
	Box r();
	Box u();
	Box d();
	friend ostream& operator<<(ostream& o, const Box& b);
};

Box::Box(Interval x, Interval y) :Intx(x), Inty(y) { }

Box::Box() { }



float Box::diameter(){
	float res = 0;
	res = max(Intx.len(), Inty.len());
	return res;
}

float Box::lenx() {
	float res = 0;
	return Intx.len();
}

float Box::leny() {
	float res = 0;
	return Inty.len();
}

Box& Box::operator =(const Box& x)
{
	Intx = x.Intx;
	Inty = x.Inty;
	return *this;
}

Box Box::ll() {
	float midx = Intx.mid();
	float midy = Inty.mid();
	Interval newx(Intx.left, Intx.mid());
	Interval newy(Inty.left, Inty.mid());
	Box llb(newx, newy);
	return llb;
}

Box Box::lr() {
	float midx = Intx.mid();
	float midy = Inty.mid();
	Interval newx(Intx.left, Intx.mid());
	Interval newy(Inty.mid(), Inty.right);
	Box lrb(newx, newy);
	return lrb;
}

Box Box::rl() {
	float midx = Intx.mid();
	float midy = Inty.mid();
	Interval newx(Intx.mid(), Intx.right);
	Interval newy(Inty.left, Inty.mid());
	Box rlb(newx, newy);
	return rlb;
}

Box Box::rr() {
	float midx = Intx.mid();
	float midy = Inty.mid();
	Interval newx(Intx.mid(), Intx.right);
	Interval newy(Inty.mid(), Inty.right);
	Box rrb(newx, newy);
	return rrb;
}


Box Box::l() {
	Interval newx(Intx.left, Intx.left);
	Box lb(newx, Inty);
	return lb;
}

Box Box::r() {
	Interval newx(Intx.right, Intx.right);
	Box rb(newx, Inty);
	return rb;
}

Box Box::u() {
	Interval newy(Inty.right, Inty.right);
	Box ub(Intx, newy);
	return ub;
}

Box Box::d() {
	Interval newy(Inty.left, Inty.left);
	Box db(Intx, newy);
	return db;
}


ostream& operator<<(ostream& o, const Box& b)
{
	o << "[" << b.Intx.left << "," << b.Intx.right << "]*[" << b.Inty.left << "," << b.Inty.right << "]";
	return o;
}

void testBox() {
	Interval x(-1, 3);
	Interval y(1, 4);
	Box box1(x, y);
	cout << "diameter=" << box1.diameter() << endl;
	cout << "boxll=" << box1.ll() << endl;
	cout << "boxlr=" << box1.lr() << endl;
	cout << "boxrl=" << box1.rl() << endl;
	cout << "boxrr=" << box1.rr() << endl;
}


/*
int main() {
	testBox();
	return 0;
}
*/



