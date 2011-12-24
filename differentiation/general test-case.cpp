/*
 *  Copyright (C) 2010,2011 Anogeianakis Vaptistis
 *
 *
 *  This file is part of ë&d++.
 *
 *  ë&d++ is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  ë&d++ is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with ë&d++.  If not, see <http://www.gnu.org/licenses/>.
 */


#include <iostream>
using std::cout;
using std::endl;

//#include <cstdlib>

#include "ënd++.h"


template<typename Func>
double Newton_Raphson(Func f,double new_x,double accuracy,unsigned int *iterations)
{
    double old_x;
    
    *iterations = 0;
    do
    {
		(*iterations)++;
		old_x = new_x;
		new_x = old_x-f(old_x)/Differentiate(f)(old_x);
	}
	while(fabs(new_x-old_x)>accuracy);
	return new_x;
}


int main()
{
	//Arg z;
	Arg x;
	double y;

	const double v1 = -2.5;
	const double v2 = 1.5;
	//auto f = 2*x;

	//std::cin >> y;
	//cout << Differentiate(f)(y) << endl;
	//cout << 1.0 << endl;

	auto f0 = -Const<int>(1);	// v
	cout << f0(v1) << endl;
	cout << -1 << endl;
	cout << Differentiate(f0)(v2) << endl;
	cout << 0 << endl << endl;
	auto f1 = x+3;	// v
	cout << f1(v1) << endl;
	cout << v1+3 << endl;
	cout << Differentiate(f1)(v2) << endl;
	cout << 1 << endl << endl;
	auto f2 = x-3;	// v
	cout << f2(v1) << endl;
	cout << v1-3 << endl;
	cout << Differentiate(f2)(v2) << endl;
	cout << 1 << endl << endl;
	auto f3 = -x;	// v
	cout << f3(v1) << endl;
	cout << -v1 << endl;
	cout << Differentiate(f3)(v2) << endl;
	cout << -1 << endl << endl;
	auto f4 = 3*x;	// v
	cout << f4(v1) << endl;
	cout << 3*v1 << endl;
	cout << Differentiate(f4)(v2) << endl;
	cout << 3 << endl << endl;
	auto f5 = 3/x;	// v
	cout << f5(v1) << endl;
	cout << 3/v1 << endl;
	cout << Differentiate(f5)(v2) << endl;
	cout << -3/(v2*v2) << endl << endl;
	auto f6 = sin(x);	// v
	cout << f6(v1) << endl;
	cout << sin(v1) << endl;
	cout << Differentiate(f6)(v2) << endl;
	cout << cos(v2) << endl << endl;
	auto f7 = cos(x);	// v
	cout << f7(v1) << endl;
	cout << cos(v1) << endl;
	cout << Differentiate(f7)(v2) << endl;
	cout << -sin(v2) << endl << endl;
	auto f8 = -cos(3*x);	// v
	cout << f8(v1) << endl;
	cout << -cos(3*v1) << endl;
	cout << Differentiate(f8)(v2) << endl;
	cout << 3*sin(3*v2) << endl << endl;
	auto f9 = 2-cos(3*x);	// v
	cout << f9(v1) << endl;
	cout << 2-cos(3*v1) << endl;
	cout << Differentiate(f9)(v2) << endl;
	cout << 3*sin(3*v2) << endl << endl;
	auto f10 = x-cos(3*x);	// v
	cout << f10(v1) << endl;
	cout << v1-cos(3*v1) << endl;
	cout << Differentiate(f10)(v2) << endl;
	cout << 1+3*sin(3*v2) << endl << endl;
	auto f11 = 2*x-cos(3*x);	// v
	cout << f11(v1) << endl;
	cout << 2*v1-cos(3*v1) << endl;
	cout << Differentiate(f11)(v2) << endl;
	cout << 2+3*sin(3*v2) << endl << endl;
	auto f12 = 2.2*x*x-cos(3*x);	// clang
	cout << f12(v1) << endl;
	cout << 2.2*v1*v1-cos(3*v1) << endl;
	cout << Differentiate(f12)(v2) << endl;
	cout << 4.4*v2+3*sin(3*v2) << endl << endl;
	auto f13 = cos(sin(x));	// v
	cout << f13(v1) << endl;
	cout << cos(sin(v1)) << endl;
	cout << Differentiate(f13)(v2) << endl;
	cout << -sin(sin(v2))*cos(v2) << endl << endl;
	auto f14 = cos(-sin(5*x*x+4*x-2.2)/3+-5-1/(x*x+2.5));	// ?
	cout << f14(v1) << endl;
	cout << cos(-sin(5*v1*v1+4*v1-2.2)/3+-5-1/(v1*v1+2.5)) << endl;
	cout << Differentiate(f14)(v2) << endl;
	cout << -sin(-sin(5*v2*v2+4*v2-2.2)/3+-5-1/(v2*v2+2.5))*(-cos(5*v2*v2+4*v2-2.2)*(10*v2+4)/3 + 2*v2/((v2*v2+2.5)*(v2*v2+2.5))) << endl << endl;
	auto f15 = 3*x*x*x*x + 2.5*x*x*x - 7*x*x - 2*x + 3.2;
	cout << f15(v1) << endl;
	cout << 3*v1*v1*v1*v1 + 2.5*v1*v1*v1 - 7*v1*v1 - 2*v1 + 3.2 << endl;
	cout << Differentiate(f15)(v2) << endl;
	cout << 12*v2*v2*v2 + 7.5*v2*v2 - 14*v2 - 2 << endl << endl;
	auto f16 = (3*x*x*x*x + 2.5*x*x*x - 7*x*x - 2*x + 3.2)/sin(x);
	cout << f16(v1) << endl;
	cout << (3*v1*v1*v1*v1 + 2.5*v1*v1*v1 - 7*v1*v1 - 2*v1 + 3.2)/sin(v1) << endl;
	cout << Differentiate(f16)(v2) << endl;
	cout << ((12*v2*v2*v2 + 7.5*v2*v2 - 14*v2 - 2)*sin(v2) - cos(v2)*(3*v2*v2*v2*v2 + 2.5*v2*v2*v2 - 7*v2*v2 - 2*v2 + 3.2))/(sin(v2)*sin(v2)) << endl << endl;
	//print(f);
	//cout << endl;

	unsigned int iterations = 0;
	cout << "**" << Newton_Raphson((x-3)*(x+2),2,1e-6,&iterations) << " after ";
	cout << iterations << endl;
	//cout << f(-2.5) << endl;
	//cout << Differentiate(f)(1.5) << endl;

	//{
	//	double z = 1.5;
	//	double x = 1.5;
	//	cout << "result = " << x+3 << endl;
	//}

	//system("pause");
	return 0;
} // end function main
