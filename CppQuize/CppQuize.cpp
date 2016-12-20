// CppQuize.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <limits>

// int _tmain(int argc, _TCHAR* argv[])
// {
// 	return 0;
// }

using namespace std;



int main() {
	int i = std::numeric_limits<int>::max();
	std::cout << ++i;
}
