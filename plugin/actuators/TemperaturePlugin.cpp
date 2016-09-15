#include "TemperaturePlugin.h"

using namespace boost::python;

TemperaturePlugin::TemperaturePlugin() :
	Temperature()
{
	this->pluginType = "";
	this->referenceName = "";
}

TemperaturePlugin::TemperaturePlugin(int communications, const std::string & pluginType, const std::vector<std::string>& params) :
	Temperature(communications)
{
	this->referenceName = "";
	this->pluginType = std::string(pluginType);
	this->params = std::vector<std::string>(params);
}


TemperaturePlugin::~TemperaturePlugin()
{
	if (!referenceName.empty()) {
		PythonEnvironment::GetInstance()->deleteInstance(referenceName);
	}
}

std::string TemperaturePlugin::getInstructions() throw(std::runtime_error)
{
	try {
		if (referenceName.empty()) {
			referenceName = PythonEnvironment::GetInstance()->makeInstance(this->pluginType, this->params);
		}

		const char* c_str = extract<const char*>(PythonEnvironment::GetInstance()->getVarInstance(referenceName).attr("getInstructions")());
		return std::string(c_str);
	}
	catch (error_already_set) {
		PyObject *ptype, *pvalue, *ptraceback;
		PyErr_Fetch(&ptype, &pvalue, &ptraceback);

		std::string error = "";
		char* c_str = PyString_AsString(pvalue);
		if (c_str) {
			error = std::string(c_str);
		}
		throw(std::runtime_error("getInstructions(), Plugin " + pluginType + ": " + "error at python environment " + error));
	}
	catch (std::invalid_argument & e)
	{
		throw(std::runtime_error("getInstructions(), Plugin " + pluginType + ": " + "internal error" + std::string(e.what())));
	}
}

void TemperaturePlugin::apply(double degrees) throw(std::runtime_error)
{
	try {
		if (referenceName.empty()) {
			referenceName = PythonEnvironment::GetInstance()->makeInstance(this->pluginType, this->params);
		}

		CommandSender* com = CommunicationsInterface::GetInstance()->getCommandSender(communications);
		PythonEnvironment::GetInstance()->getVarInstance(referenceName).attr("mix")(degrees, boost::ref(*com));
	}
	catch (error_already_set) {
		PyObject *ptype, *pvalue, *ptraceback;
		PyErr_Fetch(&ptype, &pvalue, &ptraceback);

		std::string error = "";
		char* c_str = PyString_AsString(pvalue);
		if (c_str) {
			error = std::string(c_str);
		}
		throw(std::runtime_error("apply(), Plugin " + pluginType + ": " + "error at python environment " + error));
	}
	catch (std::invalid_argument & e)
	{
		throw(std::runtime_error("apply(), Plugin " + pluginType + ": " + "internal error" + std::string(e.what())));
	}
}
