
#include "vector_template.cpp"
#include "FE_package.h"

#include "Resampler.h" //Include the resampler template


#include <time.h>

#include<fstream>
using std::ofstream;
using std::ios;

using std::cerr;


/******************************************************************************
A.1 Function:
octs = hz2octs(freq, A440)
Convert a frequency in Hz into a real number counting 
the octaves above A0. So hz2octs(440) = 4.0
Optional A440 specifies the Hz to be treated as A4 (default 440).
******************************************************************************/
bool audio_preprocessing::hz2octs(double *const freq, double *const octs, const unsigned int N, const double A440)
{
	//1. Check the parameters
	if (N<1)
	{
		cerr<<"Error in hz2octs (FE_package.cpp): data length is 0"<<'\n';
		return false;
	}
	
	if (!freq)
	{
		cerr<<"Error in hz2octs (FE_package.cpp): can not find the input data"<<'\n';
		return false;
	}

	if (!octs)
	{
		cerr<<"Error in hz2octs (FE_package.cpp): can not write the output"<<'\n';
		return false;
	}

	//2. Convert
	double log2=log(2.0);
	double A0=A440/16; //A4 = A440 = 440 Hz, so A0 = 440/16 Hz

	for (int i=0;i<N;i++)
	{
		octs[i]=log(freq[i]/A0)/log2;
	}

	return true;
}

/******************************************************************************
A.2 Function:
octs = hz2octs(freq)
Convert a frequency in Hz into a real number counting 
the octaves above A0. So hz2octs(440) = 4.0
Optional A440 specifies the Hz to be treated as A4 (default 440).
******************************************************************************/
bool audio_preprocessing::hz2octs(double *const freq, double *const octs, const unsigned int N)
{
	//1. Check the parameters
	if (N<1)
	{
		cerr<<"Error in hz2octs (FE_package.cpp): data size is 0."<<'\n';
		return false;
	}
	
	if (!freq)
	{
		cerr<<"Error in hz2octs (FE_package.cpp): can not find the input data."<<'\n';
		return false;
	}

	if (!octs)
	{
		cerr<<"Error in hz2octs (FE_package.cpp): can not write the output."<<'\n';
		return false;
	}

	//2. Convert
	double log2=log(2.0);
	double A0=440.0/16; //A4 = A440 = 440 Hz, so A0 = 440/16 Hz

	for (int i=0;i<N;i++)
	{
		octs[i]=log(freq[i]/A0)/log2;
	}

	return true;
}

/******************************************************************************
A.3 Function:
octs = hz2octs(freq, A440)
Convert a frequency in Hz into a real number counting 
the octaves above A0. So hz2octs(440) = 4.0
Optional A440 specifies the Hz to be treated as A4 (default 440).
******************************************************************************/
double audio_preprocessing::hz2octs(const double freq, const double A440)
{

	//Convert single frequency
	double log2=log(2.0);
	double A0=A440/16; //A4 = A440 = 440 Hz, so A0 = 440/16 Hz
	double octs=log(freq/A0)/log2;

	return octs;
}

/******************************************************************************
A.4 Function:
octs = hz2octs(freq)
Convert a frequency in Hz into a real number counting 
the octaves above A0. So hz2octs(440) = 4.0
Optional A440 specifies the Hz to be treated as A4 (default 440).
******************************************************************************/
double audio_preprocessing::hz2octs(const double freq)
{

	//Convert single frequency
	double log2=log(2.0);
	double A0=440.0/16; //A4 = A440 = 440 Hz, so A0 = 440/16 Hz
	double octs=log(freq/A0)/log2;

	return octs;
}



/******************************************************************************
B.1 Function:
hz = octs2hz(octs,A440)
Convert a real-number octave into a frequency in Hzfrequency in Hz into a real number counting  
the octaves above A0. So hz2octs(440) = 4.0.
Optional A440 specifies the Hz to be treated as middle A (default 440).
******************************************************************************/
bool audio_preprocessing::octs2hz(double *const octs, double *const freq, const unsigned int N, const double A440)
{
	//1. Check the parameters
	if (N<1)
	{
		cerr<<"Error in octs2hz (FE_package.cpp): data size is 0."<<'\n';
		return false;
	}
	
	if (!octs)
	{
		cerr<<"Error in octs2hz (FE_package.cpp): can not find the input data."<<'\n';
		return false;
	}

	if (!freq)
	{
		cerr<<"Error in octs2hz (FE_package.cpp): can not write the output data."<<'\n';
		return false;
	}

	//2. Convert
	double A0=A440/16; //A4 = A440 = 440 Hz, so A0 = 440/16 Hz

	for (int i=0;i<N;i++)
	{
		freq[i]=A0*pow(2.0,octs[i]);
	}

	return true;
}

/******************************************************************************
B.2 Function:
hz = octs2hz(octs)
Convert a real-number octave into a frequency in Hzfrequency in Hz into a real number counting  
the octaves above A0. So hz2octs(440) = 4.0.
Optional A440 specifies the Hz to be treated as middle A (default 440).
******************************************************************************/
bool audio_preprocessing::octs2hz(double *const octs, double *const freq, const unsigned int N)
{
	//1. Check the parameters
	if (N<1)
	{
		cerr<<"Error in octs2hz (FE_package.cpp): data size is 0."<<'\n';
		return false;
	}
	
	if (!octs)
	{
		cerr<<"Error in octs2hz (FE_package.cpp): can not find the input data."<<'\n';
		return false;
	}

	if (!freq)
	{
		cerr<<"Error in octs2hz (FE_package.cpp): can not write the output data."<<'\n';
		return false;
	}

	//2. Convert
	double A0=440.0/16; //A4 = A440 = 440 Hz, so A0 = 440/16 Hz

	for (int i=0;i<N;i++)
	{
		freq[i]=A0*pow(2.0,octs[i]);
	}

	return true;
}

/******************************************************************************
B.3 Function:
hz = octs2hz(octs,A440)
Convert a real-number octave into a frequency in Hzfrequency in Hz into a real number counting  
the octaves above A0. So hz2octs(440) = 4.0.
Optional A440 specifies the Hz to be treated as middle A (default 440).
******************************************************************************/
double audio_preprocessing::octs2hz(const double octs, const double A440)
{
	//Convert to frequency
	double A0=A440/16; //A4 = A440 = 440 Hz, so A0 = 440/16 Hz
	double freq=A0*pow(2.0,octs);

	return freq;
}



/******************************************************************************
B.4 Function:
hz = octs2hz(octs)
Convert a real-number octave into a frequency in Hzfrequency in Hz into a real number counting  
the octaves above A0. So hz2octs(440) = 4.0.
Optional A440 specifies the Hz to be treated as middle A (default 440).
******************************************************************************/
double audio_preprocessing::octs2hz(const double octs)
{
	//Convert to frequency
	double A0=440.0/16; //A4 = A440 = 440 Hz, so A0 = 440/16 Hz
	double freq=A0*pow(2.0,octs);

	return freq;
}

/******************************************************************************
C.1 Function:
freq = mel2hz(mel, htk)
Convert 'mel scale' frequencies into Hz
Optional htk = 1 means using the HTK formula
Else use the formula from Slaney's mfcc.m

Remark: Inherited from (2005-04-19 dpwe@ee.columbia.edu) and modified (slightly)
		by the author, used it carefully.
******************************************************************************/
bool audio_preprocessing::mel2hz(double *const mel, double *const freq, const unsigned int N, const bool htk)
{
	//1. Check the parameters
	if (N<1)
	{
		cerr<<"Error in mel2hz (FE_package.cpp): data length is 0"<<'\n';
		return false;
	}
	
	if (!mel)
	{
		cerr<<"Error in mel2hz (FE_package.cpp): can not find the input data"<<'\n';
		return false;
	}

	if (!freq)
	{
		cerr<<"Error in mel2hz (FE_package.cpp): can not write the output"<<'\n';
		return false;
	}

	//2. Convert
	if (htk)
	{
		for (size_t i=0;i<N;i++)
		{
			freq[i]=700.0*(pow(10.0,mel[i]/2595.0)-1);
		}
	}
	else
	{
		//Parameters
		double f_sp=200.0/3; //66.666667
		double breakFreq=1000.0;
		double breakPoint=breakFreq/f_sp; //Starting mel value for log region
		double logstep=log(6.4)/27.0; //the magic 1.0711703 which is the ratio needed to get from 1000 Hz to 6400 Hz in 27 steps, and is *almost* the ratio between 1000 Hz and the preceding linear filter center at 933.33333 Hz (actually 1000/933.33333 = 1.07142857142857 and  exp(log(6.4)/27) = 1.07117028749447)
		
		//Fill in parts separately
		for (size_t i=0;i<N;i++)
		{
			if (mel[i]<breakPoint)
			{
				freq[i]=f_sp*mel[i];
			}
			else
			{
				freq[i]=breakFreq*exp(logstep*(mel[i]-breakPoint));
			}
		}

	}

	return true;
}


/******************************************************************************
C.2 Function:
freq = mel2hz(mel, htk)
Convert 'mel scale' frequencies into Hz
Optional htk = 1 means using the HTK formula
Else use the formula from Slaney's mfcc.m

Remark: Inherited from (2005-04-19 dpwe@ee.columbia.edu) and modified (slightly)
		by the author, used it carefully.
******************************************************************************/
double audio_preprocessing::mel2hz(const double mel, const bool htk)
{

	//Convert
	if (htk)
	{
		return 700.0*(pow(10.0,mel/2595.0)-1);
	}
	else
	{
		//Parameters
		double f_sp=200.0/3; //66.666667
		double breakFreq=1000.0;
		double breakPoint=breakFreq/f_sp; //Starting mel value for log region
		double logstep=log(6.4)/27.0; //the magic 1.0711703 which is the ratio needed to get from 1000 Hz to 6400 Hz in 27 steps, and is *almost* the ratio between 1000 Hz and the preceding linear filter center at 933.33333 Hz (actually 1000/933.33333 = 1.07142857142857 and  exp(log(6.4)/27) = 1.07117028749447)
		
		//Fill in parts separately
		if (mel<breakPoint)
		{
			return f_sp*mel;
		}
		else
		{
			return breakFreq*exp(logstep*(mel-breakPoint));
		}
	}
}


/******************************************************************************
C.3 Function:
mel = hz2mel(freq, htk)
Convert frequencies (Hz) into 'mel scale'.
Optional htk = 1 means using the HTK formula
Else use the formula from Slaney's mfcc.m

Remark: Inherited from (2005-04-19 dpwe@ee.columbia.edu) and modified (slightly)
		by the author, used it carefully.
******************************************************************************/
bool audio_preprocessing::hz2mel(double *const freq, double *const mel, const unsigned int N, const bool htk)
{
	//1. Check the parameters
	if (N<1)
	{
		cerr<<"Error in hz2mel (FE_package.cpp): data length is 0"<<'\n';
		return false;
	}
	
	if (!freq)
	{
		cerr<<"Error in hz2mel (FE_package.cpp): can not find the input data"<<'\n';
		return false;
	}

	if (!mel)
	{
		cerr<<"Error in hz2mel (FE_package.cpp): can not write the output"<<'\n';
		return false;
	}

	//2. Convert
	if (htk)
	{
		for (size_t i=0;i<N;i++)
		{
			mel[i]= 2595.0*log10(1+freq[i]/700.0);
		}
	}
	else
	{
		//Parameters
		double f_sp=200.0/3; //66.666667
		double breakFreq=1000.0;
		double breakPoint=breakFreq/f_sp; //Starting mel value for log region
		double logstep=log(6.4)/27.0; //the magic 1.0711703 which is the ratio needed to get from 1000 Hz to 6400 Hz in 27 steps, and is *almost* the ratio between 1000 Hz and the preceding linear filter center at 933.33333 Hz (actually 1000/933.33333 = 1.07142857142857 and  exp(log(6.4)/27) = 1.07117028749447)
		
		//Fill in parts separately
		for (size_t i=0;i<N;i++)
		{
			if (freq[i]<breakFreq)
			{
				mel[i]=freq[i]/f_sp;
			}
			else
			{
				mel[i]=breakPoint+log(freq[i]/breakFreq)/logstep;
			}
		}

	}

	return true;
}


/******************************************************************************
C.4 Function:
mel = hz2mel(freq, htk)
Convert frequencies (Hz) into 'mel scale'.
Optional htk = 1 means using the HTK formula
Else use the formula from Slaney's mfcc.m

Remark: Inherited from (2005-04-19 dpwe@ee.columbia.edu) and modified (slightly)
		by the author, used it carefully.
******************************************************************************/
double audio_preprocessing::hz2mel(const double freq, const bool htk)
{
	//Convert
	if (htk)
	{
		return 2595.0*log10(1+freq/700.0);
	}
	else
	{
		//Parameters
		double f_sp=200.0/3; //66.666667
		double breakFreq=1000.0;
		double breakPoint=breakFreq/f_sp; //Starting mel value for log region
		double logstep=log(6.4)/27.0; //the magic 1.0711703 which is the ratio needed to get from 1000 Hz to 6400 Hz in 27 steps, and is *almost* the ratio between 1000 Hz and the preceding linear filter center at 933.33333 Hz (actually 1000/933.33333 = 1.07142857142857 and  exp(log(6.4)/27) = 1.07117028749447)
		
		if (freq<breakFreq)
		{return freq/f_sp;}
		else
		{return (breakPoint+log(freq/breakFreq)/logstep);}
	}
}




/*************************************************************************************
-----------------------------------EVIL SEPARATION LINE--------------------------------
**************************************************************************************/




