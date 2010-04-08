/**********************************************************************/
//! ASTNode function_definition_astNode implementation for NvPcomp
/*!
* \class function_definition_astNode
*
* Description: The function_definition_astNode implementation for Abstract Syntax Tree in NvPcomp
*
* \author CMT, DRJ & BFB
*
*/
/**********************************************************************/
#ifndef FUNCTION_DEFINITION_ASTNODE_H_
#define FUNCTION_DEFINITION_ASTNODE_H_

#include <ast.h>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string>
#include <vector>
#include <position.hh>
#include <location.hh>
#include <tacTree.h>
#include <NvPcomp_logger.h>

class function_definition_astNode:public astNode {
public:
	function_definition_astNode();
	function_definition_astNode(std::string _nodeString, NvPcomp::location _loc, NvPcomp::tacTree *tree);
	~function_definition_astNode();
public:
	virtual void output3AC();
};

#endif /* FUNCTION_DEFINITION_ASTNODE_H_ */
