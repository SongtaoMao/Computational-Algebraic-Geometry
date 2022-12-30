#include <iostream>
#include <graphics.h>
#include<time.h>
#include <cstdio>
#include <cassert>
#include <iostream>
#include <algorithm>
#include <fstream>
#include "polynomial3.cpp"


void testf3d(){
	Polynomial3 p1;
	//p1.NewTerm(-17, 17, 3, 1);
	//p1.NewTerm(-75, 5, 10, 6);
	//p1.NewTerm(-10, 0, 8, 13);
	//p1.NewTerm(-7, 0, 6, 15);
	//p1.NewTerm(71, 13, 2, 5);
	//p1.NewTerm(-44, 0, 5, 13);
	//p1.NewTerm(-82, 8, 0, 8);
	//p1.NewTerm(80, 0, 14, 2);
	//p1.NewTerm(62, 4, 7, 4);
	//p1.NewTerm(-10, 7, 1, 3);
	//p1.NewTerm(-83, 2, 4, 3);
	//p1.NewTerm(-4, 2, 5, 0);
	//p1.NewTerm(-73, 1, 1, 0);
	//p1.NewTerm(1, 0, 0, 0);
	p1.NewTerm(1, 4, 0, 0);
	p1.NewTerm(-5, 2, 0, 0);
	p1.NewTerm(1, 0, 4, 0);
	p1.NewTerm(-5, 0, 2, 0);
	p1.NewTerm(1, 0, 0, 4);
	p1.NewTerm(-5, 0, 0, 2);
	p1.NewTerm(10, 0, 0, 0);
    Polynomial3 px = p1.diffx();
    Polynomial3 py = p1.diffy();
	Polynomial3 pz = p1.diffy();
	float x1 = -3;
	float x2 = 3;
	float y1 = -3;
	float y2 = 3;
	float z1 = -3;
	float z2 = 3;
	float xlen = x2 - x1;
	float ylen = y2 - y1;
	float zlen = z2 - z1;
	Interval x(x1, x2);
	Interval y(y1, y2);
	Interval z(z1, z2);
	Cube b(x, y, z);
	float epsilon = 0.1;
	float xspace = epsilon;
	float yspace = epsilon;
	int xnumber = int(xlen / xspace);
	int ynumber = int(ylen / xspace);
	cout << xnumber << endl;
	cout << ynumber << endl;
	ofstream outfile("textnew1.txt", ios::out);

	int iz;
	for (int ix = 0; ix < xnumber; ix++) {
		for (int iy = 0; iy < ynumber; iy++) {
			float xleft = x1 + ix * xspace;
			float xright = x1 + (ix + 1) * xspace;
			float yleft = y1 + iy * yspace;
			float yright = y1 + (iy + 1) * yspace;
			float xmid = (xleft + xright) / 2;
			float ymid = (yleft + yright) / 2;
			Interval xs(xleft, xright);
			Interval ys(yleft, yright);
			Cube cube1(xs, ys, z);
			Interval* zinters = root_y(p1, cube1, 0.05, 0.01);
			iz = 0;
			while ((*(zinters + iz)).len() > 0) {
				float lll = p1.Eval(xleft, y.left, (*(zinters + iz)).left);
				float llr = p1.Eval(xleft, y.left, (*(zinters + iz)).right);
				float lrl = p1.Eval(xleft, y.right, (*(zinters + iz)).left);
				float lrr = p1.Eval(xleft, y.right, (*(zinters + iz)).right);
				float rll = p1.Eval(xright, y.left, (*(zinters + iz)).left);
				float rlr = p1.Eval(xright, y.left, (*(zinters + iz)).right);
				float rrl = p1.Eval(xright, y.right, (*(zinters + iz)).left);
				float rrr = p1.Eval(xright, y.right, (*(zinters + iz)).right);
				float dis = 0.01;
				if (lll * lrl < 0 && lll * rll < 0) {
					if (lll * llr < 0) {
						float d = one_point_search(p1, *(zinters + iz), xleft, yleft, dis);
						outfile << xmid << " " << yleft << " " << (*(zinters + iz)).left << " ";//x4
						outfile << xleft << " " << ymid << " " << (*(zinters + iz)).left << " ";//x1
						outfile << xleft << " " << yleft << " " << d << "\n";
					}
					else {
						float a = one_point_search(p1, *(zinters + iz), xleft, yright, dis);
						float b = one_point_search(p1, *(zinters + iz), xright, yleft, dis);
						float c = one_point_search(p1, *(zinters + iz), xright, yright, dis);
						outfile << xmid << " " << yleft << " " << (*(zinters + iz)).left << " ";
						outfile << xright << " " << yleft << " " << b << " ";
						outfile << xright << " " << yright << " " << c << "\n";
						outfile << xleft << " " << ymid << " " << (*(zinters + iz)).left << " ";
						outfile << xleft << " " << yright << " " << a << " ";
						outfile << xright << " " << yright << " " << c << "\n";
						outfile << xmid << " " << yleft << " " << (*(zinters + iz)).left << " ";
						outfile << xleft << " " << ymid << " " << (*(zinters + iz)).left << " ";
						outfile << xright << " " << yright << " " << c << "\n";
					}
				}

				else if (lll * lrl < 0 && lrl * rrl < 0) {
					if (lrl * lrr < 0) {
						float a = one_point_search(p1, *(zinters + iz), xleft, yright, dis);
						outfile << xleft << " " << ymid << " " << (*(zinters + iz)).left << " ";//x1
						outfile << xmid << " " << yright << " " << (*(zinters + iz)).left << " ";//x2
						outfile << xleft << " " << yright << " " << a << "\n";
					}
					else {
						float b = one_point_search(p1, *(zinters + iz), xright, yleft, dis);
						float c = one_point_search(p1, *(zinters + iz), xright, yright, dis);
						float d = one_point_search(p1, *(zinters + iz), xleft, yleft, dis);
						outfile << xleft << " " << ymid << " " << (*(zinters + iz)).left << " ";//x1
						outfile << xleft << " " << yleft << " " << d << " ";
						outfile << xright << " " << yleft << " " << b << "\n";
						outfile << xmid << " " << yright << " " << (*(zinters + iz)).left << " ";//x2
						outfile << xright << " " << yright << " " << c << " ";
						outfile << xright << " " << yleft << " " << b << "\n";
						outfile << xleft << " " << ymid << " " << (*(zinters + iz)).left << " ";//x1
						outfile << xmid << " " << yright << " " << (*(zinters + iz)).left << " ";//x2
						outfile << xright << " " << yleft << " " << b << "\n";
					}
				}


				else if (lll * rll < 0 && rll * rrl < 0) {
					if (rll * rlr < 0) {
						float b = one_point_search(p1, *(zinters + iz), xright, yleft, dis);
						outfile << xmid << " " << yleft << " " << (*(zinters + iz)).left << " ";//x4
						outfile << xright << " " << ymid << " " << (*(zinters + iz)).left << " ";//x3
						outfile << xright << " " << yleft << " " << b << "\n";
					}
					else {
						float a = one_point_search(p1, *(zinters + iz), xleft, yright, dis);
						float c = one_point_search(p1, *(zinters + iz), xright, yright, dis);
						float d = one_point_search(p1, *(zinters + iz), xleft, yleft, dis);
						outfile << xright << " " << ymid << " " << (*(zinters + iz)).left << " ";//x3
						outfile << xright << " " << yright << " " << c << " ";
						outfile << xleft << " " << yright << " " << a << "\n";
						outfile << xmid << " " << yleft << " " << (*(zinters + iz)).left << " ";//x4
						outfile << xleft << " " << yleft << " " << d << " ";
						outfile << xleft << " " << yright << " " << a << "\n";
						outfile << xmid << " " << yleft << " " << (*(zinters + iz)).left << " ";//x4
						outfile << xright << " " << ymid << " " << (*(zinters + iz)).left << " ";//x3
						outfile << xleft << " " << yright << " " << a << "\n";
					}
				}

				else if (rrl * rll < 0 && rrl * lrl < 0) {
					if (rrl * rrr < 0) {
						float c = one_point_search(p1, *(zinters + iz), xright, yright, dis);
						outfile << xmid << " " << yright << " " << (*(zinters + iz)).left << " ";//x2
						outfile << xright << " " << ymid << " " << (*(zinters + iz)).left << " ";//x3
						outfile << xright << " " << yright << " " << c << "\n";
					}
					else {
						float a = one_point_search(p1, *(zinters + iz), xleft, yright, dis);
						float b = one_point_search(p1, *(zinters + iz), xright, yleft, dis);
						float d = one_point_search(p1, *(zinters + iz), xleft, yleft, dis);
						outfile << xmid << " " << yright << " " << (*(zinters + iz)).left << " ";//x2
						outfile << xleft << " " << yright << " " << a << " ";
						outfile << xleft << " " << yleft << " " << d << "\n";
						outfile << xright << " " << ymid << " " << (*(zinters + iz)).left << " ";//x3
						outfile << xright << " " << yleft << " " << b << " ";
						outfile << xleft << " " << yleft << " " << d << "\n";
						outfile << xmid << " " << yright << " " << (*(zinters + iz)).left << " ";//x2
						outfile << xright << " " << ymid << " " << (*(zinters + iz)).left << " ";//x3
						outfile << xleft << " " << yleft << " " << d << "\n";
					}
				}


				else if (lll * rll < 0 && lrl * rrl < 0) {
					if (lll * llr < 0) {
						float a = one_point_search(p1, *(zinters + iz), xleft, yright, dis);
						float d = one_point_search(p1, *(zinters + iz), xleft, yleft, dis);
						outfile << xmid << " " << yright << " " << (*(zinters + iz)).left << " ";//x2
						outfile << xmid << " " << yleft << " " << (*(zinters + iz)).left << " ";//x4
						outfile << xleft << " " << yleft << " " << d << "\n";
						outfile << xmid << " " << yright << " " << (*(zinters + iz)).left << " ";//x2
						outfile << xleft << " " << yright << " " << a << " ";
						outfile << xleft << " " << yleft << " " << d << "\n";
					}
					else {
						float b = one_point_search(p1, *(zinters + iz), xright, yleft, dis);
						float c = one_point_search(p1, *(zinters + iz), xright, yright, dis);
						outfile << xmid << " " << yright << " " << (*(zinters + iz)).left << " ";//x2
						outfile << xmid << " " << yleft << " " << (*(zinters + iz)).left << " ";//x4
						outfile << xright << " " << yleft << " " << b << "\n";
						outfile << xmid << " " << yright << " " << (*(zinters + iz)).left << " ";//x2
						outfile << xright << " " << yright << " " << c << " ";
						outfile << xright << " " << yleft << " " << b << "\n";
					}
				}


				else if (lll * lrl < 0 && rll * rrl < 0) {
					if (lll * llr < 0) {
						float b = one_point_search(p1, *(zinters + iz), xright, yleft, dis);
						float d = one_point_search(p1, *(zinters + iz), xleft, yleft, dis);
						outfile << xleft << " " << ymid << " " << (*(zinters + iz)).left << " ";//x1
						outfile << xright << " " << ymid << " " << (*(zinters + iz)).left << " ";//x3
						outfile << xleft << " " << yleft << " " << d << "\n";
						outfile << xright << " " << ymid << " " << (*(zinters + iz)).left << " ";//x3
						outfile << xright << " " << yleft << " " << b << " ";
						outfile << xleft << " " << yleft << " " << d << "\n";
					}
					else {
						float a = one_point_search(p1, *(zinters + iz), xleft, yright, dis);
						float c = one_point_search(p1, *(zinters + iz), xright, yright, dis);
						outfile << xleft << " " << ymid << " " << (*(zinters + iz)).left << " ";//x1
						outfile << xright << " " << ymid << " " << (*(zinters + iz)).left << " ";//x3
						outfile << xleft << " " << yright << " " << a << "\n";
						outfile << xright << " " << ymid << " " << (*(zinters + iz)).left << " ";//x3
						outfile << xright << " " << yright << " " << c << " ";
						outfile << xleft << " " << yright << " " << a << "\n";
					}
				}

				else if (llr * lrr < 0 && llr * rlr < 0) {
					if (lll * llr < 0) {
						float d = one_point_search(p1, *(zinters + iz), xleft, yleft, dis);
						outfile << xmid << " " << yleft << " " << (*(zinters + iz)).right << " ";//x4
						outfile << xleft << " " << ymid << " " << (*(zinters + iz)).right << " ";//x1
						outfile << xleft << " " << yleft << " " << d << "\n";
					}
					else {
						float a = one_point_search(p1, *(zinters + iz), xleft, yright, dis);
						float b = one_point_search(p1, *(zinters + iz), xright, yleft, dis);
						float c = one_point_search(p1, *(zinters + iz), xright, yright, dis);
						outfile << xmid << " " << yleft << " " << (*(zinters + iz)).right << " ";
						outfile << xright << " " << yleft << " " << b << " ";
						outfile << xright << " " << yright << " " << c << "\n";
						outfile << xleft << " " << ymid << " " << (*(zinters + iz)).right << " ";
						outfile << xleft << " " << yright << " " << a << " ";
						outfile << xright << " " << yright << " " << c << "\n";
						outfile << xmid << " " << yleft << " " << (*(zinters + iz)).right << " ";
						outfile << xleft << " " << ymid << " " << (*(zinters + iz)).right << " ";
						outfile << xright << " " << yright << " " << c << "\n";
					}
				}

				else if (llr * lrr < 0 && lrr * rrr < 0) {
					if (lrl * lrr < 0) {
						float a = one_point_search(p1, *(zinters + iz), xleft, yright, dis);
						outfile << xleft << " " << ymid << " " << (*(zinters + iz)).right << " ";//x1
						outfile << xmid << " " << yright << " " << (*(zinters + iz)).right << " ";//x2
						outfile << xleft << " " << yright << " " << a << "\n";
					}
					else {
						float b = one_point_search(p1, *(zinters + iz), xright, yleft, dis);
						float c = one_point_search(p1, *(zinters + iz), xright, yright, dis);
						float d = one_point_search(p1, *(zinters + iz), xleft, yleft, dis);
						outfile << xleft << " " << ymid << " " << (*(zinters + iz)).right << " ";//x1
						outfile << xleft << " " << yleft << " " << d << " ";
						outfile << xright << " " << yleft << " " << b << "\n";
						outfile << xmid << " " << yright << " " << (*(zinters + iz)).right << " ";//x2
						outfile << xright << " " << yright << " " << c << " ";
						outfile << xright << " " << yleft << " " << b << "\n";
						outfile << xleft << " " << ymid << " " << (*(zinters + iz)).right << " ";//x1
						outfile << xmid << " " << yright << " " << (*(zinters + iz)).right << " ";//x2
						outfile << xright << " " << yleft << " " << b << "\n";
					}
				}


				else if (llr * rlr < 0 && rlr * rrr < 0) {
					if (rll * rlr < 0) {
						float b = one_point_search(p1, *(zinters + iz), xright, yleft, dis);
						outfile << xmid << " " << yleft << " " << (*(zinters + iz)).right << " ";//x4
						outfile << xright << " " << ymid << " " << (*(zinters + iz)).right << " ";//x3
						outfile << xright << " " << yleft << " " << b << "\n";
					}
					else {
						float a = one_point_search(p1, *(zinters + iz), xleft, yright, dis);
						float c = one_point_search(p1, *(zinters + iz), xright, yright, dis);
						float d = one_point_search(p1, *(zinters + iz), xleft, yleft, dis);
						outfile << xright << " " << ymid << " " << (*(zinters + iz)).right << " ";//x3
						outfile << xright << " " << yright << " " << c << " ";
						outfile << xleft << " " << yright << " " << a << "\n";
						outfile << xmid << " " << yleft << " " << (*(zinters + iz)).right << " ";//x4
						outfile << xleft << " " << yleft << " " << d << " ";
						outfile << xleft << " " << yright << " " << a << "\n";
						outfile << xmid << " " << yleft << " " << (*(zinters + iz)).right << " ";//x4
						outfile << xright << " " << ymid << " " << (*(zinters + iz)).right << " ";//x3
						outfile << xleft << " " << yright << " " << a << "\n";
					}
				}

				else if (rrr * rlr < 0 && rrr * lrr < 0) {
					if (rrl * rrr < 0) {
						float c = one_point_search(p1, *(zinters + iz), xright, yright, dis);
						outfile << xmid << " " << yright << " " << (*(zinters + iz)).right << " ";//x2
						outfile << xright << " " << ymid << " " << (*(zinters + iz)).right << " ";//x3
						outfile << xright << " " << yright << " " << c << "\n";
					}
					else {
						float a = one_point_search(p1, *(zinters + iz), xleft, yright, dis);
						float b = one_point_search(p1, *(zinters + iz), xright, yleft, dis);
						float d = one_point_search(p1, *(zinters + iz), xleft, yleft, dis);
						outfile << xmid << " " << yright << " " << (*(zinters + iz)).right << " ";//x2
						outfile << xleft << " " << yright << " " << a << " ";
						outfile << xleft << " " << yleft << " " << d << "\n";
						outfile << xright << " " << ymid << " " << (*(zinters + iz)).right << " ";//x3
						outfile << xright << " " << yleft << " " << b << " ";
						outfile << xleft << " " << yleft << " " << d << "\n";
						outfile << xmid << " " << yright << " " << (*(zinters + iz)).right << " ";//x2
						outfile << xright << " " << ymid << " " << (*(zinters + iz)).right << " ";//x3
						outfile << xleft << " " << yleft << " " << d << "\n";
					}
				}


				else if (llr * rlr < 0 && lrr * rrr < 0) {
					if (lll * llr < 0) {
						float a = one_point_search(p1, *(zinters + iz), xleft, yright, dis);
						float d = one_point_search(p1, *(zinters + iz), xleft, yleft, dis);
						outfile << xmid << " " << yright << " " << (*(zinters + iz)).right << " ";//x2
						outfile << xmid << " " << yleft << " " << (*(zinters + iz)).right << " ";//x4
						outfile << xleft << " " << yleft << " " << d << "\n";
						outfile << xmid << " " << yright << " " << (*(zinters + iz)).right << " ";//x2
						outfile << xleft << " " << yright << " " << a << " ";
						outfile << xleft << " " << yleft << " " << d << "\n";
					}
					else {
						float b = one_point_search(p1, *(zinters + iz), xright, yleft, dis);
						float c = one_point_search(p1, *(zinters + iz), xright, yright, dis);
						outfile << xmid << " " << yright << " " << (*(zinters + iz)).right << " ";//x2
						outfile << xmid << " " << yleft << " " << (*(zinters + iz)).right << " ";//x4
						outfile << xright << " " << yleft << " " << b << "\n";
						outfile << xmid << " " << yright << " " << (*(zinters + iz)).right << " ";//x2
						outfile << xright << " " << yright << " " << c << " ";
						outfile << xright << " " << yleft << " " << b << "\n";
					}
				}


				else if (llr * lrr < 0 && rlr * rrr < 0) {
					if (lll * llr < 0) {
						float b = one_point_search(p1, *(zinters + iz), xright, yleft, dis);
						float d = one_point_search(p1, *(zinters + iz), xleft, yleft, dis);
						outfile << xleft << " " << ymid << " " << (*(zinters + iz)).right << " ";//x1
						outfile << xright << " " << ymid << " " << (*(zinters + iz)).right << " ";//x3
						outfile << xleft << " " << yleft << " " << d << "\n";
						outfile << xright << " " << ymid << " " << (*(zinters + iz)).right << " ";//x3
						outfile << xright << " " << yleft << " " << b << " ";
						outfile << xleft << " " << yleft << " " << d << "\n";
					}
					else {
						float a = one_point_search(p1, *(zinters + iz), xleft, yright, dis);
						float c = one_point_search(p1, *(zinters + iz), xright, yright, dis);
						outfile << xleft << " " << ymid << " " << (*(zinters + iz)).right << " ";//x1
						outfile << xright << " " << ymid << " " << (*(zinters + iz)).right << " ";//x3
						outfile << xleft << " " << yright << " " << a << "\n";
						outfile << xright << " " << ymid << " " << (*(zinters + iz)).right << " ";//x3
						outfile << xright << " " << yright << " " << c << " ";
						outfile << xleft << " " << yright << " " << a << "\n";
					}
				}

				else if (lll * llr < 0) {
					float a = one_point_search(p1, *(zinters + iz), xleft, yright, dis);
					float b = one_point_search(p1, *(zinters + iz), xright, yleft, dis);
					float c = one_point_search(p1, *(zinters + iz), xright, yright, dis);
					float d = one_point_search(p1, *(zinters + iz), xleft, yleft, dis);
					outfile << xright << " " << yright << " " << c << " ";
					outfile << xleft << " " << yleft << " " << d << " ";
					outfile << xleft << " " << yright << " " << a << "\n";
					outfile << xright << " " << yright << " " << c << " ";
					outfile << xleft << " " << yleft << " " << d << " ";
					outfile << xright << " " << yleft << " " << b << "\n";
				}

				else {
					Interval a = two_point_search(p1, *(zinters + iz), xleft, yright, dis);
					Interval b = two_point_search(p1, *(zinters + iz), xright, yleft, dis);
					Interval c = two_point_search(p1, *(zinters + iz), xright, yright, dis);
					Interval d = two_point_search(p1, *(zinters + iz), xleft, yleft, dis);
					if (a.len() > 0 && b.len() > 0 && c.len() > 0 && d.len() > 0) {
						outfile << xright << " " << yright << " " << c.left << " ";
						outfile << xleft << " " << yleft << " " << d.left << " ";
						outfile << xleft << " " << yright << " " << a.left << "\n";
						outfile << xright << " " << yright << " " << c.left << " ";
						outfile << xleft << " " << yleft << " " << d.left << " ";
						outfile << xright << " " << yleft << " " << b.left << "\n";
						outfile << xright << " " << yright << " " << c.right << " ";
						outfile << xleft << " " << yleft << " " << d.right << " ";
						outfile << xleft << " " << yright << " " << a.right << "\n";
						outfile << xright << " " << yright << " " << c.right << " ";
						outfile << xleft << " " << yleft << " " << d.right << " ";
						outfile << xright << " " << yleft << " " << b.right << "\n";
					}
					else if (a.len() > 0 && b.len() > 0 && c.len() > 0) {
						outfile << xright << " " << yright << " " << c.left << " ";
						outfile << xleft << " " << yright << " " << a.left << " ";
						outfile << xright << " " << yleft << " " << b.left << "\n";
						outfile << xright << " " << yright << " " << c.right << " ";
						outfile << xleft << " " << yright << " " << a.right << " ";
						outfile << xright << " " << yleft << " " << b.right << "\n";
						outfile << xright << " " << yleft << " " << b.left << " ";
						outfile << xright << " " << yleft << " " << b.right << " ";
						outfile << xleft << " " << yright << " " << a.right << "\n";
						outfile << xleft << " " << yright << " " << a.left << " ";
						outfile << xleft << " " << yright << " " << a.right << " ";
						outfile << xright << " " << yleft << " " << b.left << "\n";
					}
					else if (a.len() > 0 && b.len() > 0 && d.len() > 0) {
						outfile << xleft << " " << yleft << " " << d.left << " ";
						outfile << xleft << " " << yright << " " << a.left << " ";
						outfile << xright << " " << yleft << " " << b.left << "\n";
						outfile << xleft << " " << yleft << " " << d.right << " ";
						outfile << xleft << " " << yright << " " << a.right << " ";
						outfile << xright << " " << yleft << " " << b.right << "\n";
						outfile << xright << " " << yleft << " " << b.left << " ";
						outfile << xright << " " << yleft << " " << b.right << " ";
						outfile << xleft << " " << yright << " " << a.right << "\n";
						outfile << xleft << " " << yright << " " << a.left << " ";
						outfile << xleft << " " << yright << " " << a.right << " ";
						outfile << xright << " " << yleft << " " << b.left << "\n";
					}
					else if (a.len() > 0 && c.len() > 0 && d.len() > 0) {
						outfile << xleft << " " << yleft << " " << d.left << " ";
						outfile << xleft << " " << yright << " " << a.left << " ";
						outfile << xright << " " << yright << " " << c.left << "\n";
						outfile << xleft << " " << yleft << " " << d.right << " ";
						outfile << xleft << " " << yright << " " << a.right << " ";
						outfile << xright << " " << yright << " " << c.right << "\n";
						outfile << xleft << " " << yleft << " " << d.left << " ";
						outfile << xleft << " " << yleft << " " << d.right << " ";
						outfile << xright << " " << yright << " " << c.left << "\n";
						outfile << xright << " " << yright << " " << c.left << " ";
						outfile << xright << " " << yright << " " << c.right << " ";
						outfile << xleft << " " << yleft << " " << d.right << "\n";
					}
					else if (b.len() > 0 && c.len() > 0 && d.len() > 0) {
						outfile << xleft << " " << yleft << " " << d.left << " ";
						outfile << xright << " " << yleft << " " << b.left << " ";
						outfile << xright << " " << yright << " " << c.left << "\n";
						outfile << xleft << " " << yleft << " " << d.right << " ";
						outfile << xright << " " << yleft << " " << b.right << " ";
						outfile << xright << " " << yright << " " << c.right << "\n";
						outfile << xleft << " " << yleft << " " << d.left << " ";
						outfile << xleft << " " << yleft << " " << d.right << " ";
						outfile << xright << " " << yright << " " << c.left << "\n";
						outfile << xright << " " << yright << " " << c.left << " ";
						outfile << xright << " " << yright << " " << c.right << " ";
						outfile << xleft << " " << yleft << " " << d.right << "\n";
					}
					else if (a.len() > 0 && c.len() > 0) {
						outfile << xright << " " << yright << " " << c.left << " ";
						outfile << xright << " " << yright << " " << c.right << " ";
						outfile << xleft << " " << yright << " " << a.left << "\n";
						outfile << xleft << " " << yright << " " << a.left << " ";
						outfile << xleft << " " << yright << " " << a.right << " ";
						outfile << xright << " " << yright << " " << c.right << "\n";
					}
					else if (a.len() > 0 && d.len() > 0) {
						outfile << xleft << " " << yleft << " " << d.left << " ";
						outfile << xleft << " " << yleft << " " << d.right << " ";
						outfile << xleft << " " << yright << " " << a.left << "\n";
						outfile << xleft << " " << yright << " " << a.left << " ";
						outfile << xleft << " " << yright << " " << a.right << " ";
						outfile << xleft << " " << yleft << " " << d.right << "\n";
					}

					else if (b.len() > 0 && c.len() > 0) {
						outfile << xright << " " << yright << " " << c.left << " ";
						outfile << xright << " " << yright << " " << c.right << " ";
						outfile << xright << " " << yleft << " " << b.left << "\n";
						outfile << xright << " " << yleft << " " << b.left << " ";
						outfile << xright << " " << yleft << " " << b.right << " ";
						outfile << xright << " " << yright << " " << c.right << "\n";
					}
					else if (b.len() > 0 && d.len() > 0) {
						outfile << xleft << " " << yleft << " " << d.left << " ";
						outfile << xleft << " " << yleft << " " << d.right << " ";
						outfile << xright << " " << yleft << " " << b.left << "\n";
						outfile << xright << " " << yleft << " " << b.left << " ";
						outfile << xright << " " << yleft << " " << b.right << " ";
						outfile << xleft << " " << yleft << " " << d.right << "\n";
					}
				}
				iz = iz + 1;
			}
		}
	}
	outfile.close();
}

