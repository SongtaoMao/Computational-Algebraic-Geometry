#include <iostream>
#include<time.h>
#include <cstdio>
#include <cassert>
#include <iostream>
#include <algorithm>
#include <fstream>
#include "polynomial3.cpp"



void output_2d(Polynomial2 p, float x1, float x2, float y1, float y2, ofstream* outfile) {
	float ll = p.Eval(x1, y1);
	float lr = p.Eval(x1, y2);
	float rl = p.Eval(x2, y1);
	float rr = p.Eval(x2, y2);
	if ((x2 - x1) < 0.03 && (y2 - y1) < 0.03) {
		*(outfile) << x1 << " " << x2 << " " << y1 << " " << y2 << " " << "0" << endl;
	}
	else {
		if (ll > 0) {
			if (rl < 0) {
				if (lr < 0) {
					*(outfile) << x1 << " " << x2 << " " << y1 << " " << y2 << " " << "1" << endl;
				}
				else if (rr > 0) {
					*(outfile) << x1 << " " << x2 << " " << y1 << " " << y2 << " " << "2" << endl;
				}
				else {
					*(outfile) << x1 << " " << x2 << " " << y1 << " " << y2 << " " << "5" << endl;
				}
			}
			else if (lr < 0) {
				if (rr < 0) {
					*(outfile) << x1 << " " << x2 << " " << y1 << " " << y2 << " " << "6" << endl;
				}
				else {
					*(outfile) << x1 << " " << x2 << " " << y1 << " " << y2 << " " << "3" << endl;
				}
			}
			else if (rr < 0) {
				*(outfile) << x1 << " " << x2 << " " << y1 << " " << y2 << " " << "4" << endl;
			}
		}

		else {
			if (rl > 0) {
				if (lr > 0) {
					*(outfile) << x1 << " " << x2 << " " << y1 << " " << y2 << " " << "1" << endl;
				}
				else if (rr < 0) {
					*(outfile) << x1 << " " << x2 << " " << y1 << " " << y2 << " " << "2" << endl;
				}
				else {
					*(outfile) << x1 << " " << x2 << " " << y1 << " " << y2 << " " << "5" << endl;
				}
			}
			else if (lr > 0) {
				if (rr > 0) {
					*(outfile) << x1 << " " << x2 << " " << y1 << " " << y2 << " " << "6" << endl;
				}
				else {
					*(outfile) << x1 << " " << x2 << " " << y1 << " " << y2 << " " << "3" << endl;
				}
			}
			else if (rr > 0) {
				*(outfile) << x1 << " " << x2 << " " << y1 << " " << y2 << " " << "4" << endl;
			}
		}
	}
}

