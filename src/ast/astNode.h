/**********************************************************************/
//! Abstract Syntax Tree Node
/*!
 * \class astNode
 *
 * Description: Basic node of the Abstract Syntax Tree
 *
 * \author CMT, DRJ & BFB
 *
 */
/**********************************************************************/
#ifndef ASTNODE_H_
#define ASTNODE_H_

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string>
#include <vector>
#include <location.hh>
#include <position.hh>
#include <tacTree.h>
#include <yytokentypes.h>
#include <NvPcomp_logger.h>

class astNode {

	public:
		astNode();
		astNode(std::string nodeString, NvPcomp::location loc, NvPcomp::tacTree *tree);
		~astNode();
	public:
		virtual void printNode(bool printProductions = true, int level = 0);	
		virtual void output3AC() = 0;
		
		void addChild(astNode* child);
		astNode* getChild(int child_index);
		int getNumberOfChildren();
		void setType(std::string nodeType);
		void setString(std::string nodeString);

		std::string getType();
		std::string getString();

		NvPcomp::location getLocation();
		
		NvPcomp::tacTree *gettacTree();

	protected:
		// Node string value
		std::string nodeString;
		// Node string value
		int nodeInt;
		// Node string value
		double nodeDouble;
		// List of appropriate RHS nodes
		std::vector<astNode*> children;	
		// Node token value
		// Remove
		int nodeToken;
		// Location
		NvPcomp::location loc;
		// Node type/lhs, i.e. iteration_statement, identifier, etc.
		std::string nodeType;
		// tacTree
		NvPcomp::tacTree *acTree;
};


#endif /* ASTNODE_H_ */
