#include <iostream>
#include <algorithm>
#include "polynomial2.cpp"
using namespace std;


class Polynomial3;

class Term3 {
	friend Polynomial3;
public:
	float coef;
	int expx;
	int expy;
	int expz;
};

class Polynomial3 {
public:
	Term3* termArray;
	int capacity;
	int terms;
	Polynomial3();
	Polynomial3(const Polynomial3& poly);
	~Polynomial3();
	void NewTerm(float coef, int expx, int expy, int expz);
	void insertTerm(const Term3& term);
	friend const Polynomial3 operator +(const Polynomial3& x, const Polynomial3& y);
	friend const Polynomial3 operator -(const Polynomial3& x, const Polynomial3& y);
	friend const Polynomial3 operator *(const Polynomial3& x, const Polynomial3& y);
	float Eval(float x, float y, float z);
	Polynomial2 Evalx(float x);
	Polynomial2 Evaly(float y);
	Polynomial2 Evalz(float z);
	Polynomial3 & operator=(const Polynomial3& poly);
	Polynomial3 diffx();
	Polynomial3 diffy();
	Polynomial3 diffz();
	Interval intpoly(Polynomial3 p, Cube b);
	bool zero(Polynomial3 p, Cube b);
	bool monotone(Polynomial3 p, Cube b);
	friend ostream& operator<<(ostream& o, const Polynomial3& poly);
	
};

Polynomial3::Polynomial3()
{
	this->terms = 0;
	this->capacity = 100;
	termArray = new Term3[this->capacity];
}

Polynomial3::Polynomial3(const Polynomial3& b)
{
	this->terms = 0;
	this->capacity = b.capacity;
	termArray = new Term3[this->capacity];
	for (int i = 0; i < b.terms; i++) {
		NewTerm(b.termArray[i].coef, b.termArray[i].expx, b.termArray[i].expy, b.termArray[i].expz);
	}
}

Polynomial3::~Polynomial3()
{
	delete[] termArray;
}

void Polynomial3::NewTerm(float coef, int expx, int expy, int expz)
{
	if (terms == capacity) {
		capacity *= 2;
		Term3* tmp = new Term3[capacity];
		copy(termArray, termArray + terms, tmp);
		delete[] termArray;
		termArray = tmp;
	}
	Term3 ATerm;
	ATerm.coef = coef; ATerm.expx = expx; ATerm.expy = expy; ATerm.expz = expz;
	insertTerm(ATerm);
}