void outputmc_2d(Polynomial2 p, float  x1, float  x2, float  y1, float  y2, ofstream* outfile) {
	float  ll = p.Eval(x1, y1);
	float  lr = p.Eval(x1, y2);
	float  rl = p.Eval(x2, y1);
	float  rr = p.Eval(x2, y2);
	if (ll > 0) {
		if (lr > 0) {
			if (rl > 0) {
				if (rr < 0) {
					*(outfile) << x1 << " " << x2 << " " << y1 << " " << y2 << " " << "4" << endl;
				}
			}
			else {
				if (rr > 0) {
					*(outfile) << x1 << " " << x2 << " " << y1 << " " << y2 << " " << "2" << endl;
				}
				else {
					*(outfile) << x1 << " " << x2 << " " << y1 << " " << y2 << " " << "6" << endl;
				}
			}
		}
		else {
			if (rl > 0) {
				if (rr > 0) {
					*(outfile) << x1 << " " << x2 << " " << y1 << " " << y2 << " " << "7" << endl;
				}
				else {
					*(outfile) << x1 << " " << x2 << " " << y1 << " " << y2 << " " << "3" << endl;
				}
			}
			else {
				if (rr > 0) {
					*(outfile) << x1 << " " << x2 << " " << y1 << " " << y2 << " " << "10" << endl;
				}
				else {
					*(outfile) << x1 << " " << x2 << " " << y1 << " " << y2 << " " << "1" << endl;
				}
			}
		}
	}
	else {
		if (lr > 0) {
			if (rl > 0) {
				if (rr > 0) {
					*(outfile) << x1 << " " << x2 << " " << y1 << " " << y2 << " " << "1" << endl;
				}
				else {
					*(outfile) << x1 << " " << x2 << " " << y1 << " " << y2 << " " << "5" << endl;
				}
			}
			else {
				if (rr > 0) {
					*(outfile) << x1 << " " << x2 << " " << y1 << " " << y2 << " " << "3" << endl;
				}
				else {
					*(outfile) << x1 << " " << x2 << " " << y1 << " " << y2 << " " << "7" << endl;
				}
			}
		}
		else {
			if (rl > 0) {
				if (rr > 0) {
					*(outfile) << x1 << " " << x2 << " " << y1 << " " << y2 << " " << "6" << endl;
				}
				else {
					*(outfile) << x1 << " " << x2 << " " << y1 << " " << y2 << " " << "2" << endl;
				}
			}
			else {
				if (rr > 0) {
					*(outfile) << x1 << " " << x2 << " " << y1 << " " << y2 << " " << "4" << endl;
				}
			}
		}
	}
}

//在这里是一维隔离，将两个函数的零点和临界点隔离出来
void one_dimension_slove(Polynomial1 pu, Polynomial1 pux, Polynomial1 pd, Polynomial1 pdx, Interval x, float delta, Interval* a, int* i) {
	if ((!(zero(pu, x)) || !(zero(pux, x))) && (!(zero(pd, x)) || !(zero(pdx, x)))) {
		*(a + *i) = x;
		(*i)++;
	}
	else if (x.len() < delta) {
		*(a + *i) = x;
		(*i)++;
	}
	else {
		Interval leftpart(x.left, x.mid());
		Interval rightpart(x.mid(), x.right);
		one_dimension_slove(pu, pux, pd, pdx, leftpart, delta, a, i);
		one_dimension_slove(pu, pux, pd, pdx, rightpart, delta, a, i);
	}
}


//求解二维
void two_dimension_solve(Polynomial2 p, Polynomial2 p1, Polynomial2 p2, Box b, float delta, ofstream* outfile) {
	if (zero(p, b)) {
		if (!zero(p1, b)) {
			Polynomial1 pu = p.Evalx(b.Intx.left);
			Polynomial1 pd = p.Evalx(b.Intx.right);
			Polynomial1 pux = pu.diffx();
			Polynomial1 pdx = pd.diffx();
			Interval* part = (Interval*)malloc(100 * sizeof(Interval));
			int t = 0;
			int* j = NULL;
			j = &t;
			one_dimension_slove(pu, pux, pd, pdx, b.Inty, delta, part, j);
			for (int k = 0; k < t; k++) {
				output_2d(p, b.Intx.left, b.Intx.right, (*(part + k)).left, (*(part + k)).right, outfile);
			}
			free(part);
			part = NULL;
			j = NULL;
		}
		else if (!zero(p2, b)) {
			Interval* part = (Interval*)malloc(100 * sizeof(Interval));
			Polynomial1 pu = p.Evaly(b.Inty.left);
			Polynomial1 pd = p.Evaly(b.Inty.right);
			Polynomial1 puy = pu.diffx();
			Polynomial1 pdy = pd.diffx();
			int t = 0;
			int* j = NULL;
			j = &t;
			one_dimension_slove(pu, puy, pd, pdy, b.Intx, delta, part, j);
			for (int k = 0; k < t; k++) {
				output_2d(p, (*(part + k)).left, (*(part + k)).right, b.Inty.left, b.Inty.right, outfile);
			}
			free(part);
			part = NULL;
			j = NULL;
		}

		else if (b.diameter() < delta) {
			output_2d(p, b.Intx.left, b.Intx.right, b.Inty.left, b.Inty.right, outfile);
		}

		else if (b.Inty.len() > b.Intx.len()) {
			Interval I1(b.Inty.left, b.Inty.mid());
			Interval I2(b.Inty.mid(), b.Inty.right);
			Box b1(b.Intx, I1);
			Box b2(b.Intx, I2);
			two_dimension_solve(p, p1, p2, b1, delta, outfile);
			two_dimension_solve(p, p1, p2, b2, delta, outfile);
		}
		else {
			Interval I1(b.Intx.left, b.Intx.mid());
			Interval I2(b.Intx.mid(), b.Intx.right);
			Box b1(I1, b.Inty);
			Box b2(I2, b.Inty);
			two_dimension_solve(p, p1, p2, b1, delta, outfile);
			two_dimension_solve(p, p1, p2, b2, delta, outfile);
		}
	}
}


