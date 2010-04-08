/**********************************************************************/
//! tacTree - Three Address Code Tree
/*!
 * \class tacTree
 *
 * Description: tac Tree 
 *
 * \author CMT, DRJ & BFB
 *
 */
/**********************************************************************/
#ifndef TACTREE_H_
#define TACTREE_H_

#include <tacNode.h>

namespace NvPcomp {
	class tacTree {

		public:
			tacTree();
			~tacTree();
		public:
			void addNode(tacNode *node);
			void outputASM();
	};
};

#endif /* TACNODE_H_ */