/******************************************************************************
D.1 Function:
histogram = histogram(boundaries,data)
Compute the histograms (counts of data) between each pair of boundaries.
Remark: 
the bins=#boundaries-1 (the left most and the right most boundaries are -/+ inf)
******************************************************************************/
bool audio_preprocessing::histogram(double *const boundaries, const unsigned int NB,double *const Data, const unsigned int ND, size_t *const histCounts)
{
	//1. Check the parameters
	if (!boundaries || !Data || !histCounts)
	{
		cerr<<"Error in histogram (FE_package.cpp): data handle problem."<<'\n';
		return false;
	}

	if (NB<1 || ND<1)
	{
		cerr<<"Error in histogram (FE_package.cpp): the data size is 0."<<'\n';
		return false;
	}

	//2. Intialization the count
	for (int i=0;i<NB-1; i++)
	{
		histCounts[i]=0;
	}

	for (int i=0;i<ND;i++)
	{
		if (Data[i]==negInf)
			continue;

		for (int j=1;j<NB;j++) //Compare a point between 2 boundaries
		{
			if (Data[i]<=boundaries[j] && Data[i]>=boundaries[j-1])
			{
				histCounts[j-1]+=1;
				break;
			}
		}
	}

	return true;

}

/******************************************************************************
D.2 Function:
histogram = histogram(boundaries,data)
Compute the histograms (counts of data) between each pair of boundaries.
Remark: 
the bins=#boundaries-1 (the left most and the right most boundaries are -/+ inf)
******************************************************************************/
bool audio_preprocessing::histogram(double *const boundaries, const unsigned int NB,vector<double> *const Data, const unsigned int ND, size_t *const histCounts)
{
	//1. Check the parameters
	if (!boundaries || !Data || !histCounts)
	{
		cerr<<"Error in histogram (FE_package.cpp): data handle problem."<<'\n';
		return false;
	}

	if (NB<1 || ND<1)
	{
		cerr<<"Error in histogram (FE_package.cpp): the data size is 0."<<'\n';
		return false;
	}

	//2. Intialization the count
	for (int i=0;i<NB-1; i++)
	{
		histCounts[i]=0;
	}

	for (int i=0;i<ND;i++)
	{
		for (int j=1;j<NB;j++) //Compare a point between 2 boundaries
		{
			double tempVal=Data->at(i);
			if (tempVal<=boundaries[j] && tempVal>=boundaries[j-1])
			{
				histCounts[j-1]+=1;
				break;
			}
		}
	}

	return true;

}



/*************************************************************************************
-----------------------------------EVIL SEPARATION LINE--------------------------------
**************************************************************************************/


/******************************************************************************
E.1 Function:
[instant_spectrum,STFT_spectrum] = ifgram(signal,fft length,window length,hop length,sample rate)
Compute the instant spectrum and short time fourier transform for the wav signal.

Inputs:
signal - the wav signal.
fft length - the length of fft.
window length - the window length of fft.
hop length - the hop length of each step.
sample rate - sampling rate.

Outputs:
instant_spectrum - the instantaneous frequency spectrum
STFT_spectrum - the short time Fourier transform spectrum

Remark:
Copyright (c) 2006 Columbia University.
The original function is part of LabROSA-coversongID.
******************************************************************************/
bool audio_preprocessing::ifgram(double const *signal, const int N, const int fft_len, const int win_len, const int hop_len, const int SR, const int maxbin, double *const inst_gram, complex<double> *const stft_gram)
{
	double M_PI2=2.0*M_PI/win_len;
	double T=(double)(win_len)/SR;
	double M_PI_T=M_PI/T;


	//1. Check parameters
	if (!signal || N<1)
	{
		cerr<<"Error in ifgram (FE_package.cpp): the signal size is 0."<<'\n';
		return false;
	}

	if (fft_len<1 || hop_len<1 || SR<1 || maxbin<1)
	{
		cerr<<"Error in ifgram (FE_package.cpp): the prameters are not correct."<<'\n';
		return false;
	}

	if (!inst_gram || !stft_gram)
	{
		cerr<<"Error in ifgram (FE_package.cpp): can not write the output data."<<'\n';
		return false;
	}
	

	//2.1 Hanning window
	int num_hops=1+floor((double)((N-win_len)/hop_len)); //How many complete windows
	

	double *hanning_window = new double[win_len];
	double norm=0.0;

	for (int w=0; w<win_len;w++)
	{
		hanning_window[w]=0.5*(1-cos(((double)(w))*M_PI2));
		norm+=hanning_window[w];
	}

	//sum(win) takes out integration due to window, 2 compensates for neg frequency
	norm=2/norm;



	//2.2 Window for discrete differentiation
	

	double *diff_window= new double[win_len];

	int spectrum_window=fft_len;
	if (fft_len & (fft_len-1))
	{
		int temp_index=fft_len;
		int targetlevel = 0;
		while (temp_index >>= 1) ++targetlevel;
		spectrum_window=pow(2.0,targetlevel+1);
	}

	double* wu=new double[spectrum_window];
	double* du=new double[spectrum_window];


	if (spectrum_window!=fft_len)
	{
		cerr<<"Warning in function ifgram (FE_package.cpp): the fft length is not 2^{K}, pad slience at the end!";
	}

	for (int w=0;w<spectrum_window;w++)
	{
		wu[w]=0.0;
		du[w]=0.0;
	}

	
	for (int w=0;w<win_len;w++)
	{
		diff_window[w]=-M_PI_T*sin(((double)(w))*M_PI2);
	}
	

	//2.3 
	int split_half=ceil((double)(fft_len/2))+1; //split in the middle and re-combine the signal
	int split_end=fft_len-split_half+1;
	int numw1=floor((double)((fft_len-win_len)/2));
	double* ww= new double[maxbin];
	for (int w=0;w<maxbin;w++)
	{
		ww[w]=2*M_PI*((double)(w))*SR/fft_len;
	}
	
	
	/*3. For loop, get the instant spectrum for each frequency bin/each hop steps (complex version)
	double* temp_signal=new double[win_len];
	fftw_complex *t1, *t2, *t1_out, *t2_out;
	fftw_plan p1, p2;
	
	t1 = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * spectrum_window);
	t2 = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * spectrum_window);
	t1_out = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * spectrum_window);
	t2_out = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * spectrum_window);

	p1 = fftw_plan_dft_1d(spectrum_window,t1,t1_out,FFTW_FORWARD,FFTW_ESTIMATE);
	p2 = fftw_plan_dft_1d(spectrum_window,t2,t2_out,FFTW_FORWARD,FFTW_ESTIMATE);
	

	complex<double> *t1_c = new complex<double>[spectrum_window];
	complex<double> *t2_c = new complex<double>[spectrum_window];
	complex<double> *t = new complex<double>[maxbin];
	for (int h=0;h<num_hops;h++)
	{
		//3.1 Get the signal
		int signal_lowerBound=h*hop_len;

		
		for (int w=0;w<win_len;w++)
		{
			temp_signal[w]=signal[w+signal_lowerBound];
		}

		//Pad or truncate samples if N != W
        //Apply windows now, while the length is right
		if (fft_len>=win_len)
		{
			for (int w=0;w<win_len;w++)
			{
				wu[numw1+w]=hanning_window[w]*temp_signal[w];
				du[numw1+w]=diff_window[w]*temp_signal[w];

			}
		}
		else
		{
			for (int w=0;w<fft_len;w++)
			{
				wu[w]=hanning_window[w-numw1]*temp_signal[w-numw1];
				du[w]=diff_window[w-numw1]*temp_signal[w-numw1];
			}
		}

		//FFTs of straight samples plus differential-weighted ones
		

		for (int w=0;w<spectrum_window;w++)
		{
			t1[w][1]=0.0;
			t1[w][0]=0.0;
			t2[w][1]=0.0;
			t2[w][0]=0.0;
		}
        
		for (int w=0;w<split_end;w++)
		{
			t1[w][0]=du[w+split_half-1];
			t2[w][0]=wu[w+split_half-1];
		}

		for (int w=0;w<split_half-1;w++)
		{
			t1[w+split_end][0]=du[w];
			t2[w+split_end][0]=wu[w];
		
		}

		
		
		//FFT transform
		fftw_execute(p1);
		fftw_execute(p2);
		

		
		//for (int i=0;i<spectrum_window;i++)
		//{
		//	t1_c[i]=complex<double>(t1_out[i][0],t1_out[i][1]);
		//	t2_c[i]=complex<double>(t2_out[i][0],t2_out[i][1]);
		//}

		//FFTW only return halft of the signal, and fft is symmetric
		for (int i=0;i<spectrum_window/2;i++)
		{
			t1_c[i]=complex<double>(t1_out[i][0],t1_out[i][1]);
			t2_c[i]=complex<double>(t2_out[i][0],t2_out[i][1]);
		}

		for (int i=1;i<spectrum_window/2;i++)
		{
			t1_c[spectrum_window-i]=complex<double>(t1_out[i][0],-t1_out[i][1]);
			t2_c[spectrum_window-i]=complex<double>(t2_out[i][0],-t2_out[i][1]);
		}

		
		for (int j=0;j<maxbin;j++)
		{
			//stft_gram =[h*maxbin+j]=t2[j]*norm;
			stft_gram->set(j,h,t2_c[j]*norm);
		}
		
		complex<double> temp_t(0.0,1.0); //complex 1j

		for (int j=0;j<maxbin;j++)
		{
			t[j]=t1_c[j]+temp_t*ww[j]*t2_c[j];
		}

		for (int j=0;j<maxbin;j++)
		{
			double t2_re=t2_c[j].real();
			double t2_im=t2_c[j].imag();
			double t_re=t[j].real();
			double t_im=t[j].imag();
			double t2_0=(t2_re==0.0 && t2_im==0.0);
			inst_gram->set(j,h,(0.5/M_PI)*(t2_re*t_im-t2_im*t_re)/(t2_re*t2_re+t2_im*t2_im+t2_0));
			
			//inst_gram[h*maxbin+j]=(0.5/M_PI)*(t2_re*t_im-t2_im*t_re)/(t2_re*t2_re+t2_im*t2_im+t2_0);
		}

	}	

	//Release the temp stuff
	fftw_destroy_plan(p1);
	fftw_destroy_plan(p2);

	delete[] temp_signal;
	fftw_free(t1);
	fftw_free(t1_out);
	fftw_free(t2);
	fftw_free(t2_out);
	delete[] t1_c;
	delete[] t2_c;
	delete[] t;
	delete[] ww;
	delete[] wu;
	delete[] du;
	delete[] diff_window;
	delete[] hanning_window;
	*/

	//3. For loop, get the instant spectrum for each frequency bin/each hop steps

	double* temp_signal=new double[win_len];
	double *t1 = new double[spectrum_window];
	double *t2= new double[spectrum_window];
	fftw_complex *t1_out, *t2_out;
	fftw_plan p1, p2;
	
	t1_out = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * spectrum_window);
	t2_out = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * spectrum_window);

	p1 = fftw_plan_dft_r2c_1d(spectrum_window,t1,t1_out,FFTW_MEASURE); //Only create the plan once
	p2 = fftw_plan_dft_r2c_1d(spectrum_window,t2,t2_out,FFTW_MEASURE);
	

	complex<double> *t1_c = new complex<double>[spectrum_window];
	complex<double> *t2_c = new complex<double>[spectrum_window];
	complex<double> *t = new complex<double>[maxbin];
	complex<double> temp_t(0.0,1.0); //complex 1j
	double t2_re, t2_im, t_re, t_im, t2_0;
	double inst_gram_factor=0.5/M_PI;


	for (int h=0;h<num_hops;h++)
	{

		size_t offset=h*maxbin;
		//3.1 Get the signal
		int signal_lowerBound=h*hop_len;

		
		for (int w=0;w<win_len;w++)
		{
			temp_signal[w]=signal[w+signal_lowerBound];
		}

		//Pad or truncate samples if N != W
        //Apply windows now, while the length is right
		if (fft_len>=win_len)
		{
			for (int w=0;w<win_len;w++)
			{
				wu[numw1+w]=hanning_window[w]*temp_signal[w];
				du[numw1+w]=diff_window[w]*temp_signal[w];

			}
		}
		else
		{
			for (int w=0;w<fft_len;w++)
			{
				wu[w]=hanning_window[w-numw1]*temp_signal[w-numw1];
				du[w]=diff_window[w-numw1]*temp_signal[w-numw1];
			}
		}

		//FFTs of straight samples plus differential-weighted ones
		

		//for (int w=0;w<spectrum_window;w++)
		//{
		//	t1[w]=0.0;
		//	t2[w]=0.0;
		//}
        
		for (int w=0;w<split_end;w++)
		{
			t1[w]=du[w+split_half-1];
			t2[w]=wu[w+split_half-1];
		}

		for (int w=0;w<split_half-1;w++)
		{
			t1[w+split_end]=du[w];
			t2[w+split_end]=wu[w];
		
		}


		
		//FFT transform
		fftw_execute(p1);
		fftw_execute(p2);

		
		//FFTW only return halft of the signal, and fft is symmetric
		for (int i=0;i<spectrum_window/2;i++)
		{
			t1_c[i]=complex<double>(t1_out[i][0],t1_out[i][1]);
			t2_c[i]=complex<double>(t2_out[i][0],t2_out[i][1]);
		}

		for (int i=1;i<spectrum_window/2;i++)
		{
			t1_c[spectrum_window-i]=complex<double>(t1_out[i][0],-t1_out[i][1]);
			t2_c[spectrum_window-i]=complex<double>(t2_out[i][0],-t2_out[i][1]);
		}
		
		for (int j=0;j<maxbin;j++)
		{
			stft_gram[offset+j]=conj(t2_c[j])*norm;
			//stft_gram->set(j,h,t2_c[j]*norm);
		}

		
		for (int j=0;j<maxbin;j++)
		{
			t[j]=t1_c[j]+temp_t*ww[j]*t2_c[j];
		}

		for (int j=0;j<maxbin;j++)
		{
			t2_re=t2_c[j].real();
			t2_im=t2_c[j].imag();
			t_re=t[j].real();
			t_im=t[j].imag();
			t2_0=(t2_re==0.0 && t2_im==0.0);
			//inst_gram->set(j,h,(0.5/M_PI)*(t2_re*t_im-t2_im*t_re)/(t2_re*t2_re+t2_im*t2_im+t2_0));
			
			inst_gram[offset+j]=inst_gram_factor*(t2_re*t_im-t2_im*t_re)/(t2_re*t2_re+t2_im*t2_im+t2_0);
		}

	}	

	//Release the temp stuff
	fftw_destroy_plan(p1);
	fftw_destroy_plan(p2);

	delete[] temp_signal;
	delete[] t1;
	delete[] t2;
	fftw_free(t1_out);
	fftw_free(t2_out);
	delete[] t1_c;
	delete[] t2_c;
	delete[] t;
	delete[] ww;
	delete[] wu;
	delete[] du;
	delete[] diff_window;
	delete[] hanning_window;


	return true;
}



