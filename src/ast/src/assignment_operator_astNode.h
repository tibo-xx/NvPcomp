/**********************************************************************/
//! ASTNode assignment_operator_astNode implementation for NvPcomp
/*!
* \class assignment_operator_astNode
*
* Description: The assignment_operator_astNode implementation for Abstract Syntax Tree in NvPcomp
*
* \author CMT, DRJ & BFB
*
*/
/**********************************************************************/
#ifndef ASSIGNMENT_OPERATOR_ASTNODE_H_
#define ASSIGNMENT_OPERATOR_ASTNODE_H_

#include <astNode.h>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string>
#include <vector>
#include <position.hh>
#include <location.hh>
#include <tacTree.h>
#include <NvPcomp_logger.h>

class assignment_operator_astNode:public astNode {
public:
	assignment_operator_astNode();
	assignment_operator_astNode(std::string _nodeString, NvPcomp::location _loc, NvPcomp::tacTree *tree);
	~assignment_operator_astNode();
public:
	virtual void output3AC();
};

#endif /* ASSIGNMENT_OPERATOR_ASTNODE_H_ */
