#include <iostream>
#include <graphics.h>
#include<cstdio>
#include<cassert>
#include<iostream>
#include<algorithm>
#include <fstream>
#include "polynomial2.cpp"

//void draw(Polynomial2 p, Polynomial2 px, Polynomial2 py, Box b, float epsilon, float a) {
//	float mind = epsilon * 0.94;
//	if (zero(p, b)) {
//		Interval intx = b.Intx;
//		Interval inty = b.Inty;
//		float ll = p.Eval(intx.left, inty.left);
//		float lr = p.Eval(intx.left, inty.right);
//		float rl = p.Eval(intx.right, inty.left);
//		float rr = p.Eval(intx.right, inty.right);
//		if (((ll > 0 && lr > 0 && rl > 0 && rr > 0) || (ll < 0 && lr < 0 && rl < 0 && rr < 0)) && !(zero(px, b)) && !(zero(py, b))) {}
//		else {
//			if (b.diameter() < mind) {
//				if (!(zero(px, b)) && !(zero(py, b))) { //2a2b
//					if ((ll > 0 && lr < 0 && rl < 0 && rr < 0) || (ll < 0 && lr > 0 && rl > 0 && rr > 0)) { 
//						line(a * intx.mid(), a * inty.left, a * intx.left, a * inty.mid()); //fig2
//					}
//					else if ((ll < 0 && lr > 0 && rl < 0 && rr < 0) || (ll > 0 && lr < 0 && rl > 0 && rr > 0)) {
//						line(a * intx.mid(), a * inty.right, a * intx.left, a * inty.mid()); //fig4
//					}
//					else if ((ll < 0 && lr < 0 && rl > 0 && rr < 0) || (ll > 0 && lr > 0 && rl < 0 && rr > 0)) {
//						line(a * intx.mid(), a * inty.left, a * intx.right, a * inty.mid()); //fig3
//					}
//					else if ((ll < 0 && lr < 0 && rl < 0 && rr > 0) || (ll > 0 && lr > 0 && rl > 0 && rr < 0)) {
//						line(a * intx.mid(), a * inty.right, a * intx.right, a * inty.mid()); //fig5
//					}
//					else if ((ll < 0 && lr < 0 && rl > 0 && rr > 0) || (ll > 0 && lr > 0 && rl < 0 && rr < 0)) {
//						line(a * intx.mid(), a * inty.left, a * intx.mid(), a * inty.right); //fig6
//					}
//					else if ((ll < 0 && lr > 0 && rl < 0 && rr > 0) || (ll > 0 && lr < 0 && rl > 0 && rr < 0)) {
//						line(a * intx.left, a * inty.mid(), a * intx.right, a * inty.mid()); //fig7
//					}
//					else {
//					}
//				}
//				else if (!(zero(px, b))) {//2a 
//					if (!zero(p, b.l()) || !zero(py, b.l()) && (ll > 0 && lr > 0 || ll < 0 && lr < 0)) {// 8c
//						if (!zero(p, b.r()) || !zero(py, b.r()) && (rl > 0 && rr > 0 || rl < 0 && rr < 0)) {//8d 
//							if (lr > 0 && rr < 0 || lr < 0 && rr > 0) { //6a 
//								line(a * intx.mid(), a * inty.left, a * intx.mid(), a * inty.right); //fig6
//							}
//						}
//						else if (!zero(py, b.r()) && (rl > 0 && rr < 0 || rl < 0 && rr > 0)) { //9d
//							if (ll > 0 && rl < 0 || ll < 0 && rl > 0) {//6b
//								line(a * intx.mid(), a * inty.left, a * intx.right, a * inty.mid());//fig3
//							}
//							else if (lr > 0 && rr < 0 || lr < 0 && rr > 0) {//6a
//								line(a * intx.mid(), a * inty.right, a * intx.right, a * inty.mid());//fig5
//							}
//						}
//					}
//					else if (!zero(py, b.l()) && (ll > 0 && lr < 0 || ll < 0 && lr > 0)) {//9c
//						if (!zero(p, b.r()) || !zero(py, b.r()) && (rl > 0 && rr > 0 || rl < 0 && rr < 0)) {//8d
//							if (lr > 0 && rr < 0 || lr < 0 && rr > 0) { //6a
//								line(a * intx.mid(), a * inty.right, a * intx.left, a * inty.mid());//fig4
//							}
//							else if (ll > 0 && rl < 0 || ll < 0 && rl > 0) {//6b
//								line(a * intx.mid(), a * inty.left, a * intx.left, a * inty.mid());//fig2
//							}
//						}
//						else if (!zero(py, b.r()) && (rl > 0 && rr < 0 || rl < 0 && rr > 0)) {//9d
//							line(a * intx.left, a * inty.mid(), a * intx.right, a * inty.mid());//fig7
//						}
//					}
//				}
//
//				else if (!(zero(py, b))) {//2b ok
//					if (!zero(p, b.u()) || !zero(px, b.u()) && (lr > 0 && rr > 0 || lr < 0 && rr < 0)) {// 8a ok
//						if (!zero(p, b.d()) || !zero(px, b.d()) && (ll > 0 && rl > 0 || ll < 0 && rl < 0)) {//8b ok
//							if (ll > 0 && lr < 0 || ll < 0 && lr > 0) { //6c ok
//								line(a * intx.left, a * inty.mid(), a * intx.right, a * inty.mid()); //fig7 ok
//							}
//						}
//						else if (!zero(px, b.d()) && (ll > 0 && rl < 0 || ll < 0 && rl > 0)) { //9b ok
//							if (rl > 0 && rr < 0 || rl < 0 && rr > 0) {//6d  ok
//								line(a * intx.mid(), a * inty.left, a * intx.right, a * inty.mid()); //fig3 ok
//							}
//							else if (ll > 0 && lr < 0 || ll < 0 && lr > 0) {//6c ok
//								line(a * intx.mid(), a * inty.left, a * intx.left, a * inty.mid()); //fig2 ok
//							}
//						}
//					}
//					else if (!zero(px, b.u()) && (lr > 0 && rr < 0 || lr < 0 && rr > 0)) {//9a ok
//						if (!zero(p, b.d()) || !zero(px, b.d()) && (ll > 0 && rl > 0 || ll < 0 && rl < 0)) {//8b ok
//							if (ll > 0 && lr < 0 || ll < 0 && lr > 0) { //6c ok
//								line(a * intx.mid(), a * inty.right, a * intx.left, a * inty.mid()); //fig4 ok
//							}
//							else if (rl > 0 && rr < 0 || rl < 0 && rr > 0) {//6d ok
//								line(a * intx.mid(), a * inty.right, a * intx.right, a * inty.mid()); //fig5 ok
//							}
//						}
//						else if (!zero(px, b.d()) && (ll > 0 && rl < 0 || ll < 0 && rl > 0)) {//9b ok
//							line(a * intx.mid(), a * inty.left, a * intx.mid(), a * inty.right); //fig6 ok
//						}
//					}
//				}
//
//				else if ((zero(px, b)) && (zero(py, b))) {
//					circle(a * intx.mid(), a * inty.mid(), 3);
//					cout << "1" << b << endl;
//				}
//
//				else if (zero(px, b)) {
//					if ((zero(p, b.u()) && zero(px, b.u())) || (zero(p, b.d()) && zero(px, b.d()))) {
//						circle(a * intx.mid(), a * inty.mid(), 3);
//						//cout << "p=" << p << endl;
//						//cout << "px=" << px << endl;
//						//cout << "py=" << py << endl;
//						//cout << "intpoly(p, b.u())" << intpoly(p, b.u()) << endl;
//						//cout << "intpoly(px, b.u())" << intpoly(px, b.u()) << endl;
//						//cout << "intpoly(p, b.d())" << intpoly(p, b.d()) << endl;
//						//cout << "intpoly(px, b.d())" << intpoly(px, b.d()) << endl;
//						//cout << "2b=" << b << endl;
//					}
//				}
//
//				if (zero(py, b)) {
//					if ((zero(p, b.l()) && zero(py, b.l())) || (zero(p, b.r()) && zero(py, b.r()))) {
//						circle(a * intx.mid(), a * inty.mid(), 3);
//						cout << "3" << b << endl;
//					}
//				}
//			}
//			else {
//				draw(p, px, py, b.ll(), epsilon, a);
//				draw(p, px, py, b.lr(), epsilon, a);
//				draw(p, px, py, b.rl(), epsilon, a);
//				draw(p, px, py, b.rr(), epsilon, a);
//			}
//		}
//	}
//}


