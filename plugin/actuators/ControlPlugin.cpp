#include "ControlPlugin.h"

using namespace boost::python;

ControlPlugin::ControlPlugin() :
	Control()
{
	this->pluginType = "";
	this->referenceName = "";
}

ControlPlugin::ControlPlugin(int communications, int maxconnections, const std::string & pluginType, const std::vector<std::string>& params) :
	Control(maxconnections, communications)
{
	this->referenceName = "";
	this->pluginType = std::string(pluginType);
	this->params = std::vector<std::string>(params);
	//this->params.insert(this->params.begin(), patch::to_string(maxconnections));
}


ControlPlugin::~ControlPlugin()
{
	if (!referenceName.empty()) {
		PythonEnvironment::GetInstance()->deleteInstance(referenceName);
	}
}

void ControlPlugin::addConnection(int idSource, int idTarget) throw (std::runtime_error)
{
	try {
		if (referenceName.empty()) {
			referenceName = PythonEnvironment::GetInstance()->makeInstance(this->pluginType, this->params);
		}

		CommandSender* com = CommunicationsInterface::GetInstance()->getCommandSender(communications);
		PythonEnvironment::GetInstance()->getVarInstance(referenceName).attr("addConnection")(idSource, idTarget, boost::ref(*com));
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
		throw(std::runtime_error("addConnection(), " + pluginType + ": " + "error at python environment " + error));
	}
	catch (std::invalid_argument & e)
	{
		throw(std::runtime_error("addConnection(), " + pluginType + ": " + "internal error" + std::string(e.what())));
	}
}

void ControlPlugin::setConnection(int idSource, int idTarget) throw (std::runtime_error)
{
	try {
		if (referenceName.empty()) {
			referenceName = PythonEnvironment::GetInstance()->makeInstance(this->pluginType, this->params);
		}

		CommandSender* com = CommunicationsInterface::GetInstance()->getCommandSender(communications);
		PythonEnvironment::GetInstance()->getVarInstance(referenceName).attr("setConnection")(idSource, idTarget, boost::ref(*com));
	}
	catch (error_already_set) {
		PyObject *ptype, *pvalue, *ptraceback;
		PyErr_Fetch(&ptype, &pvalue, &ptraceback);
		
		std::string error = "";
		char* c_str = PyString_AsString(pvalue);
		if (c_str) {
			error = std::string(c_str);
		}
		throw(std::runtime_error("setConnection(), Plugin " + pluginType + ": " + "error at python environment " + error));
	}
	catch (std::invalid_argument & e)
	{
		throw(std::runtime_error("setConnection(), Plugin " + pluginType + ": " + "internal error" + std::string(e.what())));
	}
}

void ControlPlugin::clearConnections() throw(std::runtime_error)
{
	try {
		if (referenceName.empty()) {
			referenceName = PythonEnvironment::GetInstance()->makeInstance(this->pluginType, this->params);
		}

		PythonEnvironment::GetInstance()->getVarInstance(referenceName).attr("clearConnections")();
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
}

std::string ControlPlugin::getInstructions() throw (std::runtime_error)
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
}
