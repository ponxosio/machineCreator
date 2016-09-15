#include "ODSensorPlugin.h"

using namespace boost::python;


ODSensorPlugin::ODSensorPlugin() :
	ODSensor()
{
	this->pluginType = "";
	this->referenceName = "";
}

ODSensorPlugin::ODSensorPlugin(int communications, const std::string & pluginType, const std::vector<std::string>& params) :
	ODSensor(communications)
{
	this->referenceName = "";
	this->pluginType = std::string(pluginType);
	this->params = std::vector<std::string>(params);
}


ODSensorPlugin::~ODSensorPlugin()
{
	if (!referenceName.empty()) {
		PythonEnvironment::GetInstance()->deleteInstance(referenceName);
	}
}

std::string ODSensorPlugin::getInstructions() throw (std::runtime_error)
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

double ODSensorPlugin::readOd() throw (std::runtime_error)
{
	try {
		if (referenceName.empty()) {
			referenceName = PythonEnvironment::GetInstance()->makeInstance(this->pluginType, this->params);
		}

		CommandSender* com = CommunicationsInterface::GetInstance()->getCommandSender(communications);
		double movementType = extract<double>(PythonEnvironment::GetInstance()->getVarInstance(referenceName).attr("readOD")(boost::ref(*com)));
		return movementType;
	}
	catch (error_already_set) {
		PyObject *ptype, *pvalue, *ptraceback;
		PyErr_Fetch(&ptype, &pvalue, &ptraceback);

		std::string error = "";
		char* c_str = PyString_AsString(pvalue);
		if (c_str) {
			error = std::string(c_str);
		}
		throw(std::runtime_error("readOd(), Plugin " + pluginType + ": " + "error at python environment " + error));
	}
	catch (std::invalid_argument & e)
	{
		throw(std::runtime_error("readOd(), Plugin " + pluginType + ": " + "internal error" + std::string(e.what())));
	}
}
