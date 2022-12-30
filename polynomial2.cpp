#include <iostream>
#include <algorithm>
#include "Polynomial1.cpp"
using namespace std;


class Polynomial2;

class Term2 {
	friend Polynomial2;
public:
	float coef;
	int expx;
	int expy;
};

class Polynomial2 {
public:
	Term2* termArray;
	int capacity;
	int terms;
	Polynomial2();
	Polynomial2(const Polynomial2& poly);
	~Polynomial2();
	void NewTerm(float coef, int expx, int expy);
	void insertTerm(const Term2& term);
	friend const Polynomial2 operator +(const Polynomial2& x, const Polynomial2& y);
	friend const Polynomial2 operator -(const Polynomial2& x, const Polynomial2& y);
	friend const Polynomial2 operator *(const Polynomial2& x, const Polynomial2& y);
	float Eval(float x, float y);
	Polynomial1 Evalx(float x);
	Polynomial1 Evaly(float y);
	Polynomial2 & operator=(const Polynomial2& poly);
	Polynomial2 diffx();
	Polynomial2 diffy();
	Interval intpoly(Polynomial2 p, Box b);
	Polynomial2 expt(Polynomial2 p, int t);
	bool zero(Polynomial2 p, Box b);
	bool monotone(Polynomial2 p, Box b);
	friend ostream& operator<<(ostream& o, const Polynomial2& poly);
	
};

Polynomial2::Polynomial2()
{
	this->terms = 0;
	this->capacity = 100;
	termArray = new Term2[this->capacity];
}

Polynomial2::Polynomial2(const Polynomial2& b)
{
	this->terms = 0;
	this->capacity = b.capacity;
	termArray = new Term2[this->capacity];
	for (int i = 0; i < b.terms; i++) {
		NewTerm(b.termArray[i].coef, b.termArray[i].expx, b.termArray[i].expy);
	}
}

Polynomial2::~Polynomial2()
{
	delete[] termArray;
}

void Polynomial2::NewTerm(float coef, int expx, int expy)
{
	if (terms == capacity) {
		capacity *= 2;
		Term2* tmp = new Term2[capacity];
		copy(termArray, termArray + terms, tmp);
		delete[] termArray;
		termArray = tmp;
	}
	Term2 ATerm;
	ATerm.coef = coef; ATerm.expx = expx; ATerm.expy = expy;
	insertTerm(ATerm);
}

void Polynomial2::insertTerm(const Term2& term)
{
	int i;
	int temp = 1;
	for (i = 0; i < terms; i++) {
		if (term.expx == termArray[i].expx && term.expy == termArray[i].expy) {
			termArray[i].coef += term.coef;
			if (!termArray[i].coef) {
				for (int j = i; j < terms - 1; j++)
					termArray[j] = termArray[j + 1];
				terms--;
			}
			temp = 0;
		}
	}
	if (temp == 1) {
		termArray[terms] = term;
		terms++;
	}
}

const Polynomial2 operator +(const Polynomial2& x, const Polynomial2& y) {
	Polynomial2 c;
	c = x;
	for (int i = 0; i < y.terms; i++) {
		c.NewTerm(y.termArray[i].coef, y.termArray[i].expx, y.termArray[i].expy);
	}
	return c;
}

const Polynomial2 operator -(const Polynomial2& x, const Polynomial2& y) {
	Polynomial2 c;
	c = x;
	for (int i = 0; i < y.terms; i++) {
		c.NewTerm(-y.termArray[i].coef, y.termArray[i].expx, y.termArray[i].expy);
	}
	return c;
}


const Polynomial2 operator *(const Polynomial2& x, const Polynomial2& y) {
	Polynomial2 c;
	for (int i = 0; i < x.terms; i++) {
		for (int j = 0; j < y.terms; j++) {
			c.NewTerm(x.termArray[i].coef * y.termArray[j].coef, x.termArray[i].expx + y.termArray[j].expx, x.termArray[i].expy + y.termArray[j].expy);
		}
	}
	return c;
}

float Polynomial2::Eval(float x, float y)
{
	float res = 0.0;
	for (int i = 0; i < terms; i++) {
		res += termArray[i].coef * pow(x, termArray[i].expx) * pow(y, termArray[i].expy);
	}
	return res;
}


Polynomial1 Polynomial2::Evalx(float x)
{
	Polynomial1 res;
	for (int i = 0; i < terms; i++) {
		res.NewTerm(termArray[i].coef * pow(x, termArray[i].expx), termArray[i].expy);
	}
	return res;
}



Polynomial1 Polynomial2::Evaly(float y)
{
	Polynomial1 res;
	for (int i = 0; i < terms; i++) {
		res.NewTerm(termArray[i].coef * pow(y, termArray[i].expy), termArray[i].expx);
	}
	return res;
}



Polynomial2& Polynomial2::operator =(const Polynomial2& x)
{
	for (int i = 0; i < x.terms; i++) {
		insertTerm(x.termArray[i]);
	}
	return *this;
}


Polynomial2 Polynomial2::diffx()
{
	Polynomial2 c;
	for (int i = 0; i < terms; i++) {
		if (termArray[i].expx != 0) {
			float nc = termArray[i].coef * float(termArray[i].expx);
			int nx = termArray[i].expx - 1;
			int ny = termArray[i].expy;
			c.NewTerm(nc, nx, ny);
		}
	}
	return c;
}


