// This is a skeleton file for use in creating your own plugin
// libraries.  Replace MyPlugin and myPlugin throughout with the name
// of your first plugin class, and fill in the gaps as appropriate.


#include "LBCPlugin.h"


#include "FE_package.h"
#include "beat_tracker.h"
#include "vector_template.h"
#include "fftw3.h"


LBCPlugin::LBCPlugin(float inputSampleRate) :
    Plugin(inputSampleRate)
{
    // Also be sure to set your plugin parameters (presumably stored
    // in member variables) to their default values here -- the host
    // will not do that for you
	m_blockSize=0;
	m_stepSize=0;
	fmin=1;
	fmax=5;
	m_SR=(int) inputSampleRate; //? Why sample rate is float?


}

LBCPlugin::~LBCPlugin()
{
}

string
LBCPlugin::getIdentifier() const
{
    return "LBC";
}

string
LBCPlugin::getName() const
{
	return "LBC: Const-hop Chromagram";
}

string
LBCPlugin::getDescription() const
{
    // Return something helpful here!
    return "Harmony Progression Analyzer - loudness based chromagram extraction. Extracting chroma features (constant hop, for visualization purposes only) for the music tracks.\nREMARK: PLEASE KEEP THE STEP SIZE AND THE WINDOW SIZE IN THE SAME LENGTH (OR SIMPLY USE THE DEFAULT).";
}

string
LBCPlugin::getMaker() const
{
    // Your name here
    return "Yizhao Ni";
}

int
LBCPlugin::getPluginVersion() const
{
    // Increment this each time you release a version that behaves
    // differently from the previous one
    return 1.0;
}

string
LBCPlugin::getCopyright() const
{
    // This function is not ideally named.  It does not necessarily
    // need to say who made the plugin -- getMaker does that -- but it
    // should indicate the terms under which it is distributed.  For
    // example, "Copyright (year). All Rights Reserved", or "GPL"
    return "Creative Commons Attribution-NonCommercial 3.0.";
}

LBCPlugin::InputDomain
LBCPlugin::getInputDomain() const
{
    return TimeDomain;
}

size_t
LBCPlugin::getPreferredBlockSize() const
{
    return (ceil)(1024.0*m_SR/11025); // 0 means "I can handle any block size"
}

size_t 
LBCPlugin::getPreferredStepSize() const
{
    return (ceil)(1024.0*m_SR/11025); // 0 means "anything sensible"; in practice this
              // means the same as the block size for TimeDomain
              // plugins, or half of it for FrequencyDomain plugins
}

size_t
LBCPlugin::getMinChannelCount() const
{
    return 1;
}

size_t
LBCPlugin::getMaxChannelCount() const
{
    return 1;
}

LBCPlugin::ParameterList
LBCPlugin::getParameterDescriptors() const
{
    ParameterList list;

    // If the plugin has no adjustable parameters, return an empty
    // list here (and there's no need to provide implementations of
    // getParameter and setParameter in that case either).

    // Note that it is your responsibility to make sure the parameters
    // start off having their default values (e.g. in the constructor
    // above).  The host needs to know the default value so it can do
    // things like provide a "reset to default" function, but it will
    // not explicitly set your parameters to their defaults for you if
    // they have not changed in the mean time.

	char *temp_name[] ={"A0","A1","A2","A3","A4","A5","G#1","G#2","G#3","G#4","G#5","G#6"};

	//
    ParameterDescriptor d;
    d.identifier = "fmin";
    d.name = "Min Key Freq";
    d.description = "The lowest frquency of the chromagram.";
    d.unit = "";
    d.minValue = 0;      //A1 (or A0?)
    d.maxValue = 5;      //A5
    d.isQuantized = true;
	d.quantizeStep=1;
	d.defaultValue = 1;  //A1
	for (size_t i=0;i<6;i++)
		d.valueNames.push_back(temp_name[i]);

	list.push_back(d);

	ParameterDescriptor d2;
	d2.identifier = "fmax";
    d2.name = "Max Key Freq";
    d2.description = "The highest frquency of the chromagram.";
    d2.unit = "";
    d2.minValue = 0;      //G#2 (or start from G1?)
    d2.maxValue = 5;      //G#6
    d2.isQuantized = true;
	d2.quantizeStep=1;
	d2.defaultValue = 5;  //G#2

	for (size_t i=6;i<12;i++)
		d2.valueNames.push_back(temp_name[i]);

    list.push_back(d2);

    return list;
}

float
LBCPlugin::getParameter(string identifier) const
{
    if (identifier == "fmin") {
        return fmin; // return the ACTUAL current value of your parameter here!
    }
	
	if (identifier=="fmax")
	{return fmax;}
    
	return 0;
}

void
LBCPlugin::setParameter(string identifier, float value) 
{

    if (identifier == "fmin") {

		fmin=value;
		
    }

	if (identifier == "fmax") {
		
		fmax=value;
    }
}