/******************************************************************************
E.2 Function:
[pitch_freqs,pitch_magnitude] = ifptrack(d,fft_len,SR,fminl,fminu,fmaxl,fmaxu)
Track pitch based on instantaneous frequency.It looks for adjacent bins with
same inst freq.

Inputs:
d - the wav signal.
fft_len - the window length of fft.
SR - the sampling rate.
fminl, fminu, fmaxl, fmaxu - the defined ramps at edge of sensitivity.

Output:
pitch_freqs (first item in the vector) - the tracked pitch frequencies.
pitch_magnitude (second item in the vector) - the tracked pitch magnitudes.

Remark:
Copyright (c) 2006 Columbia University.
The original function is part of LabROSA-coversongID.
******************************************************************************/

vector<double> audio_preprocessing::ifptrack(double const *signal, const int N, const int fft_len, const int SR, const double fminl, const double fminu, const double fmaxl, const double fmaxu)
{
	//1. Check parameters
	if (!signal || N<1)
	{
		cerr<<"Error in ifptrack (FE_package.cpp): the signal size is 0."<<'\n';
		vector<double> failed(1);
		failed.push_back(-99999.0);
		return failed;
	}

	if (fft_len<1 || SR<1)
	{
		cerr<<"Error in ifptrack (FE_package.cpp): the prameters are not correct."<<'\n';
		vector<double> failed(1);
		failed.push_back(-99999.0);
		return failed;
	}


	//2. Parameter settings
	int maxbin=floor((double)(fft_len)/SR*fmaxu+0.5);
	int win_len=floor((double)(fft_len)/2);
	int hop_len=floor((double)(fft_len)/4);

	int num_hops=1+floor((double)((N-win_len)/hop_len));

	//3. Create the instant frequency spectrums
	//matrix<double>* inst_gram = new matrix<double>(maxbin,num_hops);
	//matrix<complex<double> >* stft_gram = new matrix<complex<double> >(maxbin,num_hops);
	double *inst_gram = new double[num_hops*maxbin];
	complex<double> *stft_gram = new complex<double>[num_hops*maxbin];


	bool successFlag=ifgram(signal,N,fft_len,win_len,hop_len,SR, maxbin, inst_gram, stft_gram);
	

	if (!successFlag)
	{
		cerr<<"Error in function ifptrack (FE_package.cpp): ifgram error.";
		vector<double> failed(1);
		failed.push_back(-99999.0);
		return failed;
	}

	//4. Find plateaus in ifgram - stretches where delta IF is < threshold
	double *diff_ifgram = new double[num_hops*maxbin];
	double *dgood = new double[num_hops*maxbin];

	for (size_t h=0;h<num_hops;h++)
	{
		size_t offset=h*maxbin;
		for (size_t j=1;j<maxbin-1;j++)
		{
			//diff_ifgram[offset+j]=inst_gram->get(j+1,h)-inst_gram->get(j-1,h);
			diff_ifgram[offset+j]=inst_gram[offset+j+1]-inst_gram[offset+j-1];
		}
		//diff_ifgram[offset]=inst_gram->get(1,h)-inst_gram->get(0,h);
		//diff_ifgram[offset+maxbin-1]=inst_gram->get(maxbin-1,h)-inst_gram->get(maxbin-2,h);
		diff_ifgram[offset]=inst_gram[offset+1]-inst_gram[offset];
		diff_ifgram[offset+maxbin-1]=inst_gram[offset+maxbin-1]-inst_gram[offset+maxbin-2];
	}


	double temp_threshold=0.75*SR/fft_len;
	for (int h=0;h<num_hops;h++)
	{
		size_t offset=h*maxbin;
		for (int j=0;j<maxbin;j++)
		{
			//Expected increment per bin=SR/fft_len, threshold at 3/4 that
			dgood[offset+j]=abs(diff_ifgram[offset+j])<temp_threshold;
		}
	}

	//delete any single bins (both above and below are 0)
	for (int h=0;h<num_hops;h++)
	{
		size_t offset=h*maxbin;
		for (int j=1;j<maxbin-1;j++)
		{
			bool deleteFlag=(dgood[offset+j+1]>0) || (dgood[offset+j-1]>0);
			//Expected increment per bin=SR/fft_len, threshold at 3/4 that
			dgood[offset+j]*=deleteFlag;
		}

		bool deleteFlag=(dgood[offset+1]>0) || (dgood[offset]>0);
		dgood[offset]*=deleteFlag;

		deleteFlag=(dgood[offset+maxbin-1]>0) || (dgood[offset+maxbin-2]>0);
		dgood[offset+maxbin-1]*=deleteFlag;
	}

	//5. Start creating pitch frequency and magnitude vector (using push back)
	//For each frame extract all harmonic freqs & magnitude


	vector<double> pitch_freqs_magnitude;
	double* sample_columns = new double[maxbin];
	vector<int> st;
	vector<int> en;
	double temp_mag=0;
	double temp_freq=0;
	double tempAbs=0;

	for (int h=0;h<num_hops;h++)
	{
		//Get the h column
		size_t offset=h*maxbin;
		for (int j=0;j<maxbin;j++)
		{
			sample_columns[j]=dgood[j+offset];
		}
		

		//find nonzero regions in each frame vector
		//vector<int> st;
		//vector<int> en;
		st.clear();
		en.clear();

		//First item
		if (sample_columns[0]>0) 
		{
			st.push_back(0);
			if (sample_columns[1]==0)
				en.push_back(0);
		}
		//inbetween
		for (int j=1;j<maxbin-1;j++)
		{
			if (sample_columns[j-1]==0 && sample_columns[j]>0)
				st.push_back(j);

			if (sample_columns[j]>0 && sample_columns[j+1]==0)
				en.push_back(j);
		}

		//Last item
		if (sample_columns[maxbin-1]>0)
		{
			en.push_back(maxbin-1);
			if (sample_columns[maxbin-2]==0)
				st.push_back(maxbin-1);
		}

		int npks=st.size();


		for (int i=0;i<npks;i++)
		{
			temp_mag=0;
			temp_freq=0;
			for (int j=st[i];j<=en[i];j++)
			{
				//double tempAbs=abs(stft_gram->get(j,h));
				//temp_mag+=tempAbs;
				//temp_freq+=tempAbs*inst_gram->get(j,h);
				tempAbs=abs(stft_gram[offset+j]);
				temp_mag+=tempAbs;
				temp_freq+=tempAbs*inst_gram[offset+j];
			}

			if (temp_mag>0)
				temp_freq=temp_freq/temp_mag;

			
			if (temp_freq>fmaxu)
			{
				temp_freq=0;
				temp_mag=0;
			}
			else if (temp_freq>fmaxl)
			{
				//temp_mag=temp_mag*max<double>::max_two(0.0,(fmaxu-temp_freq)/(fmaxu-fmaxl));
				temp_mag=temp_mag*mymax(0.0,(fmaxu-temp_freq)/(fmaxu-fmaxl));
			}

			//downweight magnitudes below? 200 Hz
			if (temp_freq<fminl)
			{
				temp_freq=0;
				temp_mag=0;
			}
			else if (temp_freq<fminu)
			{	//1 octave fade-out
				temp_mag=temp_mag*(temp_freq-fminl)/(fminu-fminl);
			}
			if (temp_freq<0)
			{
				temp_mag=0;
				temp_freq=0;
			}

			//Only push back those useful frequencies (delete all 0 frequencies)
			if (temp_freq>0)
			{
				pitch_freqs_magnitude.push_back(temp_freq);
				pitch_freqs_magnitude.push_back(temp_mag);
			}
		}
	}

	return pitch_freqs_magnitude;
}



/******************************************************************************
F.A Function:
F = stft(d,N,fft_len,win_len,hop_len)
Short time fourier transform

Inputs:
d - the wav signal.
N - the length of the signal.
fft_len - the window length of fft.
win_len - the window length of hanning window.
hop_len - the hop length of the frames.

Output:
F- the short time fourier transformation.
   row - hop
   column - frequency bin
******************************************************************************/

bool audio_preprocessing::stft(double const *signal, const int N, const int fft_len,const int win_len, const int hop_len, complex<double> *const stft_gram, const size_t stft_gram_row, const size_t stft_gram_column)
{
	//1. Checking the parameters
	if (!signal || N<1)
	{
		cerr<<"Error in stft (fft_package.cpp): the signal size is 0."<<'\n';
		return false;
	}

	if (fft_len<1 || win_len<0 || hop_len<1)
	{
		cerr<<"Error in stft (fft_package.cpp): the prameters are not correct."<<'\n';
		return false;
	}

	if (!stft_gram)
	{
		cerr<<"Error in stft (fft_package.cpp): can not write the output spectrum."<<'\n';
		return false;
	}

	//2. Creating the hanning window
	double* hanning_window = new double[fft_len]; 
	int win_len_local=win_len;
	if (win_len==0)
	{
		//Special case: rectangular window
		for (size_t i=0;i<fft_len;i++)
		{
			hanning_window[i]=1;
		}
	}
	else
	{
		//Initialization
		for (size_t i=0;i<fft_len;i++)
		{
			hanning_window[i]=0;
		}
		//force window to be odd-len
		if ((win_len_local % 2)==0) win_len_local++;
		int halflen=(win_len_local-1)/2;
		int halff=fft_len/2;  //midpoint of the hanning window

		double* halfwin = new double[halflen];
		for (size_t i=0;i<halflen;i++)
		{
			halfwin[i]=0.5+0.5*cos(M_PI*i/halflen);
		}


		int acthalflen = (halff<halflen)?halff:halflen;
		for (size_t i=0;i<acthalflen;i++)
		{
			hanning_window[halff+i]=halfwin[i];
			hanning_window[halff-i]=halfwin[i];
		}

		delete[] halfwin;
	}

	//3. Pre-allocate output array
	for (size_t i=0;i<stft_gram_row;i++)
	{
		size_t offset=i*stft_gram_column;
		for (size_t j=0;j<stft_gram_column;j++)
			stft_gram[offset+j]=0.0;
	}

	/*4. Do fft on each frame (complex version)
	size_t rowIndex=0;
	fftw_complex *temp_signal, *temp_signal_out;
	fftw_plan p;
	
	temp_signal = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * fft_len);
	temp_signal_out = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * fft_len);
	p = fftw_plan_dft_1d(fft_len,temp_signal,temp_signal_out,FFTW_FORWARD,FFTW_ESTIMATE); //Only create the plan once

	for (size_t h=0;h<=(N-fft_len);h+=hop_len)
	{
		size_t offset=rowIndex*stft_gram_column;
		//A. Get the temp signal
		for (size_t i=0;i<fft_len;i++)
		{
			temp_signal[i][0]=hanning_window[i]*signal[h+i];
			temp_signal[i][1]=0.0;
		}

		

		//B. FFT
		fftw_execute(p);
		


		//Return the values (Taking the complex conjugate: Hermitian Transpose)
		//Only use half window so it is ok, but remember FFTW only return half of the signal using fft.
		for (int i=0;i<stft_gram_column;i++)
		{
			stft_gram[offset+i]=complex<double>(temp_signal_out[i][0],-temp_signal_out[i][1]);
		}

		rowIndex++;
	}
	
	fftw_free(temp_signal);
	fftw_free(temp_signal_out);
	delete[] hanning_window;
	fftw_destroy_plan(p);

	*/



	//4. Do fft on each frame (real version)
	size_t rowIndex=0;
	double *temp_signal = new double[fft_len];
	fftw_complex *temp_signal_out;
	fftw_plan p;
	
	temp_signal_out = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * fft_len);
	p = fftw_plan_dft_r2c_1d(fft_len,temp_signal,temp_signal_out,FFTW_MEASURE); //Only create the plan once

	for (size_t h=0;h<=(N-fft_len);h+=hop_len)
	{
		size_t offset=rowIndex*stft_gram_column;
		//A. Get the temp signal
		for (size_t i=0;i<fft_len;i++)
		{
			temp_signal[i]=hanning_window[i]*signal[h+i];
		}

		

		//B. FFT
		fftw_execute(p);
		


		//Return the values (Taking the complex conjugate: Hermitian Transpose)
		for (int i=0;i<stft_gram_column;i++)
		{
			stft_gram[offset+i]=complex<double>(temp_signal_out[i][0],-temp_signal_out[i][1]);
		}

		rowIndex++;
	}

	delete[] temp_signal;
	fftw_free(temp_signal_out);
	delete[] hanning_window;
	fftw_destroy_plan(p);

	return true;
}