//void judgebox(Box)




//void histest(Polynomial3 p,Box)





void runtimemine() {
	Polynomial3 p1;
	p1.NewTerm(1, 4, 0, 0);
	p1.NewTerm(-5, 2, 0, 0);
	p1.NewTerm(1, 0, 4, 0);
	p1.NewTerm(-5, 0, 2, 0);
	p1.NewTerm(1, 0, 0, 4);
	p1.NewTerm(-5, 0, 0, 2);
	p1.NewTerm(10, 0, 0, 0);
	Polynomial3 px = p1.diffx();
	Polynomial3 py = p1.diffy();
	Polynomial3 pz = p1.diffy();
	float x1 = -3;
	float x2 = 3;
	float y1 = -3;
	float y2 = 3;
	float z1 = -3;
	float z2 = 3;
	float xlen = x2 - x1;
	float ylen = y2 - y1;
	float zlen = z2 - z1;
	Interval x(x1, x2);
	Interval y(y1, y2);
	Interval z(z1, z2);
	Cube b(x, y, z);
	float epsilon = 0.1;
	float xspace = epsilon;
	float yspace = epsilon;
	int xnumber = int(xlen / xspace);
	int ynumber = int(ylen / xspace);
	ofstream outfile("textnew1.txt", ios::out);
	int iz;
	for (int ix = 0; ix < xnumber; ix++) {
		for (int iy = 0; iy < ynumber; iy++) {
			float xleft = x1 + ix * xspace;
			float xright = x1 + (ix + 1) * xspace;
			float yleft = y1 + iy * yspace;
			float yright = y1 + (iy + 1) * yspace;
			float xmid = (xleft + xright) / 2;
			float ymid = (yleft + yright) / 2;
			Interval xs(xleft, xright);
			Interval ys(yleft, yright);
			Cube cube1(xs, ys, z);
			Interval* zinters = root_y(p1, cube1, 0.05, 0.01);
			iz = 0;
			while ((*(zinters + iz)).len() > 0) {
				float lll = p1.Eval(xleft, y.left, (*(zinters + iz)).left);
				float llr = p1.Eval(xleft, y.left, (*(zinters + iz)).right);
				float lrl = p1.Eval(xleft, y.right, (*(zinters + iz)).left);
				float lrr = p1.Eval(xleft, y.right, (*(zinters + iz)).right);
				float rll = p1.Eval(xright, y.left, (*(zinters + iz)).left);
				float rlr = p1.Eval(xright, y.left, (*(zinters + iz)).right);
				float rrl = p1.Eval(xright, y.right, (*(zinters + iz)).left);
				float rrr = p1.Eval(xright, y.right, (*(zinters + iz)).right);
				float dis = 0.01;
				if (lll * lrl < 0 && lll * rll < 0) {
					if (lll * llr < 0) {
						float d = one_point_search(p1, *(zinters + iz), xleft, yleft, dis);
						outfile << xmid << " " << yleft << " " << (*(zinters + iz)).left << " ";//x4
						outfile << xleft << " " << ymid << " " << (*(zinters + iz)).left << " ";//x1
						outfile << xleft << " " << yleft << " " << d << "\n";
					}
					else {
						float a = one_point_search(p1, *(zinters + iz), xleft, yright, dis);
						float b = one_point_search(p1, *(zinters + iz), xright, yleft, dis);
						float c = one_point_search(p1, *(zinters + iz), xright, yright, dis);
						outfile << xmid << " " << yleft << " " << (*(zinters + iz)).left << " ";
						outfile << xright << " " << yleft << " " << b << " ";
						outfile << xright << " " << yright << " " << c << "\n";
						outfile << xleft << " " << ymid << " " << (*(zinters + iz)).left << " ";
						outfile << xleft << " " << yright << " " << a << " ";
						outfile << xright << " " << yright << " " << c << "\n";
						outfile << xmid << " " << yleft << " " << (*(zinters + iz)).left << " ";
						outfile << xleft << " " << ymid << " " << (*(zinters + iz)).left << " ";
						outfile << xright << " " << yright << " " << c << "\n";
					}
				}

				else if (lll * lrl < 0 && lrl * rrl < 0) {
					if (lrl * lrr < 0) {
						float a = one_point_search(p1, *(zinters + iz), xleft, yright, dis);
						outfile << xleft << " " << ymid << " " << (*(zinters + iz)).left << " ";//x1
						outfile << xmid << " " << yright << " " << (*(zinters + iz)).left << " ";//x2
						outfile << xleft << " " << yright << " " << a << "\n";
					}
					else {
						float b = one_point_search(p1, *(zinters + iz), xright, yleft, dis);
						float c = one_point_search(p1, *(zinters + iz), xright, yright, dis);
						float d = one_point_search(p1, *(zinters + iz), xleft, yleft, dis);
						outfile << xleft << " " << ymid << " " << (*(zinters + iz)).left << " ";//x1
						outfile << xleft << " " << yleft << " " << d << " ";
						outfile << xright << " " << yleft << " " << b << "\n";
						outfile << xmid << " " << yright << " " << (*(zinters + iz)).left << " ";//x2
						outfile << xright << " " << yright << " " << c << " ";
						outfile << xright << " " << yleft << " " << b << "\n";
						outfile << xleft << " " << ymid << " " << (*(zinters + iz)).left << " ";//x1
						outfile << xmid << " " << yright << " " << (*(zinters + iz)).left << " ";//x2
						outfile << xright << " " << yleft << " " << b << "\n";
					}
				}


				else if (lll * rll < 0 && rll * rrl < 0) {
					if (rll * rlr < 0) {
						float b = one_point_search(p1, *(zinters + iz), xright, yleft, dis);
						outfile << xmid << " " << yleft << " " << (*(zinters + iz)).left << " ";//x4
						outfile << xright << " " << ymid << " " << (*(zinters + iz)).left << " ";//x3
						outfile << xright << " " << yleft << " " << b << "\n";
					}
					else {
						float a = one_point_search(p1, *(zinters + iz), xleft, yright, dis);
						float c = one_point_search(p1, *(zinters + iz), xright, yright, dis);
						float d = one_point_search(p1, *(zinters + iz), xleft, yleft, dis);
						outfile << xright << " " << ymid << " " << (*(zinters + iz)).left << " ";//x3
						outfile << xright << " " << yright << " " << c << " ";
						outfile << xleft << " " << yright << " " << a << "\n";
						outfile << xmid << " " << yleft << " " << (*(zinters + iz)).left << " ";//x4
						outfile << xleft << " " << yleft << " " << d << " ";
						outfile << xleft << " " << yright << " " << a << "\n";
						outfile << xmid << " " << yleft << " " << (*(zinters + iz)).left << " ";//x4
						outfile << xright << " " << ymid << " " << (*(zinters + iz)).left << " ";//x3
						outfile << xleft << " " << yright << " " << a << "\n";
					}
				}

				else if (rrl * rll < 0 && rrl * lrl < 0) {
					if (rrl * rrr < 0) {
						float c = one_point_search(p1, *(zinters + iz), xright, yright, dis);
						outfile << xmid << " " << yright << " " << (*(zinters + iz)).left << " ";//x2
						outfile << xright << " " << ymid << " " << (*(zinters + iz)).left << " ";//x3
						outfile << xright << " " << yright << " " << c << "\n";
					}
					else {
						float a = one_point_search(p1, *(zinters + iz), xleft, yright, dis);
						float b = one_point_search(p1, *(zinters + iz), xright, yleft, dis);
						float d = one_point_search(p1, *(zinters + iz), xleft, yleft, dis);
						outfile << xmid << " " << yright << " " << (*(zinters + iz)).left << " ";//x2
						outfile << xleft << " " << yright << " " << a << " ";
						outfile << xleft << " " << yleft << " " << d << "\n";
						outfile << xright << " " << ymid << " " << (*(zinters + iz)).left << " ";//x3
						outfile << xright << " " << yleft << " " << b << " ";
						outfile << xleft << " " << yleft << " " << d << "\n";
						outfile << xmid << " " << yright << " " << (*(zinters + iz)).left << " ";//x2
						outfile << xright << " " << ymid << " " << (*(zinters + iz)).left << " ";//x3
						outfile << xleft << " " << yleft << " " << d << "\n";
					}
				}


				else if (lll * rll < 0 && lrl * rrl < 0) {
					if (lll * llr < 0) {
						float a = one_point_search(p1, *(zinters + iz), xleft, yright, dis);
						float d = one_point_search(p1, *(zinters + iz), xleft, yleft, dis);
						outfile << xmid << " " << yright << " " << (*(zinters + iz)).left << " ";//x2
						outfile << xmid << " " << yleft << " " << (*(zinters + iz)).left << " ";//x4
						outfile << xleft << " " << yleft << " " << d << "\n";
						outfile << xmid << " " << yright << " " << (*(zinters + iz)).left << " ";//x2
						outfile << xleft << " " << yright << " " << a << " ";
						outfile << xleft << " " << yleft << " " << d << "\n";
					}
					else {
						float b = one_point_search(p1, *(zinters + iz), xright, yleft, dis);
						float c = one_point_search(p1, *(zinters + iz), xright, yright, dis);
						outfile << xmid << " " << yright << " " << (*(zinters + iz)).left << " ";//x2
						outfile << xmid << " " << yleft << " " << (*(zinters + iz)).left << " ";//x4
						outfile << xright << " " << yleft << " " << b << "\n";
						outfile << xmid << " " << yright << " " << (*(zinters + iz)).left << " ";//x2
						outfile << xright << " " << yright << " " << c << " ";
						outfile << xright << " " << yleft << " " << b << "\n";
					}
				}


				else if (lll * lrl < 0 && rll * rrl < 0) {
					if (lll * llr < 0) {
						float b = one_point_search(p1, *(zinters + iz), xright, yleft, dis);
						float d = one_point_search(p1, *(zinters + iz), xleft, yleft, dis);
						outfile << xleft << " " << ymid << " " << (*(zinters + iz)).left << " ";//x1
						outfile << xright << " " << ymid << " " << (*(zinters + iz)).left << " ";//x3
						outfile << xleft << " " << yleft << " " << d << "\n";
						outfile << xright << " " << ymid << " " << (*(zinters + iz)).left << " ";//x3
						outfile << xright << " " << yleft << " " << b << " ";
						outfile << xleft << " " << yleft << " " << d << "\n";
					}
					else {
						float a = one_point_search(p1, *(zinters + iz), xleft, yright, dis);
						float c = one_point_search(p1, *(zinters + iz), xright, yright, dis);
						outfile << xleft << " " << ymid << " " << (*(zinters + iz)).left << " ";//x1
						outfile << xright << " " << ymid << " " << (*(zinters + iz)).left << " ";//x3
						outfile << xleft << " " << yright << " " << a << "\n";
						outfile << xright << " " << ymid << " " << (*(zinters + iz)).left << " ";//x3
						outfile << xright << " " << yright << " " << c << " ";
						outfile << xleft << " " << yright << " " << a << "\n";
					}
				}

				else if (llr * lrr < 0 && llr * rlr < 0) {
					if (lll * llr < 0) {
						float d = one_point_search(p1, *(zinters + iz), xleft, yleft, dis);
						outfile << xmid << " " << yleft << " " << (*(zinters + iz)).right << " ";//x4
						outfile << xleft << " " << ymid << " " << (*(zinters + iz)).right << " ";//x1
						outfile << xleft << " " << yleft << " " << d << "\n";
					}
					else {
						float a = one_point_search(p1, *(zinters + iz), xleft, yright, dis);
						float b = one_point_search(p1, *(zinters + iz), xright, yleft, dis);
						float c = one_point_search(p1, *(zinters + iz), xright, yright, dis);
						outfile << xmid << " " << yleft << " " << (*(zinters + iz)).right << " ";
						outfile << xright << " " << yleft << " " << b << " ";
						outfile << xright << " " << yright << " " << c << "\n";
						outfile << xleft << " " << ymid << " " << (*(zinters + iz)).right << " ";
						outfile << xleft << " " << yright << " " << a << " ";
						outfile << xright << " " << yright << " " << c << "\n";
						outfile << xmid << " " << yleft << " " << (*(zinters + iz)).right << " ";
						outfile << xleft << " " << ymid << " " << (*(zinters + iz)).right << " ";
						outfile << xright << " " << yright << " " << c << "\n";
					}
				}

				else if (llr * lrr < 0 && lrr * rrr < 0) {
					if (lrl * lrr < 0) {
						float a = one_point_search(p1, *(zinters + iz), xleft, yright, dis);
						outfile << xleft << " " << ymid << " " << (*(zinters + iz)).right << " ";//x1
						outfile << xmid << " " << yright << " " << (*(zinters + iz)).right << " ";//x2
						outfile << xleft << " " << yright << " " << a << "\n";
					}
					else {
						float b = one_point_search(p1, *(zinters + iz), xright, yleft, dis);
						float c = one_point_search(p1, *(zinters + iz), xright, yright, dis);
						float d = one_point_search(p1, *(zinters + iz), xleft, yleft, dis);
						outfile << xleft << " " << ymid << " " << (*(zinters + iz)).right << " ";//x1
						outfile << xleft << " " << yleft << " " << d << " ";
						outfile << xright << " " << yleft << " " << b << "\n";
						outfile << xmid << " " << yright << " " << (*(zinters + iz)).right << " ";//x2
						outfile << xright << " " << yright << " " << c << " ";
						outfile << xright << " " << yleft << " " << b << "\n";
						outfile << xleft << " " << ymid << " " << (*(zinters + iz)).right << " ";//x1
						outfile << xmid << " " << yright << " " << (*(zinters + iz)).right << " ";//x2
						outfile << xright << " " << yleft << " " << b << "\n";
					}
				}


				else if (llr * rlr < 0 && rlr * rrr < 0) {
					if (rll * rlr < 0) {
						float b = one_point_search(p1, *(zinters + iz), xright, yleft, dis);
						outfile << xmid << " " << yleft << " " << (*(zinters + iz)).right << " ";//x4
						outfile << xright << " " << ymid << " " << (*(zinters + iz)).right << " ";//x3
						outfile << xright << " " << yleft << " " << b << "\n";
					}
					else {
						float a = one_point_search(p1, *(zinters + iz), xleft, yright, dis);
						float c = one_point_search(p1, *(zinters + iz), xright, yright, dis);
						float d = one_point_search(p1, *(zinters + iz), xleft, yleft, dis);
						outfile << xright << " " << ymid << " " << (*(zinters + iz)).right << " ";//x3
						outfile << xright << " " << yright << " " << c << " ";
						outfile << xleft << " " << yright << " " << a << "\n";
						outfile << xmid << " " << yleft << " " << (*(zinters + iz)).right << " ";//x4
						outfile << xleft << " " << yleft << " " << d << " ";
						outfile << xleft << " " << yright << " " << a << "\n";
						outfile << xmid << " " << yleft << " " << (*(zinters + iz)).right << " ";//x4
						outfile << xright << " " << ymid << " " << (*(zinters + iz)).right << " ";//x3
						outfile << xleft << " " << yright << " " << a << "\n";
					}
				}

				else if (rrr * rlr < 0 && rrr * lrr < 0) {
					if (rrl * rrr < 0) {
						float c = one_point_search(p1, *(zinters + iz), xright, yright, dis);
						outfile << xmid << " " << yright << " " << (*(zinters + iz)).right << " ";//x2
						outfile << xright << " " << ymid << " " << (*(zinters + iz)).right << " ";//x3
						outfile << xright << " " << yright << " " << c << "\n";
					}
					else {
						float a = one_point_search(p1, *(zinters + iz), xleft, yright, dis);
						float b = one_point_search(p1, *(zinters + iz), xright, yleft, dis);
						float d = one_point_search(p1, *(zinters + iz), xleft, yleft, dis);
						outfile << xmid << " " << yright << " " << (*(zinters + iz)).right << " ";//x2
						outfile << xleft << " " << yright << " " << a << " ";
						outfile << xleft << " " << yleft << " " << d << "\n";
						outfile << xright << " " << ymid << " " << (*(zinters + iz)).right << " ";//x3
						outfile << xright << " " << yleft << " " << b << " ";
						outfile << xleft << " " << yleft << " " << d << "\n";
						outfile << xmid << " " << yright << " " << (*(zinters + iz)).right << " ";//x2
						outfile << xright << " " << ymid << " " << (*(zinters + iz)).right << " ";//x3
						outfile << xleft << " " << yleft << " " << d << "\n";
					}
				}


				else if (llr * rlr < 0 && lrr * rrr < 0) {
					if (lll * llr < 0) {
						float a = one_point_search(p1, *(zinters + iz), xleft, yright, dis);
						float d = one_point_search(p1, *(zinters + iz), xleft, yleft, dis);
						outfile << xmid << " " << yright << " " << (*(zinters + iz)).right << " ";//x2
						outfile << xmid << " " << yleft << " " << (*(zinters + iz)).right << " ";//x4
						outfile << xleft << " " << yleft << " " << d << "\n";
						outfile << xmid << " " << yright << " " << (*(zinters + iz)).right << " ";//x2
						outfile << xleft << " " << yright << " " << a << " ";
						outfile << xleft << " " << yleft << " " << d << "\n";
					}
					else {
						float b = one_point_search(p1, *(zinters + iz), xright, yleft, dis);
						float c = one_point_search(p1, *(zinters + iz), xright, yright, dis);
						outfile << xmid << " " << yright << " " << (*(zinters + iz)).right << " ";//x2
						outfile << xmid << " " << yleft << " " << (*(zinters + iz)).right << " ";//x4
						outfile << xright << " " << yleft << " " << b << "\n";
						outfile << xmid << " " << yright << " " << (*(zinters + iz)).right << " ";//x2
						outfile << xright << " " << yright << " " << c << " ";
						outfile << xright << " " << yleft << " " << b << "\n";
					}
				}


				else if (llr * lrr < 0 && rlr * rrr < 0) {
					if (lll * llr < 0) {
						float b = one_point_search(p1, *(zinters + iz), xright, yleft, dis);
						float d = one_point_search(p1, *(zinters + iz), xleft, yleft, dis);
						outfile << xleft << " " << ymid << " " << (*(zinters + iz)).right << " ";//x1
						outfile << xright << " " << ymid << " " << (*(zinters + iz)).right << " ";//x3
						outfile << xleft << " " << yleft << " " << d << "\n";
						outfile << xright << " " << ymid << " " << (*(zinters + iz)).right << " ";//x3
						outfile << xright << " " << yleft << " " << b << " ";
						outfile << xleft << " " << yleft << " " << d << "\n";
					}
					else {
						float a = one_point_search(p1, *(zinters + iz), xleft, yright, dis);
						float c = one_point_search(p1, *(zinters + iz), xright, yright, dis);
						outfile << xleft << " " << ymid << " " << (*(zinters + iz)).right << " ";//x1
						outfile << xright << " " << ymid << " " << (*(zinters + iz)).right << " ";//x3
						outfile << xleft << " " << yright << " " << a << "\n";
						outfile << xright << " " << ymid << " " << (*(zinters + iz)).right << " ";//x3
						outfile << xright << " " << yright << " " << c << " ";
						outfile << xleft << " " << yright << " " << a << "\n";
					}
				}

				else if (lll * llr < 0) {
					float a = one_point_search(p1, *(zinters + iz), xleft, yright, dis);
					float b = one_point_search(p1, *(zinters + iz), xright, yleft, dis);
					float c = one_point_search(p1, *(zinters + iz), xright, yright, dis);
					float d = one_point_search(p1, *(zinters + iz), xleft, yleft, dis);
					outfile << xright << " " << yright << " " << c << " ";
					outfile << xleft << " " << yleft << " " << d << " ";
					outfile << xleft << " " << yright << " " << a << "\n";
					outfile << xright << " " << yright << " " << c << " ";
					outfile << xleft << " " << yleft << " " << d << " ";
					outfile << xright << " " << yleft << " " << b << "\n";
				}

				else {
					Interval a = two_point_search(p1, *(zinters + iz), xleft, yright, dis);
					Interval b = two_point_search(p1, *(zinters + iz), xright, yleft, dis);
					Interval c = two_point_search(p1, *(zinters + iz), xright, yright, dis);
					Interval d = two_point_search(p1, *(zinters + iz), xleft, yleft, dis);
					if (a.len() > 0 && b.len() > 0 && c.len() > 0 && d.len() > 0) {
						outfile << xright << " " << yright << " " << c.left << " ";
						outfile << xleft << " " << yleft << " " << d.left << " ";
						outfile << xleft << " " << yright << " " << a.left << "\n";
						outfile << xright << " " << yright << " " << c.left << " ";
						outfile << xleft << " " << yleft << " " << d.left << " ";
						outfile << xright << " " << yleft << " " << b.left << "\n";
						outfile << xright << " " << yright << " " << c.right << " ";
						outfile << xleft << " " << yleft << " " << d.right << " ";
						outfile << xleft << " " << yright << " " << a.right << "\n";
						outfile << xright << " " << yright << " " << c.right << " ";
						outfile << xleft << " " << yleft << " " << d.right << " ";
						outfile << xright << " " << yleft << " " << b.right << "\n";
					}
					else if (a.len() > 0 && b.len() > 0 && c.len() > 0) {
						outfile << xright << " " << yright << " " << c.left << " ";
						outfile << xleft << " " << yright << " " << a.left << " ";
						outfile << xright << " " << yleft << " " << b.left << "\n";
						outfile << xright << " " << yright << " " << c.right << " ";
						outfile << xleft << " " << yright << " " << a.right << " ";
						outfile << xright << " " << yleft << " " << b.right << "\n";
						outfile << xright << " " << yleft << " " << b.left << " ";
						outfile << xright << " " << yleft << " " << b.right << " ";
						outfile << xleft << " " << yright << " " << a.right << "\n";
						outfile << xleft << " " << yright << " " << a.left << " ";
						outfile << xleft << " " << yright << " " << a.right << " ";
						outfile << xright << " " << yleft << " " << b.left << "\n";
					}
					else if (a.len() > 0 && b.len() > 0 && d.len() > 0) {
						outfile << xleft << " " << yleft << " " << d.left << " ";
						outfile << xleft << " " << yright << " " << a.left << " ";
						outfile << xright << " " << yleft << " " << b.left << "\n";
						outfile << xleft << " " << yleft << " " << d.right << " ";
						outfile << xleft << " " << yright << " " << a.right << " ";
						outfile << xright << " " << yleft << " " << b.right << "\n";
						outfile << xright << " " << yleft << " " << b.left << " ";
						outfile << xright << " " << yleft << " " << b.right << " ";
						outfile << xleft << " " << yright << " " << a.right << "\n";
						outfile << xleft << " " << yright << " " << a.left << " ";
						outfile << xleft << " " << yright << " " << a.right << " ";
						outfile << xright << " " << yleft << " " << b.left << "\n";
					}
					else if (a.len() > 0 && c.len() > 0 && d.len() > 0) {
						outfile << xleft << " " << yleft << " " << d.left << " ";
						outfile << xleft << " " << yright << " " << a.left << " ";
						outfile << xright << " " << yright << " " << c.left << "\n";
						outfile << xleft << " " << yleft << " " << d.right << " ";
						outfile << xleft << " " << yright << " " << a.right << " ";
						outfile << xright << " " << yright << " " << c.right << "\n";
						outfile << xleft << " " << yleft << " " << d.left << " ";
						outfile << xleft << " " << yleft << " " << d.right << " ";
						outfile << xright << " " << yright << " " << c.left << "\n";
						outfile << xright << " " << yright << " " << c.left << " ";
						outfile << xright << " " << yright << " " << c.right << " ";
						outfile << xleft << " " << yleft << " " << d.right << "\n";
					}
					else if (b.len() > 0 && c.len() > 0 && d.len() > 0) {
						outfile << xleft << " " << yleft << " " << d.left << " ";
						outfile << xright << " " << yleft << " " << b.left << " ";
						outfile << xright << " " << yright << " " << c.left << "\n";
						outfile << xleft << " " << yleft << " " << d.right << " ";
						outfile << xright << " " << yleft << " " << b.right << " ";
						outfile << xright << " " << yright << " " << c.right << "\n";
						outfile << xleft << " " << yleft << " " << d.left << " ";
						outfile << xleft << " " << yleft << " " << d.right << " ";
						outfile << xright << " " << yright << " " << c.left << "\n";
						outfile << xright << " " << yright << " " << c.left << " ";
						outfile << xright << " " << yright << " " << c.right << " ";
						outfile << xleft << " " << yleft << " " << d.right << "\n";
					}
					else if (a.len() > 0 && c.len() > 0) {
						outfile << xright << " " << yright << " " << c.left << " ";
						outfile << xright << " " << yright << " " << c.right << " ";
						outfile << xleft << " " << yright << " " << a.left << "\n";
						outfile << xleft << " " << yright << " " << a.left << " ";
						outfile << xleft << " " << yright << " " << a.right << " ";
						outfile << xright << " " << yright << " " << c.right << "\n";
					}
					else if (a.len() > 0 && d.len() > 0) {
						outfile << xleft << " " << yleft << " " << d.left << " ";
						outfile << xleft << " " << yleft << " " << d.right << " ";
						outfile << xleft << " " << yright << " " << a.left << "\n";
						outfile << xleft << " " << yright << " " << a.left << " ";
						outfile << xleft << " " << yright << " " << a.right << " ";
						outfile << xleft << " " << yleft << " " << d.right << "\n";
					}

					else if (b.len() > 0 && c.len() > 0) {
						outfile << xright << " " << yright << " " << c.left << " ";
						outfile << xright << " " << yright << " " << c.right << " ";
						outfile << xright << " " << yleft << " " << b.left << "\n";
						outfile << xright << " " << yleft << " " << b.left << " ";
						outfile << xright << " " << yleft << " " << b.right << " ";
						outfile << xright << " " << yright << " " << c.right << "\n";
					}
					else if (b.len() > 0 && d.len() > 0) {
						outfile << xleft << " " << yleft << " " << d.left << " ";
						outfile << xleft << " " << yleft << " " << d.right << " ";
						outfile << xright << " " << yleft << " " << b.left << "\n";
						outfile << xright << " " << yleft << " " << b.left << " ";
						outfile << xright << " " << yleft << " " << b.right << " ";
						outfile << xleft << " " << yleft << " " << d.right << "\n";
					}
				}
				iz = iz + 1;
			}
		}
	}
	outfile.close();
}