LBCPlugin::ProgramList
LBCPlugin::getPrograms() const
{
    ProgramList list;

    // If you have no programs, return an empty list (or simply don't
    // implement this function or getCurrentProgram/selectProgram)

    return list;
}

string
LBCPlugin::getCurrentProgram() const
{
    return ""; // no programs
}

void
LBCPlugin::selectProgram(string name)
{
}

LBCPlugin::OutputList
LBCPlugin::getOutputDescriptors() const
{
    OutputList list;

	char *temp_name[] ={"C","C#","D","D#","E","F","F#","G","G#","A","A#","B"};
	vector<string> chromanames;
	for (size_t i=0;i<12; i++)
	{chromanames.push_back(temp_name[i]);}

    // See OutputDescriptor documentation for the possibilities here.
    // Every plugin must have at least one output.

    OutputDescriptor d;
    d.identifier = "const_hop_LBC";
    d.name = "Loudness based chromagram";
    d.description = "Returning the LBC chromagram";
    d.unit = "";
    d.hasFixedBinCount = true;
    d.binCount = 12;
	d.binNames=chromanames;  //Get the name of the bins?
    d.hasKnownExtents = false;
    d.isQuantized = false;
	//Important beat tracker has variable sample rate and return real time (in secs)
	d.sampleType = OutputDescriptor::FixedSampleRate;//VariableSampleRate;
	d.sampleRate=(m_stepSize == 0) ?  m_SR/1024 :  m_SR/m_stepSize; //Default step is 1024

    d.hasDuration = false;
    list.push_back(d);

    return list;
}

bool
LBCPlugin::initialise(size_t channels, size_t stepSize, size_t blockSize)
{
    if (channels < getMinChannelCount() ||
	channels > getMaxChannelCount()) return false;

    // Real initialisation work goes here!
	m_blockSize=blockSize;
	m_stepSize=stepSize;
	//fmin=55.0;     //Default A1
	//fmax=1661.0;   //Default G#6

    return true;
}

void
LBCPlugin::reset()
{
    // Clear buffers, reset stored values, etc
}

LBCPlugin::FeatureSet
LBCPlugin::process(const float *const *inputBuffers, Vamp::RealTime timestamp)
{
    //Collect all examples and use in the function getRemainingFeatures()
	size_t i=0; //note: same type as m_blockSize, block size is a block of signal
	while (i<m_blockSize) {
		//Collect the signals in channel 0
		m_signal.push_back(inputBuffers[0][i]);
		++i;
	}

	m_beat_times.push_back(Vamp::RealTime::realTime2Frame(timestamp,m_SR));
	beat_times_realT.push_back(timestamp);

    return FeatureSet();
}





/* Ver 0.9
=======================================================================================================================
The main function starts here!
The Beat Tracker!
=======================================================================================================================
*/