/******************************************************************************
F.B Function:
d = istft(x,N,fft_len,win_len,hop_len)
Inverse short time fourier transform

Inputs:
x - the stft transformation (matrix version).
	row - hop
	column - frequency bin
ftsize - the window length of fft.
win_len - the window length of hanning window.
hop_len - the hop length of the frames.

Output:
d- the wav signal.
******************************************************************************/
bool audio_preprocessing::istft(complex<double> const *x, const size_t x_row, const size_t x_column, const int ftsize,const int win_len, const int hop_len, double *const signal)
{
	//1. Checking the parameters
	if (!x)
	{
		cerr<<"Error in istft (fft_package.cpp): the signal size is 0."<<'\n';
		return false;
	}

	if (ftsize<1 || win_len<0 || hop_len<1)
	{
		cerr<<"Error in istft (fft_package.cpp): the prameters are not correct."<<'\n';
		return false;
	}

	if (!signal)
	{
		cerr<<"Error in istft (fft_package.cpp): can not write the output signal."<<'\n';
		return false;
	}

	//2. Set the parameters and the size of the signal
	int x_size=ftsize+(x_row-1)*hop_len;

	//Initialization
	for (int i=0;i<x_size;i++)
		signal[i]=0.0;

	//3. Creating the hanning window
	double* hanning_window = new double[ftsize]; 
	int win_len_local=win_len;
	if (win_len==0)
	{
		for (int i=0;i<ftsize;i++)
			hanning_window[i]=1;
	}
	else
	{
		for (int i=0;i<ftsize;i++)
			hanning_window[i]=0;

		//force window to be odd-len
		if ((win_len_local % 2)==0) win_len_local++;
		int halflen=(win_len_local-1)/2;
		int halff=ftsize/2;  //midpoint of the hanning window

		double* halfwin = new double[halflen];
		for (int i=0;i<halflen;i++)
		{
			halfwin[i]=0.5+0.5*cos(M_PI*i/halflen);
		}


		int acthalflen = (halff<halflen)?halff:halflen;
		for (int i=0;i<acthalflen;i++)
		{
			//PATCH: Make stft-istft loop be identity
			hanning_window[halff+i]=0.666667*halfwin[i];
			hanning_window[halff-i]=0.666667*halfwin[i];
		}

		delete[] halfwin;
	}

	

	/*4. Do ifft on each frame (complex version)
	int final_hop_index=(x_row-1)*hop_len;
	int halff=ftsize/2;
	int signal_size=x_column+halff-1; //x_column=ftsize/2+1

	fftw_complex *temp_signal, *temp_signal_out;
	fftw_plan p;
	
	temp_signal = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * signal_size);
	temp_signal_out = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * signal_size);
	p = fftw_plan_dft_1d(signal_size,temp_signal,temp_signal_out,FFTW_BACKWARD,FFTW_MEASURE); //only create the plan once

	for (int h=0;h<=final_hop_index;h+=hop_len)
	{
		//A. Get the temp signal
		size_t offset=(h/hop_len)*x_column;

		//Taking the complex conjugate: Hermitian Transpose)
		for (int j=0;j<x_column;j++)
		{
			size_t tempIndex=offset+j;
			temp_signal[j][0]=x[tempIndex].real();//x->get(i,signal_column);
			temp_signal[j][1]=-x[tempIndex].imag();
		}

		for (int j=0;j<halff-1;j++)
		{
			//Get conjugate
			size_t tempIndex_left=j+x_column;
			size_t tempIndex_right=halff-j-1;
			temp_signal[tempIndex_left][0]=temp_signal[tempIndex_right][0];
			temp_signal[tempIndex_left][1]=-temp_signal[tempIndex_right][1];
		}


		//B. inverse fft (non-rescale version, should divide by the length of the signal N)
		fftw_execute(p);
		


		//Return the values
		for (int i=0;i<signal_size;i++)
		{
			signal[h+i]+=temp_signal_out[i][0]*hanning_window[i]/signal_size;
		}
	}

	fftw_free(temp_signal);
	fftw_free(temp_signal_out);
	delete[] hanning_window;
	fftw_destroy_plan(p);
	*/
	

	//4. Do ifft on each frame
	int final_hop_index=(x_row-1)*hop_len;
	int halff=ftsize/2;
	int signal_size=x_column+halff-1; //x_column=ftsize/2+1

	fftw_complex *temp_signal;
	double  *temp_signal_out = new double[signal_size];
	fftw_plan p;
	
	temp_signal = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * signal_size);
	p = fftw_plan_dft_c2r_1d(signal_size,temp_signal,temp_signal_out,FFTW_MEASURE); //Only create the plan once

	for (int h=0;h<=final_hop_index;h+=hop_len)
	{
		//A. Get the temp signal
		size_t offset=(h/hop_len)*x_column;

		//Taking the complex conjugate: Hermitian Transpose)
		for (int j=0;j<x_column;j++)
		{
			size_t tempIndex=offset+j;
			temp_signal[j][0]=x[tempIndex].real();//x->get(i,signal_column);
			temp_signal[j][1]=-x[tempIndex].imag();
		}

		for (int j=0;j<halff-1;j++)
		{
			//Get conjugate
			size_t tempIndex_left=j+x_column;
			size_t tempIndex_right=halff-j-1;
			temp_signal[tempIndex_left][0]=temp_signal[tempIndex_right][0];
			temp_signal[tempIndex_left][1]=-temp_signal[tempIndex_right][1];
		}


		//B. inverse fft (non-rescale version, should divide by the length of the signal N)
		fftw_execute(p);
		


		//Return the values
		for (int i=0;i<signal_size;i++)
		{
			signal[h+i]+=temp_signal_out[i]*hanning_window[i]/signal_size;
		}
	}

	fftw_free(temp_signal);
	delete[] temp_signal_out;
	delete[] hanning_window;
	fftw_destroy_plan(p);

	return true;
}


/******************************************************************************
F.C Function:
F = specgram(d,N,fft_len,win_len,hop_len)
Calculating the spectrogram using short time fourier transform
F(w,t)=|stft(w,t)|^2

Inputs:
d - the wav signal.
N - the length of the signal.
fft_len - the window length of fft.
win_len - the window length of hanning window.
hop_len - the hop length of the frames.

Output:
F- the spectrogram for each frequency bin.
   row - hop
   column - frequency bin
******************************************************************************/
bool audio_preprocessing::spectrogram(double const *signal, const int N, const int fft_len,const int win_len, const int hop_len, double *const stft_gram, const size_t stft_gram_row, const size_t stft_gram_column)
{
	//1. Checking the parameters
	if (!signal || N<1)
	{
		cerr<<"Error in stft (fft_package.cpp): the signal size is 0."<<'\n';
		return false;
	}

	if (fft_len<1 || win_len<0 || hop_len<1)
	{
		cerr<<"Error in stft (fft_package.cpp): the prameters are not correct."<<'\n';
		return false;
	}

	if (!stft_gram)
	{
		cerr<<"Error in stft (fft_package.cpp): can not write the output spectrum."<<'\n';
		return false;
	}

	//2. Creating the hanning window
	double* hanning_window = new double[fft_len]; 
	int win_len_local=win_len;
	if (win_len==0)
	{
		//Special case: rectangular window
		for (size_t i=0;i<fft_len;i++)
		{
			hanning_window[i]=1;
		}
	}
	else
	{
		//Initialization
		for (size_t i=0;i<fft_len;i++)
		{
			hanning_window[i]=0;
		}
		//force window to be odd-len
		if ((win_len_local % 2)==0) win_len_local++;
		int halflen=(win_len_local-1)/2;
		int halff=fft_len/2;  //midpoint of the hanning window

		double* halfwin = new double[halflen];
		for (size_t i=0;i<halflen;i++)
		{
			halfwin[i]=0.5+0.5*cos(M_PI*i/halflen);
		}


		int acthalflen = (halff<halflen)?halff:halflen;
		
		for (size_t i=0;i<acthalflen;i++)
		{
			hanning_window[halff+i]=halfwin[i];
			hanning_window[halff-i]=halfwin[i];
		}

		delete[] halfwin;
	}

	//3. Pre-allocate output array
	for (size_t i=0;i<stft_gram_row;i++)
	{
		size_t offset=i*stft_gram_column;
		for (size_t j=0;j<stft_gram_column;j++)
			stft_gram[offset+j]=0.0;
	}

	/*4. Do fft on each frame (complex version)
	size_t rowIndex=0;
	fftw_complex *temp_signal, *temp_signal_out;
	fftw_plan p;
	
	temp_signal = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * fft_len);
	temp_signal_out = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * fft_len);
	p = fftw_plan_dft_1d(fft_len,temp_signal,temp_signal_out,FFTW_FORWARD,FFTW_ESTIMATE);

	for (size_t h=0;h<=(N-fft_len);h+=hop_len)
	{
		size_t offset=rowIndex*stft_gram_column;
		//A. Get the temp signal
		for (size_t i=0;i<fft_len;i++)
		{
			temp_signal[i][0]=hanning_window[i]*signal[h+i];
			temp_signal[i][1]=0.0;
		}

		

		//B. FFT
		fftw_execute(p);


		//Return the values (The norm of the signal), only take half of the signal so it is ok, but remember FFTW only returns half of fft (the other half is 0)
		for (int i=0;i<stft_gram_column;i++)
		{
			stft_gram[offset+i]=temp_signal_out[i][0]*temp_signal_out[i][0]+temp_signal_out[i][1]*temp_signal_out[i][1];
		}

		rowIndex++;
	}

	fftw_free(temp_signal);
	fftw_free(temp_signal_out);
	delete[] hanning_window;
	fftw_destroy_plan(p);

	*/
	

	//4. Do fft on each frame (real data version)
	size_t rowIndex=0;
	fftw_complex *temp_signal_out;
	double* temp_signal = new double[fft_len];
	fftw_plan p;
	
	temp_signal_out = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * fft_len);
	p = fftw_plan_dft_r2c_1d(fft_len,temp_signal,temp_signal_out,FFTW_MEASURE);

	for (size_t h=0;h<=(N-fft_len);h+=hop_len)
	{
		size_t offset=rowIndex*stft_gram_column;
		//A. Get the temp signal
		for (size_t i=0;i<fft_len;i++)
		{
			temp_signal[i]=hanning_window[i]*signal[h+i];
		}

		

		//B. FFT
		fftw_execute(p);

		//Return the values (The norm of the signal)
		for (int i=0;i<stft_gram_column;i++)
		{
			stft_gram[offset+i]=temp_signal_out[i][0]*temp_signal_out[i][0]+temp_signal_out[i][1]*temp_signal_out[i][1];
		}

		rowIndex++;
	}

	delete[] temp_signal;
	fftw_free(temp_signal_out);
	fftw_destroy_plan(p);
	delete[] hanning_window;
	return true;
}


/******************************************************************************
F.D Function:
output = convolution(d1,N1,d2,N2)
Convolution using FFT

Inputs:
d1 - signal 1 (the wav signal).
N1 - the length of signal 1.
d2 - signal 2 (e.g. the hanning window).
N2 - the length of signal 2.
Remark: N2 should be odd number (to split in the middle), but it won't be check in the program.

Output:
output - the convolution 
******************************************************************************/

bool audio_preprocessing::convolution(double const *d1, const size_t N1, double const *d2, const size_t N2, double *const output)
{
	//1. Checking the parameters
	if (!d1 || N1<1)
	{
		cerr<<"Error in convolution (fft_package.cpp): the size of signal 1 is 0."<<'\n';
		return false;
	}

	if (!d2 || N2<1)
	{
		cerr<<"Error in convolution (fft_package.cpp): the size of signal 2 is 0."<<'\n';
		return false;
	}

	if (!output)
	{
		cerr<<"Error in convolution (fft_package.cpp): can not write the output convolution."<<'\n';
		return false;
	}

	//2. Initialize the length of the fft sequence (should be 2^{K})
	size_t N=N1+N2-1;
	size_t N_fft=N;

	if (N & (N-1))
	{
		size_t tempN=N;
		int targetlevel = 0;
		while (tempN >>= 1) ++targetlevel;
		N_fft=pow(2.0,targetlevel+1);
	}

	double *t1 = new double[N_fft];
	fftw_complex *t2, *convolution_vector;
	fftw_plan p1, p2, p3;
	
	t2 = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * N_fft);
	convolution_vector = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * N_fft);
	p1 = fftw_plan_dft_r2c_1d(N_fft,t1,convolution_vector,FFTW_ESTIMATE);
	p2 = fftw_plan_dft_r2c_1d(N_fft,t1,t2,FFTW_ESTIMATE);
	p3 = fftw_plan_dft_c2r_1d(N_fft,convolution_vector,t1,FFTW_ESTIMATE);

	//2.1 Get signal 1 (pad 0 at the end)
	for (size_t i=0;i<N1;i++)
	{
		t1[i]=d1[i];
	}

	for (size_t i=N;i<N_fft;i++)
	{
		t1[i]=0.0;
	}

	//2.2 Get FFT of signal 1
	fftw_execute(p1);
	fftw_destroy_plan(p1);

	//Since FFTW only return half of the FFT, so remember to pad the other half of the signal
	for (size_t i=1;i<N_fft/2;i++)
	{
		convolution_vector[N_fft-i][1]=-convolution_vector[i][1];
		convolution_vector[N_fft-i][0]=convolution_vector[i][0];
	}	


	
	//2.3 Get signal 2 (pad 0 at the end, make it the same as MATLAB)
	for (size_t i=0;i<N2;i++)
	{
		t1[i]=d2[i];
	}

	for (size_t i=N2;i<N_fft;i++)
	{
		t1[i]=0.0;
	}

	//2.3 Get FFT of signal 2
	fftw_execute(p2);
	fftw_destroy_plan(p2);

	//Since FFTW only return half of the FFT, so remember to pad the other half of the signal
	for (size_t i=1;i<N_fft/2;i++)
	{
		t2[N_fft-i][1]=-t2[i][1];
		t2[N_fft-i][0]=t2[i][0];
	}	



	//3.Get fft(d1)*fft(d2) 
	for (size_t i=0;i<N_fft;i++)
	{
		double RV=(convolution_vector[i][0]*t2[i][0]-convolution_vector[i][1]*t2[i][1]);
		double IV(convolution_vector[i][0]*t2[i][1]+convolution_vector[i][1]*t2[i][0]);
		convolution_vector[i][0]=RV;
		convolution_vector[i][1]=IV;
	}

	//4. Inverse fft on convolution
	fftw_execute(p3);
	fftw_destroy_plan(p3);

	//5. Output the convolution (remember to divided by the scale)
	for (size_t i=0;i<N;i++)
	{
		output[i]=t1[i]/N_fft;
	}

	

	//Free the memory
	delete[] t1;
	fftw_free(t2);
	fftw_free(convolution_vector);
	return true;

}



