#pragma once

#include <string>
#include <vector>
#include <stdexcept>

//local
#include "..\..\fluidControl\executable\containers\actuators\extras\Light.h"
#include "..\..\fluidControl\executable\containers\actuators\communications\CommunicationsInterface.h"
#include "..\PythonEnvironment.h"
#include "selfconfiguringplugin.h"

//cereal
#include <cereal/cereal.hpp>
#include <cereal/types/polymorphic.hpp>
#include <cereal/types/vector.hpp>
#include <cereal/types/string.hpp>

class LightPlugin :
    public Light, SelfConfiguringPlugin
{
public:
	LightPlugin();
    LightPlugin(int communications, const std::string & pluginType, const std::unordered_map<std::string,std::string> & params);
	virtual ~LightPlugin();

	virtual std::string getInstructions() throw(std::runtime_error);
	virtual void applyLight(double waveLength, double intensity) throw(std::runtime_error);

    inline virtual SelfConfiguringPlugin* clone() {
        return new LightPlugin();
    }

	//SERIALIZATIoN
	template<class Archive>
	void serialize(Archive & ar, std::uint32_t const version);
protected:
	std::string referenceName;
};

template<class Archive>
inline void LightPlugin::serialize(Archive& ar,
	const std::uint32_t version) {
	if (version <= 1) {
		Light::serialize(ar, version);
        SelfConfiguringPlugin::serialize(ar, version);
	}
};

// Associate some type with a version number
CEREAL_CLASS_VERSION(LightPlugin, (int)2);

// Include any archives you plan on using with your type before you register it
// Note that this could be done in any other location so long as it was prior
// to this file being included
#include <cereal/archives/json.hpp>
// Register DerivedClass
CEREAL_REGISTER_TYPE_WITH_NAME(LightPlugin, "LightPlugin");


