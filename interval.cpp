#include<cstdio>
#include<cassert>
#include<iostream>
#include <algorithm>
using namespace std;

class Interval {
public:
	float left;
	float right; 
	Interval();
	//Interval(float left);
	Interval(float left, float right);
	friend const Interval operator +(const Interval& x, const Interval& y);
	friend const Interval operator -(const Interval& x, const Interval& y);
	friend const Interval operator *(const Interval& x, const Interval& y);
	friend const Interval operator *(const float& x, const Interval& y);
	friend const Interval pow(Interval x, int i);
	const Interval operator -();
	friend bool operator <(const Interval& x, const Interval& y);
	friend bool operator >(const Interval& x, const Interval& y);
	friend const Interval inter(const Interval& x, const Interval& y);
	friend const Interval uni(const Interval& x, const Interval& y);
	Interval& operator =(const Interval& x);
	friend bool operator <<(const float& x, const Interval& y);
	float mid();
	float len();
	Interval lefthalf();
	Interval righthalf();
	friend ostream& operator<<(ostream& o, const Interval& x);
};

Interval::Interval(float x, float y) :left(x), right(y) { }

//Interval::Interval(float x) : left(x), right(x) { }

Interval::Interval() { }

const Interval operator +(const Interval& x, const Interval& y)
{
	Interval ans;
	ans.left = x.left + y.left;
	ans.right = x.right + y.right;
	return ans;
}

const Interval operator -(const Interval& x, const Interval& y)
{
	Interval ans;
	ans.left = x.left - y.right;
	ans.right = x.right - y.left;
	return ans;
}

const Interval operator *(const Interval& x, const Interval& y)
{
	Interval ans;
	ans.left = min(min(min(x.left * y.left, x.left * y.right), x.right * y.left), x.right * y.right);
	ans.right= max(max(max(x.left * y.left, x.left * y.right), x.right * y.left), x.right * y.right);
	return ans;
}

const Interval operator *(const float& x, const Interval& y) 
{
	Interval ans;
	if (x > 0) {
		ans.left = x * y.left;
		ans.right = x * y.right;
	}
	else {
		ans.left = x * y.right;
		ans.right = x * y.left;
	}
	return ans;
}

const Interval pow(Interval x, int i) {
	Interval res;
	if (i == 0) {
		res.left = 1;
		res.right = 1;
	}
	else if (i % 2 != 0) {
		res.left = pow(x.left, i);
		res.right = pow(x.right, i);
	}
	else {
		if (0 << x) {
			res.left = 0;
			res.right = max(pow(x.left, i), pow(x.right, i));
		}
		else {
			res.left = min(pow(x.left, i), pow(x.right, i));
			res.right = max(pow(x.left, i), pow(x.right, i));
		}
	}
	return res;
}

const Interval Interval::operator -()
{
	Interval x;
	float temp = left;
	x.left = -right;
	x.right = -temp;
	return x;
}

bool operator <(const Interval& x, const Interval& y) {
	if (x.right <= y.left) {
		return true;
	}
	else {
		return false;
	}
}
bool operator >(const Interval& x, const Interval& y) {
	if (x.left <= y.right) {
		return true;
	}
	else {
		return false;
	}
}



const Interval inter(const Interval& x, const Interval& y) {
	Interval res;
	if ((x.left > y.right) || (y.left > x.right)) {
		res.left = 1;
		res.right = 0;
	}
	else {
		res.left = max(x.left, y.left);
		res.right = min(x.right, y.right);
	}
	return res;
}

const Interval uni(const Interval& x, const Interval& y) {
	Interval res;
	res.left = min(x.left, y.left);
	res.right = max(x.right, y.right);
	return res;
}

Interval& Interval::operator =(const Interval& x)
{
	left = x.left;
	right = x.right;
	return *this;

}

bool operator << (const float& x, const Interval& I)
{
	if (I.left <= x && I.right >= x)
		return true;
	else
		return false;
}

float Interval::mid() {
	return (left + right) / 2;
}

float Interval::len(){
	float res = right - left;
	return res;
}

Interval Interval::lefthalf() {
	return Interval(left, mid());
}

Interval Interval::righthalf() {
	return Interval(mid(), right);
}

ostream& operator<<(ostream& o, const Interval& x)
{
	o << "[" << x.left << "," << x.right << "]";
	return o;
}

void testinterval()
{
	Interval x(-3.9, 4.0), y(2.0, 16.0);
	float v = 1.5;

	cout << "len(x)=" << x.len() << endl;

	cout << "x+y=" << x + y << endl;

	cout << "x-y=" << x - y << endl;

	cout << "x*y=" << x * y << endl;

	cout << "2 << x=" << (2 << x) << endl;

	cout << "-x" << -x << endl;

	cout << "x^4" << pow(x, 4) << endl;

	cout << "y^3" << pow(y, 3) << endl;

	cout << "v*x=" << v * x << endl;

	cout << "inter(x,y)=" << inter(x, y) << endl;

	cout << "uni(x,y)=" << uni(x, y) << endl;

	cout << "mid(x)=" << x.mid() << endl;

	cout << "len(x)=" << x.len() << endl;
}


//int main() {
//	testinterval();
//	return 0;
//}