/******************************************************************************
F.E Function:
d_out = xcorr(d1,N1,d2,N2,d_out,Nmax)
Get cross correlation of two signals using FFT
Formula: (f*g)[n]=sum_{m=-inf}^{inf}conj(f[m])*g[n+m]

Inputs:
d1 - signal 1 (the wav signal).
N1 - the length of signal 1.
d2 - signal 2 (the wav signal).
N2 - the length of signal 2.
Nmax - computes the cross correlation over the range -Nmax to Nmax, i.e. 2*Nmax+1 lags.

Output:
d_out - the output correlation vector
******************************************************************************/
bool audio_preprocessing::xcorr(double const *d1, const size_t N1, double const *d2, const size_t N2, double *const d_out, size_t Nmax)
{
	//1. Check the parameters (stricter on this function)
	if (!d1 || N1<1 || !d2 || N2<1)
	{
		cerr<<"Error in function xcorr (FE_package.cpp): the size of the inputs are 0.\n";
		return false;
	}
	else if (!d_out)
	{
		cerr<<"Error in function xcorr (FE_package.cpp): can not write the output.\n";
		return false;
	}
	else if (Nmax > N1 || Nmax > N2)
	{
		cerr<<"Error in function xcorr (FE_package.cpp): parameter error Nmax > N1 (or N2).\n";
	}

	//2. Create the FFT transformation of both signals
	size_t N=N1+N2-1; //The length of the signal
	size_t N_fft=N;   //The length of the FFT transform

	if (N & (N-1))
	{
		size_t tempN=N;
		int targetlevel = 0;
		while (tempN >>= 1) ++targetlevel;
		N_fft=pow(2.0,targetlevel+1);
	}

	
	double *t1 = new double[N_fft];
	fftw_complex * t2 = (fftw_complex *) fftw_malloc(sizeof(fftw_complex) * N_fft);
	fftw_complex * output = (fftw_complex *) fftw_malloc(sizeof(fftw_complex) * N_fft);
	fftw_plan p1, p2, p3;
	p1 = fftw_plan_dft_r2c_1d(N_fft,t1,output,FFTW_ESTIMATE);
	p2 = fftw_plan_dft_r2c_1d(N_fft,t1,t2,FFTW_ESTIMATE);
	p3 = fftw_plan_dft_c2r_1d(N_fft,output,t1,FFTW_ESTIMATE);

	//2.1 Get FFT of signal 1
	for (size_t i=0;i<N1;i++)
	{
		t1[i]=d1[i];
	}

	for (size_t i=N1;i<N_fft;i++)
	{
		t1[i]=0.0;
	}

	fftw_execute(p1);
	fftw_destroy_plan(p1);

	//FFTW only return half of the signal, remember to return another half
	for (size_t i=1;i<N_fft/2;i++)
	{
		output[N_fft-i][1]=-output[i][1];
		output[N_fft-i][0]=output[i][0];
	}	
		

	//2.2 Get FFT of signal 2
	for (size_t i=0;i<N2;i++)
	{
		t1[i]=d2[i];
	}

	for (size_t i=N2;i<N_fft;i++)
	{
		t1[i]=0.0;
	}
	
	fftw_execute(p2);
	fftw_destroy_plan(p2);

	//FFTW only return half of the signal, remember to return another half
	for (size_t i=1;i<N_fft/2;i++)
	{
		t2[N_fft-i][1]=-t2[i][1];
		t2[N_fft-i][0]=t2[i][0];
	}	

	//2.3 Get fft(d1)*conj(fft(d2))
	for (size_t i=0;i<N_fft;i++)
	{
		double RV=output[i][0]*t2[i][0]+output[i][1]*t2[i][1];
		double IV=-output[i][0]*t2[i][1]+output[i][1]*t2[i][0];
		output[i][0]=RV;
		output[i][1]=IV;
	}

	//3. Inverse fft on convolution
	
	fftw_execute(p3);
	fftw_destroy_plan(p3);

	//4. Get the output signal (end part)
	for (int i=0;i<Nmax;i++)
	{
		d_out[i]=t1[N_fft-Nmax+i]/N_fft;
	}

	//4.2 Get the output signal (start part)
	for (int i=0;i<=Nmax;i++)
	{
		d_out[i+Nmax]=t1[i]/N_fft;
	}

	//5. Free the memory
	delete[] t1;
	fftw_free(t2);
	fftw_free(output);

	return true;
}




/*************************************************************************************
-----------------------------------EVIL SEPARATION LINE--------------------------------
**************************************************************************************/



/******************************************************************************
G. Function:
semisoff = estimate_tuning(d,N,SR,fft_len,f_ctr,d_sd)
Estimate the tuing (semitone off) of the signal.

Inputs:
d - the wav signal.
N - the length of the signal.
fft_len - the window length of fft.
SR - the sampling rate.
fminl, fminu, fmaxl, fmaxu - the defined ramps at edge of sensitivity.

Output:
semisoff - the tuning (movement measured by semitone).
******************************************************************************/

double audio_preprocessing::estimate_tuning(double const *signal, const int N, const int SR, const int fft_len,const double f_ctr, const double f_sd)
{
	//1. Check parameters
	if (!signal || N<1)
	{
		cerr<<"Error in estimate_tuning (FE_package.cpp): the signal size is 0."<<'\n';
		return -99999.0;
	}

	if (fft_len<1 || f_ctr<0 || f_sd<0)
	{
		cerr<<"Error in estimate_tuning (FE_package.cpp): the prameters are not correct."<<'\n';
		return -99999.0;
	}

	//2. The parameters
	double fminl = octs2hz(hz2octs(f_ctr)-2*f_sd);
	double fminu= octs2hz(hz2octs(f_ctr)-f_sd);
	double fmaxl = octs2hz(hz2octs(f_ctr)+f_sd);
	double fmaxu = octs2hz(hz2octs(f_ctr)+2*f_sd);

	
	//3. Get the pitch tracked frequencies and magnitudes
	vector<double> pitch_freq_mag=ifptrack(signal,N,fft_len,SR,fminl,fminu,fmaxl,fmaxu);
	

	if (pitch_freq_mag[0]==-99999.0)
	{
		cerr<<"Error in estimate_tuning (FE_package.cpp): ifptrack problem."<<'\n';
		return -99999.0;
	}

	int dataSize=pitch_freq_mag.size()/2;


	double *pitch_freq = new double[dataSize];
	vector<double> pitch_mag(dataSize,0);
	//double *pitch_mag= new double[dataSize];
	
	

	for (int i=0;i<dataSize;i++)
	{
		pitch_freq[i]=pitch_freq_mag[2*i];
		pitch_mag[i]=pitch_freq_mag[2*i+1];
	}


	//Find significantly large magnitudes
	double median_mag=math_fun::median_score(pitch_mag);


	//*****************************Test new median function ******************
	//double *temp_pitch_mag=new double[dataSize];
	//for (size_t i=0;i<dataSize;i++)
	//	temp_pitch_mag[i]=pitch_mag[i];
	//double median_mag=math_fun::median(temp_pitch_mag,0,dataSize-1,dataSize);
	//*****************************Test new median function ******************


	double nchr=12.0; //size of features


	//Convert to octaves
	double* Pocts = new double[dataSize];
	for (int i=0;i<dataSize;i++)
	{
		if (pitch_mag[i]>median_mag)
		{
			double tempVal=nchr*hz2octs(pitch_freq[i]);
			tempVal=tempVal-floor(tempVal+0.5);
			Pocts[i]=tempVal;
		}
		else
		{
			Pocts[i]=negInf;
		}
	}


	//4. Create the boundaries for histgoram
	//make histo, resolution is 0.01, from -0.5 to 0.5
	double lowerInf=negInf;
	double upperInf=posInf; //Very large value regarding as inf
	double hop_interval=0.01;
	double lowerBound=-0.5-hop_interval/2;
	double upperBound=0.5+hop_interval/2;
	
	unsigned int NB=floor((upperBound-lowerBound)/hop_interval+0.5);
	double* boundaries = new double[NB+2];
	boundaries[0]=lowerInf;
	boundaries[NB+1]=upperInf;
	for (int i=0;i<NB;i++)
	{
		boundaries[i+1]=lowerBound+hop_interval*i;
	}

	size_t* histCounts = new size_t[NB+1]; //NB+1 bins
	bool successFlag=histogram(boundaries,NB+2,Pocts, dataSize, histCounts);
	
	//find peaks
	if (!successFlag)
	{
		cerr<<"Error in estimate_tuning (FE_package.cpp): histogram problem."<<'\n';
		return -99999.0;
	}

	vector<double> maxBins=max<size_t>::max_list(histCounts,NB+1);
	//5. Return
	//If first bin
	if (maxBins[1]==0) 
	{return -0.501;}
	//If last bin
	else if (maxBins[1]==NB)
	{return 0.501;}
	else
	{return (boundaries[(int)(maxBins[1])]+boundaries[(int)(maxBins[1])+1])/2;}

}




/******************************************************************************
H. Function:
xharmony = HPSS(d,N,fft_len,hop_len,win_len,gamma,alpha,kmax)
Deriving harmony from the signal.

Inputs:
d - the wav signal.
N - the length of the signal.
fft_len - the window length of fft.
hop_len - the hop length.
win_len - the window length of the hanning window.
gamma - power spectrum reduction factor.
alpha - the degree of initial separation.
kmax - number of iterations.

Output:
xharmony - the harmonic component.
******************************************************************************/

bool audio_preprocessing::HPSS(double const *signal, const int N, const int fft_len,const int hop_len, const int win_len,const double gamma, const double alpha, const int kmax, double *const xharmony)
{
	//1. Check parameters
	if (!signal || N<1)
	{
		cerr<<"Error in HPSS (FE_package.cpp): the signal size is 0."<<'\n';
		return false;
	}

	if (fft_len<1 || hop_len<1 || win_len<0 || kmax<1)
	{
		cerr<<"Error in HPSS (FE_package.cpp): the prameters are not correct."<<'\n';
		return false;
	}

	if (!xharmony)
	{
		cerr<<"Error in HPSS (FE_package.cpp): can not write the output signal."<<'\n';
		return false;
	}


	//2. Pre-allocate the STFT array
	size_t F_column=1+fft_len/2;
	size_t F_row=1+floor((double)(N-fft_len)/hop_len);
	complex<double>* F= new complex<double>[F_row*F_column];

	bool successFlag=stft(signal,N,fft_len,win_len,hop_len,F,F_row,F_column);


	if (!successFlag)
	{
		cerr<<"Error in HPSS (FE_package.cpp): stft function problem."<<'\n';
	}


	//2.* Power spectrum of F reduced by gamma
	//Initialization of Harmony and Percussion (half/half).
	size_t dataSize=F_row*F_column;
	double* W = new double[dataSize];
	double* H = new double[dataSize];
	double* P = new double[dataSize];
	double* Hnew = new double[dataSize];
	double* Pnew = new double[dataSize];

	double* W_point;
	W_point=W;
	double* H_point;
	H_point=H;
	double* P_point;
	P_point=P;
	

	//Create all indices (different order)
	size_t* W_indices= new size_t[dataSize];
	size_t* temp_pointer;
	size_t boundarySize=0;
	temp_pointer=W_indices;

	for (size_t j=0;j<F_column;j++)
	{
		*temp_pointer++=j;
		boundarySize++;
	}

	for (size_t j=0;j<F_column;j++)
	{
		*temp_pointer++=(F_row-1)*F_column+j;
		boundarySize++;
	}

	for (size_t i=1;i<F_row-1;i++)
	{
		*temp_pointer++=i*F_column;
		boundarySize++;
	}

	for (size_t i=1;i<F_row-1;i++)
	{
		*temp_pointer++=i*F_column+F_column-1;
		boundarySize++;
	}

	for (size_t i=1;i<F_row-1;i++)
	{
		for (size_t j=1;j<F_column-1;j++)
		{
			*temp_pointer++=i*F_column+j;
		}
	}

	//Initialize the values
	for (size_t i=0;i<F_row;i++)
	{
		size_t offset=i*F_column;
		for (size_t j=0;j<F_column;j++)
		{
			*W_point=pow(norm(F[offset+j]),gamma);
			*H_point=0.5*(*W_point);
			*P_point=0.5*(*W_point);
			W_point++;
			H_point++;
			P_point++;
		}
	}



	//3. Evaluate the constants
	double a1=alpha*0.25;
	double a2=(1-alpha)*0.25;
	temp_pointer=W_indices;


	size_t tempIndex;
	double tempVal;

	for (size_t k=0;k<kmax;k++)
	{
		//3.1 Do the boundary update. It is a square
		for (size_t i=0;i<boundarySize;i++)
		{
			tempIndex=temp_pointer[i];
			tempVal=2*H[tempIndex];
			//Hnew[tempIndex]=min<double>::min_two(max<double>::max_two(2*H[tempIndex],0.0),W[tempIndex]);
			Hnew[tempIndex]=mymin(mymax(tempVal,0.0),W[tempIndex]);
			Pnew[tempIndex]=W[tempIndex]-Hnew[tempIndex];
		}

		//3.2 Do the inner update.
		for (size_t i=boundarySize;i<dataSize;i++)
		{
			tempIndex=temp_pointer[i];
			tempVal=H[tempIndex]+a1*(H[tempIndex-F_column]-2*H[tempIndex]+H[tempIndex+F_column])-a2*(P[tempIndex-1]-2*P[tempIndex]+P[tempIndex+1]);
			//Hnew[tempIndex]=min<double>::min_two(max<double>::max_two(H[tempIndex]+tempVal,0.0),W[tempIndex]);
			Hnew[tempIndex]=mymin(mymax(tempVal,0.0),W[tempIndex]);
			Pnew[tempIndex]=W[tempIndex]-Hnew[tempIndex];
		}

		//3.3 Swap the pointers
		W_point=Hnew;
		Hnew=H;
		H=W_point;
		W_point=Pnew;
		Pnew=P;
		P=W_point;
	}


	//3.3 Finally return H and P and binarizing the result
	//I.e. if the magnitude H>P take H, otherwise take P
	for (int i=0;i<dataSize;i++)
	{
		if (H[i]<P[i])
		{
			Hnew[i]=0.0;
			//Pnew[i]=W[i];
		}
		else
		{
			Hnew[i]=W[i];
			//Pnew[i]=0;
		}
	}



	//4. Convert back to waveform
	//Only convert the harmony
	double update_factor=1.0/(2.0*gamma);
	complex<double> complexJ(0.0,1.0);

	for (int i=0;i<F_row;i++)
	{
		size_t offset=i*F_column;
		for (int j=0;j<F_column;j++)
		{
			complex<double> phasepart=exp(complexJ*atan2(F[offset+j].imag(),F[offset+j].real()));
			F[offset+j]=phasepart*pow(Hnew[offset+j],update_factor);
		}
	}


	
	successFlag=istft(F,F_row,F_column,fft_len,win_len,hop_len,xharmony);


	if (!successFlag)
	{
		cerr<<"Error in HPSS (FE_package.cpp): istft function problem."<<'\n';
	}
	
	delete[] H;
	delete[] Hnew;
	delete[] P;
	delete[] Pnew;
	delete[] W;

	return true;

}




