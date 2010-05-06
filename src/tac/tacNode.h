/*!  Three Address Code Node
 *  \file tacNode.h
 *  \class tacNode
 *  \brief Class for the three address code node
 *  \author CMT, DRJ & BFB
 */

#ifndef TACNODE_H_
#define TACNODE_H_

#include <string>
#include <location.hh>

namespace NvPcomp {
	class tacNode {
		public:
			tacNode();
			tacNode(std::string label, int op, std::string add1,
					std::string add2, std::string add3, 
					NvPcomp::location loc);
			~tacNode();

		public:
			virtual std::string outputASM();
		//private:
			std::string _label;
			int _op;
			std::string _add1;
			std::string _add2;
			std::string _add3;
			// Location
			NvPcomp::location _loc;
	};
};

#endif /* TACNODE_H_ */