void Polynomial3::insertTerm(const Term3& term)
{
	int i;
	int temp = 1;
	for (i = 0; i < terms; i++) {
		if (term.expx == termArray[i].expx && term.expy == termArray[i].expy && term.expz == termArray[i].expz) {
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

const Polynomial3 operator +(const Polynomial3& x, const Polynomial3& y) {
	Polynomial3 c;
	c = x;
	for (int i = 0; i < y.terms; i++) {
		c.NewTerm(y.termArray[i].coef, y.termArray[i].expx, y.termArray[i].expy, y.termArray[i].expz);
	}
	return c;
}

const Polynomial3 operator -(const Polynomial3& x, const Polynomial3& y) {
	Polynomial3 c;
	c = x;
	for (int i = 0; i < y.terms; i++) {
		c.NewTerm(-y.termArray[i].coef, y.termArray[i].expx, y.termArray[i].expy, y.termArray[i].expz);
	}
	return c;
}


const Polynomial3 operator *(const Polynomial3& x, const Polynomial3& y) {
	Polynomial3 c;
	for (int i = 0; i < x.terms; i++) {
		for (int j = 0; j < y.terms; j++) {
			c.NewTerm(x.termArray[i].coef * y.termArray[j].coef, x.termArray[i].expx + y.termArray[j].expx, x.termArray[i].expy + y.termArray[j].expy, x.termArray[i].expz + y.termArray[j].expz);
		}
	}
	return c;
}

float Polynomial3::Eval(float x, float y, float z)
{
	float res = 0.0;
	for (int i = 0; i < terms; i++) {
		res += termArray[i].coef * pow(x, termArray[i].expx) * pow(y, termArray[i].expy) * pow(z, termArray[i].expz);
	}
	return res;
}

Polynomial2 Polynomial3::Evalx(float x)
{
	Polynomial2 res;
	for (int i = 0; i < terms; i++) {
		res.NewTerm(termArray[i].coef * pow(x, termArray[i].expx), termArray[i].expy, termArray[i].expz);
	}
	return res;
}

Polynomial2 Polynomial3::Evaly(float y)
{
	Polynomial2 res;
	for (int i = 0; i < terms; i++) {
		res.NewTerm(termArray[i].coef * pow(y, termArray[i].expy), termArray[i].expx, termArray[i].expz);
	}
	return res;
}


Polynomial2 Polynomial3::Evalz(float z)
{
	Polynomial2 res;
	for (int i = 0; i < terms; i++) {
		res.NewTerm(termArray[i].coef * pow(z, termArray[i].expz), termArray[i].expx, termArray[i].expy);
	}
	return res;
}


Polynomial3& Polynomial3::operator =(const Polynomial3& x)
{
	for (int i = 0; i < x.terms; i++) {
		insertTerm(x.termArray[i]);
	}
	return *this;
}


Polynomial3 Polynomial3::diffx()
{
	Polynomial3 c;
	for (int i = 0; i < terms; i++) {
		if (termArray[i].expx != 0) {
			float nc = termArray[i].coef * float(termArray[i].expx);
			int nx = termArray[i].expx - 1;
			int ny = termArray[i].expy;
			int nz = termArray[i].expz;
			c.NewTerm(nc, nx, ny, nz);
		}
	}
	return c;
}


Polynomial3 Polynomial3::diffy()
{
	Polynomial3 c;
	for (int i = 0; i < terms; i++) {
		if (termArray[i].expy != 0) {
			float nc = termArray[i].coef * float(termArray[i].expy);
			int nx = termArray[i].expx;
			int ny = termArray[i].expy - 1;
			int nz = termArray[i].expz;
			c.NewTerm(nc, nx, ny, nz);
		}
	}
	return c;
}

Polynomial3 Polynomial3::diffz()
{
	Polynomial3 c;
	for (int i = 0; i < terms; i++) {
		if (termArray[i].expz != 0) {
			float nc = termArray[i].coef * float(termArray[i].expz);
			int nx = termArray[i].expx;
			int ny = termArray[i].expy;
			int nz = termArray[i].expz - 1;
			c.NewTerm(nc, nx, ny, nz);
		}
	}
	return c;
}

Interval intpoly(Polynomial3 p, Cube b) {
	Interval Intx = b.Intx;
	Interval Inty = b.Inty;
	Interval Intz = b.Intz;
	int terms = p.terms;
	Interval res(0, 0);
	for (int i = 0; i < terms; i++) {
		res = res + p.termArray[i].coef * pow(Intx, p.termArray[i].expx) * pow(Inty, p.termArray[i].expy) * pow(Intz, p.termArray[i].expz);
	}
	return res;
}

bool zero(Polynomial3 p, Cube b) {
	Interval pint = intpoly(p, b);
	if (0 << pint) {
		return true;
	}
	else {
		return false;
	}
}

bool monotone(Polynomial3 p, Cube b) {
	Polynomial3 px = p.diffx();
	Polynomial3 py = p.diffy();
	Polynomial3 pz = p.diffz();
	return !(zero(px, b)) && !(zero(py, b)) && !(zero(pz, b));
}


Polynomial1 upper_for_positive(Polynomial3 p, Interval x, Interval y) {
	Polynomial1 pu;
	for (int i = 0; i < p.terms; i++) {
		Interval resultx = p.termArray[i].coef * pow(x, p.termArray[i].expx) * pow(y, p.termArray[i].expy);
		pu.NewTerm(resultx.right, p.termArray[i].expz);
	}
	return pu;
}

Polynomial1 lower_for_positive(Polynomial3 p, Interval x, Interval y) {
	Polynomial1 pl;
	for (int i = 0; i < p.terms; i++) {
		Interval resultx = p.termArray[i].coef * pow(x, p.termArray[i].expx) * pow(y, p.termArray[i].expy);
		pl.NewTerm(resultx.left, p.termArray[i].expz);
	}
	return pl;
}


Polynomial1 upper_for_negative(Polynomial3 p, Interval x, Interval y) {
	Polynomial1 pu;
	for (int i = 0; i < p.terms; i++) {
		Interval resultx = p.termArray[i].coef * pow(x, p.termArray[i].expx) * pow(y, p.termArray[i].expy);
		if (p.termArray[i].expz % 2 == 0) {
			pu.NewTerm(resultx.right, p.termArray[i].expz);
		}
		else {
			pu.NewTerm(resultx.left, p.termArray[i].expz);
		}
	}
	return pu;
}

Polynomial1 lower_for_negative(Polynomial3 p, Interval x, Interval y) {
	Polynomial1 pl;
	for (int i = 0; i < p.terms; i++) {
		Interval resultx = p.termArray[i].coef * pow(x, p.termArray[i].expx) * pow(y, p.termArray[i].expy);
		if (p.termArray[i].expz % 2 == 0) {
			pl.NewTerm(resultx.left, p.termArray[i].expz);
		}
		else {
			pl.NewTerm(resultx.right, p.termArray[i].expz);
		}
	}
	return pl;
}


float uppereval(Polynomial3 p, Interval x, Interval y, float z) {
	Polynomial1 p1;
	if (z > 0) {
		p1 = upper_for_positive(p, x, y);
	}
	else {
		p1 = upper_for_negative(p, x, y);
	}
	return p1.Eval(z);
}


float lowereval(Polynomial3 p, Interval x, Interval y, float z) {
	Polynomial1 p1;
	if (z > 0) {
		p1 = lower_for_positive(p, x, y);
	}
	else {
		p1 = lower_for_negative(p, x, y);
	}
	return p1.Eval(z);
}


ostream& operator<<(ostream& o, const Polynomial3& poly)
{
	for (int i = 0; i < poly.terms - 1; i++) {
		o << poly.termArray[i].coef << "x^" << poly.termArray[i].expx << "y^" << poly.termArray[i].expy << "z^" << poly.termArray[i].expz << " + ";
	}
	o << poly.termArray[poly.terms - 1].coef << "x^" << poly.termArray[poly.terms - 1].expx << "y^" << poly.termArray[poly.terms - 1].expy << "z^" << poly.termArray[poly.terms - 1].expz;
	return o;
}