void slovepv(Polynomial3 p, Cube b, float epsilon, float delta, ofstream* outfile) {
	if (b.diameter() > epsilon) {
		slovepv(p, b.lll(), epsilon, delta, outfile);
		slovepv(p, b.llr(), epsilon, delta, outfile);
		slovepv(p, b.lrl(), epsilon, delta, outfile);
		slovepv(p, b.lrr(), epsilon, delta, outfile);
		slovepv(p, b.rll(), epsilon, delta, outfile);
		slovepv(p, b.rlr(), epsilon, delta, outfile);
		slovepv(p, b.rrl(), epsilon, delta, outfile);
		slovepv(p, b.rrr(), epsilon, delta, outfile);
	}
	else if (b.diameter() > delta) {
		Interval px = intpoly(p.diffx(), b);
		Interval py = intpoly(p.diffy(), b);
		Interval pz = intpoly(p.diffz(), b);
		if (!(0 << px * px + py * py + pz * pz)) {
			;
		}
		else {
			slovepv(p, b.lll(), epsilon, delta, outfile);
			slovepv(p, b.llr(), epsilon, delta, outfile);
			slovepv(p, b.lrl(), epsilon, delta, outfile);
			slovepv(p, b.lrr(), epsilon, delta, outfile);
			slovepv(p, b.rll(), epsilon, delta, outfile);
			slovepv(p, b.rlr(), epsilon, delta, outfile);
			slovepv(p, b.rrl(), epsilon, delta, outfile);
			slovepv(p, b.rrr(), epsilon, delta, outfile);
		}
	}
}