/*************************************************************************************
-----------------------------------EVIL SEPARATION LINE--------------------------------
**************************************************************************************/



/******************************************************************************
A. Function:
[hammingK,winLenK,freqBins]=cal_hamming_window(SR, minFreq, maxFreq, resolution_fact,tuning, K)
This function computes the hamming window for the constant Q transformation.

INPUTS:
SR - the sample rate
minFreq - the lowest frequency (e.g. 55HZ)
maxFreq - the highest frequency (e.g. 1661HZ)
resolution_fact - the resolution of Q (Q_new=Q_org*resolution)
tuning - tuning parameter, fk=fk*2^(tuning/bins)
K - the number of bins (K=ceil(log2(maxFreq/minFreq))*bins;

OUTPUTS:
hammingK - the hamming windows for each frequency
winLenK - the length of each hamming window k
freqBins - the frequency of each hamming window
******************************************************************************/
complex<double>* LBC::cal_hamming_window(const int SR,const double minFreq,const double maxFreq, const double resolution_fact,const double tuning, const int K, double *const winLenK, double *const freqBins)
{
	//1. Check parameters
	if (SR<0 || minFreq<0 || maxFreq<minFreq || resolution_fact<0)
	{
		cerr<<"Error in function cal_hamming_window (FE_package.cpp): parameters error."<<'\n';
		complex<double>* falseFlag= new complex<double>[1];
		falseFlag[0]=complex<double>(-99999.0,0.0);
		return falseFlag;
	}

	if (!winLenK || !freqBins)
	{
		cerr<<"Error in function cal_hamming_window (FE_package.cpp): can not write the output space."<<'\n';
		complex<double>* falseFlag= new complex<double>[1];
		falseFlag[0]=complex<double>(-99999.0,0.0);
		return falseFlag;
	}

	//2. Parameters
	size_t bins=12;
	size_t pitchClass=12;
	size_t pitchInterval = bins/pitchClass;

	double *pitchIntervalMap = new double[bins];
	for (size_t i=0;i<pitchClass;i++)
	{
		for (size_t j=0;j<pitchInterval;j++)
			pitchIntervalMap[i*pitchInterval+j]=(double)(i);
	}

	//3. Frequency bins (Get tuned frequency for each bin)
	for (size_t i=0;i<=K-pitchInterval;i+=pitchInterval)
	{
		double octaveIndex=floor((double)(i)/bins);
		int binIndex=(i%bins);
		for (size_t j=0;j<pitchInterval;j++)
		{
			//Get frequency and then shifted by the tuning
			freqBins[i+j]=minFreq*pow(2.0,octaveIndex+pitchIntervalMap[binIndex]/pitchClass)*pow(2.0,tuning/bins);
		}
	}
	
	//4. Create constant Q and window size
	double Q = resolution_fact/(pow(2.0,1.0/bins)-1);
	double SRQ_factor=SR*Q;
	for (size_t i=0;i<K;i++)
	{
		winLenK[i]=ceil(SRQ_factor/freqBins[i]);
	}

	//5. Construct the hamming window
	int maxColumn=winLenK[0];
	complex<double> temp_exp_factor=conj(-2.0*M_PI*Q*complex<double>(0.0,1.0)); //Get the conjugate, see line 68 in cal_hamming_window.m
	complex<double> *expFactor = new complex<double>[maxColumn+1]; //Largest exponential factor
	for (size_t i=0;i<=maxColumn;i++)
	{
		expFactor[i]=temp_exp_factor*(double)(i);
	}

	//6.Make the hamming window
	double hamming_window;
	double N;
	double M_PI2;
	int offset;
	complex<double>* hammingK= new complex<double>[K*maxColumn]; //Using the largest window size as the column

	for (size_t k=0;k<K;k++)
	{
		N=winLenK[k];
		M_PI2=2*M_PI/(N-1);
		offset=k*maxColumn;
		 

		//Get hamming window
		for (int w=0; w<N;w++)
		{
			hamming_window=0.54-0.46*cos(M_PI2*w);
			hammingK[offset+w]=hamming_window*exp(expFactor[w]/N)/N;
		}
	}

	delete[] pitchIntervalMap;
	delete[] expFactor;

	return hammingK;

}



/******************************************************************************
B.1 Function (original version, slow due to FFT):
[chromagram (normal_chromagram),sample_times]=cal_CQ_chroma_loudness(x,SR,...
beat_times, hammingK, winLenK, freqK, normalizationFlag)

Main function to compute the loudness based beat-sync (or fixed length) chromagram features

INPUTS:
x - the wave signal (xharmony)
SR - the sample rate 
beat_time - the beat time (unit: second)
hammingK - the hamming windows for each frequency
winLenK - the length of each hamming window k (to retrieval the hamming window)
freqK - the k'th frequency (Computed by .m function: cal_hamming_window)
normalizationFlag - 1. Return normalization chromagram, else un-normalized chromagram.
				    Normalization is: (x-x_min)/(x_max-x_min)

OUTPUTS:
chromagram - the loudness based chromagram features (length Nb+1 x bins)
normal_chromagram - the normalized loudness chromagram features (length Nb+1 x bins)
sample_times - the sample times for each frame, formated as a Nx2 matrix [start_times,end_times]
return value - the length of the chromagram (in case that the beat times exceed the length of harmony)
******************************************************************************/

int LBC::cal_LBC(const double *xharmony, const int N, const int SR, const double *beat_times, const int N_beat, const complex<double>* hammingK, const double* winLenK,const double* freqK,const int K, double *const sample_times, double *const chromagram, const bool normalizationFlag)
{
	//1. Check parameters
	if (SR<0 || !hammingK || !winLenK || !freqK || K<1)
	{
		cerr<<"Error in function cal_LBC (FE_package.cpp): parameters error."<<'\n';
		return -1;
	}

	if (!xharmony || !beat_times || N<1 || N_beat<1)
	{
		cerr<<"Error in function cal_LBC (FE_package.cpp): the size of the input is 0."<<'\n';
		return -1;
	}

	if (!sample_times || !chromagram)
	{
		cerr<<"Error in function cal_LBC (FE_package.cpp): can not write the output chromagram."<<'\n';
		return -1;
	}

	//Special check: if the hamming window is longer than the signal, return error!
	for (size_t k=0;k<K;k++)
	{
		if (winLenK[k]>N)
		{
			cerr<<"Warning (regarded as error) in function cal_LBC (FE_package.cpp): certain hamming window is longer than the music itself, check the frequency parameters."<<'\n';
			return -1;
		}
	}


	//2. Parameters
	size_t bins=12;
	

	//2.1 zero pad to 2^M
	int N_signal=N;
	if (N_signal & (N_signal))
	{
		int temp_index=N_signal;
		int targetlevel = 0;
		while (temp_index >>= 1) ++targetlevel;
		N_signal=pow(2.0,targetlevel+1);
	}

	//2.2 Get FFT of the signal
	long double ifft_factor=(double)(N_signal)*N_signal;
	double *x_in=new double[N_signal]; //Store the signal of x
	
	fftw_complex *x_fft, *w_in, *w_fft, *convol;
	fftw_plan p, pp, p_inv;
	
	w_in = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * N_signal);
	x_fft = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * N_signal);
	w_fft = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * N_signal);
	convol = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * N_signal);


	p = fftw_plan_dft_r2c_1d(N_signal,x_in,x_fft,FFTW_MEASURE); //Only create the plan once
	p_inv = fftw_plan_dft_1d(N_signal,convol,w_fft,FFTW_BACKWARD,FFTW_MEASURE);
	pp = fftw_plan_dft_1d(N_signal, w_in, w_fft, FFTW_FORWARD, FFTW_MEASURE);


	for (size_t i=0;i<N;i++)
	{
		x_in[i]=xharmony[i];
	}
	for (size_t i=N;i<N_signal;i++)
	{
		x_in[i]=0.0;
	}

	fftw_execute(p);
	fftw_destroy_plan(p);


	//since FFTW only return half of the signal, get the symmatric half
	for (size_t i=1;i<N_signal/2;i++)
	{
		x_fft[N_signal-i][1]=-x_fft[i][1];
		x_fft[N_signal-i][0]=x_fft[i][0];
	}	


	//2.3 Get the beat-time interval (in frames)
	int *beatSR = new int[N_beat+2];
	size_t N_beat_frame=1;  //N_beat_frame=#items in beatSR -1 (#columns of CQ)
	beatSR[0]=0;
	int beat_frame=ceil(beat_times[0]*SR);
	if (beat_frame>0)
	{
		beatSR[N_beat_frame]=beat_frame;
		N_beat_frame++;
	}

	for (size_t i=1;i<N_beat;i++)
	{
		beat_frame=ceil(beat_times[i]*SR);
		if (beat_frame<N)
		{
			beatSR[N_beat_frame]=beat_frame;
			N_beat_frame++;
		}
		else
		{break;}
	}
	
	beatSR[N_beat_frame]=N;

	double *beatSR_interval_frames=new double[N_beat_frame];
	for (size_t t=0;t<N_beat_frame;t++)
	{	
		beatSR_interval_frames[t]=beatSR[t+1]-beatSR[t];		
	}



	//2.4 Reference power
	long double refPower=pow(10.0,-12.0);
	double log_refPower=10.0*log10(refPower);

	//2.5 A-weighting parameters
	double AP1=pow(12200.0,2.0);
	double AP2=pow(20.6,2.0);
	double AP3=pow(107.7,2.0);
	double AP4=pow(737.9,2.0);

	double *A_offsets= new double[K];
	for (size_t k=0;k<K;k++)
	{
		double frequency_k2=freqK[k]*freqK[k];
		double A_scale=AP1*frequency_k2*frequency_k2/((frequency_k2+AP2)*sqrt((frequency_k2+AP3)*(frequency_k2+AP4))*(frequency_k2+AP1));
		A_offsets[k]=2.0+20.0*log10(A_scale); //Including the offset of the power reference
	}

	

	//2.6 Create the constant Q matrix
	double *CQ = new double[K*N_beat_frame];
	int *CQ_offset = new int[K];
	for (size_t k=0;k<K;k++)
		CQ_offset[k]=k*N_beat_frame;


	//3. Compute the CQ matrix for each point (column) each frequency bin (row)
	int half_win=0;
	int hamming_offset=0;
	int temp_index;
	double temp_CQValue;
	complex<double> tempValue_hamming;

	

	//clock_t start_time, end_time;

	for (size_t k=0; k<K; k++)
	{
//		cerr<<k<<'\n';
//		start_time=clock();
		//Get the constant Q transform
		half_win=ceil(winLenK[k]/2)-1;
		hamming_offset=k*winLenK[0];

		//3.1 Get the signal
		for (size_t i=half_win;i<winLenK[k];i++)
		{
			tempValue_hamming=hammingK[hamming_offset+i];
			temp_index=i-half_win;
			w_in[temp_index][0]=real(tempValue_hamming);
			w_in[temp_index][1]=imag(tempValue_hamming);
		}

		for (size_t i=1;i<=half_win;i++)
		{
			tempValue_hamming=hammingK[hamming_offset+half_win-i];
			temp_index=N_signal-i;
			w_in[temp_index][0]=real(tempValue_hamming);
			w_in[temp_index][1]=imag(tempValue_hamming);
		}

		for (size_t i=winLenK[k]-half_win;i<N_signal-half_win;i++)
		{
			w_in[i][0]=0.0;
			w_in[i][1]=0.0;
		}
		

//		end_time=clock();
//		cerr<<"Prepare time:"<<(double)(end_time-start_time)/CLOCKS_PER_SEC<<'\n';
		
//		start_time=clock();
		fftw_execute(pp);



		//3.2 Convolution
		for (size_t i=0;i<N_signal;i++)
		{
			convol[i][0]=x_fft[i][0]*w_fft[i][0]-x_fft[i][1]*w_fft[i][1];
			convol[i][1]=x_fft[i][0]*w_fft[i][1]+x_fft[i][1]*w_fft[i][0];
		}

		

		//3.3 IFFT
		fftw_execute(p_inv); //Note that the return value is not normalized, should divided by N_signal

		
//		end_time=clock();
//		cerr<<"FFT time:"<<(double)(end_time-start_time)/CLOCKS_PER_SEC<<'\n';

		//3.4 Get the pow spectrum
//		start_time=clock();
		for (size_t i=0;i<N;i++)
		{
			x_in[i]=(w_fft[i][0]*w_fft[i][0]+w_fft[i][1]*w_fft[i][1])/ifft_factor;
		}


		//3.5 Get the beat interval (median)
		temp_index=CQ_offset[k];
	
		for (size_t t=0;t<N_beat_frame;t++)
		{
			//In-line median sort?
			temp_CQValue=math_fun::median(x_in,beatSR[t],beatSR[t+1]-1,beatSR_interval_frames[t]);
			
			//temp_CQValue=0.0;
			//for (size_t i=beatSR[t];i<beatSR[t+1];i++)
			//	temp_CQValue+=x_in[i];
			//temp_CQValue=temp_CQValue/beatSR_interval_frames[t];    //Taking the mean instead of median, same result
			CQ[temp_index+t]=10.0*log10(temp_CQValue)-log_refPower+A_offsets[k];
		}
//		end_time=clock();
//		cerr<<"median function time:"<<(double)(end_time-start_time)/CLOCKS_PER_SEC<<'\n';
	}

	
	fftw_destroy_plan(p_inv);
	fftw_destroy_plan(pp);
	fftw_free(w_in);
	fftw_free(x_fft);
	fftw_free(w_fft);
	fftw_free(convol);
	delete[] x_in;


	//4. Compute the beat sync-ed chromagram (temporary stored in CQ, first 12 rows)
	if (normalizationFlag)
	{
		for (size_t t=0;t<N_beat_frame;t++)
		{
			double maxVal=negInf;
			double minVal=posInf;

			for (size_t i=0;i<bins;i++)
			{
				double tempValue=0.0;
				for (size_t k=i;k<K;k+=bins)
					tempValue+=CQ[CQ_offset[k]+t];

				if (maxVal<tempValue)
					maxVal=tempValue;

				if (minVal>tempValue)
					minVal=tempValue;

				CQ[CQ_offset[i]+t]=tempValue; //Sum over all pitches belonging to one pitch class
			}

			//Normalization
			if (maxVal==minVal)
			{
				for (size_t i=0;i<bins;i++)
				{
					CQ[CQ_offset[i]+t]=0.0;
				}
			}
			else
			{
				for (size_t i=0;i<bins;i++)
				{
					CQ[CQ_offset[i]+t]=(CQ[CQ_offset[i]+t]-minVal)/(maxVal-minVal);
				}
			}
		}
	}
	else
	{
		for (size_t t=0;t<N_beat_frame;t++)
		{
			for (size_t i=0;i<bins;i++)
			{
				double tempValue=0.0;
				for (size_t k=i;k<K;k+=bins)
					tempValue+=CQ[CQ_offset[k]+t];

				CQ[CQ_offset[i]+t]=tempValue; //Sum over all pitches belonging to one pitch class
			}
		}
	}



	int shift_pos=floor(12.0*log(freqK[0]/27.5)/log(2.0)+0.5); //The relative position to A0
	shift_pos=-((shift_pos % bins)-3);						     //Since A0 should shift -3

	for (size_t t=0;t<N_beat_frame;t++)
	{
		size_t chroma_offset=t*bins;
		for (size_t i=0;i<bins;i++)
		{
			size_t shift_offset=(i+shift_pos) % bins;
			chromagram[chroma_offset+i]=CQ[CQ_offset[shift_offset]+t];
		}
	}

	delete[] CQ; //Free space
	
	
	//Return the sample times
	for (size_t t=0;t<N_beat_frame;t++)
	{
		sample_times[2*t]=(double)(beatSR[t])/SR;
		sample_times[2*t+1]=(double)(beatSR[t+1])/SR;
	}

	return N_beat_frame;

}



