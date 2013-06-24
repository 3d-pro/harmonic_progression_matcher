
// This is a skeleton file for use in creating your own plugin
// libraries.  Replace MyPlugin and myPlugin throughout with the name
// of your first plugin class, and fill in the gaps as appropriate.


// Remember to use a different guard symbol in each header!
#ifndef _BT_PLUGIN_H_
#define _BT_PLUGIN_H_

#include <vamp-sdk/Plugin.h>
#include <vector>
#include <complex>




using std::string;
using std::vector;
using std::cerr;
using std::complex;


class BTPlugin : public Vamp::Plugin
{
public:
    BTPlugin(float inputSampleRate);
    virtual ~BTPlugin();

    string getIdentifier() const;
    string getName() const;
    string getDescription() const;
    string getMaker() const;
    int getPluginVersion() const;
    string getCopyright() const;

    InputDomain getInputDomain() const;
    size_t getPreferredBlockSize() const;
    size_t getPreferredStepSize() const;
    size_t getMinChannelCount() const;
    size_t getMaxChannelCount() const;

    ParameterList getParameterDescriptors() const;
    float getParameter(string identifier) const;
    void setParameter(string identifier, float value);

    ProgramList getPrograms() const;
    string getCurrentProgram() const;
    void selectProgram(string name);

    OutputList getOutputDescriptors() const;

    bool initialise(size_t channels, size_t stepSize, size_t blockSize);
    void reset();

    FeatureSet process(const float *const *inputBuffers,
                       Vamp::RealTime timestamp);

    FeatureSet getRemainingFeatures();

protected:
    // plugin-specific data and methods go here
	vector<float> m_signal;   //Store the signal (using list?)
	int beat_per_bar;
	size_t m_blockSize;
	size_t m_SR;

	};



#endif
