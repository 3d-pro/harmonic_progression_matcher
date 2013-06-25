/* Ver 0.9
=======================================================================================================================
The Beat tracker functions.
=======================================================================================================================
*/

#ifndef _BEAT_TRACKER_H_
#define _BEAT_TRACKER_H_
#define _USE_MATH_DEFINES

#include <math.h>
#include <iostream>
#include <limits>
#include "fftw3.h" //Need to use fft
#include <complex>     //Need to use fft
#include "vector_template.h"
#include "math_function.h"
#include "FE_package.h"
using std::complex;
using std::numeric_limits;

#ifndef posInf
	#define posInf numeric_limits<double>::infinity()
#endif


#ifndef negInf
	#define negInf -numeric_limits<double>::infinity()
#endif




class beat_tracker
{
public:
	static bool calculate_beat_strength(double const *signal, const int N, const int SR,const int win_len, const int hop_len,double *const beatStrength);
	static vector<double> beatestimate(double const *beatStrength, const int N, const int SR,const int hop_len);

};
#endif