//将一个二维盒子先划分为达到一定的精度
void divide_2d(Polynomial2 p, Interval x, Interval y, float epsilon, float delta, ofstream* outfile) {
	Polynomial2 px = p.diffx();
	Polynomial2 py = p.diffy();
	float k = y.left;
	while (k + epsilon < y.right) {
		two_dimension_solve(p, px, py, Box(x, Interval(k, k + epsilon)), delta, outfile);//精确求解
		k = k + epsilon;
	}
	two_dimension_solve(p, px, py, Box(x, Interval(k, y.right)), delta, outfile);//精确求解
}


//求解上下界多项式的实根
void roots_upper_and_lower_2d(Polynomial2 p, Box b, float width, float mini, Interval* upper_roots, Interval* lower_roots, int* uppers, int* lowers) {
	Interval x = b.Intx;
	Interval y = b.Inty;
	if (0 << y) {
		Interval negativepart = Interval(y.left, 0);
		Interval positivepart = Interval(0, y.right);
		Polynomial1 upper_positive = upper_for_positive(p, x);
		Polynomial1 upper_negative = upper_for_negative(p, x);
		Polynomial1 lower_positive = lower_for_positive(p, x);
		Polynomial1 lower_negative = lower_for_negative(p, x);
		roots(upper_negative, upper_negative.diffx(), negativepart, width, mini, upper_roots, uppers);
		roots(upper_positive, upper_positive.diffx(), positivepart, width, mini, upper_roots, uppers);
		roots(lower_negative, lower_negative.diffx(), negativepart, width, mini, lower_roots, lowers);
		roots(lower_positive, lower_positive.diffx(), positivepart, width, mini, lower_roots, lowers);
	}
	else if (y.left > 0) {
		Polynomial1 upper_positive = upper_for_positive(p, x);
		Polynomial1 lower_positive = lower_for_positive(p, x);
		roots(upper_positive, upper_positive.diffx(), y, width, mini, upper_roots, uppers);
		roots(lower_positive, lower_positive.diffx(), y, width, mini, lower_roots, lowers);
	}
	else {
		Polynomial1 upper_negative = upper_for_negative(p, x);
		Polynomial1 lower_negative = lower_for_negative(p, x);
		roots(upper_negative, upper_negative.diffx(), y, width, mini, upper_roots, uppers);
		roots(lower_negative, lower_negative.diffx(), y, width, mini, lower_roots, lowers);
	}
}

