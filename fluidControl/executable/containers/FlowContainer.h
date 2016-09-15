/*
 * FlowContainer.h
 *
 *  Created on: 3 de may. de 2016
 *      Author: angel
 */

#ifndef SRC_FLUIDCONTROL_EXECUTABLE_CONTAINERS_FLOWCONTAINER_H_
#define SRC_FLUIDCONTROL_EXECUTABLE_CONTAINERS_FLOWCONTAINER_H_

#include <stdexcept>

// boost
#include <memory>

//local
#include "../../executable/containers/ExecutableContainerNode.h"
#include "actuators/liquids/Extractor.h"
#include "actuators/liquids/Injector.h"

//cereal
#include <cereal/cereal.hpp>
#include <cereal/types/memory.hpp>
#include <cereal/types/polymorphic.hpp>

class FlowContainer: public ExecutableContainerNode {
public:
	//methods of being node
	FlowContainer();
	FlowContainer(const FlowContainer & node);

	//virtual std::string toText();
	virtual void loadNode(const std::string & line)
			throw (std::invalid_argument);
	//
	FlowContainer(int idContainer, float capacity,
			std::shared_ptr<Extractor> extract, std::shared_ptr<Injector> insert);

	virtual ~FlowContainer();

	virtual void setPositionInject(int source, int target) throw (std::runtime_error);
	virtual void setPositionExtract(int source, int target) throw (std::runtime_error);
	virtual void receiveLiquid(double rate) throw (std::runtime_error);
	virtual void extractLiquid(double rate) throw (std::runtime_error);
	virtual void connectContainer(int source, int target) throw (std::runtime_error);
	inline virtual void clearConnectedContainers() throw (std::runtime_error) {}

	virtual void updateCommunicationInterface(int communication);

	//SERIALIZATIoN
	template<class Archive>
	void serialize(Archive & ar, std::uint32_t const version);
protected:
	std::shared_ptr<Extractor> extract;
	std::shared_ptr<Injector> insert;
};

template<class Archive>
inline void FlowContainer::serialize(Archive& ar, const std::uint32_t version) {
	if (version <= 1) {
		ExecutableContainerNode::serialize(ar, version);
		ar(CEREAL_NVP(insert), CEREAL_NVP(extract));
	}
}

// Associate some type with a version number
CEREAL_CLASS_VERSION( FlowContainer, (int)1 );

// Include any archives you plan on using with your type before you register it
// Note that this could be done in any other location so long as it was prior
// to this file being included
#include <cereal/archives/json.hpp>
// Register DerivedClass
CEREAL_REGISTER_TYPE_WITH_NAME(FlowContainer, "FlowContainer");

#endif /* SRC_FLUIDCONTROL_EXECUTABLE_CONTAINERS_FLOWCONTAINER_H_ */
