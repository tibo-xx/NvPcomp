//! Symbol table Node
/*! 
 * \class symNode
 *
 * Description
 *
 * \author CMT & DRJ
 *
 */
#ifndef SYMNODE_H_
#define SYMNODE_H_

#include <string>
#include <location.hh>
#include <position.hh>

namespace NvPcomp {
	class symNode {

	//This is only public until some access members are defined.
	public:
		std::string	_key;	
		std::string	_strType;
		NvPcomp::location _loc;
		
	public:
		symNode(NvPcomp::location loc, \
				std::string key, \
				std::string strType);
		~symNode();
	};
}

#endif /* SYMNODE_H_ */
