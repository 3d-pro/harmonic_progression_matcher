
#include "beat_tracker.h"
#include "vector_template.cpp"


#include <fstream>
using std::ofstream;

using std::cerr;

/******************************************************************************
A. Function:
beat_strength = calculate_beat_strength(d,N,SR,win_len,hop_len,mel_channels)
Calculate the beat strength through an audio piece, which can be fed into
beatestimate() to estimate beat position.

Inputs:
d - the wav signal.
N - the length of the signal.
SR - the sampling rate (to compute the frequency).
win_len - the window length of the hanning window.
hop_len - the hop length.
mel_channels - Number of Mel bands to use (default 40, not a parameter here).

Output:
xharmony - the harmonic component.
******************************************************************************/
bool beat_tracker::calculate_beat_strength(double const *signal, const int N, const int SR,const int win_len, const int hop_len,double *const beatStrength)
{
	//1. Check parameters
	if (!signal || N<1)
	{
		cerr<<"Error in function calculate_beat_strength (FE_package.cpp): the signal size is 0."<<'\n';
		return false;
	}

	if (win_len<0 || SR<0 || hop_len<1)
	{
		cerr<<"Error in function calculate_beat_strength (FE_package.cpp): the prameters are not correct."<<'\n';
		return false;
	}

	if (!beatStrength)
	{
		cerr<<"Error in calculate_beat_strength (FE_package.cpp): can not write the output signal."<<'\n';
		return false;
	}


	//2. Get the spectrogram of the signal (fft_len is win_len)
	size_t sp_row=1+floor((double)(N-win_len)/hop_len);
	size_t sp_column=1+win_len/2;
	double* SP=new double[sp_row*sp_column];
	bool success_flag=audio_preprocessing::spectrogram(signal,N,win_len,win_len,hop_len,SP,sp_row,sp_column);

	if (!success_flag)
	{
		cerr<<"Error in function calculate_beat_strength: spectrogram error.\n";
		return false;
	}

	//Get the abs(SP)
	for (int i=0;i<sp_row;i++)
	{
		size_t SP_offset=i*sp_column;
		for (int j=0;j<sp_column;j++)
			SP[SP_offset+j]=sqrt(SP[SP_offset+j]);
	}


	//3. Get the Mel weights
	int mel_channels=40;
	double mel_width=1.0;
	double minfrq=0.0;
	double maxfrq=SR/2.0; //Use the Nyquist
	bool htkmel=0;        //HZ/MEL convert function method

	//3.1 Initialise weights
	double *wts = new double[mel_channels*win_len];

	//3.2 Get the normal fft frequencies (sampling by SR)
	double *fftfrqs=new double[sp_column];
	double freq_factor=(double)(SR)/win_len;
	for (int i=0;i<sp_column;i++)
	{
		fftfrqs[i]=freq_factor*i;
	}


	//3.3 Get the centers of the Mel frequencies
	double minmel_channels = audio_preprocessing::hz2mel(minfrq,htkmel);
	double maxmel = audio_preprocessing::hz2mel(maxfrq,htkmel);
	double mel_factor=(maxmel-minmel_channels)/(mel_channels+1);

	//binfrqs are the nearest fft frequencies to the mel frequencies
	size_t num_bins=mel_channels+2;
	double *tempMels=new double[num_bins];
	double *binfrqs = new double[num_bins];
	

	for (int i=0;i<num_bins;i++)
	{
		tempMels[i]=minmel_channels+mel_factor*i;
	}

	success_flag=audio_preprocessing::mel2hz(tempMels, binfrqs, num_bins, htkmel);



	if (!success_flag)
	{
		cerr<<"Error in function calculate_beat_strength: mel2hz error.\n";
		return false;
	}

	delete[] tempMels; //delete the pointer


	//3.4 Work out weights
	for (int i=0;i<mel_channels;i++)
	{
		size_t wts_offset=i*win_len;
		for (int j=0;j<win_len;j++)
		{
			//Initialize the weights
			wts[j+wts_offset]=0.0;
		}
	}


	//temp frequency bins
	double *fs = new double[3]; 
	for (int i=0;i<mel_channels;i++)
	{
		size_t wts_offset=i*win_len;
		double slaney_factor=2.0/(binfrqs[2+i]-binfrqs[i]);
		//temp fs, 3 bins, scale by mel_width
		for (int j=0;j<3;j++)
		{
			fs[j]=binfrqs[i+j];
		}

		double tempFS=fs[1];

		for (int j=0;j<3;j++)
		{
			fs[j]=tempFS+mel_width*(fs[j]-tempFS);
		}

		
		double lower_factor=fs[1]-fs[0];
		double upper_factor=fs[2]-fs[1];
		//lower and upper slopers for all bins
		for (int j=0;j<sp_column;j++)
		{
			double loslope=(fftfrqs[j]-fs[0])/lower_factor;
			double hislope=(fs[2]-fftfrqs[j])/upper_factor;

			//wts[wts_offset+j]=slaney_factor*max<double>::max_two(0.0,min<double>::min_two(loslope,hislope));
			wts[wts_offset+j]=slaney_factor*mymax(0.0,mymin(loslope,hislope));
		}	
	}

	delete[] fs;


	//4. Use the weights to conver the fft scale to mel scale
	
	double *D_mel = new double[sp_row*mel_channels];
	double maxDB=negInf;
	for (int i=0;i<sp_row;i++)
	{
		size_t mel_offset=i*mel_channels;
		size_t SP_offset=i*sp_column;
		for (int j=0;j<mel_channels;j++)
		{
			double tempValue=0.0;
			size_t wts_offset=j*win_len;
			for (int k=0;k<sp_column;k++)
			{
				tempValue+=wts[wts_offset+k]*SP[SP_offset+k];
			}

			//Post-process 1. Take the non numerically 0 part
			//tempValue=max<double>::max_two(0.0000000001,tempValue);
			tempValue=mymax(0.0000000001,tempValue);

			//Post-process 2. Conver to dB
			tempValue=20*log10(tempValue);
			D_mel[mel_offset+j]=tempValue;
			if (tempValue>maxDB)
				maxDB=tempValue;
		}
	}

	delete[] SP;

	

	//5. Only look at top 80 dB
	double trimmed_factor=maxDB-80.0;

	for (int i=0;i<sp_row;i++)
	{
		size_t mel_offset=i*mel_channels;
		for (int j=0;j<mel_channels;j++)
		{
			//D_mel[mel_offset+j]=max<double>::max_two(D_mel[mel_offset+j],trimmed_factor);
			D_mel[mel_offset+j]=mymax(D_mel[mel_offset+j],trimmed_factor);
		}
	}

	
	//6. Take (mean) first difference
	double *D_diff = new double[sp_row-1];
	for (int i=0;i<sp_row-1;i++)
	{
		size_t mel_offset_low=i*mel_channels;
		size_t mel_offset_up=mel_offset_low+mel_channels;
		double tempValue=0.0;
		for (int j=0;j<mel_channels;j++)
		{
			//Use non-zero part
			//tempValue+=max<double>::max_two(0.0,D_mel[mel_offset_up+j]-D_mel[mel_offset_low+j]);
			tempValue+=mymax(0.0,D_mel[mel_offset_up+j]-D_mel[mel_offset_low+j]);
		}
		D_diff[i]=tempValue/mel_channels;
	}

	

	//7. Filter with a simple window
	double *b = new double[2];
	b[0]=1.0;
	b[1]=-1.0;
	double *a = new double[2];
	a[0]=1.0;
	a[1]=-0.99;
	math_fun::filter(b,2,a,2,D_diff,sp_row-1,beatStrength);
	

	//Release the memory
	delete[] D_diff;
	delete[] D_mel;

	return true;
}



