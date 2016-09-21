#ifndef SELFCONFIGURINGPLUGIN_H
#define SELFCONFIGURINGPLUGIN_H

# include <vector>
# include <stdexcept>

#include "..\PythonEnvironment.h"

//cereal
#include <cereal/cereal.hpp>
#include <cereal/types/polymorphic.hpp>
#include <cereal/types/string.hpp>

class SelfConfiguringPlugin
{
public:
    SelfConfiguringPlugin();
    SelfConfiguringPlugin(const std::string & paramType);
    virtual ~SelfConfiguringPlugin();

    std::vector<std::pair<std::string, std::string>> getParamsType() throw (std::runtime_error);

    //SERIALIZATIoN
    template<class Archive>
    void serialize(Archive & ar, std::uint32_t const version);

protected:
    std::string pluginType;
};

template<class Archive>
inline void SelfConfiguringPlugin::serialize(Archive& ar,
    const std::uint32_t version) {
    if (version <= 1) {
        SelfConfiguringPlugin::serialize(ar, version);
        ar(CEREAL_NVP(pluginType));
    }
}

// Associate some type with a version number
CEREAL_CLASS_VERSION(SelfConfiguringPlugin, (int)1);

// Include any archives you plan on using with your type before you register it
// Note that this could be done in any other location so long as it was prior
// to this file being included
#include <cereal/archives/json.hpp>
// Register DerivedClass
CEREAL_REGISTER_TYPE_WITH_NAME(SelfConfiguringPlugin, "SelfConfiguringPlugin");

#endif // SELFCONFIGURINGPLUGIN_H
