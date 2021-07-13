#include <functional>
#include <iostream>
#include <cmath>

constexpr size_t MAX_ITR = 52; //default value for how many iterations to go through
constexpr double TOL = .01; //default value for the tolerance

double bisect(double x1, double x2, std::function<double (double)> f, double tol = TOL, size_t iters = MAX_ITR)
{
	if (x2 < x1)
		std::swap(x2, x1);
	double fx1 = f(x1), fx2 = f(x2); //we don't want to re-evaluate f(x) every time we refer to it
	std::cout << "f(" << x1 << ") = " << fx1 << std::endl << "f(" << x2 << ") = " << fx2 << std::endl;
	if (fx1 == 0) //Check if we have found the precise answer and can end early
		return x1;
	if (fx2 == 0)
		return x2;
	for (size_t i = 0; i < iters; ++i)
	{
		double x3 = x1 + (x2 - x1) / 2;
		double mid = f(x3);
		std::cout << "f(" << x3 << ") = " << mid << std::endl;
		if (mid == 0 || ((x2 - x1) / 2) < tol)
		{
			std::cout << std::endl;
			return x3;
		}
		(fx1 * mid > 0? x1: x2) = x3;// Re-assign either the top of our range or the bottom depending on whether we overshot or undershot. If fx1, or f(x1), has the same sign as mid, we want to assign x1. This way, whether f(x1) is actually the higher value or the lower doesn't matter. The importatn thing is to make sure our bounds have consistent signs. Since the sign of f(x1) will never change, we don't need to update the variable.
	}
	return NULL;
}

int main()
{
	auto f = [](double x) {return sqrt(x) - cos(x); };
	bisect(0, 1, f);
	auto g = [](double x) {return 3 * (x + 1) * (x - 1) * (x - 1); };
	bisect(-2, 1.5, g);
	bisect(-1.25, 2.5, g);
	auto h = [](double x) {return pow(x, 3) - 7 * pow(x, 2) + 14 * x - 6; };
	bisect(0, 1, h);
	bisect(1, 3.2, h);
	bisect(3.2, 4, h);
	auto k = [](double x) {return pow(x, 4) - 2 * pow(x, 3) - 4 * pow(x, 2) + 4 * x + 4; };
	bisect(-2, -1, k);
	bisect(0, 2, k);
	bisect(2, 3, k);
	bisect(-1, 0, k);
}