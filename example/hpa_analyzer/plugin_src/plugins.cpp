
// This is a skeleton file for use in creating your own plugin
// libraries.  Replace MyPlugin and myPlugin throughout with the name
// of your first plugin class, and fill in the gaps as appropriate.


#include <vamp/vamp.h>
#include <vamp-sdk/PluginAdapter.h>

#include "BTPlugin.h"
#include "LBCPlugin.h"
#include "HPAPlugin.h"
#include "HPA_LBCPlugin.h"
#include "beat_tracker.h"
#include "FE_package.h"
#include "math_function.h"
#include "vector_template.h"


// Declare one static adapter here for each plugin class in this library.

static Vamp::PluginAdapter<BTPlugin> BTPluginAdapter;
static Vamp::PluginAdapter<LBCPlugin> LBCPluginAdapter;
static Vamp::PluginAdapter<HPAPlugin> HPAPluginAdapter;
static Vamp::PluginAdapter<HPA_LBCPlugin> HPA_LBCPluginAdapter;


// This is the entry-point for the library, and the only function that
// needs to be publicly exported.

const VampPluginDescriptor *
vampGetPluginDescriptor(unsigned int version, unsigned int index)
{
    if (version < 1) return 0;

    // Return a different plugin adaptor's descriptor for each index,
    // and return 0 for the first index after you run out of plugins.
    // (That's how the host finds out how many plugins are in this
    // library.)

    switch (index) {
    case  0: return BTPluginAdapter.getDescriptor();
	case  1: return LBCPluginAdapter.getDescriptor();
	case  2: return HPAPluginAdapter.getDescriptor();
	case 3: return HPA_LBCPluginAdapter.getDescriptor();
    default: return 0;
    }
}


