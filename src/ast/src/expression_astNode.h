/**********************************************************************/
//! ASTNode expression_astNode implementation for NvPcomp
/*!
* \class expression_astNode
*
* Description: The expression_astNode implementation for Abstract Syntax Tree in NvPcomp
*
* \author CMT, DRJ & BFB
*
*/
/**********************************************************************/
#ifndef EXPRESSION_ASTNODE_H_
#define EXPRESSION_ASTNODE_H_

#include <astNode.h>
#include <leaf_astNode.h>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string>
#include <vector>
#include <position.hh>
#include <location.hh>
#include <tacTree.h>
#include <NvPcomp_logger.h>
#include <symNode.h>
#include <symTable.h>

class expression_astNode:public astNode {
public:
	expression_astNode();
	expression_astNode(std::string _nodeString, NvPcomp::location _loc, NvPcomp::tacTree *tree);
	~expression_astNode();
	bool checkType(NvPcomp::symTable *table);
public:
	virtual void output3AC();
protected:
	bool checkTypes(NvPcomp::symNode* lhs, NvPcomp::symNode* rhs);
	bool checkTypes(NvPcomp::symNode* lhs, leaf_astNode* rhs);
};

#endif /* EXPRESSION_ASTNODE_H_ */