/******************************************************************************
B. Function:
beat_times = beatestimate(beatStrength,N,SR,hop_len,startbpm,beat_tightness)
Estimate the beat times from the beat strengths.

Inputs:
beatStrength - the strengh of the beat time by stft (return by function calculate_beat_strength)
N - the length of the beat strength
SR - the sampling rate
hop_len - the hop length
startbpm - the start point of the search (default 120, not a parameter here)
beat_tightness - how tightly to stick to the startbpm (default 3, not a parameter here)

Output:
xharmony - the harmonic component.
******************************************************************************/
vector<double> beat_tracker::beatestimate(double const *beatStrength, const int N, const int SR,const int hop_len)
{
	//1. Check parameters
	if (!beatStrength || N<1)
	{
		cerr<<"Error in function cbeatestimate (FE_package.cpp): the signal size is 0."<<'\n';
		return vector<double>(1,negInf);
	}

	if (SR<0 || hop_len<1)
	{
		cerr<<"Error in function beatestimate (FE_package.cpp): the prameters are not correct."<<'\n';
		return vector<double>(1,negInf);
	}


	//2. Parameter settings
	double startbpm = 120.0;
	double beat_tightness = 3.0;

	//Find rough global period (empirically 0s-90s)
	double duration_time=90.0;   //in seconds
	double upper_time_zone=90.0; //in seconds
	double bpm_std=0.7;          //the variance of the bpm window
	double alpha=0.8;            //a update weight for forward loop (part 5).

	//Sample rate for specgram frames (due to the hop_length)
	double fftres=(double)(SR)/hop_len;

	//Get the lower bound and upper bound in the beat strength vector
	//int maxcol=min<int>::min_two(floor(upper_time_zone*fftres+0.5),N);
	//int mincol=max<int>::max_two(1,maxcol-floor(duration_time*fftres+0.5));
	int maxcol=mymin(floor(upper_time_zone*fftres+0.5),N);
	int mincol=mymax(1,maxcol-floor(duration_time*fftres+0.5));
	maxcol--; //index start from 0 to maxcol-1
	mincol--; //index start from 0 to mincol-1

	//Use auto-correlation out of 4 seconds (empirically setting)
	size_t acmax = floor(4.0*fftres+0.5);
	size_t Nsignal_segment=maxcol-mincol+1;
	double *signal_segment= new double[Nsignal_segment];
	double *xcr= new double[2*acmax+1];
	for (int i=mincol;i<=maxcol;i++)
	{
		signal_segment[i]=beatStrength[i];
	}

	bool successFlag=audio_preprocessing::xcorr(signal_segment, Nsignal_segment, signal_segment, Nsignal_segment, xcr, acmax);

	if (!successFlag)
	{
		cerr<<"Error in function beatestimate: xcorr error!\n";
		return vector<double>(1,negInf);
	}


	//Find local max in the global auto-correlation
	size_t x_window_len=acmax+1;
	double *rawxcr=new double[x_window_len];
	double *xcrwin=new double[x_window_len];
	for (int i=0;i<=acmax;i++)
	{
		//The right side of correlation part
		rawxcr[i]=xcr[i+acmax]; 
	}


	//Create a hamming like window around default bpm
	double bpm_factor=60.0*fftres;
	for (int i=0;i<=acmax;i++)
	{
		double bpms=bpm_factor/(0.1+i);
		bpms = log(bpms/startbpm)/log(2.0)*bpm_std;
		xcrwin[i]=exp(-0.5*bpms*bpms);
	}

	//The weighted auto-correlation
	for (int i=0;i<=acmax;i++)
	{
		xcrwin[i]=xcrwin[i]*rawxcr[i];
	}


	//Get the local max (the picks)
	bool *xpks = new bool[x_window_len];
	successFlag=math_fun::localmax(xcrwin, xpks, x_window_len);

	if (!successFlag)
	{
		cerr<<"Error in function beatestimate: localmax error!\n";
		return vector<double>(1,negInf);
	}

	//Not include any peaks in first down slope (before goes below 0 from the first time)
	for (int i=0;i<=acmax;i++)
	{
		if (xcrwin[i]<0)
			xpks[i]=0;
		else
			break;
	}

	//Largest local max away from 0
	double maxpk=negInf;
	for (int i=0;i<=acmax;i++)
	{
		if (xpks[i] && maxpk<xcrwin[i])
			maxpk=xcrwin[i];
	}

	//Find the position of the first largest peak
	int startpd=0;
	for (int i=0;i<=acmax;i++)
	{
		if (xpks[i] && xcrwin[i]==maxpk)
		{
			startpd=i;
			break;
		}
	}

	//Choose beat peak out of .33, .5, 2 3 x this period
	double candpds[4] ={0.33,0.5,2.0,3.0};
	double max_candPeaks=negInf;
	int startpd2=-1;
	for (int i=0;i<4;i++)
	{
		size_t candidatePos=floor(candpds[i]*startpd+0.5);
		if (candidatePos<=acmax)
		{
			if (max_candPeaks<xcrwin[candidatePos])
			{
				max_candPeaks=xcrwin[candidatePos];
				startpd2=candidatePos;
			}
		}
	}

	//Always use the faster one
	//startpd=min<int>::min_two(startpd,startpd2); 
	startpd=mymin(startpd,startpd2); 
	startbpm=(60.0*fftres)/startpd;


	delete[] xpks;
	delete[] xcrwin;
	delete[] rawxcr;
	delete[] xcr;
	delete[] signal_segment;


	//3. Smooth the beat strength

	//Gaussian window
	size_t Gaussian_window_len=2*startpd+1;
	double Gaussian_factor=(double)(startpd)/32.0;
	double *templt= new double[Gaussian_window_len];

	for (int i=-startpd;i<=startpd;i++)
	{
		double tempValue=(double)(i)/Gaussian_factor;
		templt[i+startpd]=exp(-0.5*tempValue*tempValue);
	}


	size_t localscore_len=N+Gaussian_window_len-1;

	double *temp_localscore =new double[localscore_len];

	// Avoid using FFTW convolution, seems error on implus signal?
/*
	successFlag= audio_preprocessing::convolution(templt, Gaussian_window_len, beatStrength, N, temp_localscore);

	if (!successFlag)
	{
		cerr<<"Error in function beatestimate: convolution error!\n";
		return vector<double>(1,negInf);
	}
	*/



	//Real-data convolution (N^2 computation complexity)
	for (int i=0;i<localscore_len;i++)
	{
		double tempValue=0.0;
		for (int j=0;j<Gaussian_window_len;j++)
		{
			if (i>=j && i-j<N)
				tempValue+=templt[j]*beatStrength[i-j];
		}
		temp_localscore[i]=tempValue;
	}
	


	double *localscore=new double[N];
	localscore_len = floor(0.5+(double)(Gaussian_window_len)/2);
	for (int i=0;i<N;i++)
		localscore[i]=temp_localscore[i+localscore_len];

	
	vector<double> max_local_score_location = max<double>::max_list(localscore,N);

	delete[] templt;
	delete[] temp_localscore;

	//4. Initialziation
	double *backlink = new double[N];
	double *cumscore = new double[N];

	for (int i=0;i<N;i++)
	{
		backlink[i]=0.0;
		cumscore[i]=0.0;
	}

	//Search range for previous beat. Prange is the number of samples to look back and forward
	int lowerBound=-floor(2.0*startpd+0.5);
	int upperBound=-floor(0.5*startpd+0.5);
	size_t prange_len=upperBound-lowerBound+1;


	int *prange= new int[prange_len];

	for (int i=lowerBound;i<=upperBound;i++)
		prange[i-lowerBound]=i;

	//Make a score window, which begins biased towards 120bpm and skewed.
	double *txwt = new double[prange_len];
	for (size_t i=0;i<prange_len;i++)
	{
		double tempValue=beat_tightness*log(-(double)(prange[i])/startpd);
		txwt[i]=exp(-0.5*tempValue*tempValue);
	}


	//Starting is 1 for periods of (near) silence.
	bool starting =true; 

	//5. Forwards step
	//Main forward loop. Go through each window, padding zeros backwards if
	//needed, and add the cumulative score to the prior (txwt).

	double *scorecands = new double[prange_len];
	double max_local_score_factor=0.01*max_local_score_location[0];

	for (int i=0;i<N;i++)
	{
		//Are we reaching back before time 0?
		int zpad = min<int>::min_two(-1-prange[0]-i,prange_len-1);

		//Search over all possible predecessors and apply transition weighting
		if (zpad<0)
		{
			//No 0 padding
			for (int j=0;j<prange_len;j++)
				scorecands[j]=txwt[j]*cumscore[i+prange[j]];
		}
		else
		{
			for (int j=0;j<=zpad;j++)
				scorecands[j]=0;

			for (int j=zpad+1;j<prange_len;j++)
			{
				scorecands[j]=txwt[j]*cumscore[i+prange[j]];
			}
		}

		//Find best predecessore beat
		vector<double> beat_score_location = max<double>::max_list(scorecands,prange_len);

		//Add on local score
		cumscore[i]=alpha*beat_score_location[0]+(1-alpha)*localscore[i];

		//Special case to catch first onset. Stop if the local score is 0
		//(i.e. if there is near silence)
		if (starting && localscore[i]<max_local_score_factor)
			backlink[i]=-1; //Default
		else
		{
			//Found a probable beat, store it and leave the starting silence scenario.
			starting = false;
			backlink[i]=i+prange[(int) (beat_score_location[1])];
		}

	}


	

	//6. Find the last beat
	//cumscore now stores the score through the song, backlink the best previous frame.
	
	//Get the local max (the picks)
	bool *maxes = new bool[N];
	successFlag=math_fun::localmax(cumscore, maxes, N);

	if (!successFlag)
	{
		cerr<<"Error in function beatestimate: localmax error!\n";
		return vector<double>(1,negInf);
	}

	vector<double> peak_scores;
	for (int i=0;i<N;i++)
	{
		if (maxes[i])
			peak_scores.push_back(cumscore[i]);
	}

	double medscore=0.5*math_fun::median_score(peak_scores);


	//Look the last beat (the beats above 0.5*median) since the score generally increase
	int bestendx=-1;
	for (int i=0;i<N;i++)
	{
		if (maxes[i] && cumscore[i]>medscore)
			bestendx=i;
	}


	//7. Backward step
	vector<int> b;
	b.push_back(bestendx);

	while (backlink[bestendx]>0)
	{
		bestendx=backlink[bestendx];
		b.push_back(bestendx);
	}

	vector<double> beat_times;


	//b is backwards so start from the end
	for (int i=b.size()-1;i>=0;i--)
	{
		beat_times.push_back(((double)(b[i])+1.0)/fftres);
	}

	return beat_times;
	
}


