# include "selfconfiguringplugin.h"

using namespace boost::python;

SelfConfiguringPlugin::SelfConfiguringPlugin()  {
    this->pluginType = "unknow";
}

SelfConfiguringPlugin::SelfConfiguringPlugin(const std::string & paramType) {
    this->pluginType = std::string(paramType);
}

SelfConfiguringPlugin::~SelfConfiguringPlugin() {

}

std::vector<std::pair<std::string, std::string>> SelfConfiguringPlugin::getParamsType() throw (std::runtime_error) {
    try {
        std::vector<std::pair<std::string, std::string>> params;
        dict dictionary = extract<dict>(PythonEnvironment::GetInstance()->executeStaticMethod(this->pluginType, "getParamsType"));
        boost::python::list keys = dictionary.keys();

        for(int i = 0; i < len(keys); i++) {
            std::string key = extract<std::string>(keys[i]);
            std::string value = extract<std::string>(dictionary[key]);
            params.push_back(std::make_pair(key,value));
        }
        return params;
    }
    catch (error_already_set)
    {
        PyObject *ptype, *pvalue, *ptraceback;
        PyErr_Fetch(&ptype, &pvalue, &ptraceback);

        std::string error = "";
        char* c_str = PyString_AsString(pvalue);
        if (c_str) {
            error = std::string(c_str);
        }
        throw(std::runtime_error("addConnection(), " + this->pluginType + ": " + "error at python environment " + error));
    }
    catch (std::invalid_argument & e)
    {
        throw(std::runtime_error("addConnection(), " + this->pluginType + ": " + "internal error" + std::string(e.what())));
    }
}
