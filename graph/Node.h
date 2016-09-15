/*
 * Node.h
 *
 *  Created on: 7 de mar. de 2016
 *      Author: angel
 */

#ifndef SRC_GRAPH_NODE_H_
#define SRC_GRAPH_NODE_H_

#include <string>
#include  <stdexcept>

//boost
#include <boost/algorithm/string/trim.hpp>

//local
#include "../util/Patch.h"

//cereal
#include <cereal/cereal.hpp>
#include <cereal/types/polymorphic.hpp>

/**
 * Minimum operations a all node must have, Base for all Node types to derive
 */
class Node {

public:
	//All derived clases must implement this two Constructor!!
	Node() {
		this->containerID = 0;
	}

	Node (const Node & node) {
		this->containerID = node.containerID;
	}
	//

	Node(int containerID) {
			this->containerID = containerID;
	}

	virtual ~Node(){}

	/**
	 * Returns the ID of this node
	 * @return Returns the ID of this node
	 */
	inline virtual int getContainerId() {
		return containerID;
	}

	/**
	 * Returns if this node is the same as n
	 * @param n the node to compare to
	 * @return true if the two nodes are the same, false otherwise
	 */
	inline virtual bool equals(const Node& n) {
		return (n.containerID == this->containerID);
	}

	/**
	 * Returns a string with all the information of the node, must be with a format that loadNode can manage
	 *
	 * @return a string with all the necessary information to store this node
	 */
	inline virtual string toText() {
		string vuelta = patch::to_string(containerID) + ";";
		return vuelta;
	}

	/**
	 * checks if this line has the format for a valid node, this method must changed depending of
	 * the format used for the node.
	 *
	 * @param line text that is going to be checked
	 * @return true if the format is for an edge, false otherwise
	 */
	inline virtual bool isNode(const string & line) {
		return (line.find("->") == string::npos);
	}

	//SERIALIZATIoN
	template<class Archive>
	void serialize(Archive & ar, std::uint32_t const version);

protected:
	int containerID;

};

template<class Archive>
inline void Node::serialize(Archive& ar, const std::uint32_t version) {
	if (version <= 1) {
		ar(CEREAL_NVP(containerID));
	}
}

// Associate some type with a version number
CEREAL_CLASS_VERSION( Node, (int)1 );

//// Include any archives you plan on using with your type before you register it
//// Note that this could be done in any other location so long as it was prior
//// to this file being included
//#include <cereal/archives/json.hpp>
//// Register DerivedClass
//CEREAL_REGISTER_TYPE_WITH_NAME(Node, "Node");


#endif /* SRC_GRAPH_NODE_H_ */