Polynomial2 Polynomial2::diffy()
{
	Polynomial2 c;
	for (int i = 0; i < terms; i++) {
		if (termArray[i].expy != 0) {
			float nc = termArray[i].coef * float(termArray[i].expy);
			int nx = termArray[i].expx;
			int ny = termArray[i].expy - 1;
			c.NewTerm(nc, nx, ny);
		}
	}
	return c;
}


Interval intpoly(Polynomial2 p, Box b) {
	Interval Intx = b.Intx;
	Interval Inty = b.Inty;
	int terms = p.terms;
	Interval res(0, 0);
	for (int i = 0; i < terms; i++) {
		res = res + p.termArray[i].coef * pow(Intx, p.termArray[i].expx) * pow(Inty, p.termArray[i].expy);
	}
	return res;
}

bool zero(Polynomial2 p, Box b) {
	Interval pint = intpoly(p, b);
	if (0 << pint) {
		return true;
	}
	else {
		return false;
	}
}

bool monotone(Polynomial2 p, Box b) {
	Polynomial2 px = p.diffx();
	Polynomial2 py = p.diffy();
	return !(zero(px, b)) && !(zero(py, b));
}


Polynomial1 upper_for_positive(Polynomial2 p, Interval x) {
	Polynomial1 pu;
	for (int i = 0; i < p.terms; i++) {
		Interval resultx = p.termArray[i].coef * pow(x, p.termArray[i].expx);
		pu.NewTerm(resultx.right, p.termArray[i].expy);
	}
	return pu;
}

Polynomial1 lower_for_positive(Polynomial2 p, Interval x) {
	Polynomial1 pl;
	for (int i = 0; i < p.terms; i++) {
		Interval resultx = p.termArray[i].coef * pow(x, p.termArray[i].expx);
		pl.NewTerm(resultx.left, p.termArray[i].expy);
	}
	return pl;
}

Polynomial1 upper_for_negative(Polynomial2 p, Interval x) {
	Polynomial1 pu;
	for (int i = 0; i < p.terms; i++) {
		Interval resultx = p.termArray[i].coef * pow(x, p.termArray[i].expx);
		if (p.termArray[i].expy % 2 == 0) {
			pu.NewTerm(resultx.right, p.termArray[i].expy);
		}
		else {
			pu.NewTerm(resultx.left, p.termArray[i].expy);
		}
	}
	return pu;
}

Polynomial2 expt(Polynomial2 p, int t) {
	Polynomial2 res;
	for (int i = 0; i < t; i++) {
		res = res * p;
	}
	return res;
}

Polynomial1 lower_for_negative(Polynomial2 p, Interval x) {
	Polynomial1 pl;
	for (int i = 0; i < p.terms; i++) {
		Interval resultx = p.termArray[i].coef * pow(x, p.termArray[i].expx);
		if (p.termArray[i].expy % 2 == 0) {
			pl.NewTerm(resultx.left, p.termArray[i].expy);
		}
		else {
			pl.NewTerm(resultx.right, p.termArray[i].expy);
		}
	}
	return pl;
}



float uppereval(Polynomial2 p, Interval x, float y) {
	Polynomial1 p1;
	if (y > 0) {
		p1 = upper_for_positive(p, x);
	}
	else {
		p1 = upper_for_negative(p, x);
	}
	return p1.Eval(y);
}

float lowereval(Polynomial2 p, Interval x, float y) {
	Polynomial1 p1;
	if (y > 0) {
		p1 = lower_for_positive(p, x);
	}
	else {
		p1 = lower_for_negative(p, x);
	}
	return p1.Eval(y);
}

float one_point_search(Polynomial2 p, Interval y, float x, float epsilon) {
	if (y.len() <= epsilon) {
		return y.mid();
	}
	else {
		float res;
		float yp = y.left + epsilon;
		while (p.Eval(x, y.left) * p.Eval(x, yp) > 0 && yp < y.right) {
			yp = yp + epsilon;
		}
		if (yp < y.right) {
			res = yp - epsilon / 2;
		}
		else {
			res = y.right;
		}
		return res;
	}
}


Interval two_point_search(Polynomial2 p, Interval y, float x, float epsilon) {
	if (y.len() <= epsilon) {
		return Interval(0, -1);
	}
	else {
		Interval res;
		float yp = y.left + epsilon;
		while (p.Eval(x, y.left) * p.Eval(x, yp) > 0 && yp < y.right) {
			yp = yp + epsilon;
		}
		if (yp < y.right) {
			res.left = yp - epsilon / 2;
			res.right = one_point_search(p, Interval(yp, y.right), x, epsilon);
			return res;
		}
		else {
			return Interval(0, -1);
		}
	}


}

ostream& operator<<(ostream& o, const Polynomial2& poly)
{
	for (int i = 0; i < poly.terms - 1; i++) {
		o << poly.termArray[i].coef << "x^" << poly.termArray[i].expx << "y^" << poly.termArray[i].expy << " + ";
	}
	o << poly.termArray[poly.terms - 1].coef << "x^" << poly.termArray[poly.terms - 1].expx << "y^" << poly.termArray[poly.terms - 1].expy;
	return o;
}
