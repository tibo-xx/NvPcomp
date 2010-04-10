/**********************************************************************/
//! ASTNode parameter_declaration_astNode implementation for NvPcomp
/*!
* \class parameter_declaration_astNode
*
* Description: The parameter_declaration_astNode implementation for Abstract Syntax Tree in NvPcomp
*
* \author CMT, DRJ & BFB
*
*/
/**********************************************************************/
#ifndef PARAMETER_DECLARATION_ASTNODE_H_
#define PARAMETER_DECLARATION_ASTNODE_H_

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

class parameter_declaration_astNode:public astNode {
public:
	parameter_declaration_astNode();
	parameter_declaration_astNode(std::string _nodeString, NvPcomp::location _loc, NvPcomp::tacTree *tree);
	~parameter_declaration_astNode();
public:
	virtual void output3AC();
};

#endif /* PARAMETER_DECLARATION_ASTNODE_H_ */