//通过实根隔离法，返回函数零点所在的区间
void root_isolation_and_solve_2d(Polynomial2 p, Box b, float epsilon, float delta, ofstream* outfile) {
	float width = 0.005;
	float mini = 0.001;
	Interval x = b.Intx;
	Interval y = b.Inty;
	Interval* upper_roots = (Interval*)malloc(100 * sizeof(Interval));
	Interval* lower_roots = (Interval*)malloc(100 * sizeof(Interval));
	int upper_num = 0;
	int* uppers = NULL;
	uppers = &(upper_num);
	int lower_num = 0;
	int* lowers = NULL;
	lowers = &(lower_num);
	roots_upper_and_lower_2d(p, b, width, mini, upper_roots, lower_roots, uppers, lowers);
	int i = 0;
	int j = 0;
	if (uppereval(p, x, y.left) * lowereval(p, x, y.left) < 0) {
		if (upper_num > 0 && lower_num > 0) {
			if ((*(upper_roots)).left < (*(lower_roots)).left) {
				Interval yp = uni(Interval(y.left, y.left), *(upper_roots)); //求解带边界的box。
				divide_2d(p, x, yp, epsilon, delta, outfile);
				i = 1;
			}
			else {
				Interval yp = uni(Interval(y.left, y.left), *(lower_roots)); //求解带边界的box。
				divide_2d(p, x, yp, epsilon, delta, outfile);
				j = 1;
			}
		}
		else if (upper_num > 0) {
			Interval yp = uni(Interval(y.left, y.left), *(upper_roots)); //求解带边界的box。
			divide_2d(p, x, yp, epsilon, delta, outfile);
			i = 1;
		}
		else if (lower_num > 0) {
			Interval yp = uni(Interval(y.left, y.left), *(lower_roots)); //求解带边界的box。
			divide_2d(p, x, yp, epsilon, delta, outfile);
			j = 1;
		}
		else {
			divide_2d(p, x, y, epsilon, delta, outfile);
		}
	}

	while (upper_num > i && lower_num > j) {
		if (upper_num > i + 1 && (*(upper_roots + i + 1)).right < (*(lower_roots + j)).left) {
			Interval yp = uni(*(upper_roots + i), *(upper_roots + i + 1)); //求解多根问题
			divide_2d(p, x, yp, epsilon, delta, outfile);
			i = i + 2;
		}
		else if (lower_num > j + 1 && (*(lower_roots + j + 1)).right < (*(upper_roots + i)).left) {
			Interval yp = uni(*(lower_roots + j), *(lower_roots + j + 1)); //求解多根问题
			divide_2d(p, x, yp, epsilon, delta, outfile);
			j = j + 2;
		}
		else {
			Interval yp = uni(*(upper_roots + i), *(lower_roots + j));//单根求解问题
			if (yp.len() < epsilon) {
				output_2d(p, x.left, x.right, yp.left, yp.right, outfile);
			}
			else {
				divide_2d(p, x, yp, epsilon, delta, outfile);
			}
			i = i + 1;
			j = j + 1;
		}
	}

	while (upper_num > i) {
		if (upper_num > i + 1) {
			Interval yp = uni(*(upper_roots + i), *(upper_roots + i + 1)); //求解多根问题
			divide_2d(p, x, yp, epsilon, delta, outfile);
			i = i + 2;
		}
		else {
			Interval yp = uni(*(upper_roots + i), Interval(y.right, y.right));//求解右边界问题
			divide_2d(p, x, yp, epsilon, delta, outfile);
			i = i + 1;
		}
	}

	while (lower_num > j) {
		if (lower_num > j + 1) {
			Interval yp = uni(*(lower_roots + j), *(lower_roots + j + 1)); //求解多根问题
			divide_2d(p, x, yp, epsilon, delta, outfile);
			j = j + 2;
		}
		else {
			Interval yp = uni(*(lower_roots + j), Interval(y.right, y.right));//求解右边界问题
			divide_2d(p, x, yp, epsilon, delta, outfile);
			j = j + 1;
		}
	}
	free(upper_roots);
	upper_roots = NULL;
	free(lower_roots);
	lower_roots = NULL;
}


//通过x轴划分，分别求解
void divide_and_solve_2d(Polynomial2 p, float x1, float x2, float y1, float y2, float epsilon, float delta, ofstream* outfile) {
	float xlen = x2 - x1;
	float ylen = y2 - y1;
	Interval x(x1, x2);
	Interval y(y1, y2);
	Box b(x, y);
	int xnumber = int(xlen / epsilon);
	for (int ix = 0; ix < xnumber; ix++) {
		float xleft = x1 + ix * epsilon;
		float xright = x1 + (ix + 1) * epsilon;
		Interval xs(xleft, xright);
		Box bx(xs, y);
		root_isolation_and_solve_2d(p, bx, epsilon, delta, outfile);
	}
}

