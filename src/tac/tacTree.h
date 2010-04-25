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
#include <vector>
#include <optokentypes.h>

namespace NvPcomp {
	class tacTree {

		public:
			tacTree();
			~tacTree();
		public:
			void addNode(tacNode *node);
			void outputASM();
		private:
			std::vector<tacNode> _tree;
	};
};

#endif /* TACNODE_H_ */
