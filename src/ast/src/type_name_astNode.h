/**********************************************************************/
//! ASTNode type_name_astNode implementation for NvPcomp
/*!
* \class type_name_astNode
*
* Description: The type_name_astNode implementation for Abstract Syntax Tree in NvPcomp
*
* \author CMT, DRJ & BFB
*
*/
/**********************************************************************/
#ifndef TYPE_NAME_ASTNODE_H_
#define TYPE_NAME_ASTNODE_H_

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

class type_name_astNode:public astNode {
public:
	type_name_astNode();
	type_name_astNode(std::string _nodeString, NvPcomp::location _loc, NvPcomp::tacTree *tree);
	~type_name_astNode();
public:
	virtual void output3AC();
};

#endif /* TYPE_NAME_ASTNODE_H_ */
