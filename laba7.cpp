#include <iostream>
#include <cassert>
#include "matrix.hpp"

using mtmath::Mat22d;
using mtmath::Mat33i;
using mtmath::Vec2d;



int main()
{
	setlocale(LC_ALL, "Russian");
	Mat33i A({ {
			 {1,1,1},
			 {1,1,1},
			 {9,11,-1},
		} });

	Mat33i B({ {
			 {-1,2,6},
			 {3,4,2},
			 {9,11,-1},
		} });
	cout << "Определитель матрицы А: " << endl;
	cout << A.determ() << endl;
	cout << "-----------------: " << endl;
	cout << "Обратная матрица А: " << endl;
	auto q = A.inv();
	cout << q << endl;
	cout << "-----------------: " << endl;
	cout << "Матрица А - B: " << endl;
	//cout << A - B << endl;
	cout << "-----------------: " << endl;
	cout << "Транспонировання матрица: " << endl;
	//cout << A.trans() << endl;
	//setlocale(LC_ALL, "Russian");

	system("pause");
	return 0;
}