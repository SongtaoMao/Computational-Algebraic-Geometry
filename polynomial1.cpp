#include <iostream>
#include <algorithm>
#include "Cube.cpp"
using namespace std;


class Polynomial1;

class Term1 {
	friend Polynomial1;
public:
	float coef;
	int expx;
};

class Polynomial1 {
public:
	Term1* termArray;
	int capacity;
	int terms;
	Polynomial1();
	Polynomial1(const Polynomial1& poly);
	~Polynomial1();
	void NewTerm(float coef, int expx);
	void insertTerm(const Term1& term);
	friend const Polynomial1 operator +(const Polynomial1& x, const Polynomial1& y);
	friend const Polynomial1 operator -(const Polynomial1& x, const Polynomial1& y);
	friend const Polynomial1 operator *(const Polynomial1& x, const Polynomial1& y);
	float Eval(float x);
	Polynomial1& operator=(const Polynomial1& poly);
	Polynomial1 diffx();
	Interval intpoly(Polynomial1 p, Interval I);
	bool zero(Polynomial1 p, Interval I);
	bool monotone(Polynomial1 p, Interval I);
	void roots(Polynomial1 p, Interval I, float delta, float epsilon, Interval* a, int* i);
	friend ostream& operator<<(ostream& o, const Polynomial1& poly);

};

Polynomial1::Polynomial1()
{
	this->terms = 0;
	this->capacity = 100;
	termArray = new Term1[this->capacity];
}

Polynomial1::Polynomial1(const Polynomial1& b)
{
	this->terms = 0;
	this->capacity = b.capacity;
	termArray = new Term1[this->capacity];
	for (int i = 0; i < b.terms; i++) {
		NewTerm(b.termArray[i].coef, b.termArray[i].expx);
	}
}

Polynomial1::~Polynomial1()
{
	delete[] termArray;
}

void Polynomial1::NewTerm(float coef, int expx)
{
	if (terms == capacity) {
		capacity *= 2;
		Term1* tmp = new Term1[capacity];
		copy(termArray, termArray + terms, tmp);
		delete[] termArray;
		termArray = tmp;
	}
	Term1 ATerm1;
	ATerm1.coef = coef; ATerm1.expx = expx;
	insertTerm(ATerm1);
}

void Polynomial1::insertTerm(const Term1& term)
{
	int i;
	int temp = 1;
	for (i = 0; i < terms; i++) {
		if (term.expx == termArray[i].expx) {
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

const Polynomial1 operator +(const Polynomial1& x, const Polynomial1& y) {
	Polynomial1 c;
	c = x;
	for (int i = 0; i < y.terms; i++) {
		c.NewTerm(y.termArray[i].coef, y.termArray[i].expx);
	}
	return c;
}

const Polynomial1 operator -(const Polynomial1& x, const Polynomial1& y) {
	Polynomial1 c;
	c = x;
	for (int i = 0; i < y.terms; i++) {
		c.NewTerm(-y.termArray[i].coef, y.termArray[i].expx);
	}
	return c;
}


const Polynomial1 operator *(const Polynomial1& x, const Polynomial1& y) {
	Polynomial1 c;
	for (int i = 0; i < x.terms; i++) {
		for (int j = 0; j < y.terms; j++) {
			c.NewTerm(x.termArray[i].coef * y.termArray[j].coef, x.termArray[i].expx + y.termArray[j].expx);
		}
	}
	return c;
}

float Polynomial1::Eval(float x)
{
	float res = 0.0;
	for (int i = 0; i < terms; i++) {
		res += termArray[i].coef * pow(x, termArray[i].expx);
	}
	return res;
}


Polynomial1& Polynomial1::operator =(const Polynomial1& x)
{
	for (int i = 0; i < x.terms; i++) {
		insertTerm(x.termArray[i]);
	}
	return *this;
}


Polynomial1 Polynomial1::diffx()
{
	Polynomial1 c;
	for (int i = 0; i < terms; i++) {
		if (termArray[i].expx != 0) {
			float nc = termArray[i].coef * float(termArray[i].expx);
			int nx = termArray[i].expx - 1;
			c.NewTerm(nc, nx);
		}
	}
	return c;
}

Interval intpoly(Polynomial1 p, Interval I) {
	int terms = p.terms;
	Interval res(0, 0);
	for (int i = 0; i < terms; i++) {
		res = res + p.termArray[i].coef * pow(I, p.termArray[i].expx);
	}
	return res;
}

bool zero(Polynomial1 p, Interval I) {
	Interval pint = intpoly(p, I);
	if (0 << pint) {
		return true;
	}
	else {
		return false;
	}
}

bool monotone(Polynomial1 p, Interval I) {
	Polynomial1 px = p.diffx();
	return !(zero(px, I));
}



void roots(Polynomial1 p, Polynomial1 px, Interval I, float delta, float epsilon, Interval* a, int* i) {
	if (zero(p, I) && ( zero(px, I) || p.Eval(I.left) * p.Eval(I.right) <=0 )) {
		if (I.len() > delta) {
			roots(p, px, I.lefthalf(), delta, epsilon, a, i);
			roots(p, px, I.righthalf(), delta, epsilon, a, i);
		}
		else if (I.len() < epsilon) {
			if (p.Eval(I.left) * p.Eval(I.right) <= 0) {
				*(a + *i) = I;
				(*i)++;
			}
		}
		else if (!zero(px, I)) {
			if (p.Eval(I.left) * p.Eval(I.right) <= 0) {
				*(a + *i) = I;
				(*i)++;
			}
		}
		else {
			roots(p, px, I.lefthalf(), delta, epsilon, a, i);
			roots(p, px, I.righthalf(), delta, epsilon, a, i);
		}
	}
}

ostream& operator<<(ostream& o, const Polynomial1& poly)
{
	for (int i = 0; i < poly.terms - 1; i++) {
		o << poly.termArray[i].coef << "x^" << poly.termArray[i].expx << " + ";
	}
	o << poly.termArray[poly.terms - 1].coef << "x^" << poly.termArray[poly.terms - 1].expx;
	return o;
}