/******************************************************************************
B. Function (modified version, same performance, short segment on FFT to speed up):
[chromagram (normal_chromagram),sample_times]=cal_CQ_chroma_loudness(x,SR,...
beat_times, hammingK, winLenK, freqK, normalizationFlag)

Main function to compute the loudness based beat-sync (or fixed length) chromagram features

INPUTS:
x - the wave signal (xharmony)
SR - the sample rate 
beat_time - the beat time (unit: second)
hammingK - the hamming windows for each frequency
winLenK - the length of each hamming window k (to retrieval the hamming window)
freqK - the k'th frequency (Computed by .m function: cal_hamming_window)
normalizationFlag - 1. Return normalization chromagram, else un-normalized chromagram.
				    Normalization is: (x-x_min)/(x_max-x_min)

OUTPUTS:
chromagram - the loudness based chromagram features (length Nb+1 x bins)
normal_chromagram - the normalized loudness chromagram features (length Nb+1 x bins)
sample_times - the sample times for each frame, formated as a Nx2 matrix [start_times,end_times]
return value - the length of the chromagram (in case that the beat times exceed the length of harmony)
******************************************************************************/

int LBC::cal_LBC(const double *xharmony, const int N, const int SR, const double *beat_times, const int N_beat, const complex<double>* hammingK, const double* winLenK,const double* freqK,const int K, double *const sample_times, double *const chromagram, const size_t N_block, const bool normalizationFlag)
{
	//1. Check parameters
	if (SR<0 || !hammingK || !winLenK || !freqK || K<1)
	{
		cerr<<"Error in function cal_LBC (FE_package.cpp): parameters error."<<'\n';
		return -1;
	}

	if (!xharmony || !beat_times || N<1 || N_beat<1)
	{
		cerr<<"Error in function cal_LBC (FE_package.cpp): the size of the input is 0."<<'\n';
		return -1;
	}

	if (!sample_times || !chromagram)
	{
		cerr<<"Error in function cal_LBC (FE_package.cpp): can not write the output chromagram."<<'\n';
		return -1;
	}

	//Special check: if the hamming window is longer than the signal, return error!
	for (size_t k=0;k<K;k++)
	{
		if (winLenK[k]>N)
		{
			cerr<<"Warning (regarded as error) in function cal_LBC (FE_package.cpp): certain hamming window is longer than the music itself, check the frequency parameters."<<'\n';
			return -1;
		}
	}


	//2. Parameters
	size_t bins=12;
	double cut_off=pow(10.0,-30);

	//2.0 Pad the signal
	size_t Left_extend=winLenK[0]-ceil(winLenK[0]/2)+1;
	size_t xt_len=Left_extend+N+N_block;
	double *xt=new double[xt_len];
	double *x_out=new double[N];

	for (size_t i=0;i<Left_extend;i++)
		xt[i]=0.0;

	for (size_t i=0;i<N;i++)
		xt[i+Left_extend]=xharmony[i];

	for (size_t i=Left_extend+N;i<xt_len;i++)
		xt[i]=0.0;

	

	//2.1 Get the beat-time interval (in frames)
	int *beatSR = new int[N_beat+2];
	size_t N_beat_frame=1;  //N_beat_frame=#items in beatSR -1 (#columns of CQ)
	beatSR[0]=0;
	int beat_frame=ceil(beat_times[0]*SR);
	if (beat_frame>0)
	{
		beatSR[N_beat_frame]=beat_frame;
		N_beat_frame++;
	}

	for (size_t i=1;i<N_beat;i++)
	{
		beat_frame=ceil(beat_times[i]*SR);
		if (beat_frame<N)
		{
			beatSR[N_beat_frame]=beat_frame;
			N_beat_frame++;
		}
		else
		{break;}
	}
	
	beatSR[N_beat_frame]=N;

	double *beatSR_interval_frames=new double[N_beat_frame];
	for (size_t t=0;t<N_beat_frame;t++)
	{	
		beatSR_interval_frames[t]=beatSR[t+1]-beatSR[t];		
	}

	

	int N_signal=N;
	if (N_signal & (N_signal))
	{
		int temp_index=N_signal;
		int targetlevel = 0;
		while (temp_index >>= 1) ++targetlevel;
		N_signal=pow(2.0,targetlevel+1);
	}

	//2.2 Get FFT of the signal
	size_t half_Nblock=N_block/2;
	long double ifft_factor=(double)(N_block)*N_block;
	double *x_in=new double[N_block]; //Store the signal of x
	
	fftw_complex *x_fft, *w_in, *w_fft, *convol, *convol_out;
	fftw_plan px, pw, p_inv;
	
	w_in = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * N_block);
	x_fft = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * N_block);
	w_fft = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * N_block);
	convol = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * N_block);
	convol_out = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * N_block);


	px = fftw_plan_dft_r2c_1d(N_block,x_in,x_fft,FFTW_MEASURE); //Only create the plan once
	p_inv = fftw_plan_dft_1d(N_block,convol,convol_out,FFTW_BACKWARD,FFTW_MEASURE);
	pw = fftw_plan_dft_1d(N_block, w_in, w_fft, FFTW_FORWARD, FFTW_MEASURE);

	//Each time Update the FFTW precomplie plan, could be slow at the first run (10-20 sec)
	FILE* pfile=fopen("./model/fftw_wisdom_MEASURE_precompile_plan","w");
	fftw_export_wisdom_to_file(pfile);
	fclose(pfile);
	


	//2.3 Reference power
	long double refPower=pow(10.0,-12.0);
	double log_refPower=10.0*log10(refPower);

	//2.4 A-weighting parameters
	double AP1=pow(12200.0,2.0);
	double AP2=pow(20.6,2.0);
	double AP3=pow(107.7,2.0);
	double AP4=pow(737.9,2.0);

	double *A_offsets= new double[K];
	for (size_t k=0;k<K;k++)
	{
		double frequency_k2=freqK[k]*freqK[k];
		double A_scale=AP1*frequency_k2*frequency_k2/((frequency_k2+AP2)*sqrt((frequency_k2+AP3)*(frequency_k2+AP4))*(frequency_k2+AP1));
		A_offsets[k]=2.0+20.0*log10(A_scale); //Including the offset of the power reference
	}

	

	//2.5 Create the constant Q matrix
	double *CQ = new double[K*N_beat_frame];
	int *CQ_offset = new int[K];
	for (size_t k=0;k<K;k++)
		CQ_offset[k]=k*N_beat_frame;


	//3. Compute the CQ matrix for each point (column) each frequency bin (row)
	int half_win=0;
	int hamming_offset=0;
	int hop_len=0;
	int left_pos;
	int temp_index;
	int temp_left_bound;
	double temp_CQValue;
	complex<double> tempValue_hamming;

	

