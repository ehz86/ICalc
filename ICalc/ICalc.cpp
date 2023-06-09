#include <iostream>
#include "Header1.h"
#include <string>


int main()
{
	pcalc calcc;
	parser p;
	std::string s;
	std::cout << "Write:";
	std::getline(std::cin, s);
	if (containsLetters(s)) {
		std::cout << "Error, Invalid Data" << std::endl;
		return 0;
	}
	if (!checkBrackets(s)) {
		std::cout << "Error, Invalid Data" << std::endl;
		return 0;
	}
	std::string res = p.IntoPost(s);
	std::cout << "Line after changes: " << res << "\n";
	int res2 = calcc.calc(res);
	std::cout << "Result: " << res2;
	return 0;

}