//pv算法
void slovepv_2d(Polynomial2 p, float x1, float x2, float y1, float y2, float epsilon, float delta, ofstream* outfile) {
	Interval x(x1, x2);
	Interval y(y1, y2);
	Box b(x, y);
	if (b.diameter() > epsilon) {
		slovepv_2d(p, x1, x.mid(), y1, y.mid(), epsilon, delta, outfile);
		slovepv_2d(p, x1, x.mid(), y.mid(), y2, epsilon, delta, outfile);
		slovepv_2d(p, x.mid(), x2, y1, y.mid(), epsilon, delta, outfile);
		slovepv_2d(p, x.mid(), x2, y.mid(), y2, epsilon, delta, outfile);
	}
	else if (b.diameter() > delta) {
		Interval px = intpoly(p.diffx(), b);
		Interval py = intpoly(p.diffy(), b);
		if (!(0 << px * px + py * py)) {
			output_2d(p, x1, x2, y1, y2, outfile);
		}
		else {
			slovepv_2d(p, x1, x.mid(), y1, y.mid(), epsilon, delta, outfile);
			slovepv_2d(p, x1, x.mid(), y.mid(), y2, epsilon, delta, outfile);
			slovepv_2d(p, x.mid(), x2, y1, y.mid(), epsilon, delta, outfile);
			slovepv_2d(p, x.mid(), x2, y.mid(), y2, epsilon, delta, outfile);
		}
	}
	else {
		output_2d(p, x1, x2, y1, y2, outfile);
	}
}


//mc算法
void mc_2d(Polynomial2 p, float  x1, float  x2, float  y1, float  y2, float  epsilon, float  delta, ofstream* outfile) {
	int xnumber, ynumber;
	float  xl, xr, yl, yr;
	xnumber = int((x2 - x1) / epsilon);
	ynumber = int((y2 - y1) / epsilon);
	for (int ix = 0; ix < xnumber; ix++) {
		for (int iy = 0; iy < ynumber; iy++) {
			xl = x1 + ix * epsilon;
			xr = x1 + (ix + 1) * epsilon;
			yl = y1 + iy * epsilon;
			yr = y1 + (iy + 1) * epsilon;
			outputmc_2d(p, xl, xr, yl, yr, outfile);
		}
	}
}

