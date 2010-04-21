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
			tacNode(std::string label, std::string op, std::string add1,
					std::string add2, std::string add3);
			~tacNode();

		public:
			virtual std::string outputASM();
		private:
			std::string _label;
			std::string _op;
			std::string _add1;
			std::string _add2;
			std::string _add3;
	};
};

#endif /* TACNODE_H_ */