void runtimehis() {
	Polynomial3 p1;
	p1.NewTerm(-17, 17, 3, 1);
	p1.NewTerm(-75, 5, 10, 6);
	p1.NewTerm(-10, 0, 8, 13);
	p1.NewTerm(-7, 0, 6, 15);
	p1.NewTerm(71, 13, 2, 5);
	p1.NewTerm(-44, 0, 5, 13);
	p1.NewTerm(-82, 8, 0, 8);
	p1.NewTerm(80, 0, 14, 2);
	p1.NewTerm(62, 4, 7, 4);
	p1.NewTerm(-10, 7, 1, 3);
	p1.NewTerm(-83, 2, 4, 3);
	p1.NewTerm(-4, 2, 5, 0);
	p1.NewTerm(-73, 1, 1, 0);
	p1.NewTerm(1, 0, 0, 0);
	Polynomial3 px = p1.diffx();
	Polynomial3 py = p1.diffy();
	Polynomial3 pz = p1.diffy();
	float x1 = -3;
	float x2 = 3;
	float y1 = -3;
	float y2 = 3;
	float z1 = -3;
	float z2 = 3;
	float xlen = x2 - x1;
	float ylen = y2 - y1;
	float zlen = z2 - z1;
	Interval x(x1, x2);
	Interval y(y1, y2);
	Interval z(z1, z2);
	Cube b(x, y, z);
	float epsilon = 0.1;
	ofstream outfile("runhis.txt", ios::out);
	ofstream* loc;
	loc = &outfile;
	slovepv(p1, b, epsilon, 0.05, loc);
	outfile.close();
}





int main() {
	clock_t start, end;
	start = clock();
	testf3d();
	//runtimehis();
	//testf3d2();
	end = clock();
	cout << "F1运行时间" << (double)(end - start) / CLOCKS_PER_SEC << endl;
	return 0;
}