double  jc(double  x) {
	int res = 1;
	for (int i = 1; i < x + 1; i++) {
		res = res * i;
	}
	return res;
}
void testf2d() {
	//p1.NewTerm(-46, 5, 0);
	//p1.NewTerm(-28, 4, 1);
	//p1.NewTerm(19, 3, 2);
	//p1.NewTerm(-96, 2, 3);
	//p1.NewTerm(-80, 1, 4);
	//p1.NewTerm(-69, 0, 5);
	//p1.NewTerm(-93, 4, 0);
	//p1.NewTerm(73, 3, 1);
	//p1.NewTerm(-36, 2, 2);
	//p1.NewTerm(92, 1, 3);
	//p1.NewTerm(-66, 0, 4);
	//p1.NewTerm(98, 3, 0);
	//p1.NewTerm(30, 2, 1);
	//p1.NewTerm(-50, 1, 2);
	//p1.NewTerm(13, 0, 3);
	//p1.NewTerm(-22, 2, 0);
	//p1.NewTerm(34, 1, 1);
	//p1.NewTerm(7, 0, 2);
	//p1.NewTerm(44, 1, 0);
	//p1.NewTerm(46, 0, 1);
	//p1.NewTerm(-19, 0, 0);


	//Polynomial2 p1, p2, p3, p4, p5;
	//p5.NewTerm(95, 12, 13);
	//p5.NewTerm(-71, 18, 4);
	//p5.NewTerm(73, 5, 17);
	//p5.NewTerm(46, 0, 18);
	//p5.NewTerm(53, 10, 1);
	//p5.NewTerm(43, 0, 4);
	//p2.NewTerm(31, 16, 18);
	//p2.NewTerm(-64, 16, 17);
	//p2.NewTerm(-41, 24, 2);
	//p2.NewTerm(-89, 24, 0);
	//p2.NewTerm(78, 20, 3);
	//p2.NewTerm(42, 1, 14);
	//p3.NewTerm(1, 0, 0);
	//p4 = p5 * p2;
	//p1 = p4 + p3;

	//Polynomial2 p1;
	//p1.NewTerm(1, 2, 0);
	//p1.NewTerm(1.5, 0, 2);
	//p1.NewTerm(-9, 0, 0);
	/*p0.NewTerm(1, 2, 0);
	p0.NewTerm(1, 0, 2);
	p1.NewTerm(-4, 2, 2);
	p2.NewTerm(-0.01, 0, 0);
	p3 = p0 * p0 * p0 * p0 * p0 * p0 * p0 * p0 * p0 * p0 + p1 + p2;*/





	//Polynomial2 p1, p0;
	//p1.NewTerm(2, 5, 0);
	//p1.NewTerm(1, 2, 3);
	//p1.NewTerm(3, 4, 0);
	//p1.NewTerm(1, 3, 0);
	//p1.NewTerm(-5, 2, 1);
	//p1.NewTerm(-3, 0, 2);
	//p1.NewTerm(-5, 1, 0);


	//p1.NewTerm(1, 0, 0);

	//Polynomial2 p2;
	//p2.NewTerm(1, 1, 0);
	//p2.NewTerm(1, 0, 1);

	//p1 = p1 + p2;

	//p0.NewTerm(1, 0, 0);

	//for (int i = 2; i < 14; i++) {
	//	p0.NewTerm(1 / jc(i) - 1 / jc(i - 1), 0, 0);
	//	cout << p0 << endl;
	//	p1 = p1 + p0 * expt(p2, i);
	//}

	Polynomial2 p0, p1, p2, p3, p4;
	//p1.NewTerm(1, 2, 0);
	//p1.NewTerm(-1, 4, 0);
	//p1.NewTerm(-1, 0, 2);
	//p1.NewTerm(0.001, 0, 0);

	//(-x ^ 2 + y - 1) ^ 4 * (-x ^ 2 + y) ^ 4 + (y - 1) ^ 9 * y ^ 8

	
	p0.NewTerm(1, 0, 1);

	p1.NewTerm(-1, 2, 0);
	p1.NewTerm(1, 0, 1);
	p1.NewTerm(-1, 0, 0);
	p1.NewTerm(0.001, 0, 0);

	p2.NewTerm(-1, 2, 0);
	p2.NewTerm(1, 0, 1);
	p2.NewTerm(0.001, 0, 0);

	p3.NewTerm(1, 0, 1);
	p3.NewTerm(-1, 0, 0);

	p4 = p1 * p1 * p2 * p2 + p3 * p3 * p3 * p3 * p3 * p0 * p0 * p0 * p0;

	float x1 = -2.00324;
	float x2 = 2.0034;
	float y1 = -2.002;
	float y2 = 2.0023;
	float epsilon = 0.1;
	float delta = 0.01;
	ofstream outfile("5p28pv.txt", ios::out);
	ofstream* loc;
	loc = &outfile;
	//divide_and_solve_2d(p4, x1, x2, y1, y2, epsilon, delta, loc);
	//slovepv_2d(p4, x1, x2, y1, y2, epsilon, delta, loc);
	mc_2d(p4, x1, x2, y1, y2, epsilon, delta, loc);
	outfile.close();
}

int main() {
	clock_t start, end;
	start = clock();
	testf2d();
	end = clock();
	cout << "F1运行时间" << (double)(end - start) / CLOCKS_PER_SEC << endl;
	return 0;
}