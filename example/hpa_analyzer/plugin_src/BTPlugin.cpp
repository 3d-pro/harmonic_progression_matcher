
// This is a skeleton file for use in creating your own plugin
// libraries.  Replace MyPlugin and myPlugin throughout with the name
// of your first plugin class, and fill in the gaps as appropriate.


#include "BTPlugin.h"


#include "FE_package.h"
#include "beat_tracker.h"
#include "vector_template.h"
#include "fftw3.h"


BTPlugin::BTPlugin(float inputSampleRate) :
    Plugin(inputSampleRate)
{
    // Also be sure to set your plugin parameters (presumably stored
    // in member variables) to their default values here -- the host
    // will not do that for you
	m_blockSize=0;
	beat_per_bar=1;
	m_SR=(int) inputSampleRate; //? Why sample rate is float?


}

BTPlugin::~BTPlugin()
{
}

string
BTPlugin::getIdentifier() const
{
    return "beat_tracker";
}

string
BTPlugin::getName() const
{
	return "HPA: Beat Tracker";
}

string
BTPlugin::getDescription() const
{
    // Return something helpful here!
    return "Harmony Progression Analyzer - automatic beat tracker. Estimating beat times of the music tracks.\nREMARK: PLEASE KEEP THE STEP SIZE AND THE WINDOW SIZE IN THE SAME LENGTH (OR SIMPLY USE THE DEFAULT).";
}

string
BTPlugin::getMaker() const
{
    // Your name here
    return "Yizhao Ni";
}

int
BTPlugin::getPluginVersion() const
{
    // Increment this each time you release a version that behaves
    // differently from the previous one
    return 1.0;
}

string
BTPlugin::getCopyright() const
{
    // This function is not ideally named.  It does not necessarily
    // need to say who made the plugin -- getMaker does that -- but it
    // should indicate the terms under which it is distributed.  For
    // example, "Copyright (year). All Rights Reserved", or "GPL"
    return "Creative Commons Attribution-NonCommercial 3.0.";
}

BTPlugin::InputDomain
BTPlugin::getInputDomain() const
{
    return TimeDomain;
}

size_t
BTPlugin::getPreferredBlockSize() const
{
    return (ceil)(256.0*m_SR/11025); // 0 means "I can handle any block size"
}

size_t 
BTPlugin::getPreferredStepSize() const
{
    return (ceil)(256.0*m_SR/11025); // 0 means "anything sensible"; in practice this
              // means the same as the block size for TimeDomain
              // plugins, or half of it for FrequencyDomain plugins
}

size_t
BTPlugin::getMinChannelCount() const
{
    return 1;
}

size_t
BTPlugin::getMaxChannelCount() const
{
    return 1;
}

BTPlugin::ParameterList
BTPlugin::getParameterDescriptors() const
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

	
/*
    ParameterDescriptor d;
    d.identifier = "meter";
    d.name = "Beats per bar";
    d.description = "Setting how many beats per bar";
    d.unit = "";
    d.minValue = 1;
    d.maxValue = 20;
    d.defaultValue = 1;
    d.isQuantized = true;
	d.quantizeStep=1;
    list.push_back(d);
	*/

    return list;
}

float
BTPlugin::getParameter(string identifier) const
{
    if (identifier == "meter") {
        return beat_per_bar; // return the ACTUAL current value of your parameter here!
    }
    return 0;
}

void
BTPlugin::setParameter(string identifier, float value) 
{
	/*
    if (identifier == "meter") {
        // set the actual value of your parameter
		beat_per_bar=(int)value;
    }
	*/
}

BTPlugin::ProgramList
BTPlugin::getPrograms() const
{
    ProgramList list;

    // If you have no programs, return an empty list (or simply don't
    // implement this function or getCurrentProgram/selectProgram)

    return list;
}

string
BTPlugin::getCurrentProgram() const
{
    return ""; // no programs
}

void
BTPlugin::selectProgram(string name)
{
}

BTPlugin::OutputList
BTPlugin::getOutputDescriptors() const
{
    OutputList list;


	//vector<string> chromanames;
	//chromanames.push_back("A");
	//chromanames.push_back("B");

    // See OutputDescriptor documentation for the possibilities here.
    // Every plugin must have at least one output.

    OutputDescriptor d;
    d.identifier = "beat_times";
    d.name = "Beat Times";
    d.description = "Returning the Beat Times";
    d.unit = "seconds";
    d.hasFixedBinCount = true;
    d.binCount = 1;
	//d.binNames=chromanames;  //Get the name of the bins?
    d.hasKnownExtents = false;
    d.isQuantized = false;
	//Important beat tracker has variable sample rate and return real time (in secs)
	d.sampleType = OutputDescriptor::VariableSampleRate;
	
    d.hasDuration = false;
    list.push_back(d);

	/*

	d2.identifier = "BPM";
    d2.name = "BPM";
    d2.description = "Return the estimated Beat Per Minutes";
    d2.unit = "bpm";
    d2.hasFixedBinCount = true;
	d2.hasKnownExtents = false;
    d2.isQuantized = false;
	d2.binCount = 1;
	//Important beat tracker has variable sample rate and return real time (in secs)
	d2.sampleType = OutputDescriptor::VariableSampleRate;
	
    d2.hasDuration = false;
    list.push_back(d2);
	*/

    return list;
}