void draw(Polynomial2 p, Polynomial2 px, Polynomial2 py, Box b, float epsilon, float a) {
	float mind = epsilon * 0.94;
	Interval intx = b.Intx;
	Interval inty = b.Inty;
	if (inty.len() < 7*mind) {
		line(a * intx.left, a * inty.mid(), a * intx.right, a * inty.mid());
	}
	
}

void outword(float a, float b, float c, float d, ofstream outfile) {

	outfile << a << " " << b << " " << c << " " << d << '\n';
}

void testf1(){
	Polynomial2 p1;
	p1.NewTerm(-46, 5, 0);
	p1.NewTerm(-28, 4, 1);
	p1.NewTerm(19, 3, 2);
	p1.NewTerm(-96, 2, 3);
	p1.NewTerm(-80, 1, 4);
	p1.NewTerm(-69, 0, 5);
	p1.NewTerm(-93, 4, 0);
	p1.NewTerm(73, 3, 1);
	p1.NewTerm(-36, 2, 2);
	p1.NewTerm(92, 1, 3);
	p1.NewTerm(-66, 0, 4);
	p1.NewTerm(98, 3, 0);
	p1.NewTerm(30, 2, 1);
	p1.NewTerm(-50, 1, 2);
	p1.NewTerm(13, 0, 3);
	p1.NewTerm(-22, 2, 0);
	p1.NewTerm(34, 1, 1);
	p1.NewTerm(7, 0, 2);
	p1.NewTerm(44, 1, 0);
	p1.NewTerm(46, 0, 1);
	p1.NewTerm(-19, 0, 0);
	Polynomial2 px = p1.diffx();
	Polynomial2 py = p1.diffy();
	float x1 = -5.056758789797867;
	float x2 = 5;
	float y1 = -5.0456386786897;
	float y2 = 5;
	float xlen = x2 - x1;
	float ylen = y2 - y1;
	float maxlen = max(xlen, ylen);
	float ratio = float(500) / float(maxlen);
	initgraph(xlen*ratio, ylen*ratio);
	setorigin(-x1*ratio, -y1*ratio);
	setaspectratio(1, -1);
	Interval x(x1, x2);
	Interval y(y1, y2);
	Box b(x, y);
	float epsilon = 0.01;
	//draw(p1, px, py, b, epsilon, ratio);
	float xspace = 0.5 * epsilon;
	int xnumber = int(xlen / xspace);
	int j = 0;

	//int j = 0;
	//for (int i = 0; i < xnumber; i++) {
	//	Interval tempxlen(x1 + i * xspace, x1 + (i + 1) * xspace);
	//	Box tempbox(tempxlen, y);
	//	Interval* tempyinters = root_y(p1, tempbox, 0.005, 0.001);
	//	j = 0;
	//	while ((*(tempyinters + j)).len() > 0) {
	//		Box boxss(tempxlen, *(tempyinters + j));
	//		draw(p1, px, py, boxss, epsilon, ratio);
	//		j = j + 1;
	//	}
	//}
    getchar();
    closegraph();   
}



