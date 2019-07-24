// cppClass1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#include "CRectangle.h"

int main()
{
    std::cout << "Hello Class!\n";

	int w, h;
	CRectangle r;

	std::cin >> w >> h;

	r.Init(w, h);

	std::cout << r.Area() << std::endl << r.Perimeter();

	return 0;
}