LBCPlugin::FeatureSet
LBCPlugin::getRemainingFeatures()
{
	//0. Retrieval the frequency parameters
	switch ((int)(fmin)){
			case 0:
				{
					fmin=27.5;
					break;
				}
			case 1:
				{
					fmin=55.0;
					break;
				}
			case 2:
				{
					fmin=110.0;
					break;
				}
			case 3:
				{
					fmin=220.0;
					break;
				}
			case 4:
				{
					fmin=440.0;
					break;
				}
			case 5:
				{
					fmin=880.0;
					break;
				}
			default:
				fmin=-1;
		}

	switch ((int)(fmax)){
			case 0:
				{
					fmax=51.9;
					break;
				}
			case 1:
				{
					fmax=98.0;
					break;
				}
			case 2:
				{
					fmax=207.0;
					break;
				}
			case 3:
				{
					fmax=415.0;
					break;
				}
			case 4:
				{
					fmax=830.0;
					break;
				}
			case 5:
				{
					fmax=1661.0;
					break;
				}
			default:
				fmax=-1;
	}


	//If the parameters are failed (NOTE that in this version, won't process songs of which sampling rate is < 11025Hz)
	if (fmin<0 || fmax<0 || fmin>=fmax || m_SR<11025)
	{
		/*. Return all 0 (error)
		int bins=12;
		FeatureSet fs;
		for (int i=0;i<beat_times_realT.size();i++)
		{
			Feature f;
			f.hasTimestamp=true;
			f.timestamp= beat_times_realT[i];
		
			for (size_t j=0;j<bins;j++)
				f.values.push_back(0);
		
			fs[0].push_back(f);

		}*/

		//Return empty feature set
		FeatureSet fs;
		return fs;
	}


	//1. Create the signal double * (currently using default sampling rate)
	size_t N_signal;
	vector<double> pq = math_fun::dec2frac(11025.0/m_SR,1e-10);

	if (m_SR==11025.0)
	{
		N_signal=m_signal.size();
	}
	else
	{
		N_signal=ceil(pq[0]/pq[1]*m_signal.size());
	}


	double *signal = new double[N_signal];

	//1.1 If the sampling rate is > 11025 Hz, resampled
	if (m_SR==11025.0)
	{
		for (size_t i=0;i<N_signal;i++)
		{
			signal[i]=m_signal[i];
		}
		m_signal.clear(); //free the memory
	}
	else
	{
		size_t tempN=m_signal.size();
		double* sample_signal=new double[tempN];
		for (size_t i=0;i<tempN;i++)
			sample_signal[i]=m_signal[i];
		m_signal.clear(); //free the memory
		FIR_resampler::resample(sample_signal,tempN,pq[1],pq[0],signal);
		delete[] sample_signal;
	}

	//Re-defined the sampling rate
	double org_SR=m_SR;
	m_SR=11025.0;



	//2. Define the parameters (currently default)
	//Tuning
	size_t tuning_window=4096;
	double f_center=400;

	//HPSS
	size_t HPSS_fftlen=1024;
	size_t HPSS_hoplen=512;
	size_t HPSS_window=4096;
	double HPSS_gamma=0.3;
	double HPSS_alpha=0.3;
	size_t HPSS_kmax=50;

	//Beat tracker
	size_t beat_hop_len=32;
	size_t beat_win_len=256;

	//LBC (Get resolution, if bass A0-G#3, the resolution=2,else 5)
	double resolution;
	if (fmax<220)
		resolution=2.0;
	else
		resolution=5.0;


	int bins=12;
	int K=ceil(log(fmax/fmin)/log(2.0))*bins; 


	//3. Tuning	 
	double semisoff=audio_preprocessing::estimate_tuning(signal,N_signal,m_SR,tuning_window,f_center,1);


	//Including HPSS version
	//4. HPSS: get the harmony
	size_t harmony_len=floor((double)(N_signal-HPSS_fftlen)/HPSS_hoplen)*HPSS_hoplen+HPSS_fftlen;
	double* xharmony = new double[harmony_len];
	bool successFlag=audio_preprocessing::HPSS(signal,N_signal,HPSS_fftlen,HPSS_hoplen,HPSS_window,HPSS_gamma,HPSS_alpha,HPSS_kmax,xharmony);

	//Get the harmony and free the signal space
	delete[] signal; 


/*Current the beat time is constant for visualization purpose
	//5. Beat tracker: get the beat times
	//Compute the beat strength
	size_t beatStrength_len=floor((double)(harmony_len-beat_win_len)/beat_hop_len);
	double *beatStrength = new double[beatStrength_len];
	successFlag=beat_tracker::calculate_beat_strength(xharmony,harmony_len,m_SR,beat_win_len,beat_hop_len,beatStrength);
	
	vector<double> beat_times= beat_tracker::beatestimate(beatStrength, beatStrength_len,m_SR,beat_hop_len);

	delete[] beatStrength;
	delete[] xharmony;


	//3.3 Using beat times to get BPM
	vector<double> diff_beat_times=vector<double>(beat_times.size()-1,0.0);
	for (size_t i=0;i<diff_beat_times.size();i++)
	{
		diff_beat_times[i]=beat_times[i+1]-beat_times[i];
	}

	double BPM = 60.0/math_fun::median_score(diff_beat_times);
	*/

	
	//6. LBC chromagram
	double* freqBins=new double[K];
	double* winLenK=new double[K];

	complex<double>* hammingK =LBC::cal_hamming_window(m_SR,fmin,fmax,resolution,semisoff,K,winLenK,freqBins);
	


	size_t N_beat=m_beat_times.size()-1; //Exclude the start time (time 0)
	double* beat_times_pointer =new double[N_beat];
	for (size_t i=1;i<=N_beat;i++)
		beat_times_pointer[i-1]=m_beat_times[i]/org_SR;

	double* sample_times=new double[2*(N_beat+1)];
	double* chromagram=new double[(N_beat+1)*bins];



	//Import wisdom here:
	FILE* fftw_wisdom=fopen("fftw_wisdom_MEASURE_precompile_plan","r");
	if (fftw_wisdom!=NULL)
	{
		fftw_import_wisdom_from_file(fftw_wisdom);
		fclose(fftw_wisdom);
	}

	//int numFrames=LBC::cal_LBC(xharmony, harmony_len, m_SR, beat_times_pointer,N_beat, hammingK, winLenK,freqBins,K, sample_times, chromagram, true);
	size_t N_block;
	if (fmin<55.0)
		N_block=65536;
	else
		N_block=32768;

	int numFrames=LBC::cal_LBC(xharmony, harmony_len, m_SR, beat_times_pointer,N_beat, hammingK, winLenK,freqBins,K, sample_times, chromagram, N_block, true);

	
	//7. Return the chromagram
	FeatureSet fs;
	for (int i=0;i<numFrames;i++)
	{
		Feature f;
		f.hasTimestamp=true;
		f.timestamp= beat_times_realT[i];
		
		for (size_t j=0;j<bins;j++)
			f.values.push_back(chromagram[i*bins+j]);
		
		fs[0].push_back(f);

	}

    return fs;
}

