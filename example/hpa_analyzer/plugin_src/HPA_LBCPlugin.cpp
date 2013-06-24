// This is a skeleton file for use in creating your own plugin
// libraries.  Replace MyPlugin and myPlugin throughout with the name
// of your first plugin class, and fill in the gaps as appropriate.


#include "HPA_LBCPlugin.h"


#include "FE_package.h"
#include "beat_tracker.h"
#include "vector_template.h"
#include "fftw3.h"
#include <fstream>
#include <sstream>
using std::stringstream;
using std::ios;
using std::fstream;



HPA_LBCPlugin::HPA_LBCPlugin(float inputSampleRate) :
    Plugin(inputSampleRate)
{
    // Also be sure to set your plugin parameters (presumably stored
    // in member variables) to their default values here -- the host
    // will not do that for you
	m_blockSize=0;
	m_stepSize=0;
	m_SR=(int) inputSampleRate; //? Why sample rate is float?


}

HPA_LBCPlugin::~HPA_LBCPlugin()
{
}

string
HPA_LBCPlugin::getIdentifier() const
{
    return "HPA_LBC";
}

string
HPA_LBCPlugin::getName() const
{
	return "LBC: Beat-synced Chromagram";
}

string
HPA_LBCPlugin::getDescription() const
{
    // Return something helpful here!
    return "Harmony Progression Analyzer - loudness based chromagram extraction. Extracting chroma features (beat synced, for research purpose) for the music tracks.\nREMARK: PLEASE KEEP THE STEP SIZE AND THE WINDOW SIZE IN THE SAME LENGTH (OR SIMPLY USE THE DEFAULT).";
}

string
HPA_LBCPlugin::getMaker() const
{
    // Your name here
    return "Yizhao Ni";
}

int
HPA_LBCPlugin::getPluginVersion() const
{
    // Increment this each time you release a version that behaves
    // differently from the previous one
    return 1.0;
}

string
HPA_LBCPlugin::getCopyright() const
{
    // This function is not ideally named.  It does not necessarily
    // need to say who made the plugin -- getMaker does that -- but it
    // should indicate the terms under which it is distributed.  For
    // example, "Copyright (year). All Rights Reserved", or "GPL"
    return "Creative Commons Attribution-NonCommercial 3.0.";
}

HPA_LBCPlugin::InputDomain
HPA_LBCPlugin::getInputDomain() const
{
    return TimeDomain;
}

size_t
HPA_LBCPlugin::getPreferredBlockSize() const
{
    return (ceil)(1024.0*m_SR/11025); // 0 means "I can handle any block size"
}

size_t 
HPA_LBCPlugin::getPreferredStepSize() const
{
    return (ceil)(1024.0*m_SR/11025); // 0 means "anything sensible"; in practice this
              // means the same as the block size for TimeDomain
              // plugins, or half of it for FrequencyDomain plugins
}

size_t
HPA_LBCPlugin::getMinChannelCount() const
{
    return 1;
}

size_t
HPA_LBCPlugin::getMaxChannelCount() const
{
    return 1;
}

HPA_LBCPlugin::ParameterList
HPA_LBCPlugin::getParameterDescriptors() const
{
    ParameterList list;
    return list;
}

float
HPA_LBCPlugin::getParameter(string identifier) const
{
    
	return 0;
}

void
HPA_LBCPlugin::setParameter(string identifier, float value) 
{

}

HPA_LBCPlugin::ProgramList
HPA_LBCPlugin::getPrograms() const
{
    ProgramList list;

    // If you have no programs, return an empty list (or simply don't
    // implement this function or getCurrentProgram/selectProgram)

    return list;
}

string
HPA_LBCPlugin::getCurrentProgram() const
{
    return ""; // no programs
}

void
HPA_LBCPlugin::selectProgram(string name)
{
}

HPA_LBCPlugin::OutputList
HPA_LBCPlugin::getOutputDescriptors() const
{
    OutputList list;

    // See OutputDescriptor documentation for the possibilities here.
    // Every plugin must have at least one output.

    OutputDescriptor d;
    d.identifier = "beat_synced_LBC";
    d.name = "Loudness based chromagram";
    d.description = "Returning the LBC chromagram";
    d.unit = "";
    d.hasFixedBinCount = true;
    d.binCount = 0;
    d.hasKnownExtents = false;
    d.isQuantized = false;
	//Important beat tracker has variable sample rate and return real time (in secs)
	d.sampleType = OutputDescriptor::VariableSampleRate;//
	
    d.hasDuration = false;
    list.push_back(d);

    return list;
}

