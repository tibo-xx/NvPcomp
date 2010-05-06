/*!  Three Address Code Tree
 *  \file tacTree.h
 *  \class tacTree
 *  \brief Class for the three address code tree
 *  \author CMT, DRJ & BFB
 */
#ifndef TACTREE_H_
#define TACTREE_H_

#include <tacNode.h>
#include <vector>
#include <optokentypes.h>
#include <string>

class ast;

namespace NvPcomp {
	class tacTree {

		public:
			tacTree();
			~tacTree();
		public:
			void addNode(tacNode *node);
			void outputASM();
			void displayTree();
			std::vector<tacNode> *getTree();
			std::string getOp(int op);
			ast* asTree;
		private:
			std::vector<tacNode> _tree;
			std::vector<std::string> translateOps;
	};
};

#endif /* TACNODE_H_ */