void testf2(){
	Polynomial2 p1, p2, p3, p4, p5;
	p1.NewTerm(95, 12, 13);
	p1.NewTerm(-71, 18, 4);
	p1.NewTerm(73, 5, 17);
	p1.NewTerm(46, 0, 18);
	p1.NewTerm(53, 10, 1);
	p1.NewTerm(43, 0, 4);
	p2.NewTerm(31, 16, 18);
	p2.NewTerm(-64, 16, 17);
	p2.NewTerm(-41, 24, 2);
	p2.NewTerm(-89, 24, 0);
	p2.NewTerm(78, 20, 3);
	p2.NewTerm(42, 1, 14);
	p3.NewTerm(1, 0, 0);
	p4 = p1 * p2;
	p5 = p4 + p3;
    Polynomial2 px = p5.diffx();
    Polynomial2 py = p5.diffy();
	float x1 = -5.2798;
	float x2 = 5;
	float y1 = -5.5676;
	float y2 = 5;
	float xlen = x2 - x1;
	float ylen = y2 - y1;
	float maxlen = max(xlen, ylen);
	float ratio = float(500) / float(maxlen);
	initgraph(xlen * ratio, ylen * ratio);
	setorigin(-x1 * ratio, -y1 * ratio);
	setaspectratio(1, -1);
	Interval x(x1, x2);
	Interval y(y1, y2);
	Box b(x, y);
	float epsilon = 0.01;
	//draw(p5, px, py, b, epsilon, ratio);
	float xspace = 0.5 * epsilon;
	int xnumber = int(xlen / xspace);


	cout <<  "p=" << p5 << endl;
	cout << "px=" << px << endl;
	cout << "py=" << py << endl;
	Interval tttt(-4, -4 + 0.0005);
	Box ttttbox(tttt, y);
	Polynomial1 upper_for_positive1 = upper_for_positive(p5, tttt);
	Polynomial1 upper_for_negative1 = upper_for_negative(p5, tttt);
	Polynomial1 lower_for_positive1 = lower_for_positive(p5, tttt);
	Polynomial1 lower_for_negative1 = lower_for_negative(p5, tttt);
	cout << "upper_for_positive=" << upper_for_positive1 << endl;
	cout << "upper_for_negative=" << upper_for_negative1 << endl;
	cout << "lower_for_positive=" << lower_for_positive1 << endl;
	cout << "lower_for_negative=" << lower_for_negative1 << endl;
	Interval I_negative(-5, 0);
	Interval I_positive(0, 5);
	Interval* roots_upper_for_positive = root(upper_for_positive1, I_positive, 0.005, 0.001);
	Interval* roots_upper_for_negative = root(upper_for_negative1, I_negative, 0.005, 0.001);
	Interval* roots_lower_for_positive = root(lower_for_positive1, I_positive, 0.005, 0.001);
	Interval* roots_lower_for_negative = root(lower_for_negative1, I_negative, 0.005, 0.001);
	cout << "These are roots_upper_for_positive" << endl;
	int i = 0;
	while ((*(roots_upper_for_positive + i)).len() > 0) {
		cout << *(roots_upper_for_positive + i) << endl;
		i = i + 1;
	}
	cout << "These are roots_upper_for_negative" << endl;
	i = 0;
	while ((*(roots_upper_for_negative + i)).len() > 0) {
		cout << *(roots_upper_for_negative + i) << endl;
		i = i + 1;
	}
	cout << "These are roots_lower_for_positive" << endl;
	i = 0;
	while ((*(roots_lower_for_positive + i)).len() > 0) {
		cout << *(roots_lower_for_positive + i) << endl;
		i = i + 1;
	}
	cout << "These are roots_lower_for_negative" << endl;
	i = 0;
	while ((*(roots_lower_for_negative + i)).len() > 0) {
		cout << *(roots_lower_for_negative + i) << endl;
		i = i + 1;
	}
	Interval* root_fory = root_y(p5, ttttbox, 0.005, 0.001);
	cout << "These are roots" << endl;
	i = 0;
	while ((*(root_fory + i)).len() > 0) {
		cout << *(root_fory + i) << endl;
		i = i + 1;
	}

	ofstream outfile("a.txt", ios::out);


	int jy = 0;
	for (int ix = 0; ix < xnumber; ix++) {
		float xleft = x1 + ix * xspace;
		float xright = x1 + (ix + 1) * xspace;
		float xmid = (xleft + xright) / 2;
		Interval tempxlen(xleft, xright);
		Box tempbox(tempxlen, y);
		Interval* tempyinters = root_y(p5, tempbox, 0.05, 0.01);
		jy = 0;
		while ((*(tempyinters + jy)).len() > 0) {
			float ll = p5.Eval(xleft, (*(tempyinters + jy)).left);
			float lr = p5.Eval(xleft, (*(tempyinters + jy)).right);
			float rl = p5.Eval(xright, (*(tempyinters + jy)).left);
			float rr = p5.Eval(xright, (*(tempyinters + jy)).right);
			float dis = 0.01;
			if (ll * rl < 0) {
				if (ll * lr < 0) {
					float a = one_point_search(p5, *(tempyinters + jy), x1 + ix * xspace, dis);
					//line(xmid, (*(tempyinters + jy)).left, xleft, a);
					outfile << xmid << " " << (*(tempyinters + jy)).left << " " << xleft << " " << a << '\n';
				}
				else {
					float a = one_point_search(p5, *(tempyinters + jy), x1 + (ix + 1) * xspace, dis);
					//line(xmid, (*(tempyinters + jy)).left, xright, a);
					outfile << xmid << " " << (*(tempyinters + jy)).left << " " << xright << " " << a << '\n';
				}
			}
			else if (lr * rr < 0) {
				if (ll * lr < 0) {
					float a = one_point_search(p5, *(tempyinters + jy), x1 + ix * xspace, dis);
					//line(xmid, (*(tempyinters + jy)).right, xleft, a);
					outfile << xmid << " " << (*(tempyinters + jy)).right << " " << xleft << " " << a << '\n';
				}
				else {
					float a = one_point_search(p5, *(tempyinters + jy), x1 + (ix + 1) * xspace, dis);
					//line(xmid, (*(tempyinters + jy)).right, xright, a);
					outfile << xmid << " " << (*(tempyinters + jy)).right << " " << xright << " " << a << '\n';
				}
			}
			else if (ll * lr < 0) {
				float a = one_point_search(p5, *(tempyinters + jy), x1 + ix * xspace, dis);
				float b = one_point_search(p5, *(tempyinters + jy), x1 + (ix + 1) * xspace, dis);
				//line(xleft, a, xright, b);
				outfile << xleft << " " << a << " " << xright << " " << b << '\n';
			}
			else {
				Interval a = two_point_search(p5, *(tempyinters + jy), x1 + ix * xspace, dis);
				Interval b = two_point_search(p5, *(tempyinters + jy), x1 + (ix + 1) * xspace, dis);
				if (a.len() > 0 && b.len() > 0) {
					//line(xleft, a.left, xright, b.left);
					outfile << xleft << " " << a.left << " " << xright << " " << b.left << '\n';
					//line(xleft, a.right, xright, b.right);
					outfile << xleft << " " << a.right << " " << xright << " " << b.right << '\n';
				}
				else if (a.len() > 0) {
					//line(xleft, a.left, xleft, a.right);
					outfile << xleft << " " << a.left << " " << xleft << " " << a.right << '\n';
				}
				else if (b.len() > 0) {
					//line(xright, b.left, xright, b.right);
					outfile << xright << " " << b.left << " " << xright << " " << b.right << '\n';
				}
			}

			//Box boxss(tempxlen, *(tempyinters + jy));

			//draw(p5, px, py, boxss, epsilon, ratio);
			jy = jy + 1;
		}
	}
	outfile.close();
	//line(-3 * ratio, -5 * ratio, -3 * ratio, 5 * ratio);
	//line(-4 * ratio, -5 * ratio, -4 * ratio, 5 * ratio);
	//line(-2 * ratio, -5 * ratio, -2 * ratio, 5 * ratio);
	//line(-1 * ratio, -5 * ratio, -1 * ratio, 5 * ratio);




	//int i, j;
	//Interval** p;

	//p = (Interval**)malloc(sizeof(Interval*) * xnumber);
	//for (i = 0; i < xnumber; i++)
	//{
	//	*(p + i) = (Interval*)malloc(sizeof(Interval) * 100);
	//}
	//for (i = 0; i < xnumber; i++) {
	//	p[i] = root_y(p5, Box(Interval(x1 + i * xspace, x1 + (i + 1) * xspace), y), 0.005, 0.001);
	//}
	//

	//Interval* first = p[0];
	//Interval* second = p[1];
	//Interval* third = p[2];
	//i = 0;
	//j = 0;
	//while ((*(second + i)).len() > 0) {
	//	if (p5.Eval(x1 + 1 * xspace, (*(second + i)).right) * p5.Eval(x1 + 1 * xspace, (*(second + i)).left) < 0) {

	//	}
	//	i = i + 1;
	//}



	getchar();
	closegraph();
}


void testf3() {
	Polynomial2 p1;
	p1.NewTerm(1, 2, 0);
	p1.NewTerm(1, 0, 2);
	p1.NewTerm(-20, 0, 0);
	Polynomial2 px = p1.diffx();
	Polynomial2 py = p1.diffy();
	float x1 = -5.3243123;
	float x2 = 5;
	float y1 = -5.121213;
	float y2 = 5;
	float xlen = x2 - x1;
	float ylen = y2 - y1;
	float maxlen = max(xlen, ylen);
	float ratio = float(500) / float(maxlen);
	initgraph(xlen * ratio, ylen * ratio);
	setorigin(-x1 * ratio, -y1 * ratio);
	setaspectratio(1, -1);
	Interval x(x1, x2);
	Interval y(y1, y2);
	Box b(x, y);
	float epsilon = 0.02;
	draw(p1, px, py, b, epsilon, ratio);
	getchar();
	closegraph();
}


int main() {
	//testf1();
	testf2();
	//testf3();
}