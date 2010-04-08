/**********************************************************************/
//! tacNode - Three Address Code base class
/*!
 * \class tacNode
 *
 * Description: Basic node of the Three Address Code Tree
 *
 * \author CMT, DRJ & BFB
 *
 */
/**********************************************************************/
#ifndef TACNODE_H_
#define TACNODE_H_

#include <string>


namespace NvPcomp {
	class tacNode {
		public:
			tacNode();
			~tacNode();
		public:
			virtual std::string outputASM();
	};
};

#endif /* TACNODE_H_ */
