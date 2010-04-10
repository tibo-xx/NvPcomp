//! Symbol table Node
/*! 
 * \class symNode
 *
 * Description
 *
 * \author CMT, DRJ & BFB
 *
 */
#ifndef SYMNODE_H_
#define SYMNODE_H_

#include <string>
#include <location.hh>
#include <position.hh>
#include <vector>

namespace NvPcomp {
	class symNode {

	//This is only public until some access members are defined.
	public:
		void addType(int);
		int getTopType();
		int popType();
		bool hasType();
		void setMangledName(std::string newName);
		std::string getMangledName();
	public:
		std::string	_key;	
		std::string	_strType;
		NvPcomp::location _loc;
		
	private:
		std::vector<int> _type;
		std::string _mangledName;
		
	public:
		symNode(NvPcomp::location loc, \
				std::string key, \
				std::string strType);
		~symNode();
	};
}

#endif /* SYMNODE_H_ */
