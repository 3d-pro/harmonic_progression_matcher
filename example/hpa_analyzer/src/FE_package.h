/* Ver 0.9
=======================================================================================================================
The Feature extraction functions.
1. estimate_tuning - This function calculates the semitones off from standard pitch that a wavefile is.
=======================================================================================================================
*/

#ifndef _FE_PACKAGE_H_
#define _FE_PACKAGE_H_
#define _USE_MATH_DEFINES

#define IRREGULAR_VALUE 100000000000.0

#include <math.h>
#include <iostream>
#include <algorithm>
#include <complex>     //Need to use fft
#include "vector_template.h"
#include "math_function.h"
#include "fftw3.h" //Need to use fft
using std::complex;

#ifndef mymax
	#define mymax( a, b ) ( ((a) > (b)) ? (a) : (b) )
#endif

#ifndef mymin
	#define mymin( a, b ) ( ((a) < (b)) ? (a) : (b) )
#endif




//Audio pre-processing class
class audio_preprocessing
{
public:

	//1. Math function
	static bool histogram(double *const boundaries, const unsigned int NB,double *const Data, const unsigned int ND, size_t *const histCounts);
	static bool histogram(double *const boundaries, const unsigned int NB,vector<double> *const Data, const unsigned int ND, size_t *const histCounts);


	//2. Convert functions
	static bool hz2octs(double *const freq, double *const octs, const unsigned int N, const double A440);
	static bool hz2octs(double *const freq, double *const octs, const unsigned int N);
	static bool octs2hz(double *const octs, double *const freq, const unsigned int N, const double A440);
	static bool octs2hz(double *const octs, double *const freq, const unsigned int N);
	static double hz2octs(const double freq, const double A440);
	static double hz2octs(const double freq);
	static double octs2hz(const double octs, const double A440);
	static double octs2hz(const double octs);

	static bool mel2hz(double *const mel, double *const freq, const unsigned int N, const bool htk);
	static double mel2hz(const double mel, const bool htk);

	static bool hz2mel(double *const freq, double *const mel, const unsigned int N, const bool htk);
	static double hz2mel(const double freq, const bool htk);



	//3. Audio processing functions
	//A. Short Time Fourier Transform (coded by Y. Ni)
	static bool stft(double const *signal, const int N, const int fft_len,const int win_len, const int hop_len, complex<double> *const stft_gram, size_t stft_gram_row, size_t stft_gram_column);
    static bool istft(complex<double> const *x, const size_t x_row, const size_t x_column, const int ftsize,const int win_len, const int hop_len, double *const signal);

	//B. Spectrogram and convolution
	static bool spectrogram(double const *signal, const int N, const int fft_len,const int win_len, const int hop_len, double *const stft_gram, const size_t stft_gram_row, const size_t stft_gram_column);
	static bool convolution(double const *d1, const size_t N1, double const *d2, const size_t N2, double *const output);

	//C.cross correlation
	static bool xcorr(double const *d1, const size_t N1, double const *d2, const size_t N2, double *const d_out, size_t Nmax);


	//D. Tuning and HPSS
	static double estimate_tuning(double const *signal, const int N, const int SR, const int fft_len,const double f_ctr, const double f_sd);
	static bool HPSS(double const *signal, const int N, const int fft_len,const int hop_len, const int win_len,const double gamma, const double alpha, const int kmax, double *const xharmony);



protected:
	
	//1. Protected function (not in-house)
	static vector<double> ifptrack(double const *signal, const int N, const int fft_len, const int SR, const double fminl, const double fminu, const double fmaxl, const double fmaxu);
	static bool ifgram(double const *signal, const int N, const int fft_len, const int win_len, const int hop_len, const int SR, const int maxbin, double *const inst_gram, complex<double> *const stft_gram);

};




//Loudness based Chromagram
class LBC
{
public:
	static complex<double>* cal_hamming_window(const int SR,const double minFreq,const double maxFreq, const double resolution_fact,const double tuning, const int K, double *const winLenK, double *const freqBins);

	static int cal_LBC(const double *xharmony, const int N, const int SR, const double *beat_times, const int N_beat, const complex<double>* hammingK, const double* winLenK,const double* freqK,const int K, double *const sample_times, double *const chromagram, const bool normalizationFlag);
	static int cal_LBC(const double *xharmony, const int N, const int SR, const double *beat_times, const int N_beat, const complex<double>* hammingK, const double* winLenK,const double* freqK,const int K, double *const sample_times, double *const chromagram, const size_t N_block, const bool normalizationFlag);

};



//Resampler (downsampler/upsampler)
class FIR_resampler
{
public:
	//Zeroth order Modified Bessel function (used in Kaiser window)
	static double io(const double x);
	static void kaiser_window(const size_t n, const double beta, double *const k_win);
	static double sinc(const double x);
	static void fir_filter_least_square(const size_t N, double F[], double M[], size_t Nf, double *const filter);
	static bool resample(double *const signal, const size_t N, const double SR_in, const double SR_out, double *const sample_signal);

};

#endif