bool
BTPlugin::initialise(size_t channels, size_t stepSize, size_t blockSize)
{
    if (channels < getMinChannelCount() ||
	channels > getMaxChannelCount()) return false;

    // Real initialisation work goes here!
	m_blockSize=blockSize;

    return true;
}

void
BTPlugin::reset()
{
    // Clear buffers, reset stored values, etc
}

BTPlugin::FeatureSet
BTPlugin::process(const float *const *inputBuffers, Vamp::RealTime timestamp)
{
    //Collect all examples and use in the function getRemainingFeatures()
	size_t i=0; //note: same type as m_blockSize, block size is a block of signal
	while (i<m_blockSize) {
		//Collect the signals in channel 0
		m_signal.push_back(inputBuffers[0][i]);
		++i;
	}

    return FeatureSet();
}





/* Ver 0.9
=======================================================================================================================
The main function starts here!
The Beat Tracker!
=======================================================================================================================
*/

BTPlugin::FeatureSet
BTPlugin::getRemainingFeatures()
{
	//If the parameters are failed (NOTE that in this version, won't process songs of which sampling rate is < 11025Hz)
	if (m_SR<11025)
	{
		//*. Return all 0 (error)
		FeatureSet fs;
		Feature f;
		f.hasTimestamp=true;
		f.timestamp= Vamp::RealTime::fromSeconds(0.0);
		f.label="Error: sampling rate is <11025 Hz.";
		f.values.push_back(-1);

		fs[0].push_back(f);
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
	m_SR=11025.0;



	//2. Define the parameters (currently default)
	/*HPSS
	size_t HPSS_fftlen=1024;
	size_t HPSS_hoplen=512;
	size_t HPSS_window=4096;
	double HPSS_gamma=0.3;
	double HPSS_alpha=0.3;
	size_t HPSS_kmax=50;
	*/

	//Beat tracker
	size_t beat_hop_len=32;
	size_t beat_win_len=256;

  //Excluding HPSS version
	//3.1 Beat tracker: get the beat times

	//Compute the beat strength
	size_t beatStrength_len=floor((double)(N_signal-beat_win_len)/beat_hop_len);
	double *beatStrength = new double[beatStrength_len];
	bool successFlag=beat_tracker::calculate_beat_strength(signal,N_signal,m_SR,beat_win_len,beat_hop_len,beatStrength);
	
	vector<double> beat_times= beat_tracker::beatestimate(beatStrength, beatStrength_len,m_SR,beat_hop_len);

	delete[] beatStrength;
	delete[] signal;


	/*  //Including HPSS version
	//3.1 HPSS: get the harmony (necessary?)
	size_t harmony_len=floor((double)(N_signal-HPSS_fftlen)/HPSS_hoplen)*HPSS_hoplen+HPSS_fftlen;
	double* xharmony = new double[harmony_len];
	bool successFlag=audio_preprocessing::HPSS(signal,N_signal,HPSS_fftlen,HPSS_hoplen,HPSS_window,HPSS_gamma,HPSS_alpha,HPSS_kmax,xharmony);

	//Get the harmony and free the signal space
	delete[] signal; 

	//3.2 Beat tracker: get the beat times

	//Compute the beat strength
	size_t beatStrength_len=floor((double)(harmony_len-beat_win_len)/beat_hop_len);
	double *beatStrength = new double[beatStrength_len];
	successFlag=beat_tracker::calculate_beat_strength(xharmony,harmony_len,m_SR,beat_win_len,beat_hop_len,beatStrength);
	
	vector<double> beat_times= beat_tracker::beatestimate(beatStrength, beatStrength_len,m_SR,beat_hop_len);

	delete[] beatStrength;
	delete[] xharmony;
*/


	//3.3 Using beat times to get BPM
/*	
	vector<double> diff_beat_times=vector<double>(beat_times.size()-1,0.0);
	for (size_t i=0;i<diff_beat_times.size();i++)
	{
		diff_beat_times[i]=beat_times[i+1]-beat_times[i];
	}

	double BPM = 60.0/math_fun::median_score(diff_beat_times);
*/	

	int N_diff=beat_times.size()-1;
	double *diff_beat_times= new double[N_diff];
	for (size_t i=0;i<N_diff;i++)
		diff_beat_times[i]=beat_times[i+1]-beat_times[i];

	double BPM=60.0/math_fun::median(diff_beat_times,0,N_diff-1,N_diff);
	

	
	//4. Return the beat times
	FeatureSet fs;
	for (int i=0;i<beat_times.size();i+=beat_per_bar)
	{
		Feature f;
		f.hasTimestamp=true;
		f.timestamp= Vamp::RealTime::fromSeconds(beat_times[i]);
		
		f.values.push_back(BPM);
		
		fs[0].push_back(f);

	}

	/*
	Feature f1; //For BPM
	f1.hasTimestamp=true;
	f1.timestamp= Vamp::RealTime::fromSeconds(beat_times[0]);
	f1.values.push_back(BPM);
	fs[1].push_back(f1);
	*/


	delete[] diff_beat_times;

    return fs;
}

