//prevent multiple inclusions of head file
#ifndef MATH_FUNCTION_H
#define MATH_FUNCTION_H

#include <vector>        //the vector operator
#include <algorithm>
#include <limits>
#include <complex>
#include <iostream>

using std::vector;
using std::sort;
using std::numeric_limits;



#ifndef posInf
	#define posInf numeric_limits<double>::infinity()
#endif


#ifndef negInf
	#define negInf -numeric_limits<double>::infinity()
#endif




class math_fun{
public:
	//1. median function definition
	static double median_score(vector<double> scores);

	//2. find local maximum (x[i]>x[i-1] && x[i]>x[i+1]
	static bool localmax(double *x, bool* output, const size_t N);

	//3. Reverse a list (will modified the original list)
	static void reverse(double *const x, const size_t N);

	//4. Filter function (MATLAB version)
	static void filter(double const *b, const size_t Nb, double const *a, const size_t Na, double const *x, const size_t N, double *const y);

	//5. Partition/selection function (for in house median)
	static size_t partition(double *list, size_t left, size_t right, size_t pivotIndex);
	static double selection(double *const list, size_t left, size_t right, size_t k, const size_t maxRound);
	static double median(double *const list, size_t left, size_t right, const size_t maxRound);

	//6. Math function: decimal to fraction
	static vector<double> dec2frac(const double org_x, const double tol);

};



#endif