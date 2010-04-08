/**********************************************************************/
//! ASTNode parameter_type_list_astNode implementation for NvPcomp
/*!
* \class parameter_type_list_astNode
*
* Description: The parameter_type_list_astNode implementation for Abstract Syntax Tree in NvPcomp
*
* \author CMT, DRJ & BFB
*
*/
/**********************************************************************/
#ifndef PARAMETER_TYPE_LIST_ASTNODE_H_
#define PARAMETER_TYPE_LIST_ASTNODE_H_

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

class parameter_type_list_astNode:public astNode {
public:
	parameter_type_list_astNode();
	parameter_type_list_astNode(std::string _nodeString, NvPcomp::location _loc, NvPcomp::tacTree *tree);
	~parameter_type_list_astNode();
public:
	virtual void output3AC();
};

#endif /* PARAMETER_TYPE_LIST_ASTNODE_H_ */