bool
HPA_LBCPlugin::initialise(size_t channels, size_t stepSize, size_t blockSize)
{
    if (channels < getMinChannelCount() ||
	channels > getMaxChannelCount()) return false;

    // Real initialisation work goes here!
	m_blockSize=blockSize;
	m_stepSize=stepSize;
	
    return true;
}

void
HPA_LBCPlugin::reset()
{
    // Clear buffers, reset stored values, etc
}

HPA_LBCPlugin::FeatureSet
HPA_LBCPlugin::process(const float *const *inputBuffers, Vamp::RealTime timestamp)
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

HPA_LBCPlugin::FeatureSet
HPA_LBCPlugin::getRemainingFeatures()
{
	
	//If the parameters are failed (NOTE that in this version, won't process songs of which sampling rate is < 11025Hz)
	if (m_SR<11025)
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


	//3. Tuning	 
	double semisoff=audio_preprocessing::estimate_tuning(signal,N_signal,m_SR,tuning_window,f_center,1);


	//Including HPSS version
	//4. HPSS: get the harmony
	size_t harmony_len=floor((double)(N_signal-HPSS_fftlen)/HPSS_hoplen)*HPSS_hoplen+HPSS_fftlen;
	double* xharmony = new double[harmony_len];
	bool successFlag=audio_preprocessing::HPSS(signal,N_signal,HPSS_fftlen,HPSS_hoplen,HPSS_window,HPSS_gamma,HPSS_alpha,HPSS_kmax,xharmony);

	//Get the harmony and free the signal space
	delete[] signal; 


	///5. Beat tracker: get the beat times
	size_t beat_hop_len=32;
	size_t beat_win_len=256;
	//Compute the beat strength
	size_t beatStrength_len=floor((double)(harmony_len-beat_win_len)/beat_hop_len);
	double *beatStrength = new double[beatStrength_len];
	successFlag=beat_tracker::calculate_beat_strength(xharmony,harmony_len,m_SR,beat_win_len,beat_hop_len,beatStrength);

		
	vector<double> beat_times= beat_tracker::beatestimate(beatStrength, beatStrength_len,m_SR,beat_hop_len);


		//Debuging ...
		//ofstream beat_file("test_beat",ios::out);
		//for (size_t i=0;i<beat_times.size();i++)
		//	beat_file<<beat_times[i]<<' ';
		//beat_file<<'\n';
		//beat_file.close();



	//5.2 Using beat times to get BPM
	vector<double> diff_beat_times=vector<double>(beat_times.size()-1,0.0);
	for (size_t i=0;i<diff_beat_times.size();i++)
	{
		diff_beat_times[i]=beat_times[i+1]-beat_times[i];
	}

	double BPM = 60.0/math_fun::median_score(diff_beat_times);

	if (BPM<120)
	{
		//Post-processing: if bpm<120, double everything. (used only in chromagram and HPA)
		diff_beat_times.assign(beat_times.begin(),beat_times.end());

		beat_times.clear();

		beat_times.push_back(diff_beat_times[0]);
		for (size_t i=1;i<diff_beat_times.size();i++)
		{
			beat_times.push_back((diff_beat_times[i-1]+diff_beat_times[i])/2);
			beat_times.push_back(diff_beat_times[i]);
		}

	}

	size_t N_beat=beat_times.size(); //Exclude the start time (time 0)
	double* beat_times_pointer =new double[N_beat];
	for (size_t i=0;i<N_beat;i++)
		beat_times_pointer[i]=beat_times[i];

		
	//6. LBC chromagram (if maxGamma or Viterbi, the first half is treble and the second half is bass)
	int bins=12;
	double resolution;
	int K;

	double* sample_times=new double[2*(N_beat+1)];
	double* temp_chromagram=new double[(N_beat+1)*bins];


	
	//6. LBC chromagram
	//Import wisdom here:
	FILE* fftw_wisdom=fopen("./model/fftw_wisdom_MEASURE_precompile_plan","r");
	if (fftw_wisdom!=NULL)
	{
		fftw_import_wisdom_from_file(fftw_wisdom);
		fclose(fftw_wisdom);
	}


	//A. Bass chromagram
	size_t N_block=32768;
	fmin=55.0;
	fmax=207.0;
	resolution=2.0;
	K=ceil(log(fmax/fmin)/log(2.0))*bins; 
	double* freqBins_bass=new double[K];
	double* winLenK_bass=new double[K];

	complex<double>* hammingK_bass =LBC::cal_hamming_window(m_SR,fmin,fmax,resolution,semisoff,K,winLenK_bass,freqBins_bass);
		
	int numFrames=LBC::cal_LBC(xharmony, harmony_len, m_SR, beat_times_pointer,N_beat, hammingK_bass, winLenK_bass,freqBins_bass,K, sample_times, temp_chromagram, N_block, true);
		
		
	//B. Create the combined chromgram and assigned bass
	size_t comb_dim=2*bins;
	double *comb_chromagram = new double[numFrames*comb_dim];
	double *temp_pointer, *assign_pointer, *chroma_pointer;
		
	chroma_pointer=comb_chromagram+bins;
	assign_pointer=temp_chromagram;
		
	for (size_t t=0; t<numFrames;t++)
	{
		temp_pointer=chroma_pointer;
		for (size_t d=0;d<bins;d++)
			*temp_pointer++=*assign_pointer++;
		chroma_pointer+=comb_dim;
	}

	delete[] freqBins_bass;
	delete[] winLenK_bass;
	delete[] hammingK_bass;

	//C.Treble chromagram
	fmin=220.0;
	fmax=1661.0;
	resolution=5.0;
	K=ceil(log(fmax/fmin)/log(2.0))*bins; 
	double* freqBins_treble=new double[K];
	double* winLenK_treble=new double[K];

	complex<double>* hammingK_treble =LBC::cal_hamming_window(m_SR,fmin,fmax,resolution,semisoff,K,winLenK_treble,freqBins_treble);
		
	numFrames=LBC::cal_LBC(xharmony, harmony_len, m_SR, beat_times_pointer,N_beat, hammingK_treble, winLenK_treble,freqBins_treble,K, sample_times, temp_chromagram, N_block, true);
		

	chroma_pointer=comb_chromagram;
	assign_pointer=temp_chromagram;
		
	for (size_t t=0; t<numFrames;t++)
	{
		temp_pointer=chroma_pointer;
		for (size_t d=0;d<bins;d++)
			*temp_pointer++=*assign_pointer++;
		chroma_pointer+=comb_dim;
	}

	//Release the pointer
	chroma_pointer=0;
	temp_pointer=0;
	assign_pointer=0;
	delete[] temp_chromagram;
	delete[] freqBins_treble;
	delete[] winLenK_treble;
	delete[] hammingK_treble;
	delete[] xharmony;


	double* temp_sample_times=new double[2*numFrames];
	for (size_t i=0;i<2*numFrames;i+=2)
	{
		temp_sample_times[i]=sample_times[i];
		temp_sample_times[i+1]=sample_times[i+1];
	}
	

	//Store the chroma in temp bin file
	fstream outFile("./model/temp.bin",ios::out | ios::binary);
	
	if (!outFile.is_open())
	{
		cerr<<"Can not open the output file\n";
		FeatureSet fs;
		return fs;
	}
	int parameterSet[2]={numFrames,comb_dim};
	outFile.write((char*)parameterSet,sizeof(int)*2);
	outFile.write((char*)temp_sample_times,sizeof(double)*2*numFrames);
	outFile.write((char*)comb_chromagram,sizeof(double)*numFrames*comb_dim);
	outFile.close();
	
	
	//7. Return the chromagram
	FeatureSet fs;
	size_t frame_offset;
	for (int i=0;i<numFrames;i++)
	{
		Feature f;
		f.hasTimestamp=true;
		f.timestamp= Vamp::RealTime::fromSeconds(temp_sample_times[2*i]);
		
		stringstream f_value;
		f_value<<temp_sample_times[2*i+1]<<' ';

		frame_offset=i*comb_dim;
		for (size_t j=0;j<comb_dim;j++)
			f_value<<comb_chromagram[frame_offset+j]<<' ';
		
		f.label=f_value.str();
		fs[0].push_back(f);

	}

    return fs;
}