//	clock_t start_time, end_time;

	for (size_t k=0; k<K; k++)
	{
		//Initialization of x_out
		for (size_t i=0;i<N;i++)
			x_out[i]=0.0;


//		cerr<<k<<'\n';
//		start_time=clock();
		//Get the constant Q transform
		half_win=ceil(winLenK[k]/2)-1;
		hamming_offset=k*winLenK[0];
		hop_len=N_block-winLenK[k];

		//3.1 Get the w signal
		for (size_t i=half_win;i<winLenK[k];i++)
		{
			tempValue_hamming=hammingK[hamming_offset+i];
			temp_index=i-half_win;
			w_in[temp_index][0]=real(tempValue_hamming);
			w_in[temp_index][1]=imag(tempValue_hamming);
		}

		for (size_t i=1;i<=half_win;i++)
		{
			tempValue_hamming=hammingK[hamming_offset+half_win-i];
			temp_index=N_block-i;
			w_in[temp_index][0]=real(tempValue_hamming);
			w_in[temp_index][1]=imag(tempValue_hamming);
		}

		for (size_t i=winLenK[k]-half_win;i<N_block-half_win;i++)
		{
			w_in[i][0]=0.0;
			w_in[i][1]=0.0;
		}


	/*
		ofstream ccFile("test_win_out.txt",ios::out);
	
		for (size_t i=0;i<N_block;i++)
			ccFile<<w_in[i][0]<<' '<<w_in[i][1]<<'\n';
		ccFile.close();
	*/
		

//		end_time=clock();
//		cerr<<"Prepare time:"<<(double)(end_time-start_time)/CLOCKS_PER_SEC<<'\n';		
//		start_time=clock();
		
		
		fftw_execute(pw);

		/*
		ofstream cFile("test_wfft_out.txt",ios::out);
	
		for (size_t i=0;i<N_block;i++)
			cFile<<w_fft[i][0]<<' '<<w_fft[i][1]<<'\n';
		cFile.close();
		*/


		//3.2 For each block, get the convolution and compute the power spectrum
		temp_left_bound=winLenK[k]-ceil(winLenK[k]/2)+1;
		for (size_t h=0;h<N+1;h+=hop_len)
		{
			left_pos=h+Left_extend-temp_left_bound;
			for (size_t hh=0;hh<N_block;hh++)
				x_in[hh]=xt[hh+left_pos];

			fftw_execute(px);


			for (size_t hh=1;hh<half_Nblock;hh++)
			{
				x_fft[N_block-hh][1]=-x_fft[hh][1];
				x_fft[N_block-hh][0]=x_fft[hh][0];
			}	

			//Convolution signal
			for (size_t hh=0;hh<N_block;hh++)
			{
				convol[hh][0]=x_fft[hh][0]*w_fft[hh][0]-x_fft[hh][1]*w_fft[hh][1];
				convol[hh][1]=x_fft[hh][0]*w_fft[hh][1]+x_fft[hh][1]*w_fft[hh][0];
			}

			//Get ifft of convolution and compute the pow spectrum
			fftw_execute(p_inv); //Note that the return value is not normalized, should divided by N_signal

			temp_index=temp_left_bound;
			for (size_t hh=h;hh<mymin(h+hop_len,N);hh++)
			{
				x_out[hh]=(convol_out[temp_index][0]*convol_out[temp_index][0]+convol_out[temp_index][1]*convol_out[temp_index][1])/ifft_factor;
				temp_index++;
			}
		}

		
		/*
		ofstream chromaFile("test_x_out.txt",ios::out);
	
		for (size_t i=0;i<N;i++)
			chromaFile<<x_out[i]<<' ';
		chromaFile<<'\n';
		chromaFile.close();
		*/
		
//		end_time=clock();
//		cerr<<"FFT time:"<<(double)(end_time-start_time)/CLOCKS_PER_SEC<<'\n';
//		start_time=clock();

		
		
		//3.3 Get the beat interval (median) and compensate with A-weighting
		temp_index=CQ_offset[k];
	
		for (size_t t=0;t<N_beat_frame;t++)
		{
			//In-line median sort
			temp_CQValue=mymax(cut_off,math_fun::median(x_out,beatSR[t],beatSR[t+1]-1,beatSR_interval_frames[t]));
			
			//temp_CQValue=0.0;
			//for (size_t i=beatSR[t];i<beatSR[t+1];i++)
			//	temp_CQValue+=x_out[i];
			//temp_CQValue=max(cut_off,temp_CQValue/beatSR_interval_frames[t]);    //Taking the mean instead of median, same result
			CQ[temp_index+t]=10.0*log10(temp_CQValue)-log_refPower+A_offsets[k];
		}


//		end_time=clock();
//		cerr<<"median function time:"<<(double)(end_time-start_time)/CLOCKS_PER_SEC<<'\n';
	}

	
	fftw_destroy_plan(p_inv);
	fftw_destroy_plan(pw);
	fftw_destroy_plan(px);
	fftw_free(w_in);
	fftw_free(x_fft);
	fftw_free(w_fft);
	fftw_free(convol);
	fftw_free(convol_out);
	delete[] x_in;
	delete[] x_out;
	delete[] xt;


	//4. Compute the beat sync-ed chromagram (temporary stored in CQ, first 12 rows)
	if (normalizationFlag)
	{
		for (size_t t=0;t<N_beat_frame;t++)
		{
			double maxVal=negInf;
			double minVal=posInf;

			for (size_t i=0;i<bins;i++)
			{
				double tempValue=0.0;
				for (size_t k=i;k<K;k+=bins)
					tempValue+=CQ[CQ_offset[k]+t];

				if (maxVal<tempValue)
					maxVal=tempValue;

				if (minVal>tempValue)
					minVal=tempValue;

				CQ[CQ_offset[i]+t]=tempValue; //Sum over all pitches belonging to one pitch class
			}

			//Normalization
			if (maxVal==minVal)
			{
				for (size_t i=0;i<bins;i++)
				{
					CQ[CQ_offset[i]+t]=0.0;
				}
			}
			else
			{
				for (size_t i=0;i<bins;i++)
				{
					CQ[CQ_offset[i]+t]=(CQ[CQ_offset[i]+t]-minVal)/(maxVal-minVal);
				}
			}
		}
	}
	else
	{
		for (size_t t=0;t<N_beat_frame;t++)
		{
			for (size_t i=0;i<bins;i++)
			{
				double tempValue=0.0;
				for (size_t k=i;k<K;k+=bins)
					tempValue+=CQ[CQ_offset[k]+t];

				CQ[CQ_offset[i]+t]=tempValue; //Sum over all pitches belonging to one pitch class
			}
		}
	}



	int shift_pos=floor(12.0*log(freqK[0]/27.5)/log(2.0)+0.5); //The relative position to A0
	shift_pos=-((shift_pos % bins)-3);						     //Since A0 should shift -3

	for (size_t t=0;t<N_beat_frame;t++)
	{
		size_t chroma_offset=t*bins;
		for (size_t i=0;i<bins;i++)
		{
			size_t shift_offset=(i+shift_pos) % bins;
			chromagram[chroma_offset+i]=CQ[CQ_offset[shift_offset]+t];
		}
	}

	delete[] CQ; //Free space
	
	
	//Return the sample times
	for (size_t t=0;t<N_beat_frame;t++)
	{
		sample_times[2*t]=(double)(beatSR[t])/SR;
		sample_times[2*t+1]=(double)(beatSR[t+1])/SR;
	}

	return N_beat_frame;

}




/*************************************************************************************
-----------------------------------EVIL SEPARATION LINE--------------------------------
**************************************************************************************/

/*
1. Zeroth order Modified Bessel function (used in Kaiser window)
*/

double FIR_resampler::io(const double x)
{
	double tol=1e-8;
	double y=0.5*x;
	double e=1.0;
	double de=1.0;
	double sde=0.0;

	for (size_t i=1;i<26;i++)
	{
		de=de*y/((double)(i));
		sde=de*de;
		e+=sde;
		if ((e*tol-sde)>0)
			break;
	}

	return e;
}

/*
2. Creation of the Kaiser window
See:
http://www.koders.com/cpp/fidB2F0E1A286DEA96ED5E585749F91947312458C35.aspx?s=ifft

http://en.wikipedia.org/wiki/Kaiser_window
Corrected according to matlab function kaiser()
*/

void FIR_resampler::kaiser_window(const size_t n, const double beta, double *const k_win)
{
	//1. Initialization
	double bes = 1.0/io(beta);
	double odd=n%2;
	double xind=((double)(n)-1.0)*((double)(n)-1.0);
	size_t nw=floor(((double)(n)+1.0)/2);

	double *k_temp= new double[nw];
	double xi;
	for (size_t i=0;i<nw;i++)
	{
		if (odd) xi=(double)(i);
		else xi=0.5+i;

		xi=4.0*xi*xi;

		k_temp[i]=io(beta*sqrt(1.0-xi/xind))*bes;

	}

	//2. Creating the Kaiser window
	for (size_t i=0;i<nw-1;i++)
	{
		k_win[i]=k_temp[nw-i-1];
	}

	for (size_t i=0;i<nw;i++)
	{
		k_win[i+nw-1]=k_temp[i];
	}

	delete[] k_temp;
}



/*
3. sinc function:
*/
double FIR_resampler::sinc(const double x)
{
    if (x==0.0)
        return 1.0;
    return sin(M_PI*x)/(M_PI*x);
} 


/*
4. Type I/II FIR filter (according to MATLAB function firls()
See: firls() in MATLAB

The return filter coefficient h will be in length N+1
*/

void FIR_resampler::fir_filter_least_square(const size_t N, double F[], double M[], size_t Nf, double *const filter)
{
	//1. Parameters:
	size_t Nw=Nf/2;
//	double *W=new double[Nw];
	size_t N_filter=N+1;

	for (size_t i=0;i<Nf;i++)
	{
		F[i]=F[i]/2;
	}

//	for (size_t i=0;i<Nw;i++)
//		W[i]=1.0;

	size_t L=(N_filter-1)/2;
	double Nodd=N_filter%2; //Whether odd (type II) or even (type I)

	//2. Process: basic vectors are cos(2*pi*m*f) see m below
	size_t Nb=L+1;
	double *m = new double[Nb];
	double *k = new double[Nb];
	double *b= new double[Nb];
	double b0;  //First entry must be handled separately (where k(1)=0) for type I FIR

	if (Nodd)
	{
		for (size_t i=0;i<=L;i++)
			m[i]=(double)(i);

		b0=0.0;

		for (size_t i=0;i<=L;i++)
		{
			k[i]=m[i];
			b[i]=0.0;
		}
	}
	else
	{
		for (size_t i=0;i<=L;i++)
			m[i]=0.5+i;

		for (size_t i=0;i<=L;i++)
		{
			k[i]=m[i];
			b[i]=0.0;
		}
	}

	//Update the b vector
	double slope;
	double y_intercept;
	double pipi=4*M_PI*M_PI;

	for (size_t s=0;s<Nf;s+=2)
	{
		slope=(M[s+1]-M[s])/(F[s+1]-F[s]);  //slope
		y_intercept=M[s]-slope*F[s];        //y-intercept

		if (Nodd)
		{
			b0+=(y_intercept*(F[s+1]-F[s])+0.5*slope*(F[s+1]*F[s+1]-F[s]*F[s]));//*abs(W[s/2]*W[(s/2]);
			for (size_t i=1;i<=L;i++)
			{
				b[i]+=(slope/pipi*(cos(2*M_PI*k[i]*F[s+1])-cos(2*M_PI*k[i]*F[s]))/(k[i]*k[i]));//*abs(W[s/2]*W[(s/2]);
				b[i]+=(F[s+1]*(slope*F[s+1]+y_intercept)*sinc(2*k[i]*F[s+1])-F[s]*(slope*F[s]+y_intercept)*sinc(2*k[i]*F[s]));//*abs(W[s/2]*W[(s/2]);
			}
		}
		else
		{
			for (size_t i=0;i<=L;i++)
			{
				b[i]+=(slope/pipi*(cos(2*M_PI*k[i]*F[s+1])-cos(2*M_PI*k[i]*F[s])/(k[i]*k[i])));//*abs(W[s/2]*W[(s/2]);
				b[i]+=(F[s+1]*(slope*F[s+1]+y_intercept)*sinc(2*k[i]*F[s+1])-F[s]*(slope*F[s]+y_intercept)*sinc(2*k[i]*F[s]));//*abs(W[s/2]*W[(s/2]);
			}
		}

	}

	if (Nodd)
		b[0]=b0;

	//3. Get the output
	for (size_t i=0;i<=L;i++)
		b[i]=4.0*b[i];//*W[0]*W[0];

	if (Nodd)
		b[0]=b[0]/2;

	if (Nodd)
	{
		for (size_t i=0;i<L;i++)
			filter[i]=0.5*b[L-i];
		filter[L]=b[0];
		for (size_t i=L+1;i<N_filter;i++)
			filter[i]=0.5*b[i-L];
	}
	else
	{
		for (size_t i=0;i<=L;i++)
			filter[i]=0.5*b[L-i];

		for (size_t i=L+1;i<N_filter;i++)
			filter[i]=0.5*b[i-L];
	}

	delete[] m;
	delete[] k;
	delete[] b;
	
}



/*
5. Resampling function:
RESAMPLE  Change the sampling rate of a signal.
Y = RESAMPLE(X,P,Q) resamples the sequence in vector X at P/Q times
the original sample rate using a polyphase implementation.  Y is P/Q 
times the length of X (or the ceiling of this if P/Q is not an integer).  
P and Q must be positive integers.

RESAMPLE applies an anti-aliasing (lowpass) FIR filter to X during the 
resampling process, and compensates for the filter's delay.  The filter 
is designed using FIR (least square version).

Remark: this is a function mimic resample.m in MATLAB
*/

bool FIR_resampler::resample(double *const signal, const size_t N, const double SR_in, const double SR_out, double *const sample_signal)
{

	//1. Check the parameters
	if (!signal || N<1)
	{
		cerr<<"Error in function resampler (FE_package.cpp): the size of the input signal is 0\n";
		return false;
	}
	

	if (!sample_signal)
	{
		cerr<<"Error in function resampler (FE_package.cpp): can not write the output space.\n";
		return false;
	}

	
	//2. Parameters
	//vector<double> pq = math_fun::dec2frac(SR_in/SR_out,1e-10);
	//double p = pq[0];  //The numerator
	//double q = pq[1];  //The denominator
	double p=SR_out;      //convert it outside the function
	double q=SR_in;       //convert it outside the function
	double pqmax=mymax(p,q);

	//If it is obvious case, just copy the signal
	if (p==1.0 && q==1.0)
	{
		for (size_t i=0;i<N;i++)
			sample_signal[i]=signal[i];

		return true;
	}

	//FIR filter parameter
	size_t Nexample=10; //Default
	double fc=0.5/pqmax;
	double F[]={0.0, 2.0*fc,2.0*fc,1.0}; //1.0 1 corresponds to the Nyquist frequency or half the sampling frequency.
	double M[]={1.0,1.0,0.0,0.0};        //Amplitude of those frequency

	size_t h_size=2*Nexample*pqmax+1;


	
	//3. Creating the FIR filter (coefficients)
	double *h_coeff = new double[h_size];

	//3.1 Kaiser window
	double beta=5.0;    //Parameters for Kaiser window
	double *k_win=new double[h_size];
	FIR_resampler::kaiser_window(h_size,beta,k_win);

	//3.2 The FIR least square
	FIR_resampler::fir_filter_least_square(h_size-1,F,M,4,h_coeff);
	
	//3.3 Multiply the Kaiser window
	for (size_t i=0;i<h_size;i++)
		h_coeff[i]=p*h_coeff[i]*k_win[i];



	//4. Compute the delay of the signal (in downsampling by q hits center tap of filter.
	size_t output_len=ceil(p/q*N);

	size_t h_half=(h_size-1)/2;

	size_t nz=floor(q-h_half%((int)(q)));

	Nexample=h_size;  //retain h_size for further use
	h_half+=nz;		 //increase filter in the front 
	h_size+=nz;

	//4.1 Number of samples removed from beginning of output sequence to compensate for delay of linear phase filter:
	size_t delay = floor(ceil((double)(h_half))/q);

	//Need to zero-pad so output length is exactly ceil(N*p/q)
	size_t nz1=0;
	

	while (ceil(((N-1)*p+h_size+nz1)/q)-delay<output_len)
		nz1++;

	//4.2 0-padding the h-coefficient at the beginning and the end
	h_size+=nz1;

	double *h_final=new double[h_size];
	for (size_t i=0;i<nz;i++)
		h_final[i]=0.0;

	for (size_t i=0;i<Nexample;i++)
		h_final[i+nz]=h_coeff[i];

	for (size_t i=Nexample+nz;i<h_size;i++)
		h_final[i]=0.0;

	
	//5. Main process, do the sampling
	//Up-sampling by p and then downsampling by q
	vector<double> y;
    upfirdn(p, q,signal,N,h_final, h_size, y);


	//6. Fill the output space
	for (size_t i=0;i<output_len;i++)
	{
		sample_signal[i]=y[i+delay];
	}	



	delete[] h_final;
	delete[] k_win;

	return true;
}



